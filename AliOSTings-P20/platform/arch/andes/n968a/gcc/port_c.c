/*
 * Copyright (C) 2015-2017 Alibaba Group Holding Limited
 */

#include <k_api.h>
/* Processor constants. */
#include "os_cpu.h"

#include "irqn.h"
#include <nds32_intrinsic.h>
#include "timer.h"

#define portNO_CRITICAL_NESTING		( ( unsigned long ) 0 )
volatile unsigned long ulCriticalNesting = 0UL;
volatile  uint32_t psw_0 = 0;
extern volatile uint32_t gSysTick;
/*-----------------------------------------------------------*/
extern void CtxSave(void);
extern void CtxRestore(void);
extern INT32U _SDA_BASE_ __attribute__ ((weak));


/*-----------------------------------------------------------*/


inline void vPortYield(void)
{
       /* trigger swi*/
       __nds32__mtsr(0x10000,NDS32_SR_INT_PEND);
       __nds32__isb();
}


void SwitchContext(void)
{
	g_active_task[0] = g_preferred_ready_task[0];
}

/*-----------------------------------------------------------*/

/* Kernel interrupt mask, it imply the kernel priority comapre with interrupt */
inline unsigned long ulPortSetInterruptMask( void )
{
	/* By default, the kerenl has the highest priority */
	/* It's mean that we don't support kernel preemptive */

#ifdef CONFIG_HW_PRIO_SUPPORT
	/* @Apply HW priority */
	/* GIE on/off control by kernel ISR*/
	/* Mask(disable) all interrupt */
	return hal_intc_irq_mask(-1);
#else
	/* Apply SW priority */
	/* GIE on/off control by user ISR*/
	/* Disable GIE */
	unsigned long psw = __nds32__mfsr(NDS32_SR_PSW);
	__nds32__mtsr_isb((psw & (~(7<<16)))|( 0 /*configMAX_SYSCALL_INTERRUPT_PRIORITY*/ <<16), NDS32_SR_PSW); //
	//GIE_DISABLE();
	return psw;
#endif
}

/*-----------------------------------------------------------*/

inline void vPortClearInterruptMask( unsigned long msk )
{
/* see ulPortSetInterruptMask comment */
#ifdef CONFIG_HW_PRIO_SUPPORT
	/* restore interrupt mask */
	hal_timer_irq_unmask(msk)
#else
	/* restore GIE */
	//GIE_RESTORE(msk);
	__nds32__mtsr_isb(msk, NDS32_SR_PSW);
#endif
}



/*-----------------------------------------------------------*/
void *cpu_task_stack_init(cpu_stack_t *base, size_t size, void *arg, task_entry_t entry)
{
	int i;
	cpu_stack_t *pxTopOfStack;
	cpu_stack_t *old_stk;

     uint32_t temp = (uint32_t)((size_t)base + size* sizeof(cpu_stack_t));

     /*stack need 8 bytes align*/
     temp &= 0xfffffff8;
     pxTopOfStack = (cpu_stack_t *)temp;


	//pxOriginalTOS = pxTopOfStack;

	/* Setup the initial stack of the task.  The stack is set exactly as
	expected by the portRESTORE_CONTEXT() macro. */

	/* First on the stack is the return address - which in this case is the
	start of the task.  The offset is added to make the return address appear
	as it would within an IRQ ISR. */
        *--pxTopOfStack = (INT32U)0x01010101L * 1;			/* R1 */
        *--pxTopOfStack = (INT32U)arg;                  	/* R0 : argument */
        *--pxTopOfStack = (INT32U)krhino_task_deathbed;             	/* $30:LP */
        *--pxTopOfStack = (INT32U)&_SDA_BASE_;                   	/* $29:GP For relax support */
        *--pxTopOfStack = (INT32U)0x01010101UL * 28;			/* $28:FP */
	#ifdef __NDS32_REDUCE_REGS__
        *--pxTopOfStack = (INT32U)0x01010101UL * 15;
	i = 10;
	#else
	i = 27;
	#endif
        for (; i >= 2; i--)
		*--pxTopOfStack = (INT32U)0x01010101UL * i;
	#if (defined(__NDS32_ISA_V2__) && defined(__NDS32_DX_REGS__)) || (!defined(__NDS32_ISA_V2__) && (defined(__NDS32_DIV__)||defined(__NDS32_MAC__)))
	for (i = 35; i >= 32; i--)                      	  	/* d0.hi, d0.lo, d1.hi, d1.lo */
		*--pxTopOfStack = (INT32U)0x01010101UL * i;
	#endif

#ifdef __NDS32_EXT_IFC__
# ifndef CONFIG_NO_NDS32_EXT_IFC
		*--pxTopOfStack = (INT32U)0x01010101UL * 40;		/* $IFC_LP */
# endif
#endif


	/* IPSW, enable GIE, clear IFCON */
        *--pxTopOfStack = (uint32_t)((GET_PSW() | (1UL << PSW_offGIE)) & (~(1UL << PSW_offIFCON)));
	/* IPC */
        *--pxTopOfStack = (uint32_t)entry;
	/* PSW */
        *--pxTopOfStack = (uint32_t)(GET_PSW() | (1UL << PSW_offINTL) );

       old_stk = pxTopOfStack;                                	  	/* Save curent unaligned sp */
        *--pxTopOfStack = (uint32_t)((INT32U)old_stk);    	/* sp(R31) */
        if ((INT32U)pxTopOfStack & 0x7)
                *--pxTopOfStack = (uint32_t)((INT32U)old_stk);    /* sp(R31) */


	/* push fpu */
#if defined(__NDS32_EXT_FPU_DP__) || defined(__NDS32_EXT_FPU_SP__)
	int start, end;
#if defined(__NDS32_EXT_FPU_CONFIG_0__)
        end = 36; start = 35 + 2 * 4;
#elif defined(__NDS32_EXT_FPU_CONFIG_1__)
        end = 36; start = 35 + 2 * 8;
#elif defined(__NDS32_EXT_FPU_CONFIG_2__)
        end = 36; start = 35 + 2 * 16;
#elif defined(__NDS32_EXT_FPU_CONFIG_3__)
        end = 36; start = 35 + 2 * 32;
#else
	end = 1; start = 0;
#endif
	for (i = start; i >= end; i--)
		*--pxTopOfStack = (INT32U)0x01010101UL * i;
#endif


	return pxTopOfStack;
}





void cpu_first_task_start( void )  //xPortStartScheduler
{
	extern void SysTickInit(void);

	NVIC_EnableIRQ(SWI_IRQn);
	NVIC_SetPriority(SWI_IRQn,3);
	NVIC_EnableIRQ(TMR2_IRQn);
	NVIC_SetPriority(TMR2_IRQn,2);

	Timer_Config(TIMER2,1000000/RHINO_CONFIG_TICKS_PER_SECOND,0);
	Timer_Start(TIMER2);	
	__builtin_nds32_setgie_en();//GIE_ENABLE();
	/* Start the first task. */
	CtxRestore();//vPortISRStartFirstTask();
}


size_t cpu_intrpt_save(void)
{

       /*
        *       in order to avoid race condition
        *       1.store psw into stack
        *       2.disable gie
        *       3.store psw into global if ulCriticalNesting==0
        *       4.ulCriticalNesting++
        */
       volatile unsigned int psw = __nds32__mfsr(NDS32_SR_PSW);
       GIE_DISABLE();
       if (ulCriticalNesting == portNO_CRITICAL_NESTING )
               psw_0 = psw;
       ulCriticalNesting++;
    return 0;
}

void cpu_intrpt_restore(size_t cpsr)
{
       --ulCriticalNesting;
       if ( ulCriticalNesting == portNO_CRITICAL_NESTING )
               GIE_RESTORE(psw_0);
}


void   cpu_intrpt_switch(void)
{
    uint32_t msk;

	msk =  ulPortSetInterruptMask();
	/* Increment the tick count - this may wake a task. */
	//if ( xTaskIncrementTick() == pdTRUE )
	{
		/* Raise a SWI pending bit */
		vPortYield();
	}
	vPortClearInterruptMask(msk);


}
void   cpu_task_switch(void)
{
    vPortYield();
}

/*-----------------------------------------------------------*/
__attribute__((section(".driver.isr")))
void Timer2Interrupt(void)
{
	Timer_InterruptFlagClear(TIMER2,UPDATE_INTERRUPT_SRC);
	gSysTick++;
    krhino_intrpt_enter();
    krhino_tick_proc();
    krhino_intrpt_exit();
}


