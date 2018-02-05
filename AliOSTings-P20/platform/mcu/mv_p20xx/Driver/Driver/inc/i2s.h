/**
 **************************************************************************************
 * @file    i2s.h
 * @brief   I2S Module API
 *
 * @author  Cecilia Wang
 * @version V1.0.0
 *
 * $Created: 2014-10-22 15:32:38$
 *
 * @copyright Shanghai Mountain View Silicon Technology Co.,Ltd. All rights reserved.
 **************************************************************************************
 */
 
/**
 * @addtogroup I2S
 * @{
 * @defgroup i2s i2s.h
 * @{
 */
 
#ifndef __I2S_H__
#define __I2S_H__
 
#ifdef  __cplusplus
extern "C" {
#endif//__cplusplus

#include "type.h"
    
/**
 * @brief I2S֧�ֵ����ݶ����ʽ
 */    
typedef enum _I2S_DATA_FORMAT
{
    I2S_FORMAT_RIGHT = 0,
    I2S_FORMAT_LEFT,
    I2S_FORMAT_I2S,
    I2S_FORMAT_DSPA,
    I2S_FORMAT_DSPB
} I2S_DATA_FORMAT;


/**
 * @brief I2S֧�ֵ�����λ��
 */ 
typedef enum _I2S_DATA_WORDLTH
{
    I2S_LENGTH_16BITS = 0,
    I2S_LENGTH_20BITS,
    I2S_LENGTH_24BITS,
    I2S_LENGTH_32BITS
} I2S_DATA_LENGTH;

/**
 * @brief  ��DSP��A�����ݶ����ʽ�£�����I2S���뵥������˫����ģʽ
 * @param  IsMono  : 1: ���������ݴ���
 *                    0: ˫�������ݴ���
 * @return ��
 */
void I2S_MonoModeSet(bool IsMono);

/****************************************************************************/
/*                Lrclk��Bclkʱ�ӵķ�Ƶ����λ��غ���                    */
/****************************************************************************/
/**
 * @brief  ����I2Sģ���Bclkʱ���Ƿ���
 * @param  IsBclkInvert: 1:���� 0:������
 * @return ��
 */
void I2S_BclkInvertSet(bool IsBclkInvert);

/**
 * @brief  ����I2Sģ���Bclk���ʱ��Ƶ��
 * @param  BclkDiv  : Bclk��Ƶֵ, ��Χ(0~20),ֻ��I2Sģ�鴦��Masterģʽ����Ч
 * @param          |  0: i2s_clk     |  1: i2s_clk/1.5  |   2: i2s_clk/2  |
 * @param          |  3: i2s_clk/3   |  4: i2s_clk/4    |   5: i2s_clk/5  |
 * @param          |  6: i2s_clk/5.5 |  7: i2s_clk/6    |   8: i2s_clk/8  |
 * @param          |  9: i2s_clk/10  | 10: i2s_clk/11   |  11: i2s_clk/12 |
 * @param          | 12: i2s_clk/16  | 13: i2s_clk/20   |  14: i2s_clk/22 |
 * @param          | 15: i2s_clk/24  | 16: i2s_clk/25   |  17: i2s_clk/30 |
 * @param          | 18: i2s_clk/32  | 19: i2s_clk/44   |  20: i2s_clk/48 |
 * @return ��
 */
void I2S_BclkFreqSet(uint32_t BclkDiv);

/**
 * @brief  ����I2Sģ���Lrclkʱ���Ƿ���
 * @param  IsLrclkInvert: 1:���� 0: ������
 * @return ��
 */
void I2S_LrclkInvertSet(bool IsLrclkInvert);

/**
 * @brief  ����I2Sģ��Lrclkʱ�ӵ����Ƶ��
 * @param  FreqDiv  : lrclk freq=bclk freq/FreqDiv,��Χ(8~2047),��ҪI2Sģ�鴦��
 *                    Masterģʽ��ʱ��Ч
 * @return NONE
 */
void I2S_LrclkFreqSet(uint32_t FreqDiv);

/****************************************************************************/
/*                Masterģʽ��Slaveģ����غ���                              */
/****************************************************************************/
/**
 * @brief  ��ȡI2Sģ�鵱ǰ������
 * @return ��ǰ������: 8K/11.025K/12K/16K/22.05K/24K/32K/44.1K/48K/64K/88.2K/96K/176.4K/192K
 *         �������0�������
 */
uint32_t I2S_SampleRateGet(void);

/**
 * @brief  ����I2Sģ�������
 * @param  SampleRate: ��Ҫ���õĲ����ʣ�8K/11.025K/12K/16K/22.05K/24K/32K/44.1K/48K/64K/88.2K/96K/176.4K/192K
 * @return ��
 */ 
void I2S_SampleRateSet(uint32_t SampleRate);

/**
 * @brief  ����I2Sģ�����Masterģʽ
 * @param  I2SFormat : ���ݶ����ʽ��right/left/i2s/dsp
 * @param  I2SWordlth: ����λ�������16bits/20bits/24bits/32bits
 * @return ��
 */ 
void I2S_SetMasterMode(uint8_t I2SFormat, uint8_t I2SWordlth);

/**
 * @brief  ����I2Sģ�����Slaveģ��
 * @param  I2SFormat : ���ݶ����ʽ��right/left/i2s/dsp
 * @param  I2SWordlth: ����λ��16bits/20bits/24bits/32bits
 * @return NONE
 */ 
void I2S_SetSlaveMode(uint8_t I2SFormat, uint8_t I2SWordlth);

/**
 * @brief  ����I2Sģ����PCM-Syncģʽ�µĲ�����Ϊ8KHZ
 * @return ��
 */
void I2S_PCMSyncSampleRateSet(void);

/**
 * @brief  ����I2S����PCM-Syncģʽ��ʹ��ΪMasterģʽ
 * @return ��
 */
void I2S_PCMSyncSetMasterMode(void);

/**
 * @brief  ����I2S����PCM-Syncģʽ��ʹ��ΪSlaveģʽ
 * @return ��
 */
void I2S_PCMSyncSetSlaveMode(void);

/****************************************************************************/
/*                ʹ�ܡ���ͣ�͸�λ��صĺ���                                 */
/****************************************************************************/

/**
 * @brief  ʹ��I2Sģ����ͣ��ȡ����ͣ����
 * @param  IsPause  : �Ƿ���ͣ������0:��������, 1:��ͣ����
 * @return ��
 */
void I2S_ModuleTxPause(bool IsPause);

/**
 * @brief  ʹ��I2S�ķ���ģ��
 * @param  IsEnable  : 1�� ʹ��  0�� ����
 * @return ��
 */
void I2S_ModuleTxEnable(bool IsEnable);

/**
 * @brief  ʹ��I2S Dout����ģʽ����I2S����ģ�����ʱ��DoutΪ����״̬
 *         ��I2S����ģ��ʹ��ʱ�����ʹ�ܸ���ģʽ������Чbitʱ���ڸ���״̬
 *                            ������ܸ���ģʽ������Чbitʱ���ڵ͵�ƽ
 * @param  IsEnable  : 1�� ʹ��  0�� ����
 * @return ��
 */
void I2S_ModuleTxHizEnable(bool IsEnable);

/**
 * @brief  ʹ��I2S�Ľ���ģ��
 * @param  IsEnable  : 1�� ʹ��  0�� ����
 * @return ��
 */
void I2S_ModuleRxEnable(bool IsEnable);

/**
 * @brief  ������ر�����I2Sģ��
 * @param  IsEnable : �Ƿ���I2Sģ�飬0:�ر�, 1:����
 * @return ��
 */
void I2S_ModuleEnable(uint8_t IsEnable);


/****************************************************************************/
/*                ��Slaveģ���²�����ʵʱ��⹦����غ���                    */
/****************************************************************************/
/**
 * @brief  ʹ�ܻ����I2Sģ����Slaveģʽ�²�����ʵʱ��⹦��
 * @param  IsEnable : �Ƿ�ʹ�ܣ�1:ʹ�� 0:����
 * @return ��
 */
void I2S_SampleRateCheckEnable(bool IsEnable);

/**
 * @brief  ��ȡI2S������ʵʱ����жϱ�־
 * @return �жϱ�־��1:������ 0:��Ч
 */
bool I2S_GetSampleRateCheckInt(void);

/**
 * @brief  ���I2S������ʵʱ����жϱ�־
 * @return ��
 */
void I2S_ClrSampleRateCheckInt(void);

/****************************************************************************/
/*                       ����������/����Ч��������غ���                     */
/****************************************************************************/
/**
 * @brief  ����I2S���뾲����Ǿ���״̬
 * @param  IsMute   : �Ƿ�����־��0:�Ǿ��� 1:����
 * @return ��
 */
void I2S_MuteSet(bool IsEnable);

/**
 * @brief  ��ȡI2Sģ�鵱ǰ����״̬
 * @return 1:����״̬ 0:�Ǿ���״̬
 */
bool I2S_GetMuteStatus(void);

/**
 * @brief  ����I2Sģ�鵭�뵭����ʱ�䡣
 * @param  FadeTime : ���뵭��ʱ������,��λ:Ms,��ʽΪ��FadeTime = (2^12)/(Fs*(1 ~ 255)),
 *                    ����FsΪ�����ʣ���λ��KHz.
 *                    ����:1)������Ϊ8KHzʱ��FadeTime��Χ��2ms ~ 512ms��
 *                         2)������Ϊ192KHzʱ��FadeTime��Χ��1ms ~ 21ms��
 * @return ��
 */
void I2S_FadeTimeSet(uint32_t FadeTime);

/**
 * @brief  ������ر�I2Sģ�鵭�뵭������
 * @param  IsEnable : �Ƿ������뵭�����ܣ�0: �ر� 1: ����
 * @return None
 */
void I2S_FadeEnable(bool IsEnable);

#ifdef  __cplusplus
}
#endif//__cplusplus

#endif//__I2S_H__

/**
 * @}
 * @}
 */
