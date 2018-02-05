/**
 *******************************************************************************
 * @file    watchdog.c
 * @author  Sean
 * @version V1.0.0
 * @date    2016/11/14
 * @brief		watchdog driver source file
 ******************************************************************************* 
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT 2014 MVSilicon </center></h2>
 */

/**
 * @addtogroup WATCHDOG
 * @{
 * @defgroup watchdog watchdog.h
 * @{
 */
 
#ifndef __WATCH_DOG_H__
#define __WATCH_DOG_H__
 
#ifdef __cplusplus
extern "C" {
#endif//__cplusplus

/**
 *  ���忴�Ź��ĸ�λ����
 */
typedef enum _WDG_STEP_SEL
{
    WDG_STEP_1S = 0,/**<���Ź��ĸ�λ����:1S*/
    WDG_STEP_3S = 1,/**<���Ź��ĸ�λ����:3S*/
    WDG_STEP_4S = 2 /**<���Ź��ĸ�λ����:4S*/
} WDG_STEP_SEL;


/**
 * @brief  ���Ź�ʹ��
 * @param  Mode ���ÿ��Ź��ĸ�λ����
 *     @arg WDG_STEP_1S
 *     @arg WDG_STEP_3S
 *     @arg WDG_STEP_4S
 * @return ��
 */
void WDG_Enable(WDG_STEP_SEL Mode);


/**
 * @brief  ���Ź���ֹ
 * @param  ��
 * @return ��
 */
void WDG_Disable(void);


/**
 * @brief  ι��
 * @param  ��
 * @return ��
 */
void WDG_Feed(void);
#ifdef  __cplusplus
}
#endif//__cplusplus

#endif

/**
 * @}
 * @}
 */
