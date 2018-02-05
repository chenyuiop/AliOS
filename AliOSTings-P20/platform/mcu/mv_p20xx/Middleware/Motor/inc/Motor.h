/**
 *****************************************************************************
 * @file     MOTOR.h
 * @author   Grayson
 * @version  V1.0.0
 * @date     25-May-2017
 * @brief    MOTOR module driver header file
 * @maintainer: Grayson
 * change log:
 *			 Add by Grayson -20170529
 *****************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT 2013 MVSilicon </center></h2>
 */
/**
 * @addtogroup ����
 * @{
 * @defgroup MOTOR MOTOR
 * @{
 */

#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "type.h"
#include "timer.h"
#include "pwm.h"

/**
 * @brief      HALL����
 *
 * @param[in]  TimerIndex  ��ʱ�������ţ�֧��TIMER5~TIMER8
 * @param[in]  ucHall      ����ֵ
 * @param[in]  Upload      ִ�л��� ��1=�������� 0=��ʱ�����ڻ���
 *
 * @return     ����ţ�0 - ��ȷ������Ϊ������ϸ�ο�PWM_ERROR_CODE
 */
TIMER_ERROR_CODE Motor_HallCommutator(TIMER_INDEX TimerIndex,uint8_t ucHall,bool Upload);


/**
 * @brief      ������ʱ����,��ʱʱ�䵽�ｫ��������źŵ������õ�TIMER���Ե����Ҫ���ڷ��綯�Ʋ������ʱ����
 *
 * @param[in]  TimerIndex  ��ʱ�������ţ�֧��TIMER5~TIMER8
 * @param[in]  Val         ��ʱʱ�䣬��ʱ��ʱ����
 *
 * @return     ����ţ�0 - ��ȷ������Ϊ������ϸ�ο�PWM_ERROR_CODE
 */
TIMER_ERROR_CODE Motor_CommutDelaySet(TIMER_INDEX TimerIndex, uint16_t Val);

/**
 * @brief      ��ȡPWC��ǰ������ֵ���Ե�����ϴ�HALL����ĿǰΪֹ�ļ���ֵ��
 *
 * @param[in]  TimerIndex  ��ʱ�������ţ�֧��TIMER5~TIMER8
 *
 * @return     PWC������ֵ
 */
uint16_t Motor_PWCCounterGet(TIMER_INDEX TimerIndex);


/**
 * @brief      �������PWM�������
 *
 * @param[in]  TimerIndex  ��ʱ�������ţ�֧��TIMER5~TIMER8
 * @param[in]  Polar       PWM���������ѡ��
 * @param[in]  A_P         A�����ű�����(PWM1_P)��1=���� 0=�ر�
 * @param[in]  A_N         A�����ű�����(PWM1_N)��1=���� 0=�ر�
 * @param[in]  B_P         B�����ű�����(PWM2_P)��1=���� 0=�ر�
 * @param[in]  B_N         B�����ű�����(PWM2_N)��1=���� 0=�ر�
 * @param[in]  C_P         C�����ű�����(PWM3_P)��1=���� 0=�ر�
 * @param[in]  C_N         C�����ű�����(PWM3_N)��1=���� 0=�ر�
 *
 * @return     ����ţ�0 - ��ȷ������Ϊ���� ����ϸ�ο� PWM_ERROR_CODE
 */
TIMER_ERROR_CODE  Motor_PWMOutPutSet(TIMER_INDEX TimerIndex,PWM_OUTPUT_POLARITY_MODE Polar,bool A_P,bool A_N,bool B_P,bool B_N,bool C_P,bool C_N);


/**
 * @brief      SVPWM����
 *
 * @param[in]  TimerIndex  ��ʱ�������ţ�֧��TIMER5~TIMER8
 * @param[in]  Ualpha      alpha���ѹ����IQ24
 * @param[in]  Ubeta       beta ���ѹ����IQ24
 * @param[in]  Ts          �ز���������ֵ�����ز�����(���Ķ���ģʽ�ز����ڵ�һ��)
 *
 * @return     ��
 */
void Motor_SVPWM(TIMER_INDEX TimerIndex,int32_t Ualpha,int32_t Ubeta,int16_t Ts);

/**
 * @brief      SVPWM������ʽ���Ƕȳ�ʼ��
 *
 * @param[in]  ucID            ���������,0~1
 * @param[in]  ucDir           ������з���,0=����1=��
 * @param[in]  ucHall          Hall������ֵ
 * @param[in]  usMaxLmtAng     �Ƕ��޶�ƫ��ֵ����HALL�źŲ��仯ʱ�����Ƕ�ƫ�ƣ�,0~0x3FFF
 *
 * @return     ��Ƕ�,0~0xFFFF(��Ӧ�Ƕ�0~2*Pi)
 */
uint16_t Motor_SvpwmAngleInit(uint8_t ucID,uint8_t ucDir,uint8_t ucHall,uint16_t usMaxLmtAng);


/**
 * @brief      SVPWM������ʽ�������������Ƕ�У��
 *
 * @param[in]  ucID            ���������,0~1
 * @param[in]  sFreqFed        �������Ƶ��
 * @param[in]  ucHall          Hall������ֵ
 *
 * @return     ��
 */
void Motor_SvpwmAngleHall(uint8_t ucID,int16_t sFreqFed,uint8_t ucHall);


/**
 * @brief      SVPWM������ʽ���Ƕȼ���
 *
 * @param[in]  ucID            ���������,0~1
 * @param[in]  usAng           ��ǰ��Ƕ�,0~0xFFFF
 * @param[in]  usDelta         ��Ƕ�������һ��PWM�����ڵĽǶ�������
 * @param[in]  sFreqFed        �������Ƶ��
 * @param[in]  ucHall          Hall������ֵ
 * @param[in]  usMaxLmtAng     �Ƕ��޶�ƫ��ֵ����HALL�źŲ��仯ʱ�����Ƕ�ƫ�ƣ�,0~0x3FFF
 * @param[in]  ucFltTime       �Ƕ��˲�����
 *
 * @return     ��Ƕȼ���ֵ,0~0xFFFF(��Ӧ�Ƕ�0~2*Pi)
 */
uint16_t Motor_SvpwmAngleProc(uint8_t ucID,uint16_t usAng,uint16_t usDelta,int16_t sFreqFed,uint8_t ucHall,uint16_t usMaxLmtAng,uint8_t ucFltTime);



#endif

/**
 * @}
 * @}
 */
