/**
 *******************************************************************************
 * @file    dpa.h
 * @author  Aissen Li
 * @version V1.0.0
 *
 * @brief   DPA ����������
 *
 *******************************************************************************
 */
 
 /**
 * @addtogroup DPA
 * @{
 * @defgroup dpa dpa.h
 * @{
 */
 
#ifndef __DPA__H__
#define __DPA__H__

#ifdef  __cplusplus
extern "C" {
#endif//__cplusplus

#include "type.h"

enum
{
	DPA_ERROR_INVALID_FUNC_MODE = -256,
	DPA_ERROR_INVALID_REVERSE_MODE,
	DPA_ERROR_INVALID_SHIFT_BITS,
	DPA_ERROR_OK = 0,
};

enum
{
	DPA_FUNC_MODE_BIT_SHIFT,             //����λ��
	DPA_FUNC_MODE_BIT_SHIFT_AND,         //����λ�� & �����
	DPA_FUNC_MODE_BIT_SHIFT_OR,          //����λ�� & �����
	DPA_FUNC_MODE_BIT_SHIFT_XOR,         //����λ�� & ������
	DPA_FUNC_MODE_BIT_REVERSE8,          //8λ���ط�ת
	DPA_FUNC_MODE_BIT_REVERSE16,         //16λ���ط�ת
	DPA_FUNC_MODE_BIT_REVERSE24,         //24λ���ط�ת
	DPA_FUNC_MODE_BIT_REVERSE32,         //32λ���ط�ת
	DPA_FUNC_MODE_BIT_TRANSPOSE8X8,      //8x8���ؾ���ת��
	DPA_FUNC_MODE_BIT_TRANSPOSE16X16,    //16x16���ؾ���ת��
};

enum
{
	DPA_REVERSE_MODE_CONTINOUS = 0,
	DPA_REVERSE_MODE_INTERLEAVE,
};

/**
 * @brief  DPA����������
 * @param  FuncMode     ����������
 * @param  ReverseMode  ��תģʽ
 * @param  SrcOff       Դ����ƫ��
 * @param  DstOff       Ŀ������ƫ��
 * @return ������
 */
int32_t DPA_Config(int32_t FuncMode, int32_t ReverseMode, int32_t SrcOff, int32_t DstOff);

/**
 * @brief  DPA����������
 * @param  ��
 * @return ��
 */
void DPA_Start();

/**
 * @brief  DPA������ֹͣ
 * @param  ��
 * @return ��
 */
void DPA_Stop();

#ifdef  __cplusplus
}
#endif//__cplusplus

#endif//__DPA__H__

/**
 * @}
 * @}
 */
