/**
 **************************************************************************************
 * @file    pwc.h
 * @brief   Pulse Width Capture (Reuse with General Timer 3&4, Advanced Timer 5&6 ) API
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
 * @addtogroup PWC
 * @{
 * @defgroup pwc pwc.h
 * @{
 */

#ifndef __PWC_H__
#define __PWC_H__

#ifdef __cplusplus
extern "C" {
#endif//__cplusplus

#include "type.h"
#include "timer.h"

#define   PWC_MAX_TIMESCALE   0xffff       /**< PWC ���ֵ���� */
    
//PWC ���ͨ��GPIO���ù�ϵ
#define   TIMER3_PWC1_A2_B22_A30_C7    0   /**< TIMER3��PWC1���Ÿ�����GPIOA2,A30,B22����C7 */

#define   TIMER4_PWC1_A3_B23_A31_C8    1   /**< TIMER4��PWC1���Ÿ�����GPIOA3,A31��B23����C8 */
    
    
#define   TIMER5_PWC1_A16              2   /**< TIMER5��PWC1���Ÿ�����GPIOA16 */
    
#define   TIMER5_PWC2_A17              3   /**< TIMER5��PWC2���Ÿ�����GPIOA17 */
    
#define   TIMER5_PWC3_A18              4   /**< TIMER5��PWC3���Ÿ�����GPIOA18 */
    
#define   TIMER5_PWC4_A19              5   /**< TIMER5��PWC4���Ÿ�����GPIOA19 */
    
    
#define   TIMER6_PWC1_B6               6   /**< TIMER6��PWC1���Ÿ�����GPIOB6 */
    
#define   TIMER6_PWC2_B4               7   /**< TIMER6��PWC2���Ÿ�����GPIOB4 */
    
#define   TIMER6_PWC3_B2               8   /**< TIMER6��PWC3���Ÿ�����GPIOB2 */

#define   TIMER6_PWC4_B5               9   /**< TIMER6��PWC4���Ÿ�����GPIOB5 */


#define   TIMER7_PWC1_C4               10   /**< TIMER7��PWC1���Ÿ�����GPIOC4 */

#define   TIMER7_PWC2_C5               11   /**< TIMER7��PWC2���Ÿ�����GPIOC5 */

#define   TIMER7_PWC3_C6               12   /**< TIMER7��PWC3���Ÿ�����GPIOC6 */
    
#define   TIMER7_PWC4_C3               13   /**< TIMER7��PWC4���Ÿ�����GPIOC3 */


#define   TIMER8_PWC1_B9               14   /**< TIMER8��PWC1���Ÿ�����GPIOB9 */

#define   TIMER8_PWC2_B11              15   /**< TIMER8��PWC2���Ÿ�����GPIOB11 */

#define   TIMER8_PWC3_B13              16   /**< TIMER8��PWC3���Ÿ�����GPIOB13 */

#define   TIMER8_PWC4_B8               17   /**< TIMER8��PWC4���Ÿ�����GPIOB8 */


/**
 * @brief PWC IO Mode ѡ��
 */ 
typedef enum _PWC_IO_MODE
{
    PWC_IO_MODE_NONE = 0xFF,  /**< ��ԭΪGPIO */
    PWC_IO_MODE_IN   = 1     /**< ֱ����� */
} PWC_IO_MODE;
    

/**
 * @brief   PWCͨ������
 * @note    TIMER1,TIMER2��֧��PWCͨ��
 *          TIMER3,TIMER4ֻ֧��һ��PWCͨ����PWC1
 *          TIMER5,TIMER6֧��4��PWCͨ��
 */
typedef enum __PWC_INDEX
{
    PWC1 = 0, /**< PWCͨ��1 */
    PWC2,/**< PWCͨ��2 */
    PWC3,/**< PWCͨ��3 */
    PWC4,/**< PWCͨ��4 */
    
} PWC_INDEX;

/**
 * @brief  PWC����ģʽ
 */
typedef enum _PWC_CAPTURE_MODE
{
	PWC_CAPTURE_CONTINUES = 0,	/**< �������� */

	PWC_CAPTURE_ONCE = 1		/**< ֻ����һ�� */

} PWC_CAPTURE_MODE;

/**
 * @brief  PWC1����Դѡ��
 */
typedef enum _PWC1_INPUT_SOURCE_SEL
{
	PWC1_INPUT_PWC1_ONLY = 0,		/**< PWC1ֱ������ */
	PWC1_INPUT_PWC1_XOR_PWC2PWC3,   /**< PWC1��PWC2��PWC3�������� */

} PWC1_INPUT_SOURCE_SEL;

/**
 * @brief  PWC����ģʽ���жϻ�DMA
 */
typedef enum _PWC_DMA_INTERRUPT_MODE
{
	PWC_REQ_INTERRUPT_MODE = 0, /**< �ж�ģʽ */

	PWC_REQ_DMA_MODE            /**< DMAģʽ */

} PWC_DMA_INTERRUPT_MODE;

/**
 * @brief  PWC���뼫��
 */
typedef enum _PWC_POLARITY
{
    PWC_POLARITY_BOTH     = 1,  /**< ˫���ز��� */
    PWC_POLARITY_RAISING  = 2,  /**< �����ز��� */
    PWC_POLARITY_FALLING  = 3   /**< �½��ز��� */

} PWC_POLARITY;

/**
 * @brief  PWC����ͨ��ѡ��
 */
typedef enum _PWC_INPUT_CHANNEL_SEL
{
	PWC_INPUT_CHANNEL_PWC1 = 0,				/**< ֻʹ��PWC1ͨ���ɼ� */
	PWC_INPUT_CHANNEL_PWC1_PWC2,			/**< ʹ��PWC1��PWC2ͨ���ɼ� */
	PWC_INPUT_CHANNEL_PWC1_PWC3,			/**< ʹ��PWC1��PWC3ͨ���ɼ� */
	PWC_INPUT_CHANNEL_PWC1_PWC4,			/**< ʹ��PWC1��PWC4ͨ���ɼ� */
	PWC_INPUT_CHANNEL_PWC1_PWC2_PWC3,		/**< ʹ��PWC1��PWC2��PWC3ͨ���ɼ� */
	PWC_INPUT_CHANNLE_PWC1_PWC2_PWC4,		/**< ʹ��PWC1��PWC2��PWC4ͨ���ɼ� */
	PWC_INPUT_CHANNEL_PWC1_PWC3_PWC4,		/**< ʹ��PWC1��PWC3��PWC4ͨ���ɼ� */
	PWC_INPUT_CHANNEL_PWC1_PWC2_PWC3_PWC4,	/**< ʹ��PWC1��PWC2��PWC3��PWC4ͨ���ɼ� */

} PWC_INTPUT_CHANNEL_SEL;


/**
 * @brief  PWC�����˲�������ʱ�ӷ�Ƶ��
 */
typedef enum _PWC_FILTER_CLK_DIV
{   
    FILTER_CLK_DIV1 = 0,/**< ����Ƶ,����ϵͳʱ�ӣ���Fsys */
    FILTER_CLK_DIV2,    /**< ϵͳʱ�ӵ�2��Ƶ���� Fsys / 2 */
    FILTER_CLK_DIV3,    /**< ϵͳʱ�ӵ�4��Ƶ���� Fsys / 4 */
    FILTER_CLK_DIV4,    /**< ϵͳʱ�ӵ�8��Ƶ���� Fsys / 8 */
    
} PWC_FILTER_CLK_DIV;

/**
 * @brief  DMA����ռ�ձȵ�Դѡ��
 */
typedef enum _PWC_DMA_SRC_SEL
{
	PWC_PWC1_TRIGGER_DMA_REG = 1,  /**< PWC1����DMA */

	PWC_PWC2_TRIGGER_DMA_REG,      /**< PWC2����DMA */

	PWC_PWC3_TRIGGER_DMA_REG,      /**< PWC3����DMA */

	PWC_PWC4_TRIGGER_DMA_REG       /**< PWC4����DMA */

} PWC_DMA_SRC_SEL;

/**
 * @brief  PWC����Ŷ���
 */
typedef enum _PWC_ERROR_CODE
{
    PWC_ERROR_INVALID_PWC_INDEX = -128,       /**< PWC��ʱ�������Ŵ��� */
    PWC_ERROR_INVALID_PWC_POLARITY,           /**< PWC���뼫�Դ��� */
    PWC_ERROR_INVALID_FILTER_CLK_DIV,         /**< PWC�˲���ʱ�ӷ�Ƶ�ȴ��� */

    PWC_ERROR_INVALID_PWCx_INDEX,             /**< PWCͨ�������Ŵ��� */
    PWC_ERROR_INVALID_CHANNEL_INDEX,          /**< PWC����ͨ��ѡ����� */

    PWC_ERROR_OK = 0                          /**< �޴��� */
} PWC_ERROR_CODE;


/** 
 * @brief  PWC��ʼ���ṹ�嶨��
 */  
typedef struct __PWC_StructInit
{
	PWC_CAPTURE_MODE  		SingleGet;          /**< ��������� 1 -- ֻ��ȡ1�Σ� 0 -- ������ȡ */

	PWC_DMA_INTERRUPT_MODE  DMAReqEnable;       /**< �Ƿ�ʹ��DMA����ȡ�����ݰ���MEM�У�����ȡֵ�� 1 -- ʹ��DMA���� 0 -- ����DMA���� */
    
    uint16_t 				TimeScale;          /**< PWC���������̣�ȡֵ��Χ[1,65535], �����Բ����ķ�Χ��1/Fsys * TimeScale  ~  65535/Fsys * TimeScale�� */
    
    uint8_t  				FilterTime;         /**< �˲�ʱ�䣬��Χ��1/Fpwc ~ 128/Fpwc */
    

	uint8_t  				InputPrescale[4];	/**< ֻҪ�и߼���ʱ�����д˹��ܣ�ȡֵ��Χ[0, 7]��Ĭ��Ϊ0�������źŲ���Ƶ��InputPrescale[0]~InputPrescale[3]��ӦPWC1~PWC4�������ź� */


    PWC_POLARITY  			Polarity[4];        /**< �����ԣ�����ȡֵ��Χ����Ե����Ե�� �����ص������أ��½��ص��½��أ���ϸ��� #PWC_POLARITY��Polarity[0]~Polarity[3]��ӦPWC1~PWC4 */


    PWC1_INPUT_SOURCE_SEL 	PWC1Source;	       /**< ֻ�и߼���ʱ�����д˹��ܣ�PWC1����Դѡ�� */
           
}PWC_StructInit;  

/**
 * @brief PWC IOCTROL ����
 */
typedef enum _PWC_IOCTRL_CMD
{
	PWC_DATA_GET = 0,                    /**< PWC���ݻ�ȡ */
	PWC_DONE_STATUS_GET,                 /**< PWC�������״̬��ȡ */
	PWC_OVER_CAPTURE_STATUS_GET,         /**< PWC�ظ�����״̬��ȡ */
	PWC_ERR_STATUS_GET,                  /**< PWC����״̬��ȡ */

	PWC_OVER_CAPTURE_STATUS_CLR,         /**< PWC�ظ�����״̬��� */
	PWC_ERR_STATUS_CLR,                  /**< PWC����״̬��� */

    PWC_DMA_SRC_SET,                     /**< PWC DMA����Դ���� */

    PWC_POLARITY_UPDATE,                 /**< PWC���뼫������ */


} PWC_IOCTRL_CMD;

/**
 * @brief PWC IOCTROL ����
 */
typedef struct _PWC_IOCTRL_ARG
{
	PWC_DMA_SRC_SEL PWCDmaSel;      /**< DMA����Դ */

	PWC_POLARITY    PWCPolarity;    /**< PWC���뼫�� */

} PWC_IOCTRL_ARG;


/**
 * @brief      ��GPIO����ΪPWC���Ż�ԭΪGPIO����.
 *
 * @param[in]  PWCChSel  PWCͨ��ѡ����� #PWC ���ͨ��GPIO���ù�ϵ �ĺ궨��
 * @param[in]  PWCIoSel  ���磺��PWCChSel = TIMER3_PWC1_A2_B22_A30_C7��
 * 							  0��������A2��
 * 							  1��������B22��
 * 							  2��������A30��
 * 							  3��������C7
 * @param[in]  PWCMode   1 - ����ΪPWC���ţ� 0 - ��ԭΪ��ͨGPIO���ţ����PWC_IO_MODE
 *
 * @return     ��
 */
void PWC_GpioConfig(uint8_t PWCChSel, uint8_t PWCIoSel, PWC_IO_MODE PWCMode);

/**
 * @brief     ����һ����ʱ���µ�PWC����ͨ��
 *
 * @param[in] TimerIdx  ��ʱ�������ţ���� # TIMER_INDEX
 * @param[in] PWCParam  PWC��ʼ����������ϸ�ο� PWCInfo
 * @param[in] PWCChannelSel PWC�ɼ�ͨ��ѡ�����#PWC_INTPUT_CHANNEL_SEL
 *
 * @return    ����ţ�0 - ��ȷ������Ϊ������ϸ�ο�PWC_ERROR_CODE
 */
PWC_ERROR_CODE PWC_Config(TIMER_INDEX TimerIdx, PWC_StructInit *PWCParam, PWC_INTPUT_CHANNEL_SEL PWCChannelSel);

/**
 * @brief     ʹ��TimerIdx�µ�PWCͨ�����вɼ�
 *
 * @param[in] TimerIdx  ��ʱ�������ţ���� # TIMER_INDEX
 *
 * @return    ����ţ�0 - ��ȷ������Ϊ������ϸ�ο�PWC_ERROR_CODE
 */
PWC_ERROR_CODE PWC_Enable(TIMER_INDEX TimerIdx);

/**
 * @brief     �ر�TimerIdx�µ�PWCͨ�����вɼ�
 *
 * @param[in] TimerIdx  ��ʱ�������ţ���� # TIMER_INDEX
 *
 * @return    ����ţ�0 - ��ȷ������Ϊ������ϸ�ο�PWC_ERROR_CODE
 */
PWC_ERROR_CODE PWC_Disable(TIMER_INDEX TimerIdx);


/**
 * @brief     TimerIdx�µ�һ·PWC���в���
 *
 * @param[in] TimerIdx  ��ʱ�������ţ���� # TIMER_INDEX
 * @param[in] PWCIdx    PWC�����ţ���� # PWCIdx
 *
 * @return    >=0: ��ȷ��ֵ�� < 0: ���󷵻�ֵ
 */
PWC_ERROR_CODE PWC_IOCTRL(TIMER_INDEX TimerIdx, PWC_INDEX PWCIdx, PWC_IOCTRL_CMD Cmd, PWC_IOCTRL_ARG *Arg);



#ifdef  __cplusplus
}
#endif//__cplusplus

#endif//__PWC_H__

/**
 * @}
 * @}
 */

