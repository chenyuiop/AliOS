/**
 *******************************************************************************
 * @file    cache_tcm.h
 * @author  Robert, Aissen Li
 * @version V2.0.0
 * @date    2014/09/22
 *
 *******************************************************************************
 * @attention
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, MVSILICON SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
 * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * <h2><center>&copy; COPYRIGHT 2014 MVSilicon </center></h2>
 */

/**
 * @addtogroup CACHE_TCM
 * @{
 * @defgroup cache_tcm cache_tcm.h
 * @{
 */

#ifndef __CACHE_TCM_H__
#define __CACHE_TCM_H__

#include <string.h>

/**
 * @brief
 * ����/������ڴ���Ҫ���ڼ���ָ��ȡָ
 * оƬ�ڲ�����224KB�ڴ棬��Ҫ��Ϊ����7�������ڴ�飬��Щ�ڴ�������������ԣ�
 * Note: 1. ÿ���ڴ�����ͱ���Ϊ������/������ڴ�/��ͨ�ڴ� ֮һ
 *       2. �ڴ��˳�����Ϊ: ���棬������ڴ棬��ͨ�ڴ�
 *       3. PM8ֻ��Ϊ������ڴ�. PM7ֻ��Ϊ��ͨ�ڴ�
 *
 *       224K   208KB  192KB   128K      64K       0
 *       |  PM0 |  PM1 |  PM2  |   PM3   |   PM7   | PM8 |
 *       | 16KB | 16KB | 64KB  |  64KB   |  64KB   | 4KB |
 *                                                                                
 * Cache |------------>|                                                  
 * TCM   |------------------------------>|         |*****|
 * XMEM  |<------------------------------|*********|
 * e.g.  |    Cache    |  TCM  |       XMEM        | TCM |
 *
 * PM0: ���� / ������ڴ� / ��ͨ�ڴ�
 * PM1: ���� / ������ڴ� / ��ͨ�ڴ�
 * PM2: ������ڴ� / ��ͨ�ڴ�
 * PM3: ������ڴ� / ��ͨ�ڴ�
 * PM7: ��ͨ�ڴ�
 * PM8: ������ڴ�
 */

/**
 * @brief �����ڴ�鶨��
 */
typedef enum
{
	PHYMEM_NONE 	=   (0),
	PHYMEM_16KBPM0	=	(1 << 0),
	PHYMEM_16KBPM1	=	(1 << 1),
	PHYMEM_64KBPM2	=	(1 << 2),
	PHYMEM_64KBPM3	=	(1 << 3),
	PHYMEM_64KBPM7	=	(1 << 7),
	PHYMEM_4KBPM8	=	(1 << 8),
	PHYMEM_MASKALL	=	(0x1FF),
} PHYMEM_TYPE_T;

/**
 * @brief ���� / ������ڴ����ò����ṹ��
 */
typedef struct PHYMEM_SELECT
{
	PHYMEM_TYPE_T	CacheMemSel;
	PHYMEM_TYPE_T	TcmMemSel;
	PHYMEM_TYPE_T	XmemSel;
	unsigned int	Tcm0CodeAddr;
	unsigned int 	Tcm0CodeSz;
	unsigned int	Tcm1CodeAddr;
	unsigned int 	Tcm1CodeSz;
} PHYMEM_CONTROL_T;

/**
 * @brief ���� / ������ڴ��ʼ��
 * @param[in] PhyMemCtl ���� / ������ڴ����ò����ṹ��ָ�� 
 * @return 0: ��ʾ��ʼ���ɹ�������ֵ��ʾ��ʼ��ʧ��
 */
int CacheTcmInit(PHYMEM_CONTROL_T* PhyMemCtl);

/**
 * @brief ���� / ������ڴ���ٳ�ʼ��
 * @param[in] CacheMemSel  �����ڴ��ѡ�� 
 * @param[in] Tcm0MemSel   ������ڴ��ѡ��
 * @param[in] Tcm0CodeAddr ��פ��������0��ʼ��ַ
 * @param[in] Tcm0CodeSz   ��פ��������0��С
 * @param[in] Tcm1CodeAddr ��פ��������1��ʼ��ַ
 * @param[in] Tcm1CodeSz   ��פ��������1��С
 * @return 0: ��ʾ��ʼ���ɹ�������ֵ��ʾ��ʼ��ʧ��
 */
static inline int CacheTcmInitFast(PHYMEM_TYPE_T CacheMemSel, PHYMEM_TYPE_T Tcm0MemSel, long Tcm0CodeAddr, int Tcm0CodeSz, PHYMEM_TYPE_T Tcm1MemSel, long Tcm1CodeAddr, int Tcm1CodeSz)
{
	PHYMEM_CONTROL_T PhyMemCtl;

	/*
	 * set to default value
	 */
	memset(&PhyMemCtl, 0, sizeof(PHYMEM_CONTROL_T));

	PhyMemCtl.XmemSel       = PHYMEM_16KBPM0 | PHYMEM_16KBPM1 | PHYMEM_64KBPM2 | PHYMEM_64KBPM3;
	PhyMemCtl.CacheMemSel   = CacheMemSel;
	PhyMemCtl.TcmMemSel     = Tcm0MemSel | Tcm1MemSel;
	PhyMemCtl.XmemSel      &= ~(Tcm0MemSel | Tcm1MemSel | CacheMemSel);
	PhyMemCtl.Tcm0CodeAddr  = Tcm0CodeAddr;
	PhyMemCtl.Tcm0CodeSz    = Tcm0CodeSz;
	PhyMemCtl.Tcm1CodeAddr  = Tcm1CodeAddr;
	PhyMemCtl.Tcm1CodeSz    = Tcm1CodeSz;

	return CacheTcmInit(&PhyMemCtl);
}

/**
 * @brief  ���� / ������ڴ�ȥ��ʼ��
 * @param	 ��
 * @return ��
 */
void CacheTcmDeInit(void);

/**
 * @brief  ���� / ������ڴ��������
 */
typedef enum {

    CACHETCM_IOCTL_GET_XMEM_USGBLK          = 0x10,
    CACHETCM_IOCTL_GET_XMEM_FREEBLK,

    CACHETCM_IOCTL_DIS_CACHE                = 0x20,
    CACHETCM_IOCTL_DIS_TCM,

    CACHETCM_IOCTL_SELMAP_SOURCE            = 0x30,
    CACHETCM_IOCTL_SELMAP_MEMORY,

    CACHETCM_IOCTL_DBGSTAT_ACCESS_CNT_CM3   = 0xE0,
    CACHETCM_IOCTL_DBGSTAT_ACCESS_CNT_SLV,
    CACHETCM_IOCTL_DBGSTAT_MISS_CNT_BASIC,
    CACHETCM_IOCTL_DBGSTAT_MISS_CNT_ADV,
    CACHETCM_IOCTL_DBGSTAT_PENALTY_CYCLE_CNT_CM3,
    CACHETCM_IOCTL_DBGSTAT_PENALTY_CYCLE_CNT_SLV,
    CACHETCM_IOCTL_DBGSTAT_MISS_ADDR,
    CACHETCM_IOCTL_DBGSTAT_BIST_ERR_CNT,
    CACHETCM_IOCTL_DBGSTAT_DECRYPT_BIST_ERR_CNT,
    CACHETCM_IOCTL_RESET_STATISTIC_INFO,
} CACHETCM_IOCTL_T;

/**
 * @brief  ���� / ������ڴ����
 * @param  Cmd	 ���� / ������ڴ��������
 * @param  Arg	 ���� / ������ڴ���Ʋ���
 * @return ���ƽ��
 */
int CacheTcmIOctl(CACHETCM_IOCTL_T Cmd, ...);

#endif //__CACHE_TCM_H__

/**
 * @}
 * @}
 */
