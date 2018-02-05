/**
 **************************************************************************************
 * @file    timer.h
 * @brief   Timer (Basic Timer 1 & 2, General Timer 3 & 4& 7& 8, Advanced Timer 5 & 6 ) API
 *
 * @author  Aissen Li, Cecilia Wang
 * @version V1.0.0
 *
 * $Created: 2015-01-28 10:19:30$
 *
 * @copyright Shanghai Mountain View Silicon Technology Co.,Ltd. All rights reserved.
 **************************************************************************************
 */
 
 /*
 ======================================================================================
                       ##### ���ʹ�ö�ʱ����صĺ���API�ӿ� #####
 ======================================================================================
   [..]����������ΪP2ϵ��оƬ�Ķ�ʱ���ṩ�˺����ӿ�
       ��Щ�������չ��ܣ�����������3��ͷ�ļ��У�������ͬһ��ͨ����3�ֹ���Ϊ�����ϵ��
       
       ��##��������ʱ���ܣ�timer.h 
       
            (++)ѡ��һ����ʱ�������ö�ʱʱ���Լ���ʱģʽ   --  TimerStart
            (++)����ͨ����ȡ�жϱ�־���ж϶�ʱ�Ƿ��ѵ�      --  TimerInterruptFlagGet
            (++)�ڶ�ʱ�����й����У���ʱ��ѡ���Ƿ���ͣ      --  TimerPause
            (++)�ڵ���ģʽ�£�����ѡ���Ƿ�֧����ͣ             --  TimerSetHaltEnabled
            (++)��ȡʣ��ʱ��                                                   --  TimerGetResidualTime
       
       ��##��PWM������ܣ� pwm.h
       
            ��+����׼���/ǿ�����
                (++)��GPIO����ΪPWM����
                (++)ѡ��һ����ʱ����ѡ��ö�ʱ���µ�һ��ͨ��
                (++)ѡ��Ϊ����ģʽ�����ϼ���/���¼���/�м���������
                (++)ѡ��һ��������ͣ�ǿ�����/��׼���1/��׼���2��
                (++)����PWMƵ���Լ�ռ�ձ�
                (++)�Ƿ�ʹ��DMA����ռ�ձ�
                (++)ѡ���ǵ���������ǲ�����
                (++)ʹ��
                (++)֧�ֶ�̬����ռ�ձ�
                
             (+) ������
                 ͬһ����ʱ���У�ֻ֧��PWM1��PWM2��ϣ� PWM3��PWM4��ϡ�
                (++)������·�ļ���ģʽ
                (++)������·Ƶ�ʣ�ռ�ձȵȲ���
                (++)����һ·Ϊ��������������һ·����Ϊ��׼�������
                (++)ʹ��
                 
             (+) ���Գ����
                (++)����PWM1��PWM2��·ռ�ձ������PWM3��PWM4��·ռ�ձ�������
                (++)�����������Ϊ���Գ��������
                (++)ʹ��
                
             
             (+) �����Ͷ�·����
                (++)������������صĲ���
                (++)ʹ��
                
                (++)���ö�·����ļ���
                (++)���ö�·������˲�������
                (++)ʹ��
            
       
       ��##��PWC���빦�ܣ� pwc.h
       
            (++)����GPIO����ΪPWC����
            (++)ѡ��һ����ʱ����ѡ��ö�ʱ���µ�һ·PWC����ͨ��
            (++)ѡ�񲶻��ԣ���Ե����Ե/�����ص�������/�½��ص��½��أ�
            (++)����PWC��ʱ������
            (++)�����ź�������˲�������
            (++)ʹ��
       
       ��##��DMA���ƹ��ܣ� timer.h
       
            �ڸ߼���ʱ���У�ÿ�������Ķ�ʱ��֧��4·PWC,PWM�Լ�������ʱ���ܣ�����ֻ����һ��
            Ϊ��ģʽ�����ƶ�ʱ���ļ�����DMA����
            
            (++)ѡ��һ����ʱ������ֻ֧��TIMER5��TIMER6��ѡ��һ������Դ
 **************************************************************************************
 */

/**
 * @addtogroup TIMER
 * @{
 * @defgroup timer timer.h
 * @{
 */

#ifndef __TIMER_H__
#define __TIMER_H__

#ifdef __cplusplus
extern "C" {
#endif//__cplusplus

#include "type.h"

#define  TIMER_MAX_TIMEOUT_VALUE_IN_US  (23860201)      ///< �������õ�����ֵ microsecond(us) = 65535 * 65535 / 180


/**
 * @brief   ��ʱ��������
 * @note    P20��8����ʱ��������TIMER1�Ѿ�����Systick����
 */
typedef enum __TIMER_INDEX
{
    TIMER2 = 1, ///< ��ʱ2��BTimer
    TIMER3,     ///< ��ʱ3��GTimer
    TIMER4,     ///< ��ʱ4��GTimer
    TIMER5,     ///< ��ʱ5��ATimer
    TIMER6,     ///< ��ʱ6��ATimer
    TIMER7,     ///< ��ʱ7��ATimer
    TIMER8      ///< ��ʱ8��ATimer
    
} TIMER_INDEX;



/**
 * @brief   TIMER���봥��Դѡ��
 * @note    TIMER3���봥��Դ0~3���ζ�Ӧ��˳��Ϊ��TIMER4�� TIMER5�� TIMER6�� TIMER7
 * @note    TIMER4���봥��Դ0~3���ζ�Ӧ��˳��Ϊ��TIMER3�� TIMER5�� TIMER6�� TIMER7
 * @note    TIMER5���봥��Դ0~3���ζ�Ӧ��˳��Ϊ��TIMER6�� TIMER7�� TIMER8�� TIMER3
 * @note    TIMER6���봥��Դ0~3���ζ�Ӧ��˳��Ϊ��TIMER5�� TIMER7�� TIMER8�� TIMER3
 * @note    TIMER7���봥��Դ0~3���ζ�Ӧ��˳��Ϊ��TIMER8�� TIMER5�� TIMER6�� TIMER4
 * @note    TIMER8���봥��Դ0~3���ζ�Ӧ��˳��Ϊ��TIMER7�� TIMER5�� TIMER6�� TIMER4
 *
 */
typedef enum _TIMER_INPUT_TRIGGER_SRC
{
	INPUT_TRIGGER_0	  = 0,      ///< ѡ�����봥��Դ0

	INPUT_TRIGGER_1,            ///< ѡ�����봥��Դ1

	INPUT_TRIGGER_2,            ///< ѡ�����봥��Դ2

	INPUT_TRIGGER_3,            ///< ѡ�����봥��Դ3

	NONE_INTPUT_TRIGGER         ///< �����봥��Դ

} TIME_INPUT_TRIGGER_SRC;


/**
 * @brief   ��ʱ���������Դ
 * @note    PWM1~4�������ͽ�֧��TIMER5��6��7��8
 */
typedef enum _TIMER_OUTPUT_TRIGGER_SRC
{
	OUTPUT_TRIGGER_ENABLE = 0,   ///< ��ʱ��ʹ����Ϊ�������Դ

	OUTPUT_TRIGGER_UPDATE,       ///< ��ʱ��update��Ϊ�������Դ

	OUTPUT_TRIGGER_PWM1,         ///< PWM1�Ƚ��ź���Ϊ�������Դ

	OUTPUT_TRIGGER_PWM2,         ///< PWM2�Ƚ��ź���Ϊ�������Դ

	OUTPUT_TRIGGER_PWM3,         ///< PWM3�Ƚ��ź���Ϊ�������Դ

	OUTPUT_TRIGGER_PWM4          ///< PWM4�Ƚ��ź���Ϊ�������Դ
} TIMER_OUTPUT_TRIGGER_SRC;

/**
 * @brief   ��ʱ���ж��ź�Դѡ��
 */
typedef enum _TIMER_INTERRUPT_SRC
{
	UPDATE_INTERRUPT_SRC = 1,           ///< ��ʱ�������ж�
	PWC_OVER_RUN_INTERRUPT_SRC = 2,     ///< PWC����ж�
	PWC1_CAP_DATA_INTERRUPT_SRC = 4,    ///< PWC1�����ж�
	PWC2_CAP_DATA_INTERRUPT_SRC = 8,    ///< PWC2�����ж�
	PWC3_CAP_DATA_INTERRUPT_SRC = 16,   ///< PWC3�����ж�
	PWC4_CAP_DATA_INTERRUPT_SRC = 32,   ///< PWC4�����ж�
	PWM1_COMP_INTERRUPT_SRC = 64,       ///< PWM1�Ƚ��ж�
	PWM2_COMP_INTERRUPT_SRC = 128,      ///< PWM2�Ƚ��ж�
	PWM3_COMP_INTERRUPT_SRC = 256,      ///< PWM3�Ƚ��ж�
	PWM4_COMP_INTERRUPT_SRC = 512,      ///< PWM4�Ƚ��ж�
	PWM_BREAK_IN_INTERRUPT_SRC = 1024   ///< PWM Break in�ж�
} TIMER_INTERRUPT_SRC;

/**
 * @brief   ��ʱ�����ô������Ͷ���
 */
typedef enum _TIMER_ERROR_CODE
{
    TIMER_ERROR_INVALID_TIMER_INDEX = -128,  ///< ��ʱ�������Ŵ���
    TIMER_INPUT_TRIGGER_SRC_SEL,             ///< ��ʱ�����봥��Դ����
    TIMER_OUTPUT_TRIGGER_SRC_SEL,            ///< ��ʱ���������Դ����
    TIMER_INTERRUPT_SRC_SEL,                 ///< ��ʱ���ж�Դ����
    TIMER_ERROR_OK = 0                       ///< �޴���
} TIMER_ERROR_CODE;

////////////////////////////////////////////////////////////////////////////////////
//
//                      ���������ڶ�ʱ���ܵĺ����ӿ�
//
////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief      ���ö�ʱ���������ú�����λΪus
 *
 * @param[in]  TimerIndex        ��ʱ������, ��� #TIMER_INDEX
 * @param[in]  usec              ��ʱ����, ��λ��΢��(us)
 * @param[in]  SingleShot        0: ����ģʽ����ʱ֮�󣬶�ʱ��������װ�ؼ���ֵ.
 *                               1: ����ģʽ, ��ʱ֮�󣬶�ʱ��ֹͣ������
 * @return     �����, ��� #TIMER_ERROR_CODE
 */

TIMER_ERROR_CODE Timer_Config(TIMER_INDEX TimerIndex, uint32_t usec, bool SingleShot);

/**
 * @brief      ������ʱ��
 *
 * @param[in]  TimerIndex        ��ʱ������, ��� #TIMER_INDEX
 *
 * @return     �����, ��� #TIMER_ERROR_CODE
 */
TIMER_ERROR_CODE Timer_Start(TIMER_INDEX TimerIndex);

/**
 * @brief      ��ͣ��ʱ��
 *
 * @param[in]  TimerIndex        ��ʱ������, ��� #TIMER_INDEX
 * 			   IsPause           1:��ͣTimerIndex����    0������ʹ��TimerIndex����
 *
 * @return     �����, ��� #TIMER_ERROR_CODE
 */
TIMER_ERROR_CODE Timer_Pause(TIMER_INDEX TimerIndex, bool IsPause);

/**
 * @brief      ��ȡʣ��ʱ��
 *
 * @param[in]  TimerIndex   ��ʱ������, ��� #TIMER_INDEX
 *
 * @return     ʣ��ʱ��.
 */
TIMER_ERROR_CODE Timer_GetResidualTime(TIMER_INDEX TimerIndex);

////////////////////////////////////////////////////////////////////////////////////
//
//                      �����Ƕ�ʱ���ж���غ���
//
////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief      ʹ���ж�Դ
 *
 * @param[in]  TimerIndex      ��ʱ������, ��� #TIMER_INDEX
 * @param[in]  IntSrc:         �ж�Դѡ�񣬿���ѡ����
 *
 * @return     �����, ��� #TIMER_ERROR_CODE
 */
TIMER_ERROR_CODE Timer_InterrputSrcEnable(TIMER_INDEX TimerIndex, TIMER_INTERRUPT_SRC IntSrc);

/**
 * @brief      �ر��ж�Դ
 *
 * @param[in]  TimerIndex      ��ʱ������, ��� #TIMER_INDEX
 * @param[in]  IntSrc:         �ж�Դѡ�񣬿���ѡ����
 *
 * @return     �����, ��� #TIMER_ERROR_CODE
 */
TIMER_ERROR_CODE Timer_InterrputSrcDisable(TIMER_INDEX TimerIndex, TIMER_INTERRUPT_SRC IntSrc);

/**
 * @brief      ��ȡ��ʱ���жϱ�־
 *
 * @param[in]  TimerIndex    ��ʱ������
 * @param[in]  IntSrc:       �ж�Դѡ�񣬿���ѡ����
 *
 * @return     >0: �����ж�  0:���жϲ����� TIMER_ERROR_INVALID_TIMER_INDEX--����Ķ�ʱ������
 */
TIMER_ERROR_CODE Timer_InterruptFlagGet(TIMER_INDEX TimerIndex, TIMER_INTERRUPT_SRC IntSrc);

/**
 * @brief      �����ʱ���ж�
 *
 * @param[in]  TimerIndex    ��ʱ������
 * @param[in]  IntSrc:       �ж�Դѡ��ֻѡ��һ��
 *
 * @return     �����, ��� #TIMER_ERROR_CODE
 */
TIMER_ERROR_CODE Timer_InterruptFlagClear(TIMER_INDEX TimerIndex, TIMER_INTERRUPT_SRC IntSrc);

////////////////////////////////////////////////////////////////////////////////////
//
//                      �����Ƕ����ʱ��֮���ͬ���Դ�����
//
////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief      �����������봥��Դѡ�񣬿���Ϊ�ⲿ�����������Ҳ����Ϊ�������ڲ��Զ����������
 *
 * @param[in]  TimerIndex     ��ʱ������
 * @param[in]  TriggerSrc:    ���봥��Դ�����#TIMER_INPUT_TRIGGER_SRC
 *
 * @return     �����, ��� #TIMER_ERROR_CODE
 */
TIMER_ERROR_CODE Timer_InputTriggerSelect(TIMER_INDEX TimerIdx, TIME_INPUT_TRIGGER_SRC TriggerSrc);

/**
 * @brief      ���������������Դѡ�񣬿���Ϊ�ⲿ�����������Ҳ����Ϊ�������ڲ��Զ����������
 *
 * @param[in]  TimerIndex     ��ʱ������
 * @param[in]  TriggerSrc:    �������Դ�����#TIMER_INPUT_TRIGGER_SRC
 *
 * @return     �����, ��� #TIMER_ERROR_CODE
 */
TIMER_ERROR_CODE Timer_OutputTriggerSelect(TIMER_INDEX TimerIdx, TIMER_OUTPUT_TRIGGER_SRC TriggerSrc);


////////////////////////////////////////////////////////////////////////////////////
//
//                      ������SysTick��غ���
//
////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief	ϵͳ�δ�ʱ�ӳ�ʼ��
 * @param	��
 * @return ��
 * @note �ú�����ʼ��ϵͳ�δ�ʱ�ӣ�ÿ1ms����һ���ж�
 */
void SysTickInit(void);


/**
 * @brief	�ر�ϵͳ�δ�ʱ��
 * @param	��
 * @return ��
 * @note �ú����ر�ϵͳ�δ�ʱ��
 */
void SysTickDeInit(void);

/**
 * @brief	���ϵͳʱ���жϱ�ʶ
 * @param	��
 * @return ��
 * @note ���û���������дϵͳ�δ�ʱ���жϺ���ʱ����Ҫ���ȵ��øú�������жϱ�ʶ
 */
void SysTimerIntFlagClear(void);

/**
 * @brief	ϵͳ�δ��жϷ��������ú���Ϊweak���ԣ����Ա����¸�д
 * @param	��
 * @return ��
 * @note ���û���������дϵͳ�δ�ʱ���жϺ���ʱ����Ҫ���ȵ���SysTimerIntFlagClear
 */
__attribute__((weak)) void Timer2Interrupt(void);


#ifdef  __cplusplus
}
#endif//__cplusplus

#endif//__TIMER_H__

/**
 * @}
 * @}
 */
