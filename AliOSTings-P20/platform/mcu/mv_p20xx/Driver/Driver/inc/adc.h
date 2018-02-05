/**
 *******************************************************************************
 * @file    adc.h
 * @brief	SarAdc module driver interface
 
 * @author  Sam
 * @version V1.0.0
 
 * $Created: 2014-12-26 14:01:05$
 * @Copyright (C) 2014, Shanghai Mountain View Silicon Co.,Ltd. All rights reserved.
 ******************************************************************************* 
 */

/**
 * @addtogroup ADC
 * @{
 * @defgroup adc adc.h
 * @{
 */
 
#ifndef __ADC_H__
#define __ADC_H__

#define  AUDIO_SAMPLE_RATE_8KHZ   	8000
#define  AUDIO_SAMPLE_RATE_11KHZ   	11025
#define  AUDIO_SAMPLE_RATE_12KHZ   	12000
#define  AUDIO_SAMPLE_RATE_16KHZ   	16000
#define  AUDIO_SAMPLE_RATE_22KHZ   	22050
#define  AUDIO_SAMPLE_RATE_24KHZ   	24000
#define  AUDIO_SAMPLE_RATE_32KHZ   	32000
#define  AUDIO_SAMPLE_RATE_44KHZ   	44100
#define  AUDIO_SAMPLE_RATE_48KHZ   	48000

typedef enum __ADC_MODE
{
	DC_MODE,
	AUDIO_MMODE
	
}ADC_MODE;


typedef enum __ADC_DC_CLK_DIV
{
	CLK_DIV_NONE,
	CLK_DIV_2,
	CLK_DIV_4,
	CLK_DIV_8,
	CLK_DIV_16,
	CLK_DIV_32,
	CLK_DIV_64,
	CLK_DIV_128,
	CLK_DIV_256
	
}ADC_DC_CLK_DIV;

 
typedef enum __ADC_DC_CHANNEL_SEL
{
	ADC_CHANNEL_VDD33,
	ADC_CHANNEL_VDD_BK,
	ADC_CHANNEL_VDD12,
	ADC_CHANNEL_GPIOA3,
	ADC_CHANNEL_GPIOA4,
	ADC_CHANNEL_GPIOA5,
	ADC_CHANNEL_GPIOA6,
	ADC_CHANNEL_GPIOA9,
	ADC_CHANNEL_GPIOA10, //8
	ADC_CHANNEL_GPIOA11,
	ADC_CHANNEL_GPIOA12,
	ADC_CHANNEL_GPIOA13,
	ADC_CHANNEL_GPIOA14,
	ADC_CHANNEL_GPIOA16,
	ADC_CHANNEL_GPIOA17, //14
	ADC_CHANNEL_GPIOA18,
	ADC_CHANNEL_GPIOB0,
	ADC_CHANNEL_GPIOB1,
	ADC_CHANNEL_GPIOB2,
	ADC_CHANNEL_GPIOB3,
	ADC_CHANNEL_GPIOB24, //20
	ADC_CHANNEL_GPIOB25,
	ADC_CHANNEL_GPIOB26,
	ADC_CHANNEL_GPIOB27,
	ADC_CHANNEL_GPIOB28,
	ADC_CHANNEL_GPIOB29,
	ADC_CHANNEL_GPIOC10, //26
	ADC_CHANNEL_GPIOC11
	
}ADC_DC_CHANNEL_SEL;


typedef enum __ADC_VREF
{
	ADC_VREF_VMID, //2��VMID
	ADC_VREF_VDDA,
	ADC_VREF_Extern //�ⲿ����
	
}ADC_VREF;

/**
 * @brief  ADC����ʹ��
 * @param  ��
 * @return ��
 */
void ADC_Enable(void);

/**
 * @brief  ADC������ֹ
 * @param  ��
 * @return ��
 */
void ADC_Disable(void);

/**
 * @brief  ADC����ģʽѡ��
 * @param  AdcMode 0:DC����;    1:AC��Ƶ����;  
 * @return NONE
 */
void ADC_ModeSet(ADC_MODE AdcMode);

/**
 * @brief  ��ѯADC����ģʽ
 * @param  ��
 * @return ADC����ģʽ��0:DC����;	1:AC��Ƶ����;
 */
ADC_MODE ADC_ModeGet(void);

/**
 * @brief  ADC����ʱ�ӷ�Ƶ(DCģʽ����Ч)
 * @param  div: ��Ƶϵ��
 * @return ��
 */
void ADC_DCClkDivSet(ADC_DC_CLK_DIV Div);

/**
 * @brief  ADCģ��ͨ������(DCģʽ����Ч)
 * @param  DcChannel DCͨ���ţ���ο�˵���ĵ���
 * @return ��
 */
void ADC_DCChannelSet(ADC_DC_CHANNEL_SEL ChannelIndex);

/**
 * @brief  ADC DC����һ��ת���������
 * @param  ��
 * @return ��ɱ�־ 1:����ת����ɣ� 0:����ת��δ���
 */
bool ADC_DCReady(void);

/**
 * @brief  ��ȡADC��������
 * @param  ��
 * @return ADC��������[0-4095]
 */
uint16_t ADC_DCDataGet(void);

/**
 * @brief  ��ȡһ��ADC DC�������ݣ�����ʽ���
 * @param  ChannelNum ADC DC����ͨ��		
 * @return ADC��������[0-4095]
 * @note   �ú���������ADC_DCChannelSet(),ADC_DCReady(),ADC_DCDataGet()3������������
 */         
uint16_t ADC_DCChannelDataGet(ADC_DC_CHANNEL_SEL ChannelIndex);
            
/**         
 * @brief  ADC�����־
 * @param  ��
 * @return ��
 */         
void ADC_Clr(void);
            
/**         
 * @brief  ADC�ο���ѹѡ��
 * @param  Mode 2:Extern Vref; 1:VDDA; 0: 2*VMID
 * @return ��
 */         
void ADC_VrefSet(ADC_VREF Mode);

/**
 * @brief  ADC����������
 * @param  SampleRate 9�ֲ�����
  * @arg	8000:8000Hz
  * @arg	11025:11025Hz
  * @arg	12000:12000Hz
  * @arg	16000:16000Hz
  * @arg	22050:22050Hz
  * @arg	24000:24000Hz
  * @arg	32000:32000Hz
  * @arg	44100:44100Hz
  * @arg	48000:48000Hz
 * @return ��
 */
void ADC_AudioSampleRateSet(uint16_t SampleRate);

/**
 * @brief  ��ȡADC������
 * @param  ��
 * @return SampleRate 9�ֲ�����
 */
uint32_t ADC_AudioSampleRateGet(void);

/**
 * @brief  ADC��ͨ�˲�������(��Ƶȥ��DC)
 * @param  IsHpfEn 1:ʹ�ܷ�����ȥ��DC; 0:��ֹ����ȥ��DC����;
 * @return ��
 */
void ADC_AudioHighPassFilterSet(bool IsHpfEn);

/**
 * @brief  ADC������������
 * @param  Vol ��������[0-4095]
 * @return ��
 */
void ADC_AudioVolSet(uint16_t Vol);

/**
 * @brief  ADCģ����������
 * @param  IsGainBoostEn ǰ��20dB�Ŵ����Ƿ�ʹ�ܣ�TRUE��ʹ�ܣ�FALSE����ֹ
 * @param  Vol ģ������Ŵ���ѡ��0:38dB��61:0.2dB��63:-1dB��step��-0.6dB
 * @return ��
 */
void ADC_AudioMicInGainSet(bool IsGainBoostEn, uint32_t Vol);

/**
 * @brief  ADCģ�������·����͹��ģ�ʹ���ڵ͹���ģʽ
 * @param  ��
 * @return ��
 */
void ADC_AudioMicInPoweDown(void);

/**
 * @brief  ADC���뵭��ʱ������(0dB��0��ʱ��)
 * @param  FadeTime ʱ�䣬��λMs
 * @return ��
 */
void ADC_FadeTimeSet(uint8_t FadeTime);

/**
 * @brief  ADC���뵭��ʹ��
 * @param  ��
 * @return ��
 */
void ADC_FadeEnable(void);

/**
 * @brief  ADC���뵭����ֹ
 * @param  ��
 * @return ��
 */
void ADC_FadeDisable(void);

/**
 * @brief  ADC����ʹ��
 * @param  ��
 * @return ��
 */
void ADC_AudioDigitalMuteEnable(void);

/**
 * @brief  ADC��������
 * @param  ��
 * @return ��
 */
void ADC_AudioDigitalMuteDisable(void);


/**
 * @brief  ADC����ʹ��(�ڲ�����ʱ���ȵ�����Ϊ0ʱ���Ƴ�����)
 * @param  ��
 * @return ��
 */
void ADC_AudioSoftMuteEnable(void);

/**
 * @brief  ADC��������
 * @param  ��
 * @return ��
 */
void ADC_AudioSoftMuteDisable(void);

/**
 * @brief  ADC Mic����ƫ�õ�ѹʹ��
 * @param  ��
 * @return ��
 */
void ADC_MicBiasEnable(void);

/**
 * @brief  ADC Mic����ƫ�õ�ѹ��ֹ
 * @param  ��
 * @return ��
 */
void ADC_MicBiasDisable(void);

#endif

/**
 * @}
 * @}
 */
