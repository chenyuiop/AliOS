/**
  *****************************************************************************
  * @file:			spis.h
  * @author			Lilu
  * @version		V1.0.0
  * @data			18-June-2013
  * @Brief			SPI Slave driver header file.
  * @note			For sdio and spi can't access memory simultaneously
  ******************************************************************************
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, MVSILICON SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
  * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2013 MVSilicon </center></h2>
  */
  
/**
 * @addtogroup SPIS
 * @{
 * @defgroup spis spis.h
 * @{
 */
#ifndef __SPIS_H__
#define __SPIS_H__

#ifdef __cplusplus
extern "C" {
#endif//__cplusplus
	
/**
 * @brief
 *    ��ʼ��SPISģ��
 * @param	ClkMode		
 *					0 - CPOL = 0 & CPHA = 0, 1 - CPOL = 0 & CPHA = 1,
 *					2 - CPOL = 1 & CPHA = 0, 3 - CPOL = 1 & CPHA = 1
 * @return
 *   ��
 * @note
 */
void SPIS_Init(uint8_t ClkMode);




//--------------------------------MCU MODE-------------------------------------
/**
 * @brief
 *    MCU��ʽ�������ݣ���TimeOutʱ���ڵȴ�������ɣ���ʱ����ʵ�ʷ������ݸ�������λByte
 * @param	SendBuf			�����׵�ַ
 * @param	BufLen			�������ݳ���
 * @param	TimeOut			��ʱʱ��
 *
 * @return
 *   ����ʵ�ʷ������ݳ���
 * @note
 */
uint32_t SPIS_Send(uint8_t* SendBuf, uint32_t BufLen, uint32_t TimeOut);

/**
 * @brief
 *    MCU��ʽ�������ݣ���TimeOutʱ���ڵȴ�������ɣ���ʱ����ʵ�ʽ������ݸ�������λByte
 * @param	SendBuf			�����׵�ַ
 * @param	BufLen			�������ݳ���
 * @param	TimeOut			��ʱʱ��
 *
 * @return
 *   ����ʵ�ʽ������ݳ���
 * @note
 */
uint32_t SPIS_Recv(uint8_t* RecvBuf, uint32_t BufLen, uint32_t TimeOut);

/**
 * @brief
 *    MCU��ʽ����1�ֽ�����
 * @param	SendBuf			���ֽ�����
 *
 * @return
 *   ��
 * @note
 */
void SPIS_SendByte(uint8_t SendByte);

/**
 * @brief
 *    MCU��ʽ����1�ֽ�����
 * @param	SendBuf			���ֽ�����
 *
 * @return
 *   ��
 * @note
 */
uint8_t SPIS_RecvByte(void);

//--------------------------------DMA MODE-------------------------------------
/**
 * @brief
 *    ��ʼ��SPIS DMA����
 * @param	RxBufferAddr  ���ջ������׵�ַ		
 * @param	RxBufferLen   ���ջ���������				
 * @param	TxBufferAddr  ���ͻ������׵�ַ
 * @param   TxBufferLen   ���ͻ���������
 * @return
 *   TRUE   �ɹ���  FALSE ʧ��
 * @note
 */
bool SPIS_DMA_Init(void* RxBufferAddr, uint16_t RxBufferLen, void* TxBufferAddr, uint16_t TxBufferLen);


/**
 * @brief
 *    DMA��ʽ�������ݣ���FIFO���������ݣ���TimeOutʱ���ڵȴ�������ɣ���ʱ����ʵ�ʷ������ݸ�������λByte
 * @param	SendBuf			�����׵�ַ
 * @param	BufLen			�������ݳ���
 * @param	TimeOut			��ʱʱ��
 *
 * @return
 *   ����ʵ�ʷ������ݳ���
 * @note
 */
uint32_t SPIS_DMA_Send(uint8_t* SendBuf, uint32_t BufLen, uint32_t TimeOut);

/**
 * @brief
 *    DMA��ʽ�������ݣ���FIFO��ȡ�����ݣ���TimeOutʱ���ڵȴ�������ɣ���ʱ����ʵ�ʽ������ݸ�������λByte
 * @param	SendBuf			�����׵�ַ
 * @param	BufLen			�������ݳ���
 * @param	TimeOut			��ʱʱ��
 *
 * @return
 *   ����ʵ�ʽ������ݳ���
 * @note
 */
uint32_t SPIS_DMA_Recv(uint8_t* RecvBuf, uint32_t BufLen, uint32_t TimeOut);

/**
 * @brief
 *    �����ж�ʹ��
 * @param	En			1�������жϣ�0���ر��ж�
 *
 * @return
 *   ��
 * @note
 *	 ÿ����һ��Byte����һ���ж�
 */
void SPIS_RxIntEn(bool En);

/**
 * @brief
 *    ��ȡ�����жϱ�־
 * @param	
 *
 * @return
 *   ���ؽ����жϱ�־
 * @note
 *	 ÿ����һ��Byte����һ���ж�
 */
bool SPIS_GetRxIntFlag(void);

/**
 * @brief
 *   ��������жϱ�־
 * @param	
 *
 * @return
 *   ��
 * @note
 *	 ÿ����һ��Byte����һ���ж�
 */
void SPIS_ClrRxIntFlag(void);

/**
 * @brief
 *    ��ȡ���������־
 * @param	
 *
 * @return
 *   ���ؽ��������־
 * @note
 *	 SPIS �ڲ�4Byte Ӳ��Rx FIFO�����ٴ��յ�һ��Byte������������־
 */
bool SPIS_GetRxOverrunFlag(void);

/**
 * @brief
 *    ������������־
 * @param	
 *
 * @return
 *   ��
 * @note
 *	 SPIS �ڲ�4Byte Ӳ��Rx FIFO�����ٴ��յ�һ��Byte������������־
 */
void SPIS_ClrRxOverrunFlag(void);


/**
 * @brief
 *    DMA��ʽ��������ģʽ����
 * @param	1--ʹ��DMA�������ݣ�
 *          0--��ʹ��DMA��������
 * @return
 *   ��
 * @note
 *	 
 */
void SPIS_RX_DMA_MODE_SET(bool EN);

/**
 * @brief
 *    LSB/MSB��������
 * @param	1--LSB���д���
 *          0--MSB���д���
 * @return
 *   ��
 * @note
 *   ��SPIS_Init()֮�����ã�����������Ĭ��MSB���д���
 */
void SPIS_LSBFirst_SET(bool EN);

/**
 * @brief
 *   ��ս��ջ�����FIFO
 * @param
 *   ��
 * @return
 *   ��
 * @note
 *
 */
void SPIS_ClrRxFIFO(void);
/**
 * @brief
 *   ��շ��ͻ�����FIFO
 * @param
 *   ��
 * @return
 *   ��
 * @note
 *
 */
void SPIS_ClrTxFIFO(void);



#ifdef  __cplusplus
}
#endif//__cplusplus

#endif

/**
 * @}
 * @}
 */

