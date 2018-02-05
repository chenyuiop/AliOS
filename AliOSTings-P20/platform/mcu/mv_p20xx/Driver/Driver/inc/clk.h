/**
 *******************************************************************************
 * @file    clk.h
 * @brief	Clock driver interface
 *
 * @author  Sam
 * @version V1.0.0
 *
 * $Created: 2015-11-05 10:46:11$
 *
 * &copy; Shanghai Mountain View Silicon Technology Co.,Ltd. All rights reserved.
 ******************************************************************************* 
 */
 
 
/**
 * @addtogroup CLOCK
 * @{
 * @defgroup clk clk.h
 * @{
 */
 
#ifndef __CLK_H__
#define __CLK_H__
 
#ifdef __cplusplus
extern "C" {
#endif//__cplusplus

/**
 * CLK module switch macro define
 */
typedef enum __CLOCK_MODULE_SWITCH
{
	FLASHC_CLK_EN = (1 << 0),           /**<FLASH control module clk switch */
	FLASHC_CLK_480M_EN = (1 << 1),			/**<FLASH control module clk 480M switch */
	USB_CLK_480M_EN = (1 << 2),         /**<USB module clk switch */
	FLASHC_HPM_CLK_480M_EN = (1 << 3),  /**<FLASH control HPM module clk 480M switch */
	EFUSE_CLK_EN = (1 << 4),            /**<AUDIO ADC1 module clk switch */
	I2S_CLK_EN = (1 << 5),             /**<I2S module clk switch */
	SARADC_CLK_EN = (1 << 6),           /**<SarADC module clk switch */
	I2C_CLK_EN = (1 << 7),              /**<I2C module clk switch */
	SD_CLK_EN = (1 << 8),               /**<SD module clk switch */
	SPIM0_CLK_EN = (1 << 9),           /**<SPIM0 module clk switch */
	SPIM1_CLK_EN = (1 << 10),           /**<SPIM1 module clk switch */
	UART0_CLK_EN = (1 << 11),           /**<UART0 module clk switch */
	UART1_CLK_EN = (1 << 12),           /**<UART1 module clk switch */
	UART2_CLK_EN = (1 << 13),           /**<UART2 module clk switch */
	USB_CLK_EN = (1 << 14),             /**<USB module clk switch */
	DMA_CLK_EN = (1 << 15),             /**<DMA module clk switch */
	FDMA_CLK_EN = (1 << 16),            /**<FDMA module clk switch */
	DPA_CLK_EN = (1 << 17),             /**<ACC module clk switch */
	LEDC_CLK_EN = (1 << 18),            /**<LED control module clk switch */
	TIMER1_CLK_EN = (1 << 19),          /**<TIMER1 module clk switch */
	TIMER2_CLK_EN = (1 << 20),          /**<TIMER2 module clk switch */
	TIMER3_CLK_EN = (1 << 21),          /**<TIMER3 module clk switch */
	TIMER4_CLK_EN = (1 << 22),          /**<TIMER4 module clk switch */
	TIMER5_CLK_EN = (1 << 23),          /**<TIMER5 module clk switch */
	TIMER6_CLK_EN = (1 << 24),          /**<TIMER6 module clk switch */
	TIMER7_CLK_EN = (1 << 25),          /**<TIMER7 module clk switch */
	TIMER8_CLK_EN = (1 << 26),          /**<TIMER8 module clk switch */
	ALL_MODULE_CLK_SWITCH = (0x7FFFFFF),/**<all module clk SWITCH*/
} CLOCK_MODULE_SWITCH;

/**
 * CLK module GATE switch macro define
 */
typedef enum __CLOCK_MODULE_GATE_SWITCH
{
	I2S_CLK_GATE_EN = (1 << 0),          				/**<I2S module clk gating switch */
	SARADC_CLK_GATE_EN = (1 << 1),              /**<SarADC module clk gating switch */
	FLASHC_CLK_GATE_EN = (1 << 2),              /**<FLASH control module clk gating switch */
	UART0_CLK_GATE_EN = (1 << 3),               /**<UART0 module clk gating switch */
	UART1_CLK_GATE_EN = (1 << 4),               /**<UART1 module clk gating switch */
	UART2_CLK_GATE_EN = (1 << 5),               /**<UART2 module clk gating switch */
	CORE_CLK_GATE_EN = (1 << 6),                /**<CORE module clk gating switch */
	GPIO_CLK_GATE_EN = (1 << 7),                /**<GPIO module clk gating switch */
	SRAM1_CLK_GATE_EN = (1 << 8),               /**<SRAM1 module clk gating switch */
	SRAM2_CLK_GATE_EN = (1 << 9),               /**<SRAM2 module clk gating switch */
	SRAM3_CLK_GATE_EN = (1 << 10),              /**<SRAM3 module clk gating switch */
	SRAM7_CLK_GATE_EN = (1 << 11),              /**<SRAM7 module clk gating switch */
	DMA_CLK_GATE_EN = (1 << 12),                /**<DMA module clk gating switch */
	SDIO_CLK_GATE_EN = (1 << 13),               /**<SDIO module clk gating switch */
	SPIM0_CLK_GATE_EN = (1 << 14),              /**<SPIM0 module clk gating switch */
	SPIM1_CLK_GATE_EN = (1 << 15),              /**<SPIM1 module clk gating switch */
	SPIS_CLK_GATE_EN = (1 << 16),               /**<SPIS module clk gating switch */
	ROM_CLK_GATE_EN = (1 << 17),                /**<ROM module clk gating switch */
	DPLL_CLK_GATE_EN = (1 << 18),               /**<DPLL module clk gating switch */
	RESET_CLK_GATE_EN = (1 << 19),              /**<RESET module clk gating switch */
	CLOCK_CLK_GATE_EN = (1 << 20),              /**<CLOCK module clk gating switch */
	TIMER1_CLK_GATE_EN = (1 << 21),             /**<TIMER1 module clk gating switch */
	TIMER2_CLK_GATE_EN = (1 << 22),             /**<TIMER1 module clk gating switch */
	TIMER3_CLK_GATE_EN = (1 << 23),             /**<TIMER1 module clk gating switch */
	TIMER4_CLK_GATE_EN = (1 << 24),             /**<TIMER1 module clk gating switch */
	TIMER5_CLK_GATE_EN = (1 << 25),             /**<TIMER1 module clk gating switch */
	TIMER6_CLK_GATE_EN = (1 << 26),             /**<TIMER1 module clk gating switch */
	TIMER7_CLK_GATE_EN = (1 << 27),             /**<TIMER1 module clk gating switch */
	TIMER8_CLK_GATE_EN = (1 << 28),             /**<TIMER1 module clk gating switch */
	LEDC_CLK_GATE_EN = (1 << 29),               /**<LED control module clk gating switch */
	FDMA_CLK_GATE_EN = (1 << 30),               /**<SPDIF module clk gating switch */
	ALL_MODULE_CLK_GATE_SWITCH = (0x7FFFFFFF), /**<all module clk gating SWITCH*/
} CLOCK_MODULE_GATE_SWITCH;


typedef enum __CLK_MODE{
	RC_CLK_MODE,
	PLL_CLK_MODE,
	SYSTEM_CLK_MODE /*Fpll / 4 / SYS DIV NUM*/
}CLK_MODE;


typedef enum __MCLK_CLK_SEL{
	PLL_GEN_12M288,		/**PLL�Զ�����12.288M*/
	PLL_GEN_11M2896,	/**PLL�Զ�����11.2896M*/
	PLL_GPIO_IN,		/**GPIO����*/
	PLL_USER_CONFIG,	/**�û��ֶ�����PLL��Ƶ��*/
}MCLK_CLK_SEL;

/**
 * @brief	ϵͳ�ο�ʱ��Դ����ѡ��
 * @param	IsOsc TURE������ʱ�ӣ�FALSE��XIN�˿���෽��ʱ��
 * @param   Freq  ϵͳ�ο�ʱ�ӵĹ���Ƶ�ʣ�32.768K,1M,2M,...40M,��λHZ
 * @return	ϵͳ����Ƶ��
 * @note	���ʹ��PLLʱ�������Ҫ�ȵ��øú���
 */
void Clock_Config(bool IsOsc, uint32_t Freq);

/**
 * @brief	��ȡϵͳ������ϵͳʱ��Ƶ��
 * @param	��
 * @return	ϵͳ����Ƶ��
 */
uint32_t Clock_SysClockFreqGet(void);
/**
 * @brief  ����ϵͳʱ�ӷ�Ƶϵ��
 * @param  DivVal [0-256]��0�رշ�Ƶ����, 1����Ƶ
 * @return ��
 */
void Clock_SysClkDivSet(uint32_t DivVal);
    
/**
 * @brief  ��ȡϵͳ��Ƶϵ��
 * @param  NONE
 * @return  ϵͳ��Ƶϵ��[1-256]
 */
uint32_t Clock_SysClkDivGet(void);

/**
 * @brief  ����APB���߷�Ƶϵ��������ϵͳ���߷�Ƶ
 * @param  DivVal [2-16]
 * @return ��
 */
void Clock_ApbClkDivSet(uint32_t DivVal);

/**
 * @brief  ��ȡAPB���߷�Ƶϵ��������ϵͳ���߷�Ƶ
 * @param  ��
 * @return  APB���߷�Ƶϵ��[2-12]
 */
uint32_t Clock_ApbClkDivGet(void);
    
/**
 * @brief	��ȡrcƵ��
 * @param	IsReCount �Ƿ��ٴλ�ȡӲ��������ֵ��TRUE���ٴ�����Ӳ����������FALSE����ȡ�ϴμ�¼ֵ��
 * @return  rcƵ��
 */	
uint32_t Clock_RcFreqGet(bool IsReCount);

/**
 * @brief	����pll����Ƶ��,�ȴ�pll lock
 * @param	PllFreq pllƵ��,��λKHz[240000K-480000K]
 * @return  PLL�������  TRUE:���趨Ŀ��Ƶ������
 */
bool Clock_PllLock(uint32_t PllFreq);

/**
 * @brief	����pll����Ƶ��,��������ģʽ���ȴ�pll lock
 * @param	PllFreq pllƵ��,��λKHz[240000K-480000K]
 * @param	K1 [0-15]
 * @param	OS [0-31]
 * @param	NDAC [0-4095]
 * @param	Slope [0-16777216]
 * @return  PLL�������  TRUE:���趨Ŀ��Ƶ������
 */
bool Clock_PllQuicklock(uint32_t PllFreq, uint8_t K1, uint8_t OS, uint32_t NDAC, uint32_t Slope);

/**
 * @brief	����pll����Ƶ��,��������ģʽ(����Ҫ���壬����У׼)
 * @param	PllFreq pllƵ��,��λKHz[240000K-480000K]
 * @param	K1 [0-15]
 * @param	OS [0-31]
 * @param	NDAC [0-4095]
 * @return  ��
 */
void Clock_PllFreeRun(uint32_t PllFreq, uint32_t K1, uint32_t OS, uint32_t NDAC);

/**
 * @brief	����pll����Ƶ��,��������ģʽ(����Ҫ���壬����У׼)��������Դ��Efuse
 * @param	��
 * @return  Efuseֵ������Ч������TRUE
 */
bool Clock_PllFreeRunEfuse(void);

/**
 * @brief	��ȡpllƵ��
 * @param	��
 * @return  pllƵ��
 * @note    �ú���������ҪӦ��ȷ��pll�Ѿ�lock�����������׼
 */
uint32_t Clock_PllFreqGet(void);

/**
 * @brief	pllģ��ر�
 * @param	��
 * @return  ��
 */
void Clock_PllClose(void);

/**
 * @brief	ѡ��ϵͳ����ʱ��
 * @param	ClkMode, 0: RC12Mʱ��; 1:pllʱ��; 
 * @return  �Ƿ�ɹ��л�ϵͳʱ�ӣ�TRUE�������л���FALSE���л�ʱ��ʧ�ܡ�
 * @note    ϵͳʱ�ӹ�����pllʱ��ʱ��Ϊpllʱ�ӵ�4��Ƶ
 */
bool Clock_SysClkSelect(CLK_MODE ClkMode);

/**
 * @brief	Uartģ��ʱ��ѡ��pllʱ�ӻ���RCʱ��
 * @param	ClkMode 0: RCʱ��; 1:pllʱ��
 * @return  ��
 */
void Clock_UARTClkSelect(CLK_MODE ClkMode);

/**
 * @brief	USBģ��ʱ��ѡ��,��Ҫ�ṩ60Mʱ�ӡ�����PLLʱ��7��Ƶ����8��Ƶ
 * @param	ClkMode 0: pll8��Ƶ��pll����480M��; 1:pllʱ��7��Ƶ��pll����420M��
 * @return  ��
 */
void Clock_USBClkSelect(uint32_t ClkMode);

/**
 * @brief	Timer3ģ��ʱ��ѡ��,ϵͳʱ��ʱ�ӻ���RCʱ��
 * @param	ClkMode 0: ϵͳʱ��; 1:RC 12Mʱ��
 * @return  ��
 */
void Clock_Timer3ClkSelect(uint32_t ClkMode);

/**
 * @brief	Timer4ģ��ʱ��ѡ��,ϵͳʱ��ʱ�ӻ���RCʱ��
 * @param	ClkMode 0: ϵͳʱ��; 1:RC 12Mʱ��
 * @return  ��
 */
void Clock_Timer4ClkSelect(uint32_t ClkMode);

/**
 * @brief	SarADCģ��ʱ��ѡ��
 * @param	ClkMode 0: MCLKʱ��; 1:SarADCʱ��
 * @return  ��
 * @note    Mclkʱ�Ӻ�I2s����,һ������MIC����ʱ��
 * 			SarADCʱ��Ϊ����ʱ�ӣ���߿ɵ�30M��������DC��������¡������Clock_SarADCClkSelect()����
 */
void Clock_SarADCClkSelect(uint32_t ClkMode);

/**
 * @brief	SarADCģ��ʱ�ӷ�Ƶ�����ã���ʱ��Ƶ��ѡ��
 * @param	DivNum ��Ƶ��ѡ��[7-63]
 * @return  ��Ƶ�����Ƿ�ɹ���TRUE�����óɹ���FALSE������ʧ��
 * @note    ����Ŀ���Ƶ��Ϊ��PLL_frequency/2(DivNum+1)��PLL_frequencyΪ��ǰPLLƵ��
 */
bool Clock_SarADCClkDivSet(uint32_t DivNum);

/**
 * @brief	ģ��ʱ��ʹ��
 * @param	ClkSel ģ��Դ������CLOCK_MODULE_SWITCHѡ��
 * @return  ��
 */
void Clock_ModuleEnable(CLOCK_MODULE_SWITCH ClkSel);

/**
 * @brief	ģ��ʱ�ӽ���
 * @param	ClkSel ģ��Դ������CLOCK_MODULE_SWITCHѡ��
 * @return  ��
 */
void Clock_ModuleDisable(CLOCK_MODULE_SWITCH ClkSel);

/**
 * @brief	��ģ��ʱ�Ӷ�̬�Զ��رչ���ʹ�ܣ������Ͷ�̬����
 * @param	ClkGateSel ģ��Դ������CLOCK_MODULE_GATE_SWITCHѡ��
 * @return  ��
 */
void Clock_ModuleGateEnable(CLOCK_MODULE_GATE_SWITCH ClkGateSel);

/**
 * @brief	��ģ��ʱ�Ӷ�̬�Զ��رչ��ܽ��ܣ������Ͷ�̬����
 * @param	ClkGateSel ģ��Դ������CLOCK_MODULE_GATE_SWITCHѡ��
 * @return  ��
 */
void Clock_ModuleGateDisable(CLOCK_MODULE_GATE_SWITCH ClkGateSel);

/**
 * @brief	I2S&Mic, Master Clockѡ������
 * @param	ClkSel ʱ��ѡ������
 * @param	DivNum PLL��Ƶ�ȣ�ֻ��ClkSelΪ3ʱ��Ч����8bitΪ�������֣���8bitΪС������
 * @return  ��
 */
void Clock_MclkConfig(MCLK_CLK_SEL ClkSel, uint16_t DivNum);

/**
 * @brief	I2S&Mic, ������΢��
 * @param	Sign  0��������1������
 * @param	Ppm ʱ��΢��������Ϊ0ʱӲ��ʱ����΢�����ܡ�
 * @return  ��
 */
void Clock_MclkAdjust(uint8_t Sign, uint8_t Ppm);

/**
 * @brief	RCCntģ��ʱ��Դѡ��
 * @param	ClkSel  0��32Kʱ�ӣ�1��xMHzʱ��
 * @return  ��
 * @note	����ʹ�ã�������������ѯMV����ʦ
 */
void Clock_RCCntClockSelect(uint32_t ClkSel);

/**
 * @brief	RCCntģ��ʱ��Դѡ��
 * @param	ClkSel  0��32Kʱ�ӣ�1��RC32kʱ��; 2��xMHzʱ��
 * @return  ��
 * @note	����ʹ�ã�������������ѯMV����ʦ
 */
void Clock_LPClockSelect(uint32_t ClkSel);

/**
 * @brief	 �������OSC32K�Ƿ�ͣ����
 *
 * @param
 *   		NONE
 * @return
 *   		NONE
 * @note
 */
void Clock_DetectOSC32KEnable(void);

/**
 * @brief	 �رռ��OSC32K�Ƿ�ͣ����
 *
 * @param
 *   		NONE
 * @return
 *   		NONE
 * @note
 */
void Clock_DetectOSC32KDisable(void);

/**
 * @brief	 �ر� OSC12M����.
 *
 * @param
 *   		NONE
 * @return
 *   		NONE
 * @note
 */
void Clock_OSC12MDisable(void);

/**
 * @brief	 ʹ�ܶ�̬����clock��gate���ܣ��Խ�ʡ����
 *
 * @param
 *   		NONE
 * @return
 *   		NONE
 * @note
 */
void Clock_DynamicClockGateEnable(void);

#ifdef  __cplusplus
}
#endif//__cplusplus

#endif

/**
 * @}
 * @}
 */
 
