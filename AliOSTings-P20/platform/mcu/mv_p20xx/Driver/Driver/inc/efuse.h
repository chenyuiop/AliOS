/*
 * efuse.h
 *
 *  Created on: Jun 9, 2017
 *      Author: jerry_rao
 */

#ifndef EFUSE_H_
#define EFUSE_H_

/**
 * @addtogroup EFUSE
 * @{
 * @defgroup efuse efuse.h
 * @{
 */
 
#include "type.h"

/**
 * @brief  ��ȡEfuse��ָ����ַ������
 * @param  AddrΪEfuse��ָ���ĵ�ַ��ʮ�����Ʊ�ʾ
 *         �ɶ��ĵ�ַΪ0x00~0x3A������
 *             (1)�ͻ��Զ���ĵ�ַ��0x23~0x2A����8���ֽڵ�ַ�ռ䣬Ĭ��Ϊȫ0
 *             (2)оƬΨһ��ID��ţ�0x0A~0x11����8���ֽڵ�ַ�ռ䣬��������ֵ
 * @return ��ȡ��ָ����ַ������
 */
uint8_t Efuse_ReadData(uint8_t Addr);

#endif /* EFUSE_H_ */
