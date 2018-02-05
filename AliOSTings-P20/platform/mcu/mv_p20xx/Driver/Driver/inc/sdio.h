/**
 *****************************************************************************
 * @file     sdio.h
 * @author   Owen
 * @version  V1.0.0
 * @date     2017-03-27
 * @brief    declare sdio controller driver interface
 *****************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT 2013 MVSilicon </center></h2>
 */

 /**
 * @addtogroup SDIO
 * @{
 * @defgroup sdio sdio.h
 * @{
 */
 
#ifndef __SDIO_H__
#define __SDIO_H__

#ifdef __cplusplus
extern "C" {
#endif//__cplusplus
	
#define SD_SECTOR_SIZE			512

#define NO_ERR                  (0)
#define SEND_CMD_TIME_OUT_ERR   (1)
/**
 * SDIO BUS MODE
 * In terms of operating supply voltage, two types of SD Memory Cards are defined:
 * SD Memory Cards which supports initialization/identification process with a range of 2.0-3.6v
 * and operating voltage within this range as defined in the CSD register.
 * SDLV Memory Cards - Low Voltage SD Memory Cards, that can be operate in voltage range of
 * 1.6-3.6V. The SDLV Memory Cards will be labeled differently then SD Memory Cards.
 */
#define 	CMD0_GO_IDLE_STATE			0   /**<reset command and sets each card into Idle State regardless of the current card state*/
#define 	CMD1_SEND_OP_COND			1	/**<in idle state, only CMD1,ACMD41 and CMD58 are legal host CMD,response R1*/
#define	CMD2_ALL_SEND_CID				2	/**<to each card to get its unique card identification (CID) number*/
#define	CMD3_SEND_RELATIVE_ADDR			3   /**<asks the card to publish a new relative card address*/
#define	CMD4_SET_DSR					4   /**<programs their DSP registers*/
#define	CMD7_SELECT_DESELECT_CARD		7   /**<used to select one card and put it into thansfer states */
#define	CMD8_SEND_IF_COND				8	/**<get the range of the volatage of the card support*/
#define	CMD9_SEND_CSD					9
#define	CMD10_SEND_CID					10
#define	CMD12_STOP_TRANSMISSION			12
#define	CMD13_SEND_STATUS				13
#define	CMD15_GO_INACTIVE_STATE			15

/**<block oriented read commands (class 2)*/
#define	CMD16_SET_BLOCKLEN				16
#define	CMD17_READ_SINGLE_BLOCK			17
#define	CMD18_READ_MULTIPLE_BLOCK		18

/**<block oriented write commands (class 4)*/
#define	CMD24_WRITE_BLOCK				24
#define	CMD25_WRITE_MULTIPLE_BLOCK		25
#define	CMD27_PROGRAM_CSD				27

/**<block oriented write protection commands (class 6)*/
#define	CMD28_SET_WRITE_PROT			28
#define	CMD29_CLR_WRITE_PROT			29
#define	CMD30_SEND_WRITE_PROT			30

/**<erase commands (class 5)*/
#define	CMD32_ERASE_WR_BLK_START		32
#define	CMD33_ERASE_WR_BLK_END			33
#define	CMD38_ERASE						38

/**<lock card (class 7)*/
#define	CMD42_LOCK_UNLOCK				42

/**<application specific commands (class 8)*/
#define	CMD55_APP_CMD					55
#define	CMD56_GEN_CMD					56

/**<define ACMD index (ACMD6 ~ ACMD51)*/
/**<application specific commands used/reserved by SD memory card*/
#define	ACMD6_SET_BUS_WIDTH				70	//6  + 64
#define	ACMD13_SD_STATUS				77	//13 + 64
#define	ACMD22_SEND_NUM_WR_BLOCKS		86	//22 + 64
#define	ACMD23_SET_WR_BLK_ERASE_COUNT	87	//23 + 64
#define	ACMD41_SD_SEND_OP_COND			105	//41 + 64             /**<The response to ACMD41 is the operation condition register of the card*/
#define	ACMD42_SET_CLR_CARD_DETECT		106	//42 + 64
#define	ACMD51_SEND_SCR					115	//51 + 64

typedef enum
{
	SDIO_RESP_TYPE_R0 = 0,
	SDIO_RESP_TYPE_R1,
	SDIO_RESP_TYPE_R1B,
	SDIO_RESP_TYPE_R2,
	SDIO_RESP_TYPE_R3,
	SDIO_RESP_TYPE_R6,
	SDIO_RESP_TYPE_R7
}SDIO_RESP_TYPE;

typedef enum
{
	SDIO_INT_CMD = 0,
	SDIO_INT_DAT,
}SDIO_INT_TYPE;

extern const uint8_t CmdRespType[128];

/**
 * @brief  sdioʱ�ӷ�Ƶ����
 * @param  0:20MHz,1:10MHz
 * @return NONE
 * @note
 */
void SDIO_ClkSet(uint8_t ClkDiv);

/**
 * @brief  ʹ��sdioʱ��
 * @return NONE
 * @note
 */
void SDIO_ClkEnable();


/**
 * @brief  �ر�sdioʱ��
 * @return NONE
 * @note
 */
void SDIO_ClkDisable();

/**
 * @brief  ��ȡ���ݴ����״̬
 * @param  NONE
 * @return NONE
 * @note
 */
bool SDIO_DataStartStatusGet();

/**
 * @brief  Sdio ��������ʼ��
 * @param  NONE
 * @return NONE
 * @note
 */
bool SDIO_Init(void);

/**
 * @brief  SDIO��������
 * @param  SDIO��Ҫ���͵�������
 * @param  ��������Ĳ���
 * @param  ��ʱʱ��
 * @return ��������ɹ�����NO_ERR�����󷵻�SEND_CMD_TIME_OUT_ERR
 * @note
 */	
bool SDIO_CmdSend(uint8_t Cmd, uint32_t Param, uint16_t TimeOut);

/**
 * @brief  ��ȡ����ķ��ص���Ӧ
 * @param  bufferָ��
 * @param  ��Ӧ����
 * @return NONE
 */
bool SDIO_CmdRespGet(uint8_t* RespBuf, uint8_t RespType);

/**
 * @brief  ����SDIO��������
 * @param  bufferָ��
 * @param  �������ݵĳ���
 * @return NONE
 * @note
 */
void SDIO_RXStart(uint8_t *Buf,uint32_t Size);

/**
 * @brief  ��ȡ�����Ƿ�������
 * @param  NONE
 * @return 1:��ɣ�0δ���
 * @note
 */
bool SDIO_RXIsDone(void);

/**
 * @brief  ���������ɱ�־
 * @param  NONE
 * @return NONE
 * @note
 */
void SDIO_RXDoneFlagClear(void);


/**
 * @brief  ֹͣ���ݽ���
 * @param  NONE
 * @return NONE
 * @note
 */
void SDIO_RXEnd(void);


/**
 * @brief  �������ݷ���
 * @param  bufferָ��
 * @param  �������ݵĳ���
 * @return NONE
 * @note
 */
void SDIO_TXStart(uint8_t *Buf,uint32_t Size);


/**
 * @brief  ��ȡ�����Ƿ������
 * @param  NONE
 * @return 1:��� 0:δ���
 * @note
 */
bool SDIO_TXIsDone(void);

/**
 * @brief   ���������ɱ�־
 * @param  NONE
 * @return NONE
 * @note
 */
void SDIO_TXDoneFlagClear(void);

/**
 * @brief  ֹͣ���ݷ���
 * @param  NONE
 * @return NONE
 * @note
 */
void SDIO_TXEnd(void);

/**
 * @brief  ��ȡSDIO�Ƿ�busy
 * @param  NONE
 * @return 0 is busy, 1 is idle
 * @note
 */
bool SDIO_IsDataLineBusy(void);


/**
 * @brief  ʹ��SDIO�ж�
 * @param  �ж����� 	SDIO_INT_CMD or SDIO_INT_DAT
 * @return 
 * @note
 */
void SDIO_InterruptEnable(SDIO_INT_TYPE IntType);

/**
 * @brief  �ر�SDIO�ж�
 * @param  �ж����� 	SDIO_INT_CMD or SDIO_INT_DAT
 * @return 
 * @note
 */
void SDIO_InterruptDisable(SDIO_INT_TYPE IntType);

/**
 * @brief  ��ȡSDIO�жϱ�־
 * @param  �ж����� 	SDIO_INT_CMD or SDIO_INT_DAT
 * @return �жϱ�־
 * @note
 */
bool SDIO_InterruptFlagGet(SDIO_INT_TYPE IntType);

/**
 * @brief  ���SDIO�жϱ�־
 * @param  �ж����� SDIO_INT_CMD or SDIO_INT_DAT
 * @return NONE
 * @note
 */
void SDIO_InterruptFlagClear(SDIO_INT_TYPE IntType);

#ifdef  __cplusplus
}
#endif//__cplusplus

#endif //__SDIO_H__

/**
 * @}
 * @}
 */

