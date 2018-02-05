/**
 *******************************************************************************
 * @file    dma.h
 * @author  lilu
 * @version V1.0.0
 * @date    2014/10/21
 * @brief	dma module drever interface
 *
 * Changelog:
 *			2014-10-21	create by lilu
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
 * @addtogroup DMA
 * @{
 * @defgroup dma dma.h
 * @{
 */
 
#ifndef __DMA_H__
#define __DMA_H__

typedef void (*INT_FUNC)(void);

typedef enum
{
	DMA_STREAM_INVALID = -127,
	DMA_DIRECTION_INVALID,
	DMA_AINCR_INVALID,
	DMA_MODE_INVALID,
	DMA_CBT_LEN_INVALID,
	DMA_CHANNEL_UNALLOCATED,
	DMA_NOT_ENOUGH_SPACE,
	DMA_UNALIGNED_ADDRESS,
	DMA_INT_TYPE_INVALID,
	DMA_OK = -1
}DMA_ERROR;

typedef enum
{
	PERIPHERAL_ID_SPIS_RX = 0,	//0
	PERIPHERAL_ID_SPIS_TX,		//1
	PERIPHERAL_ID_SD_RX,		//2
	PERIPHERAL_ID_SD_TX,		//3
	PERIPHERAL_ID_SPIM0_RX,		//4
	PERIPHERAL_ID_SPIM0_TX,		//5
	PERIPHERAL_ID_SPIM1_RX,		//6
	PERIPHERAL_ID_SPIM1_TX,		//7
	PERIPHERAL_ID_UART0_RX,		//8
	PERIPHERAL_ID_UART1_RX,		//9
	PERIPHERAL_ID_UART2_RX,		//10
	PERIPHERAL_ID_TIMER3,		//11
	PERIPHERAL_ID_TIMER4,		//12
	PERIPHERAL_ID_I2S_TX,		//13
	PERIPHERAL_ID_I2S_RX,		//14
	PERIPHERAL_ID_SARADC,		//15
	PERIPHERAL_ID_UART0_TX,		//16
	PERIPHERAL_ID_UART1_TX,		//17
	PERIPHERAL_ID_UART2_TX,		//18
	PERIPHERAL_ID_TIMER5,		//19
	PERIPHERAL_ID_TIMER6,		//20
	PERIPHERAL_ID_TIMER7,		//21
	PERIPHERAL_ID_TIMER8,		//22
	PERIPHERAL_ID_DPA_SRC,		//23
	PERIPHERAL_ID_DPA_DST,		//24
	PERIPHERAL_ID_DPA_DSTRD,   //25
	PERIPHERAL_ID_SOFTWARE,		//26

}DMA_PERIPHERAL_ID;

typedef enum
{
	DMA_BLOCK_MODE = 0,
	DMA_CIRCULAR_MODE
}DMA_MODE;

typedef enum
{
	DMA_CHANNEL_DIR_PERI2MEM = 0,
	DMA_CHANNEL_DIR_MEM2PERI,
	DMA_CHANNEL_DIR_MEM2MEM
}DMA_CHANNEL_DIR;

typedef enum
{
	DMA_PRIORITY_LEVEL_LOW = 0,
	DMA_PRIORITY_LEVEL_HIGH
}DMA_PRIORITY_LEVEL;

typedef enum
{
	DMA_SRC_DWIDTH_BYTE = 0,
	DMA_SRC_DWIDTH_HALF_WORD,
	DMA_SRC_DWIDTH_WORD
}DMA_SRC_DWIDTH;

typedef enum
{
	DMA_DST_DWIDTH_BYTE = 0,
	DMA_DST_DWIDTH_HALF_WORD,
	DMA_DST_DWIDTH_WORD
}DMA_DST_DWIDTH;

typedef enum
{
	DMA_SRC_AINCR_NO = 0,
	DMA_SRC_AINCR_SRC_WIDTH
}DMA_SRC_AINCR;

typedef enum
{
	DMA_DST_AINCR_NO = 0,
	DMA_DST_AINCR_DST_WIDTH
}DMA_DST_AINCR;

typedef struct
{
	DMA_CHANNEL_DIR		Dir;
	DMA_MODE			Mode;
	uint16_t			ThresholdLen;//����ѭ��ģʽ����Ч
	DMA_SRC_DWIDTH		SrcDataWidth;
	DMA_DST_DWIDTH		DstDataWidth;
	DMA_SRC_AINCR		SrcAddrIncremental;
	DMA_DST_AINCR		DstAddrIncremental;
	uint32_t			SrcAddress;
	uint32_t			DstAddress;	
	uint16_t			BufferLen;
} DMA_CONFIG;

typedef enum
{
	DMA_DONE_INT = 0,
	DMA_THRESHOLD_INT,
	DMA_ERROR_INT
}DMA_INT_TYPE;

//------------------------------------------------------����Ϊͨ������API---------------------------------------------------------
/**
 * @brief	����DMA��ͨ�������
 * @param	PeripheralID		����ID�����DMA_PERIPHERAL_ID
 * @param	DMAChannelMap		DMAͨ�������
 *
 * @return
 *   		NONE
 * @note 
 */
void DMA_ChannelAllocTableSet(uint8_t* DMAChannelMap);

/**
 * @brief	ʹ��DMAͨ������������
 * @param	PeripheralID	����ID�����DMA_PERIPHERAL_ID
 * @param	En				1:����    0:�ر�
 *
 * @return
 *   		DMA_ERROR
 * @note
 */
DMA_ERROR DMA_ChannelEnable(uint8_t PeripheralID, bool En);

/**
 * @brief	����ָ��ͨ���жϵĻص�����
 * @param	PeripheralID		����ID�����DMA_PERIPHERAL_ID
 * @param	IntType				�ж����ͣ����DMA_INT_TYPE
 * @param	CallBack			�жϻص�����
 *								 
 * @return
 *   		DMA_ERROR
 * @note
 */
DMA_ERROR DMA_InterruptFunSet(uint8_t PeripheralID, DMA_INT_TYPE IntType, INT_FUNC CallBack);

/**
 * @brief	������ر�ָ��ͨ�����ж�
 * @param	PeripheralID		����ID�����DMA_PERIPHERAL_ID
 * @param	IntType				�ж����ͣ����DMA_INT_TYPE
 * @param	En					1:����    0:�ر�	
 *								 
 * @return
 *   		DMA_ERROR
 * @note
 */
DMA_ERROR DMA_InterruptEnable(uint8_t PeripheralID, DMA_INT_TYPE IntType, bool En);

/**
 * @brief	��ȡָ��ͨ�����жϱ�־
 * @param	PeripheralID		����ID�����DMA_PERIPHERAL_ID
 * @param	IntType				�ж����ͣ����DMA_INT_TYPE
 *								 
 * @return
 *   		�����жϱ�־��DMA_ERROR
 * @note	�жϱ�־�ڲ������жϵ������Ҳ����λ
 */
int32_t DMA_InterruptFlagGet(uint8_t PeripheralID, DMA_INT_TYPE IntType);

/**
 * @brief	���ָ��ͨ�����жϱ�־
 * @param	PeripheralID		����ID�����DMA_PERIPHERAL_ID
 * @param	IntType				�ж����ͣ����DMA_INT_TYPE
 *								 
 * @return
 *   		DMA_ERROR
 * @note	�жϱ�־�ڲ������жϵ������Ҳ����λ
 */
DMA_ERROR DMA_InterruptFlagClear(uint8_t PeripheralID, DMA_INT_TYPE IntType);

//------------------------------------------------------����ΪBlockģʽר��API-------------------------------------------------------
/**
 * @brief	��������IDָ����DMAͨ��ΪBlockģʽ
 * @param	PeripheralID		����ID�����DMA_PERIPHERAL_ID
 *
 * @return
 *   		DMA_ERROR
 * @note	
 */
DMA_ERROR DMA_BlockConfig(uint8_t PeripheralID);

/**
 * @brief	����blockģʽ�Ĵ���buffer
 * @param	PeripheralID		����ID�����DMA_PERIPHERAL_ID
 * @param	Ptr					����buffer�׵�ַ
 * @param	Len					����buffer����
 *
 * @return	
 *			DMA_ERROR
 * @note
*/
DMA_ERROR DMA_BlockBufSet(uint8_t PeripheralID, void* Ptr, uint16_t Len);

/**
 * @brief	��ȡblockģʽ�Ĵ���buffer���Ѿ���������ݳ���
 * @param	PeripheralID		����ID�����DMA_PERIPHERAL_ID
 *
 * @return	
 *			�Ѿ���������ݳ��Ȼ�DMA_ERROR
 * @note
*/
int32_t DMA_BlockDoneLenGet(uint8_t PeripheralID);

//-----------------------------------------------------����ΪCircularģʽר��API----------------------------------------------------
/**
 * @brief	��������IDָ����DMAͨ��ΪCircularģʽ
 * @param	PeripheralID		����ID�����DMA_PERIPHERAL_ID
 * @param	CircularThreshold	ѭ��FIFOˮλ����󳤶�65535����λByte (����������ѭ��ģʽ����Ч)
 * @param	CircularFifoAddr	ѭ��FIFO�׵�ַ �����ַ�����룬�᷵��DMA_UNALIGNED_ADDRESS��(����������ѭ��ģʽ����Ч)
 * @param	CircularFifoLen		ѭ��FIFO���ȣ���󳤶�65535����λByte (����������ѭ��ģʽ����Ч)
 *
 * @return
 *   		DMA_ERROR
 * @note	
 */
DMA_ERROR DMA_CircularConfig(uint8_t PeripheralID, uint16_t CircularThreshold, void* CircularFifoAddr, uint16_t CircularFifoLen);

/**
 * @brief	��ѭ��FIFO����������
 * @param	PeripheralID	����ID�����DMA_PERIPHERAL_ID
 * @param	Ptr				�������ݵ��׵�ַ
 * @param	Len				�������ݳ��ȣ���λByte
 *
 * @return
 *   		�������������ʵ�ʳ���
 * @note	ѭ��ģʽ�£�ʣ��ռ䳤��С��Len����ʱ���Ὣbuffer����������ʵ������ĳ���
 */
int32_t DMA_CircularDataPut(uint8_t PeripheralID, void* Ptr, uint16_t Len);

/**
 * @brief	��ѭ��FIFO��ȡ������
 * @param	PeripheralID	����ID�����DMA_PERIPHERAL_ID
 * @param	Ptr				ȡ�����ݴ�ŵ��׵�ַ
 * @param	Len				����ȡ�����ݵ���󳤶ȣ���λByte
 *
 * @return
 *   		����ȡ�����ݵ�ʵ�ʳ���
 * @note	ѭ��ģʽ�£�ʣ�����ݳ���С��Lenʱ���Ὣbufferȡ�գ�����ʵ������ĳ���
 */
int32_t DMA_CircularDataGet(uint8_t PeripheralID, void* Ptr, uint16_t MaxLen);

/**
 * @brief	����ѭ��FIFO��ˮλֵ�����������������ˮλʱ��λDMA_THRESHOLD_FLAG
 * @param	PeripheralID	����ID�����DMA_PERIPHERAL_ID
 * @param	Len				ˮλֵ����λByte��
 *
 * @return
 *   		DMA_ERROR
 * @note	
 */
DMA_ERROR DMA_CircularThresholdLenSet(uint8_t PeripheralID, uint16_t Len);

/**
 * @brief	��ȡѭ��FIFO��ˮλֵ�����������������ˮλʱ��λDMA_THRESHOLD_FLAG
 * @param	PeripheralID	����ID�����DMA_PERIPHERAL_ID
 *
 * @return
 *   		����ˮλֵ��DMA_ERROR
 * @note	
 */
int32_t DMA_CircularThresholdLenGet(uint8_t PeripheralID);

/**
 * @brief	��ȡѭ��FIFO�е����ݳ��ȣ���λByte
 * @param	PeripheralID		����ID�����DMA_PERIPHERAL_ID
 *
 * @return
 *    		����buffer�е����ݳ���(��λByte) �� DMAC_ERROR
 * @note
 */
int32_t DMA_CircularDataLenGet(uint8_t PeripheralID);

/**
 * @brief	��ȡѭ��FIFO�е�ʣ��ռ䳤�ȣ���λByte
 * @param	PeripheralID		����ID�����DMA_PERIPHERAL_ID
 *
 * @return
 *   		����buffer��ʣ��ռ䳤�Ȼ� DMAC_ERROR
 * @note
 */
int32_t DMA_CircularSpaceLenGet(uint8_t PeripheralID);

/**
 * @brief	���ѭ��FIFO
 * @param	PeripheralID	����ID�����DMA_PERIPHERAL_ID
 *
 * @return
 *   		����DMA_ERROR
 * @note	ѭ��FIFO������ǽ���дָ��ָ��ͬһ��ַ
 */
DMA_ERROR DMA_CircularFIFOClear(uint8_t PeripheralID);

/**
 * @brief	��ȡѭ��FIFO��дָ���λ�ã���λByte
 * @param	PeripheralID		����ID�����DMA_PERIPHERAL_ID
 *
 * @return
 *    		����ѭ��FIFO��дָ��λ�û�DMA_ERROR
 * @note
 */
int32_t DMA_CircularWritePtrGet(uint8_t PeripheralID);

/**
 * @brief	��ȡѭ��FIFO�Ķ�ָ���λ�ã���λByte
 * @param	PeripheralID		����ID�����DMA_PERIPHERAL_ID
 *
 * @return
 *    		����ѭ��FIFO�ж�ָ��λ�û�DMA_ERROR
 * @note
 */
int32_t DMA_CircularReadPtrGet(uint8_t PeripheralID);

/**
 * @brief	����ѭ��FIFO��дָ���λ�ã���λByte
 * @param	PeripheralID		����ID�����DMA_PERIPHERAL_ID
 *
 * @return
 *    		DMA_ERROR
 * @note
 */
DMA_ERROR DMA_CircularWritePtrSet(uint8_t PeripheralID, uint16_t Ptr);

/**
 * @brief	����ѭ��FIFO��дָ���λ�ã���λByte
 * @param	PeripheralID		����ID�����DMA_PERIPHERAL_ID
 *
 * @return
 *    		DMA_ERROR
 * @note
 */
DMA_ERROR DMA_CircularReadPtrSet(uint8_t PeripheralID, uint16_t Ptr);

//--------------------------------------------------------����ΪTimerר��API-------------------------------------------------------
/**
 * @brief	��������IDָ����DMAͨ��������һ����޶�ΪTIMER��
 * @param	PeripheralID		����ID�����DMA_PERIPHERAL_ID
 * @param	DMA_CONFIG			DMA���ýṹ�壬���DMA_CONFIG �����ַ�����룬�᷵��DMA_UNALIGNED_ADDRESS��
 *
 * @return
 *   		DMA_ERROR
 * @note
 */
DMA_ERROR DMA_TimerConfig(uint8_t PeripheralID, DMA_CONFIG* Config);

#endif

/**
 * @}
 * @}
 */
