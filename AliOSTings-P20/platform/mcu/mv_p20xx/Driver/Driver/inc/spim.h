/**
  *****************************************************************************
  * @file:			spim.h
  * @author			Lilu
  * @version		V1.0.0
  * @data			2014-11-20
  * @Brief			SPI Master driver interface
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
 * @addtogroup SPIM
 * @{
 * @defgroup spim spim.h
 * @{
 */
 
 
#ifndef __SPIM_H__
#define __SPIM_H__

#ifdef __cplusplus
extern "C" {
#endif//__cplusplus


#define	SPIM_CLK_DIV_30M	0x0			/**< SPI master clock Div 30MHz*/
#define	SPIM_CLK_DIV_15M	0x1			/**< SPI master clock Div 15MHz*/
#define	SPIM_CLK_DIV_7M5	0x2			/**< SPI master clock Div 7.5MHz*/
#define	SPIM_CLK_DIV_3M7        0x3			/**< SPI master clock Div 3.75MHz*/
#define	SPIM_CLK_DIV_1M8	0x4			/**< SPI master clock Div 1.875MHz*/
#define	SPIM_CLK_DIV_937K	0x5			/**< SPI master clock Div 937.5KHz*/
#define	SPIM_CLK_DIV_468K	0x6			/**< SPI master clock Div 438.75KHz*/

/**
 * err code define
 */
typedef enum _SPI_MASTER_ERR_CODE
{
    ERR_SPIM_TIME_OUT = -255,			/**<function execute time out*/
    ERR_SPIM_DATALEN_OUT_OF_RANGE,		/**<data len is out of range < 0*/
    SPIM_NONE_ERR = 0,                  /**<no error*/
} SPI_MASTER_ERR_CODE;


/**
 * @brief
 *		��ʼ��SPIMģ��
 * @param	Mode
 *				0 - CPOL = 0 & CPHA = 0, 1 - CPOL = 0 & CPHA = 1,
 *				2 - CPOL = 1 & CPHA = 0, 3 - CPOL = 1, CPHA = 1
 * @param	ClkDiv 	��Ƶϵ��:0 ~ 11
 * 				spi clock = system clock / (2 EXP (ClkDivExp)).
 * @return
 *		��
 * @note
 */
bool SPIM0_Init(uint8_t Mode, uint8_t ClkDiv);

/**
 * @brief
 *		��ʼ��SPIMģ��
 * @param	Mode
 *				0 - CPOL = 0 & CPHA = 0, 1 - CPOL = 0 & CPHA = 1,
 *				2 - CPOL = 1 & CPHA = 0, 3 - CPOL = 1, CPHA = 1
 * @param	ClkDiv 	��Ƶϵ��:0 ~ 11
 * 				spi clock = system clock / (2 EXP (ClkDivExp)).
 * @return
 *		��
 * @note
 */
bool SPIM1_Init(uint8_t Mode, uint8_t ClkDiv);

//--------------------------------MCU MODE-------------------------------------
/**
 * @brief
 *		MCUģʽ��������
 * @param	SendBuf		���������׵�ַ
 * @param	Length		�������ݳ��ȣ���λ��Byte��
 * @return
 *		���ش����
 * @note
 */
SPI_MASTER_ERR_CODE SPIM0_SendNBytes(uint8_t* SendBuf, uint32_t Length);

/**
 * @brief
 *		MCUģʽ��������
 * @param	SendBuf		���������׵�ַ
 * @param	Length		�������ݳ��ȣ���λ��Byte��
 * @return
 *		���ش����
 * @note
 */
SPI_MASTER_ERR_CODE SPIM1_SendNBytes(uint8_t* SendBuf, uint32_t Length);

/**
 * @brief
 *		MCUģʽ��������
 * @param	RecvBuf		���������׵�ַ
 * @param	Length		�������ݳ��ȣ���λ��Byte��
 * @return
 *		���ش����
 * @note
 */
SPI_MASTER_ERR_CODE SPIM0_RecvNBytes(uint8_t* RecvBuf, uint32_t Length);

/**
 * @brief
 *		MCUģʽ��������
 * @param	RecvBuf		���������׵�ַ
 * @param	Length		�������ݳ��ȣ���λ��Byte��
 * @return
 *		���ش����
 * @note
 */
SPI_MASTER_ERR_CODE SPIM1_RecvNBytes(uint8_t* RecvBuf, uint32_t Length);

/**
 * @brief
 *		MCUģʽ����1�ֽ�����
 * @param	SendByte  ���ֽ�����
 * @return
 *		��
 */
void SPIM0_SendByte(uint8_t SendByte);

/**
 * @brief
 *		MCUģʽ����1�ֽ�����
 * @param	SendByte  ���ֽ�����
 * @return
 *		��
 */
void SPIM1_SendByte(uint8_t SendByte);

/**
 * @brief
 *		MCUģʽ����1�ֽ�����
 * @param	��
 * @return
 *		���ؽ��յĵ��ֽ�����
 */
uint8_t SPIM0_RecvByte(void);

/**
 * @brief
 *		MCUģʽ����1�ֽ�����
 * @param	��
 * @return
 *		���ؽ��յĵ��ֽ�����
 */
uint8_t SPIM1_RecvByte(void);

//--------------------------------DMA MODE-------------------------------------
/**
 * @brief
 *		DMAģʽ��������
 * @param	SendBuf	���ݻ������׵�ַ
 * @param	Length	���ݳ��ȣ���λ��Byte�������65536 byte
 * @return
 *		���ش����
 * @Note
 */
SPI_MASTER_ERR_CODE SPIM0_DMA_SendData(uint8_t* SendBuf, uint32_t Length);

/**
 * @brief
 *		DMAģʽ��������
 * @param	SendBuf	���ݻ������׵�ַ
 * @param	Length	���ݳ��ȣ���λ��Byte�������65536 byte
 * @return
 *		���ش����
 * @Note
 */
SPI_MASTER_ERR_CODE SPIM1_DMA_SendData(uint8_t* SendBuf, uint32_t Length);

/**
 * @brief
 *		DMAģʽ��������
 * @param	RecvBuf �����׵�ַ
 * @param	Length	���ݳ��ȣ���λ��Byte�������65536 byte
 * @return
 *		���ش����
 * @note
 */
SPI_MASTER_ERR_CODE SPIM0_DMA_RecvData(uint8_t* RecvBuf, uint32_t Length);

/**
 * @brief
 *		DMAģʽ��������
 * @param	RecvBuf �����׵�ַ
 * @param	Length	���ݳ��ȣ���λ��Byte�������65536 byte
 * @return
 *		���ش����
 * @note
 */
SPI_MASTER_ERR_CODE SPIM1_DMA_RecvData(uint8_t* RecvBuf, uint32_t Length);

/**
 * @brief
 *		����DMAģʽ�������ݣ�������
 * @param	SendBuf	���ݻ������׵�ַ
 * @param	Length	���ݳ��ȣ���λ��Byte�������65536 byte
 * @return
 *		��
 * @Note SPIM�жϱ�־��λ��־����������ɣ���ʹ�ò�ѯ���жϷ�ʽ
 */
void SPIM0_DMA_StartSendData(uint8_t* SendBuf, uint32_t Length);

/**
 * @brief
 *		����DMAģʽ�������ݣ�������
 * @param	SendBuf	���ݻ������׵�ַ
 * @param	Length	���ݳ��ȣ���λ��Byte�������65536 byte
 * @return
 *		��
 * @Note SPIM�жϱ�־��λ��־����������ɣ���ʹ�ò�ѯ���жϷ�ʽ
 */
void SPIM1_DMA_StartSendData(uint8_t* SendBuf, uint32_t Length);

/**
 * @brief
 *		����DMAģʽ�������ݣ�������
 * @param	RecvBuf �����׵�ַ
 * @param	Length	���ݳ��ȣ���λ��Byte�������65536 byte
 * @return
 *		��
 * @note DMA D��־��λ��־����������ɣ���ʹ�ò�ѯ���жϷ�ʽ
 */
void SPIM0_DMA_StartRecvData(uint8_t* RecvBuf, uint32_t Length);

/**
 * @brief
 *		����DMAģʽ�������ݣ�������
 * @param	RecvBuf �����׵�ַ
 * @param	Length	���ݳ��ȣ���λ��Byte�������65536 byte
 * @return
 *		��
 * @note DMA D��־��λ��־����������ɣ���ʹ�ò�ѯ���жϷ�ʽ
 */
void SPIM1_DMA_StartRecvData(uint8_t* RecvBuf, uint32_t Length);


/**
 * @brief
 *		�ж�ʹ��
 * @param	��
 * @return
 *		��
 */
void SPIM0_IntEn();

/**
 * @brief
 *		�ж�ʹ��
 * @param	��
 * @return
 *		��
 */
void SPIM1_IntEn();

/**
 * @brief
 *		��ȡ�жϱ�־
 * @param	��
 * @return
 *		�����жϱ�־
 */
bool SPIM0_GetIntFlag();

/**
 * @brief
 *		��ȡ�жϱ�־
 * @param	��
 * @return
 *		�����жϱ�־
 */
bool SPIM1_GetIntFlag();

/**
 * @brief
 *		����жϱ�־
 * @param	��
 * @return
 *		��
 */
void SPIM0_ClrIntFlag();

/**
 * @brief
 *		����жϱ�־
 * @param	��
 * @return
 *		��
 */
void SPIM1_ClrIntFlag();

/**
 * @brief
 *		��ȡ���ٱ�־
 * @param	��
 * @return
 *		1-����
 *      0-�޹���
 */
bool SPI0_Get_OverWr();

/**
 * @brief
 *		��ȡ���ٱ�־
 * @param	��
 * @return
 *		1-����
 *      0-�޹���
 */
bool SPI1_Get_OverWr();

/**
 * @brief
 *		��ȡ���ٱ�־
 * @param	��
 * @return
 *		��
 */
void SPI0_Set_OverWr();

/**
 * @brief
 *		��ȡ���ٱ�־
 * @param	��
 * @return
 *		��
 */
void SPI1_Set_OverWr();
#ifdef __cplusplus
}
#endif//__cplusplus

#endif

/**
 * @}
 * @}
 */
