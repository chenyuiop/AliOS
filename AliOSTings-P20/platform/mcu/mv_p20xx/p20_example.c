#include <string.h>
#include <nds32_intrinsic.h>
#include "type.h"
#include "irqn.h"
#include "cache_tcm.h"
#include "timeout.h"
#include "debug.h"
#include "delay.h"
#include "timeout.h"
#include "watchdog.h"
#include "gpio.h"
#include "clk.h"
#include "uarts_interface.h"
#include "spi_flash.h"
#include "spim.h"

#include <aos/aos.h>
#include <k_api.h>
#include <aos/kernel.h>
#include "hal/soc/soc.h"

ktask_t *g_aos_init;
extern int application_start(int argc, char **argv);
char Uart_RxBuf[256];
extern void hal_init(void);
extern void board_init(void);

static uint8_t DmaChannelMap[27] =
{
	255,//PERIPHERAL_ID_SPIS_RX = 0,	//0
	255,//PERIPHERAL_ID_SPIS_TX,		//1
	0,//PERIPHERAL_ID_SD_RX,			//2
	1,//PERIPHERAL_ID_SD_TX,			//3
	255,//PERIPHERAL_ID_SPIM0_RX,		//4
	255,//PERIPHERAL_ID_SPIM0_TX,		//5
	255,//PERIPHERAL_ID_SPIM1_RX,		//6
	255,//PERIPHERAL_ID_SPIM1_TX,		//7
	2,//PERIPHERAL_ID_UART0_RX,		//8
	255,//PERIPHERAL_ID_UART1_RX,		//9
	3,//PERIPHERAL_ID_UART2_RX,		//10
	255,//PERIPHERAL_ID_TIMER3,			//11
	255,//PERIPHERAL_ID_TIMER4,			//12
	255,//PERIPHERAL_ID_I2S_TX,			//13
	255,//PERIPHERAL_ID_I2S_RX,			//14
	255,//PERIPHERAL_ID_SARADC,			//15
	4,//PERIPHERAL_ID_UART0_TX,		//16
	5,//PERIPHERAL_ID_UART1_TX,		//17
	255,//PERIPHERAL_ID_UART2_TX,		//18
	255,//PERIPHERAL_ID_TIMER5,			//19
	255,//PERIPHERAL_ID_TIMER6,			//20
	255,//PERIPHERAL_ID_TIMER7,			//21
	255,//PERIPHERAL_ID_TIMER8,			//22
	255,//PERIPHERAL_ID_LACC_SRC,		//23
	255,//PERIPHERAL_ID_LACC_DST,		//24
	255,//PERIPHERAL_ID_LACC_DSTRD,     //25
	255,//PERIPHERAL_ID_SOFTWARE,		//26
};
char *argvv[]= {"test","yloop","vcall","basic"};//
static void app_entry(void *arg)
{
	kinit_t kinit = {
	    .argc = 0,
	    .argv = argvv,
	    .cli_enable = 1
	};

	hal_init();
	board_init();
	aos_kernel_init(&kinit);
}
void InitZiArea(void)
{
	/* Use compiler builtin and memset */
	#define MEMSET(s, c, n) __builtin_memset ((s), (c), (n))

	extern char _end;
	extern char __bss_start;
	int size;

	/* Clear bss section */
	size = &_end - &__bss_start;
	MEMSET(&__bss_start, 0, size);
	return;
}
__attribute__((weak))
void add_test(void)
{
	//test_certificate();
}
__attribute__((weak))
void  aos_components_init(void)
{

}

int main(void)
{
	WDG_Disable();
	CacheTcmInitFast(PHYMEM_16KBPM0 /*cache*/, PHYMEM_16KBPM1/*tcm r0*/, 0/*tcm r0 offset*/, 4/*tcm r0 size*/, PHYMEM_NONE/*tcm r1*/, 0/*tcm r1 offset*/, 0/*tcm r1 size*/);

	GPIO_RegOneBitClear(GPIO_B_PU, GPIOB30);
	GPIO_RegOneBitSet(GPIO_B_PD, GPIOB30);
	GPIO_RegOneBitClear(GPIO_B_PU, GPIOB31);
	GPIO_RegOneBitSet(GPIO_B_PD, GPIOB31);
	Clock_Config(1, 12000000);
	Clock_PllLock(480000);
	Clock_SysClkSelect(PLL_CLK_MODE);
	Clock_UARTClkSelect(1);

	InitZiArea();
	SpiFlashInit(80000000, MODE_4BIT, 0, 1);


	GPIO_UartTxIoConfig(0, 1);//C2
	GPIO_UartRxIoConfig(0, 1);//C3
	UARTS_Init(0, 115200, 8, 0, 1);
	DMA_ChannelAllocTableSet(DmaChannelMap);//DMA
	UART0_DMA_RxInit(Uart_RxBuf,256,128,NULL);  //´®¿ÚDMA³õÊ¼»¯
	DBG("-------------------------------------------------------\n");
	DBG("AliOS-Things Example:\n");
	DBG("-------------------------------------------------------\n");

	aos_init();
	krhino_task_dyn_create(&g_aos_init, "aos_app", 0, AOS_DEFAULT_APP_PRI, 0, 2048, (task_entry_t)app_entry, 1);
	aos_start();

	DBG("-------------------------end!------------------------------\n");

	while(1);

	return 0;
}

