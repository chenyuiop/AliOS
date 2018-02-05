/**
 *****************************************************************************
 * @file     rtc_interface.h
 * @author   Sean
 * @version  V1.0.0
 * @date     29-03-2017
 * @brief    rtc module interface header file
 * @maintainer: Sean
 * change log:
 *			 Modify by Sean -20170329
 *****************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT 2013 MVSilicon </center></h2>
 */

/**
 * @addtogroup RTC_INTERFACE
 * @{
 * @defgroup rtc_interface rtc_interface.h
 * @{
 */

#ifndef __RTC_INTERFACE_H__
#define __RTC_INTERFACE_H__

#ifdef __cplusplus
extern "C" {
#endif//__cplusplus

#include "type.h"

/**
 * ����״̬����
 */
#define ALARM_STATUS_OPENED      0x01  /**< ��״̬   */
#define ALARM_STATUS_CLOSED      0x02  /**< �ر�״̬   */
/**
 * ����ģʽ����
 */
typedef enum _RTC_ALARM_MODE
{
	ALARM_MODE_ONCE_ONLY = 1,	/**< �������� */
	ALARM_MODE_PER_DAY,			/**< ÿ������ */
	ALARM_MODE_PER_WEEK,		/**< ÿ������ */
	ALARM_MODE_WORKDAY,			/**< ���������� */
	ALARM_MODE_USER_DEFINED,	/**< �Զ������� */
	ALARM_MODE_MAX,	
} RTC_ALARM_MODE;


#pragma pack(1)	/*Ensure this structure is byte aligned, and not use padding bytes */
typedef struct _ALARM_TIME
{
	uint32_t AlarmTimeAsSeconds;
	uint8_t  AlarmStatus : 2;
	uint8_t  AlarmMode : 4;
	uint8_t  AlarmData; //�������ڣ�bit0�������죬bit6��������
} ALARM_TIME;
#pragma pack()


/**
 * ����ʱ��ṹ�嶨��
 */
typedef struct _RTC_DATE_TIME
{
	uint16_t	Year;  /**< ������ */
	uint8_t	Mon;   /**< ������ */
	uint8_t	Date;  /**< ������ */
	uint8_t	WDay;  /**< ���ںţ�0�������գ�1~6������1����6 */
	uint8_t	Hour;  /**< Сʱ�� */
	uint8_t	Min;   /**< ������ */
	uint8_t	Sec;   /**< ���� */
} RTC_DATE_TIME;


/**
 * ũ��ʱ��ṹ�嶨��
 */
typedef struct _RTC_LUNAR_DATE
{
	uint16_t Year;         /**< ũ���� */
	uint8_t Month;        /**< ũ���� */
	uint8_t Date;         /**< ũ���� */
	uint8_t MonthDays;	   /**< ũ��ÿ�µ�������30 ���� 29*/
	bool IsLeapMonth;  /**< �Ƿ�Ϊ����*/
} RTC_LUNAR_DATE;


typedef enum _RTC_STATE_
{
	RTC_STATE_IDLE = 0,
	RTC_STATE_SET_TIME,
	RTC_STATE_SET_ALARM,

} RTC_STATE;

typedef enum _RTC_SUB_STATE_
{
    RTC_SET_IDLE = 0,	// ������
	RTC_SET_YEAR,    	// �������
    RTC_SET_MON,     	// �����·�
    RTC_SET_DAY,     	// ��������
	RTC_SET_WEEK,		// ������
    RTC_SET_HOUR,    	// ����Сʱ
    RTC_SET_MIN,     	// ���÷���
    RTC_SET_SEC,     	// ��������
	RTC_SET_ALARM_NUM,
	RTC_SET_ALARM_MODE,

} RTC_SUB_STATE;


typedef enum _RTC_WEEK_
{
    SUNDAY = 0,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,

} RTC_WEEK;

typedef struct _RTC_CONTROL_
{
	uint8_t  		State;          // RTC��ǰ״̬,IDLE, Set Time, Set Alarm
	uint8_t  		SubState;       // RTC��ǰ��״̬,set year/mon/...

	RTC_DATE_TIME 	DataTime;  		// ʱ������
	uint8_t	 		AlarmMode;		// ����ģʽ
	uint8_t  		AlarmData;		// �Զ�������ģʽ�£�����ʱ��ѡ��bit0�������죬bit1������һ��...,bit6��������,��λ��ʾѡ��
	uint8_t  		CurAlarmNum;	// ��ǰ��Ӧ�����ӱ��

	RTC_LUNAR_DATE	LuarDate; 		// ũ��
} RTC_CONTROL;

typedef struct _ALARM_INFO_
{
	ALARM_TIME* AlarmTimeList;// ����ʱ����Ϣ
}ALARM_INFO;


/**
 * @brief  RTCģ���ʼ��
 * @param  ʱ��ṹ��ָ�룬���ڷ��ص�ǰʱ��
 * @return ��
 */
void RTC_Init(RTC_CONTROL* ptr1,ALARM_INFO* ptr2,uint8_t alarmSum);

/**
 * @brief  ��ȡ��ǰʱ��
 * @param  ʱ��ṹ��ָ�룬���ڷ��ص�ǰʱ��
 * @return ��
 */
void RTC_CurrTimeGet(RTC_DATE_TIME* CurrTime);

/**
 * @brief  ���õ�ǰʱ��
 * @param  ʱ��ṹ��ָ�룬ΪҪ���õ�ʱ��ֵ
 * @return ��
 */
void RTC_CurrTimeSet(RTC_DATE_TIME* CurrTime);

/**
 * @brief  ʹ��ĳ������
 * @param  ��������
 * @return ��
 */
void RTC_AlarmEnable(uint8_t AlarmID);

/**
 * @brief  ��ֹĳ������
 * @param  ��������
 * @return ��
 */
void RTC_AlarmDisable(uint8_t AlarmID);

/**
 * @brief  ��ȡĳ������״̬
 * @param  ��������
 * @return TRUE~ʹ�� FALSE~��ֹ
 */
bool RTC_AlarmEnDisGet(uint8_t AlarmID);

/**
 * @brief  ��ȡĳ�����ӵ�����ģʽ������ʱ��
 * @param  AlarmID		���Ӻ�
 * @param  AlarmMode	����ģʽָ�룬���ڱ����ȡ������ģʽ
 * @param  ModeData		������ģʽ��������Ч��ʱ�䣨�ܼ������Զ��ͬʱ��Ч��
 * @param  AlarmTime	����ʱ��ṹ��ָ�룬���ڱ����ȡ������ʱ��
 * @return ���ִ�гɹ�����TRUE�����򷵻�FALSE��
 */
void RTC_AlarmTimeGet(uint8_t AlarmID, uint8_t* AlarmMode, uint8_t* AlarmData, RTC_DATE_TIME* AlarmTime);

/**
 * @brief  ����ĳ�����ӵ�����ģʽ������ʱ��
 * @param  AlarmID		���Ӻ�
 * @param  AlarmMode	����ģʽ
 * @param  ModeData		������ģʽ��������Ч��ʱ�䣨�ܼ������Զ��ͬʱ��Ч��
 * @param  AlarmTime	����ʱ��ṹ��ָ�룬���ڱ�������ʱ��
 * @return ���ִ�гɹ�����TRUE�����򷵻�FALSE��
 */
void RTC_AlarmTimeSet(uint8_t AlarmID, uint8_t AlarmMode, uint8_t AlarmData, RTC_DATE_TIME* AlarmTime);

/**
 * @brief  ����Ƿ������ӵ��ˡ�
 * @param  ��
 * @return ����0��ʾû�����ӵ������ش���0��ֵ��ʾ��Ӧ�����ӵ���
 */
uint8_t RTC_AlarmFlagGet(void);

/**
 * @brief  ��������жϱ�־
 * @param  ��
 * @return ��
 */
void RTC_AlarmIntClear(void);

/**
 * @brief  ���ӵ�ʱ��Ҫ���Ĵ����ϲ���յ����ӵ�����Ϣ�󣬱�����ô˺�����
 * @param  ��
 * @return ��
 */
void RTC_AlarmArrivedProcess(void);


/**
 * @brief  ��ĳ���ũ����Ϣ��ȡ��������
 * @param  Year:�������
 * @return NONE
 */
void RTC_LunarLoadLunarInfo(uint16_t Year);

/**
 * @brief  ��������תũ������
 * @param  DateTime:����ʱ��ṹ��ָ�룬��Ϊ�������
 * @param  LunarDate:ũ��ʱ��ṹ��ָ�룬��Ϊ�������
 * @return NONE
 */
void RTC_LunarSolarToLunar(RTC_DATE_TIME* DateTime, RTC_LUNAR_DATE* LunarDate);

/**
 * @brief  ��ȡũ����ݵ����
 * @param  Year:ũ�����
 * @return ����0-9, �ֱ��Ӧ���: {"��", "��", "��", "��", "��", "��", "��", "��", "��", "��"}
 */
uint8_t RTC_LunarGetHeavenlyStem(uint16_t Year);

/**
 * @brief  ��ȡũ����ݵĵ�֧
 * @param  Year:ũ�����
 * @return ����0-11, �ֱ��Ӧ��֧: {"��", "��", "��", "î", "��", "��", "��", "δ", "��", "��", "��", "��"}
 *         �ֱ��Ӧ��Ф: {"��", "ţ", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��"}
 */
uint8_t RTC_LunarGetEarthlyBranch(uint16_t Year);

#ifdef  __cplusplus
}
#endif//__cplusplus

#endif

/**
 * @}
 * @}
 */
