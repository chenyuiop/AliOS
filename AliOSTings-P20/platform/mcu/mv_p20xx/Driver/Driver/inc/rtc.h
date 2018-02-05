/**
 *****************************************************************************
 * @file     rtc.h
 * @author   Sean
 * @version  V1.0.0
 * @date     29-Nov-2016
 * @brief    rtc module driver header file
 * @maintainer: Sean
 * change log:
 *			 Add by Sean -20161129
 *****************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT 2013 MVSilicon </center></h2>
 */
/**
 * @addtogroup RTC
 * @{
 * @defgroup rtc rtc.h
 * @{
 */

#ifndef __RTC_H__
#define __RTC_H__

#ifdef __cplusplus
extern "C" {
#endif//__cplusplus

#include "type.h"

/**
 *  RTC Clock Source Select
 */
typedef enum _RTC_CLOCK_SEL
{
    OSC_32K = 0,/**<RTCʱ��ѡ���徧��32.768kHZ��ʱ��Ƶ��Ϊ32768HZ*/
    OSC_12M = 1,/**<RTCʱ��ѡ���徧��12MHZ���ҽ��з�Ƶ��Ƶ��ʱ��Ƶ�ʿ���*/
    RC_32K = 2  /**<RTCʱ��ѡ��RC 32.768kHZ��ʱ��Ƶ��Ϊ32768HZ��RC���ϴ�*/
} RTC_CLOCK_SEL;

/**
 *  RTC��ʱ�����ӽṹ�壬Sec��λΪ�룬FracԶС���뵥λΪʱ�����ڡ�ʹ��ʱһ��ʹ��Sec���ɣ�Fracʹ�ó�������ֱ�Ӹ�0���ɡ�
 */
typedef struct _RTC_REG_TIME_UNIT
{
    uint32_t Sec;
    uint16_t Frac;
} RTC_REG_TIME_UNIT;

 /**
  * @brief  RTC�ж�ʹ��
  * @param  ��
  * @return ��
  */
void RTC_IntEnable(void);

 /**
  * @brief  RTC�жϽ�ֹ
  * @param  ��
  * @return ��
  */
void RTC_IntDisable(void);

 /**
  * @brief  RTC�жϱ�־���
  * @param  ��
  * @return ��
  */
void RTC_IntFlagClr(void);

 /**
  * @brief  RTC�жϱ�־��ȡ
  * @param  ��
  * @return ��
  */
bool RTC_IntFlagGet(void);

 /**
  * @brief  RTC���ѹ��ܿ���
  * @param  ��
  * @return ��
  */
void RTC_WakeupEnable(void);

 /**
  * @brief  RTC���ѹ��ܹر�
  * @param  ��
  * @return ��
  */
void RTC_WakeupDisable(void);

/**
 * @brief  ����RTC
 * @param  RTCֵ
 * @return ��
 */
void RTC_TimeSet(RTC_REG_TIME_UNIT time);

/**
 * @brief  ��ȡRTC
 * @param  ��
 * @return ��ǰRTC
 */
RTC_REG_TIME_UNIT RTC_TimeGet(void);

/**
 * @brief  ����Alarm
 * @param  Alarmֵ
 * @return ��
 */
void RTC_AlarmSet(RTC_REG_TIME_UNIT alarm);
/**
 * @brief  ��ȡAlarm
 * @param  ��
 * @return ��ǰAlarm
 */
RTC_REG_TIME_UNIT RTC_AlarmGet(void);


/**
 * @brief  ����RTCģ���ʱ��Դ��Ƶ��
 * @param  ClkSel ����RTCģ���ʱ��Դ
 *	@arg OSC_32K:ѡ��32.768kHZ���徧����ΪRTCʱ�ӣ�ʱ��Ƶ��Ϊ32768HZ
 *	@arg OSC_12M:ѡ��12MHZ���徧���Ҷ�����з�Ƶ��ΪRTCʱ�ӣ�ʱ��Ƶ�����û����ã���λΪHZ
 *	@arg RC_32K: ѡ��32.768kHZ���徧����Ϊrtcʱ�ӣ�ʱ��Ƶ��Ϊ32768HZ,RCʱ�����ϴ�
 * @param Freq ����RTCģ���Ƶ�ʣ���ѡ��OSC_12Mʱ���䣬��λΪHZ������ʱ��ԴĬ��32768HZ���ݲ���32768����
 * @return ��
 */
void RTC_ClockSrcSel(RTC_CLOCK_SEL ClkSel,uint16_t Freq);

#ifdef  __cplusplus
}
#endif//__cplusplus

#endif

/**
 * @}
 * @}
 */
