/**
 **************************************************************************************
 * @file    pwm.h
 * @brief   Pulse Width Modulation (Reuse with General Timer 3&4, Advanced Timer 5&6 ) API
 *
 * @author  Cecilia Wang, Grayson Chen
 * @version V1.0.0
 *
 * $Created: 2016-04-29 13:25:30$
 *
 * @copyright Shanghai Mountain View Silicon Technology Co.,Ltd. All rights reserved.
 **************************************************************************************
 */

/**
 * @addtogroup PWM
 * @{
 * @defgroup pwm pwm.h
 * @{
 */

#ifndef __PWM_H__
#define __PWM_H__

#ifdef __cplusplus
extern "C" {
#endif//__cplusplus

#include "type.h"
#include "timer.h"

#define   PWM_MAX_FREQ_DIV_VALUE   (65535 << 15)   /**< PWM����Ƶ�� */


//PWM ���ͨ��GPIO���ù�ϵ
#define   TIMER3_PWM1_A2_B22_A30_C7  0    /**< TIMER3��PWM���ſɸ�����A2, A30, B22����C7 */

#define   TIMER4_PWM1_A3_B23_A31_C8  1    /**< TIMER4��PWM���Ÿ�����A3, A31, B23����C8 */
    

#define   TIMER5_PWM1_N_A19        2    /**< TIMER5��PWM1�ĸ�����������ſɸ�����A19 */
    
#define   TIMER5_PWM1_P_A16        3    /**< TIMER5��PWM1��������������Ÿ�����A16 */
    
#define   TIMER5_PWM2_N_A20        4    /**< TIMER5��PWM2�ĸ�����������Ÿ�����A20 */
    
#define   TIMER5_PWM2_P_A17        5    /**< TIMER5��PWM2��������������Ÿ�����A17 */

#define   TIMER5_PWM3_N_A21        6    /**< TIMER5��PWM3�ĸ�����������Ÿ�����A21 */

#define   TIMER5_PWM3_P_A18        7    /**< TIMER5��PWM3��������������Ÿ�����A18 */

#define   TIMER5_PWM4_P_A19        8    /**< TIMER5��PWM4��������������Ÿ�����A19 */


#define   TIMER6_PWM1_N_B5         9    /**< TIMER6��PWM1�ĸ�����������Ÿ�����B5 */

#define   TIMER6_PWM1_P_B6         10   /**< TIMER6��PWM1��������������Ÿ�����B6 */

#define   TIMER6_PWM2_N_B3     	   11   /**< TIMER6��PWM2�ĸ�����������Ÿ�����B3 */

#define   TIMER6_PWM2_P_B4     	   12   /**< TIMER6��PWM2��������������Ÿ�����B4 */

#define   TIMER6_PWM3_N_B1         13   /**< TIMER6��PWM3�ĸ�����������Ÿ�����B1 */
    
#define   TIMER6_PWM3_P_B2         14   /**< TIMER6��PWM3��������������Ÿ�����B2 */
 
#define   TIMER6_PWM4_P_B5         15   /**< TIMER6��PWM4��������������Ÿ�����B5 */


#define   TIMER7_PWM1_N_C3         16    /**< TIMER7��PWM1�ĸ�����������Ÿ�����C3 */
    
#define   TIMER7_PWM1_P_C4         17    /**< TIMER7��PWM1��������������Ÿ�����C4 */
    
#define   TIMER7_PWM2_N_C2     	   18    /**< TIMER7��PWM2�ĸ�����������Ÿ�����C2 */
    
#define   TIMER7_PWM2_P_C5     	   19    /**< TIMER7��PWM2��������������Ÿ�����C5 */

#define   TIMER7_PWM3_N_C1         20    /**< TIMER7��PWM3�ĸ�����������Ÿ�����C1 */
    
#define   TIMER7_PWM3_P_C6         21    /**< TIMER7��PWM3��������������Ÿ�����C6 */
 
#define   TIMER7_PWM4_P_C3         22    /**< TIMER7��PWM4��������������Ÿ�����C3 */


#define   TIMER8_PWM1_N_B8         23    /**< TIMER8��PWM1�ĸ�����������Ÿ�����B8 */

#define   TIMER8_PWM1_P_B9         24    /**< TIMER8��PWM1��������������Ÿ�����B9 */

#define   TIMER8_PWM2_N_B10        25    /**< TIMER8��PWM2�ĸ�����������Ÿ�����B10 */

#define   TIMER8_PWM2_P_B11        26    /**< TIMER8��PWM2��������������Ÿ�����B11 */

#define   TIMER8_PWM3_N_B12        27    /**< TIMER8��PWM3�ĸ�����������Ÿ�����B12 */

#define   TIMER8_PWM3_P_B13        28    /**< TIMER8��PWM3��������������Ÿ�����B13 */

#define   TIMER8_PWM4_P_B8         29    /**< TIMER8��PWM4��������������Ÿ�����B8 */

//Break in��GPIO���ù�ϵ
#define   TIMER5_BREAK_A15         0   /**< TIMER5��break in�������� */

#define   TIMER6_BREAK_B0          1   /**< TIMER6��break in��������  */

#define   TIMER7_BREAK_C0		   2   /**< TIMER7��break in��������  */

#define   TIMER8_BREAK_B7          3   /**< TIMER8��break in��������  */


/**
 * @brief   PWMͨ������
 * @note    TIMER1,TIMER2��֧��PWMͨ��    
 * @note    TIMER3,TIMER4ֻ֧��һ��PWMͨ����PWM1
 * @note    TIMER5,TIMER6,TIMER7,TIMER8֧��4��PWMͨ��
 */
typedef enum __PWM_INDEX
{
    PWM1 = 0,    /**< PWMͨ��1  */
    PWM2,        /**< PWMͨ��2  */
    PWM3,        /**< PWMͨ��3  */
    PWM4         /**< PWMͨ��4  */
    
} PWM_INDEX;

/**
 * @brief PWM IO Modeѡ��
 */ 
typedef enum _PWM_IO_MODE
{
    PWM_IO_MODE_NONE = 0xff,    /**< ��ԭΪGPIO  */
    PWM_IO_MODE_OUT  = 1,       /**< ֱ�����  */
    PWM_IO_MODE_PD1  = 2,       /**< PWM����1.7mA���  */
    PWM_IO_MODE_PD2  = 3,       /**< PWM����2.4mA���  */
    PWM_IO_MODE_PD12 = 4        /**< PWM����4.1mA���  */
    
} PWM_IO_MODE;

/**
 * @brief  PWM����ģʽ
 */
typedef enum _PWM_COUNTER_MODE
{
    PWM_COUNTER_MODE_DOWN = 0,        /**< �Ӹߵ��ͼ���  */
    PWM_COUNTER_MODE_UP,              /**< �ӵ͵��߼���  */
    PWM_COUNTER_MODE_CENTER_ALIGNED1, /**< �ȴӵͼӵ��ߣ��ٴӸ߼����ͣ�ֻ�������ʱ�����ж�  */
    PWM_COUNTER_MODE_CENTER_ALIGNED2, /**< �ȴӵͼӵ��ߣ��ٴӸ߼����ͣ�ֻ�������ʱ�����ж�  */
    PWM_COUNTER_MODE_CENTER_ALIGNED3  /**< �ȴӵͼӵ��ߣ��ٴӸ߼����ͣ���������������ʱ�������ж�  */
} PWM_COUNTER_MODE;


/**
 * @brief  PWM������Ͷ���  
 */
typedef enum _PWM_OUTPUT_TYPE
{
    PWM_OUTPUT_SINGLE_FORCE_NOACTIVE 	= 4,      /**< ǿ�������Ч��ƽ  */
    PWM_OUTPUT_SINGLE_FORCE_ACTIVE 		= 5,      /**< ǿ�������Ч��ƽ  */
    
    PWM_OUTPUT_SINGLE_1    				= 6,      /**< ��׼�����DutyΪ��Ч��ƽռ�ձ�  */
    PWM_OUTPUT_SINGLE_2     			= 7,      /**< ��׼�����DutyΪ��Ч��ƽռ�ձ�  */
    
    PWM_OUTPUT_COMBINED_PWM1_OR_PWM2 	= 8,	  /**< PWM1(������ΪͬPWM_OUTPUT_SINGLE_1)��PWM2(������ΪͬPWM_OUTPUT_SINGLE_2)�����㣬������ͨ��PWM1���  */
    PWM_OUTPUT_COMBINED_PWM1_AND_PWM2 	= 9,	  /**< PWM1��PWM2���������  */
    PWM_OUTPUT_COMBINED_PWM3_OR_PWM4 	= 10,	  /**< PWM3(������ΪͬPWM_OUTPUT_SINGLE_1)��PWM4(������ΪͬPWM_OUTPUT_SINGLE_2)�����㣬������ͨ��PWM3���  */
    PWM_OUTPUT_COMBINED_PWM3_AND_PWM4 	= 11,	  /**< PWM3��PWM4���������  */

    PWM_OUTPUT_ASYMMETRIC_1 			= 12,     /**< PWM1~4��ϲ��Գ������ͨ��PWM1��PWM3�����������Ϊ��PWM_OUTPUT_SINGLE_1��ͬ  */
    PWM_OUTPUT_ASYMMETRIC_2 			= 13,     /**< PWM1~4��ϲ��Գ������ͨ��PWM1��PWM3�����������Ϊ��PWM_OUTPUT_SINGLE_2��ͬ  */

    PWM_OUTPUT_ONE_PULSE				= 14	  /**< ���һ����������  */
} PWM_OUTPUT_TYPE;

/**
 * @brief  PWM����ģʽ���жϻ�DMA
 */
typedef enum _PWM_DMA_INTERRUPT_MODE
{
	PWM_REQ_INTERRUPT_MODE = 0,  /**< �ж�ģʽ  */

	PWM_REQ_DMA_MODE             /**< DMAģʽ  */

} PWM_DMA_INTERRUPT_MODE;

/**
 * @brief  PWM���������ѡ��OutPolarity
 */
typedef enum _PWM_OUTPUT_POLARITY_MODE
{
	OUTP_ACTIVE_H_AND_OUTN_ACTIVE_H = 0, /**< ����˺͸���˾�Ϊ��Ч��ƽΪ�ߵ�ƽ  */

	OUTP_ACTIVE_L_AND_OUTN_ACTIVE_H = 1, /**< ����Ϊ�͵�ƽ��Ч���͵�ƽΪ�ߵ�ƽ��Ч  */

	OUTP_ACTIVE_H_AND_OUTN_ACTIVE_L = 2, /**< �����Ϊ�ߵ�ƽ��Ч�������Ϊ�͵�ƽ��Ч  */

	OUTP_ACTIVE_L_AND_OUTN_ACTIVE_L = 3, /**< ����˺͸���˾�Ϊ��Ч��ƽΪ�͵�ƽ  */

} PWM_OUTPUT_POLARITY_MODE;

/**
 * @brief  PWM������˿�ѡ��
 */
typedef enum _PWM_OUTPUT_ENABLE_MODE
{
	OUTP_AND_OUTN_DISABLE = 0,			    /**< N�˺�P�˶��������  */

	OUTP_ENABLE_AND_OUTN_DISABLE = 1,       /**< N�˽��������P��ʹ�����  */

	OUTP_DISABLE_AND_OUTN_ENABLE = 2,       /**< N��ʹ�������P�˽������  */

	OUTP_AND_OUTN_ENABLE = 3,               /**< N�˺�P�˶�ʹ�����  */

} PWM_OUTPUT_ENABLE_MODE;

/**
 * @brief  PWM��idle״̬��ƽѡ��
 */
typedef enum _PWM_IDLE_STATE_SEL
{
	IDLE_P_LOW_AND_N_LOW = 0,          /**< idle״̬ʱ��P������͵�ƽ��N������͵�ƽ  */

	IDLE_P_HIGH_AND_N_LOW,			   /**< idle״̬ʱ��P������ߵ�ƽ��N������͵�ƽ  */

	IDLE_P_LOW_AND_N_HIGH,			   /**< idle״̬ʱ��P������͵�ƽ��N������ߵ�ƽ  */

	IDLE_P_HIGH_AND_N_HIGH,			   /**< idle״̬ʱ��P������ߵ�ƽ��N������ߵ�ƽ  */

} PWM_IDLE_STATE_SEL;

/**
 * @brief  DMA����ռ�ձȵ�Դѡ��
 */
typedef enum _PWM_DMA_SRC_SEL
{
	PWM_PWM1_TRIGGER_DMA_REG = 1,  /**< DMAԴѡ��PWM1 */

	PWM_PWM2_TRIGGER_DMA_REG,  /**< DMAԴѡ��PWM2 */

	PWM_PWM3_TRIGGER_DMA_REG,  /**< DMAԴѡ��PWM3 */

	PWM_PWM4_TRIGGER_DMA_REG   /**< DMAԴѡ��PWM4 */

} PWM_DMA_SRC_SEL;

/**
 * @brief  ��·����ļ���
 */
typedef enum _BREAK_IN_POLAR
{
    BREAK_POLARITY_LOW      = 0, /**< �͵�ƽ��Ч  */
    BREAK_POLARITY_HIGH     = 1  /**< �ߵ�ƽ��Ч  */
} BREAK_IN_POLAR;


/**
 * @brief  �����Ͷ�·�����˲�����ʱ�ӷ�Ƶ��
 */
typedef enum _DEAD_TIME_BREAK_FILTER_CLK_DIV
{
    SYS_CLK_DIV_1       = 0, /**< ��������ʱ�� = ϵͳʱ��  */
    SYS_CLK_DIV_2       = 1, /**< ��������ʱ�� = ϵͳʱ��/2  */
    SYS_CLK_DIV_4       = 2, /**< ��������ʱ�� = ϵͳʱ��/4  */
    SYS_CLK_DIV_8       = 3  /**< ��������ʱ�� = ϵͳʱ��/8  */
} DEAD_TIME_BREAK_FILTER_CLK_DIV;

/**
 * @brief  �˳�break in״̬�����ִ�����ʽ
 */
typedef enum _BREAK_IN_EXIT_TRIGGER_MODE
{
	BREAK_IN_BY_SOFTWARE_WRITE_UPDATE = 0,			/**< ͨ�����update�˳�break in״̬  */
	BREAK_IN_BY_SOFRWARE_UPDATE_OR_HARDWARE_UPDATE, /**< ͨ�����update������һ��Ӳ��updateʱ�˳�break in״̬  */

} BREAK_IN_EXIT_TRIGGER_MODE;

/**
 * @brief  ����break in���״̬
 */
typedef enum _BREAK_IN_STATE_MODE
{
	SWITCH_IDLE_STATE_DIRECTLY = 0,				 /**< ֱ�ӽ���idle״̬  */
	SWITCH_ACTIVE_STATE_BEFORE_SWITCH_IDLE_STATE /**< �Ƚ�����Ч��ƽ״̬��Ȼ��������ʱ��֮�����IDLE״̬  */

} BREAK_IN_STATE_MODE;

/**
 * @brief  PWM���ô������Ͷ���  
 */
typedef enum _PWM_ERROR_CODE
{
    PWM_ERROR_INVALID_TIMER_INDEX = -128,/**< PWM��ʱ�������Ŵ���  */
    PWM_ERROR_INVALID_PWM_TYPE,          /**< PWM������ʹ���  */
    PWM_ERROR_INVALID_PWM_COUNTER_MODE,  /**< PWM����ģʽ����  */
    
    PWM_ERROR_DEAD_CLK_DIV,              /**< PWM����ʱ�ӷ�Ƶ����  */
    PWM_ERROR_BREAK_FILTER_CLK_DIV,      /**< PWM BREAK IN�˲�ʱ�ӷ�Ƶ����  */

    PWM_ERROR_DMA_TIGGER_SRC,            /**< PWM DMAԴѡ�����  */
    PWM_ERROR_OUTPUT_POLARITY_ACTIVE,    /**< PWM ������Դ���  */
    PWM_ERROR_OUTPUT_ENABLE,             /**< PWM ���ʹ�ܴ���  */

    PWM_ERROR_OK = 0                     /**< �޴���  */
} PWM_ERROR_CODE;

/**
 * @brief  PWM��ʼ���ṹ�嶨��
 */
typedef struct __PWM_StructInit
{
	PWM_COUNTER_MODE     		CounterMode;        /**< PWM����ģʽ������ȡֵ��Χ #PWM_COUNTER_MODE  */
    
	PWM_OUTPUT_TYPE      		OutputType;         /**< PWM�������,����ȡֵΪ#PWM_OUTPUT_TYPE  */

	PWM_DMA_INTERRUPT_MODE   	DMAReqEnable;       /**< �Ƿ�ʹ��DMA��Mem����ռ�ձȵ������У�����ȡֵ�� 1 -- ʹ��DMA���� 0 -- ����DMA����  */
    
    uint32_t    		 		FreqDiv;            /**< PWMƵ����ϵͳʱ�ӵķ�Ƶ�ȣ�ȡֵ��Χ[1, PWM_MAX_FREQ_DIV_VALUE]  */

    uint16_t    				Duty[4];            /**< ռ�ձ�,ȡֵ��Χ[0~100]��Ӧռ�ձ�Ϊ[0%~100%],Duty[0]~Duty[3]��ӦPWM1~4��ռ�ձ�  */

    PWM_OUTPUT_POLARITY_MODE    OutPolarity[4];	    /**< PWM���������ѡ��OutPolarity[0]~OutPolarity[3]��ӦPWM1~4�ļ��ԣ�����ֻ���TIMER5~8��Ч  */

    PWM_OUTPUT_ENABLE_MODE      OutEnable[4];	    /**< PWM������˿�ʹ�ܣ�OutEnable[0]~OutEnable[3]��ӦPWM1~4�Ķ˿�ʹ�� */

    PWM_IDLE_STATE_SEL	        OutIdleState[4];    /**< PWM��idle״̬��ƽ��OutIdleState[0]~OutIdleState[3]��ӦPWM1~4�Ķ˿�idle״̬ */
           
}PWM_StructInit;   



/**
 * @brief �����Ͷ�·�����ʼ���ṹ��
 */
typedef struct _BDTInfo
{    
	DEAD_TIME_BREAK_FILTER_CLK_DIV     DTFreqDiv;          /**< ����ʱ�ӷ�Ƶ��  */

    uint16_t   						   DTCycle;            /**< ����ռ�õ�Cycle,��Χ��1~256  */

    uint8_t     					   FilterTime;         /**< ��·�����˲������˲�ʱ�䣬��Χ��1 ~ 128  */
    
    BREAK_IN_POLAR     				   BreakPolar;         /**< Break in��������  */

    BREAK_IN_EXIT_TRIGGER_MODE		   AutoExitIdleEnable; /**< break in״̬�˳���ʽ  */

    BREAK_IN_STATE_MODE			       BreakOffStateSel;   /**< ����break in���״̬ѡ��  */
    
} BDTInfo;
 

/**
 * @brief PWM IOCTRL ����
 */
typedef enum _PWM_IOCTRL_CMD
{
	//update and Select cmd
	OUTPUT_SOFTWARE_UPDATE 		= 0x1,	    /**< TIMERx���update�Ĵ���  */

	OUTPUT_TYPE_UPDATE 			= 0x2,		/**< #PWM_OUTPUT_TYPE  */

	OUTPUT_ENABLE_UPDATE	 	= 0x4, 		/**< ͬPWM_StructInit�е�OutEnable  */

	OUTPUT_POLARITY_UPDATE 		= 0x8,		/**< ���Ը���  */

	OUTPUT_FREQUENCY_UPDATE 	= 0x10,	    /**< Ƶ�ʸ���  */

	OUTPUT_DUTY_UPDATE 			= 0x20,		/**< ռ�ձȸ���  */

    DMA_SRC_PWM_SEL 			= 0x40,		/**< DMA����Դѡ��  */

	BREAKIN_FLAG_CLR 			= 0x80,		/**< break in��־���  */

	SOFT_BREAKIN_SET 			= 0x100, 	/**< software break ���ã�0��1  */

    //���Ͽ�������֧�ֶ�������ͬʱ���룬����cmd = OUTPUT_FREQUENCY_UPDATE | OUTPUT_DUTY_UPDATE

    //���¿������֧������ͬʱ����
	//Get cmd
	OUTPUT_STATE_GET = 0x1000,    			/**< PWM���״̬��ȡ��1 -- ���У�0 -- IDLE  */

	BREAKIN_FLAG_GET = 0x2000,	 			/**< Break in�ж�ʹ�ܱ�־��ȡ��1 -- ʹ��break in�� 0 -- ����break in�� -128 -- ����Ķ�ʱ������  */

	BREAKIN_STATUS_GET = 0x4000,		    /**< ��ȡbreak in��״̬  */


} PWM_IOCTRL_CMD;


/**
 * @brief PWM IOCTRL ����
 */
typedef struct _PWM_IOCTRL_ARG
{
	PWM_OUTPUT_TYPE     	   OutputType;         /**< PWM�������  */

	PWM_OUTPUT_ENABLE_MODE     OutEnable;          /**< PWM������˿�ʹ��  */

	PWM_OUTPUT_POLARITY_MODE   OutPolarity;		   /**< PWM���������ѡ��  */

	uint32_t    			   FreqDiv;            /**< PWMƵ����ϵͳʱ�ӵķ�Ƶ�ȣ�ȡֵ��Χ[1, PWM_MAX_FREQ_DIV_VALUE]  */

	uint16_t				   Duty;			   /**< ռ�ձ�  */

	PWM_DMA_SRC_SEL			   DMATiggerSel;	   /**< DMAԴѡ��  */

	bool					   SoftBreakSet;       /**< ���break in״̬����  */

} PWM_IOCTRL_ARG;

/**
 * @brief     ����һ·PWM��GPIO����
 *
 * @param[in] PWMChSel  PWMͨ��ѡ�񣬲����ɼ�#PWM ͨ��GPIO���ù�ϵ�궨��
 * @param[in] PwmIoSel  ���磺��ѡ��TIMER3_PWM1_A2_B22_A30_C7����PwmIoSel = 0XFF����PWM������A2��
 *                          ��PwmIoSel = 1��������B22��, PwmIoSel = 2,������ A30�� PwmIoSel = 3��������C7��
 * @param[in] PWMMode   PWM���ù�ϵ����ϸ�ο� #PWM_IO_MODE
 *
 * @return    ��
 */
void PWM_GpioConfig(uint8_t PWMChSel, uint8_t PwmIoSel, PWM_IO_MODE PWMMode);


/**
 * @brief     ����һ·PWM break in��GPIO����
 *
 * @param[in] BreakSel  break in������ѡ��
 * @param[in] PWMMode   1 -- ����Ϊbreak in�� 0xFF -- ��ԭΪgpio
 *
 * @return    ��
 */
void PWM_BreakGpioConfig(uint8_t BreakSel, uint8_t PWMMode);


/**
 * @brief     ѡ��һ����ʱ���µ�PWMͨ�������������
 *
 * @param[in] TimerIdx  ��ʱ�������ţ���� # TIMER_INDEX
 * @param[in] PWMIdx    PWM�����ţ���� # PWMIdx
 * @param[in] PWMParam  PWM��ʼ����������ϸ�ο� PWMInfo
 *
 * @return    ����ţ�0 - ��ȷ������Ϊ������ϸ�ο�PWM_ERROR_CODE
 */
PWM_ERROR_CODE PWM_Config(TIMER_INDEX TimerIdx, PWM_INDEX PWMIdx, PWM_StructInit *PWMParam);

/**
 * @brief     ������ʱ��TimerIdx��һ��ͨ��PWM
 *
 * @param[in] TimerIdx  ��ʱ�������ţ���� # TIMER_INDEX
 *
 * @return    ����ţ�0 - ��ȷ������Ϊ������ϸ�ο�PWM_ERROR_CODE
 */
PWM_ERROR_CODE PWM_Enable(TIMER_INDEX TimerIdx);

/**
 * @brief     �رն�ʱ��TimerIdx��һ��ͨ��PWM
 *
 * @param[in] TimerIdx  ��ʱ�������ţ���� # TIMER_INDEX
 *
 * @return    ����ţ�0 - ��ȷ������Ϊ������ϸ�ο�PWM_ERROR_CODE
 */
PWM_ERROR_CODE PWM_Disable(TIMER_INDEX TimerIdx);

/**
 * @brief     ��ͣ��ʱ��TimerIdx��һ��ͨ��PWM
 *
 * @param[in] TimerIdx  ��ʱ�������ţ���� # TIMER_INDEX
 * 			  IsPause   1: PWM��ͣ����������������ƽ  0��PWM�������
 *
 * @return    ����ţ�0 - ��ȷ������Ϊ������ϸ�ο�PWM_ERROR_CODE
 */
PWM_ERROR_CODE PWM_Pause(TIMER_INDEX TimerIdx, bool IsPause);

/**
 * @brief     TimerIdx�µ�һ·PWM���в���
 *
 * @param[in] TimerIdx  ��ʱ�������ţ���� # TIMER_INDEX
 * @param[in] PWMIdx    PWM�����ţ���� # PWMIdx
 * @param[in] IOCtrl    IOCtrl����
 *
 * @return    ����ţ�0 - ��ȷ������Ϊ������ϸ�ο�PWM_ERROR_CODE
 */
PWM_ERROR_CODE PWM_IOCTRl(TIMER_INDEX TimerIdx, PWM_INDEX PWMIdx, PWM_IOCTRL_CMD Cmd, PWM_IOCTRL_ARG *Arg);

/**
 * @brief      Deadʱ������
 *
 * @param[in]  TimerIdx  ��ʱ�������ţ�ֻ��TIMER5��TIMER6֧��Break in����
 * @param[in]  BDTParam  DeadTime��ز�������
 *
 * @return     ����ţ�0 - ��ȷ������Ϊ������ϸ�ο�PWM_ERROR_CODE
 */
PWM_ERROR_CODE  PWM_DeadTimeConfig(TIMER_INDEX TimerIdx, BDTInfo *BDTParam);

/**
 * @brief      Dead����ʹ��
 *
 * @param[in]  TimerIdx  ��ʱ�������ţ�ֻ��TIMER5��TIMER6֧��Break in����
 *
 * @return     ����ţ�0 - ��ȷ������Ϊ������ϸ�ο�PWM_ERROR_CODE
 */
PWM_ERROR_CODE  PWM_DeadTimeEnable(TIMER_INDEX TimerIdx);

/**
 * @brief      Dead���ܽ���
 *
 * @param[in]  TimerIdx  ��ʱ�������ţ�ֻ��TIMER5��TIMER6֧��Break in����
 *
 * @return     ����ţ�0 - ��ȷ������Ϊ������ϸ�ο�PWM_ERROR_CODE
 */
PWM_ERROR_CODE  PWM_DeadTimeDisable(TIMER_INDEX TimerIdx);


/**
 * @brief      Break in��������
 *
 * @param[in]  TimerIdx  ��ʱ�������ţ�ֻ��TIMER5��TIMER6֧��Break in����
 * @param[in]  BDTParam  break in��ز�������
 *
 * @return     ����ţ�0 - ��ȷ������Ϊ������ϸ�ο�PWM_ERROR_CODE
 */
PWM_ERROR_CODE  PWM_BreakInConfig(TIMER_INDEX TimerIdx, BDTInfo *BDTParam);

/**
 * @brief      break in����ʹ��
 *
 * @param[in]  TimerIdx  ��ʱ�������ţ�ֻ��TIMER5��TIMER6֧��Break in����
 *
 * @return     ����ţ�0 - ��ȷ������Ϊ������ϸ�ο�PWM_ERROR_CODE
 */
PWM_ERROR_CODE  PWM_BreakInEnable(TIMER_INDEX TimerIdx);

/**
 * @brief      break in���ܽ���
 *
 * @param[in]  TimerIdx  ��ʱ�������ţ�ֻ��TIMER5��TIMER6֧��Break in����
 *
 * @return     ����ţ�0 - ��ȷ������Ϊ������ϸ�ο�PWM_ERROR_CODE
 */
PWM_ERROR_CODE  PWM_BreakInDisable(TIMER_INDEX TimerIdx);

/**
 * @brief      ռ�ձȶ�̬����,���ڸ߾���ռ�ձ�����
 *
 * @param[in]  TimerIdx ��ʱ��������
 * @param[in]  PWMIdx   PWMͨ����������
 * @param[in]  Duty     0~0xFFFF��Ӧ0~100%
 *
 * @return     ����ţ�0 - ��ȷ������Ϊ������ϸ�ο�PWM_ERROR_CODE
 */
int32_t PWM_DutyConfigIQ16(TIMER_INDEX TimerIdx, PWM_INDEX PWMIdx, uint16_t Duty);


/**
 * @brief      ����ʱ��TimerIdxռ�ձȲ�������ת�������ٷֱ�����ת��ʮ����������
 *
 * @param[in]  TimerIdx ��ʱ��������
 * @param[in]  BufIn    ռ�ձ����������ַ����λ��
 * @param[out] BufOut   ռ�ձ����������ַ��ʮ������
 * @param[in]  Len      BufIn�ĳ���,��λ���ֽ�
 *
 * @return     BufOut   ����
 */
uint32_t PWM_DutyPercentoHex(TIMER_INDEX TimerIdx, uint8_t *BufIn, uint16_t *BufOut, uint16_t Len);



#ifdef  __cplusplus
}
#endif//__cplusplus

#endif//__PWM_H__

/**
 * @}
 * @}
 */

