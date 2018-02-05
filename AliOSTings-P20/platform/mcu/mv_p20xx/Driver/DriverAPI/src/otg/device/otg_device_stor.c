/**
 *****************************************************************************
 * @file     device_stor.c
 * @author   Owen
 * @version  V1.0.0
 * @date     7-September-2015
 * @brief    device mass-storage module driver interface
 *****************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT 2013 MVSilicon </center></h2>
 */

#include <string.h>
#include "type.h"
#include "otg_device_hcd.h"
#include "sd_card.h"
#include "timeout.h"
#include "debug.h"
#include "delay.h"
//#include "otg_detect.h"
#include "otg_device_hcd.h"
#include "otg_device_stor.h"
#include "otg_device_standard_request.h"
#include "sd_card.h"
#include "sdio.h"


// SCSI opcodes
#define TEST_UNIT_READY			0x00
#define REQUEST_SENSE				0x03
#define READ_6						0x08
#define WRITE_6					0x0A
#define SEEK_6						0x0B
#define INQUIRY					0x12
#define MODE_SELECT				0x15
#define MODE_SENSE					0x1A
#define START_STOP_UNIT			0x1B
#define ALLOW_MEDIUM_REMOVAL		0x1E
#define	READ_FORMAT_CAPACITY	0x23
#define READ_CAPACITY				0x25
#define READ_10					0x28
#define WRITE_10					0x2A
#define SEEK_10					0x2B
#define VERYFY						0x2F
#define MODE_SELECT_10				0x55
#define MODE_SENSE_10				0x5A
#define READ_12					0xA8
#define WRITE_12					0xAA
#define READ_DISC_STRUCTURE		0xAD
#define DVD_MACHANISM_STATUS  		0xBD
#define REPORT_KEY			  		0xA4
#define SEND_KEY			  		0xA3
#define READ_TOC			  		0x43
#define READ_MSF			  		0xB9



#define READER_UNREADY				0 // δ����
#define READER_INIT				1 // ��ʼ��
#define READER_READY				2 // ����
#define READER_READ				3 // ������
#define READER_WIRTE				4 // д����
#define READER_INQUIRY				5 // ��ѯ��������Ϣ
#define READER_READ_FORMAT_CAPACITY 6 // ��ѯ��ʽ������
#define READER_READ_CAPACITY		7 // ��ѯ��������
#define READER_NOT_ALLOW_REMOVAL	8 // ������ɾ���豸
#define READER_ALLOW_REMOVAL		9 // ����ɾ���豸


#define	DEVICE_STOR_BLOCK_SIZE	512
extern int kprintf(const char *fmt, ...);
#define	OTG_DBG(format, ...)		kprintf(format, ##__VA_ARGS__)



extern void OTG_DeviceRequestProcess(void);

uint8_t    gInquiryData[] =
{
	0x00, 		//Direct Access Device
	0x80, 		//RMB
	0x02, 		//ISO/ECMA/ANSI
	0x02, 		//Response Data Format
	0x1F, 		//Additional Length
	0x00, 		//Reserved
	0x00, 		//Reserved
	0x00, 		//Reserved
	'M', 'V', 'S', 'I', 0, 0, 0, 0,				//Vendor Information
	'C', 'a', 'r', 'd', ' ', 'R', 'e', 'a', 'd', 'e', 'r', 0, 0, 0, 0, 0,		//Product Identification
	'V', '1', '.', '0'		//Product Revision Level
};

uint8_t gFmtCapacityData[] =
{
	0x00, 0x00, 0x00, 0x08,
	0x00, 0x1D, 0xC3, 0xFF,
	0x03,
	0x00,
	(uint8_t)(DEVICE_STOR_BLOCK_SIZE >> 8),
	(uint8_t)DEVICE_STOR_BLOCK_SIZE
};

uint8_t gCapacityData[] =
{
	0x00, 0x1D, 0xC3, 0xFF,
	0x00,
	0x00,
	(uint8_t)(DEVICE_STOR_BLOCK_SIZE >> 8),
	(uint8_t)DEVICE_STOR_BLOCK_SIZE
};


const uint8_t gModeSenseProtectPage[] = {0x03, 0x00, 0x00, 0x00};

uint8_t	gModeSenseAllPage[] =
{
	0x0B,
	0x00,
	0x00,
	0x08,
	0x00,
	0x02, 0x00, 0x00, 		// block size 131072
	0x00,
	0x00, 0x02, 0x00,
};

const uint8_t gRequestSenseNotReady[] =
{
	0x70, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x0A,
	0x00, 0x00, 0x00, 0x00, 0x3A, 0x00, 0x00, 0x00,
	0x00, 0x00
};

const uint8_t gRequestSenseReady[] =
{
	0x70, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x0A,
	0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00,
	0x00, 0x00
};

uint8_t gCBW[64];

uint8_t gCSW[] = {'U', 'S', 'B', 'S', 0x08, 0x70, 0xBA, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00};

bool DeviceStorPreventFlag;
TIMER DeviceStorPreventTimer;

bool DeviceStorStoppedFlag;
bool DeviceStorCmdFlag;
TIMER DeviceStorCmdTimer;

bool IsCardLink(void)
{
	return 1;
}
//extern bool IsCardLink(void);
bool DeviceStorIsCardInitOK;

static uint8_t sReaderState = READER_UNREADY;;
uint8_t GetSdReaderState(void)
{
	return sReaderState;
}

void SetSdReaderState(uint8_t State)
{
	sReaderState = State;
}

//////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief  ��ȡSD������״̬
 * @param  NONE
 * @return 1-�ɹ���0-ʧ��
 */
bool DeviceStorIsCardLink(void)
{
	return TRUE;
	if(!IsCardLink())		//��ǰ�޿�����
	{
		DeviceStorIsCardInitOK = FALSE;
	}
	else if(!DeviceStorIsCardInitOK)	//��ǰ�п����ӣ�������δ��ʼ���������ʼ����
	{
		if(SDCard_Init() == NONE_ERR)
		{
			DeviceStorIsCardInitOK = TRUE;
		}
		return FALSE;
	}

	return DeviceStorIsCardInitOK;
}



////////////////////////////Mass Storage Request//////////////////////////////////////
/**
 * @brief  ����CSW
 * @param  Status CSW״̬
 * @return NONE
 */
void DeviceStorSendCSW(uint8_t Status)
{
	gCSW[12] = Status;
	OTG_DeviceBulkSend(DEVICE_BULK_IN_EP,gCSW, sizeof(gCSW),100000);
}

/**
 * @brief  ����ReadFmtCapacity����
 * @param  NONE
 * @return NONE
 */
void DeviceStorReadFmtCapacity(void)
{
	uint32_t Temp = SDCard_CapacityGet();
	if(!DeviceStorIsCardLink())
	{
		OTG_DeviceStallSend(DEVICE_BULK_IN_EP);
		WaitMs(10);
		OTG_DeviceRequestProcess();
		DeviceStorSendCSW(1);
		return;
	}

	((uint32_t*)&gFmtCapacityData[4])[0] = CpuToBe32(Temp);
//	((uint32_t*)&gFmtCapacityData[4])[0] = CpuToBe32(2000000);

	OTG_DeviceBulkSend(DEVICE_BULK_IN_EP,gFmtCapacityData, sizeof(gFmtCapacityData),10000);
	DeviceStorSendCSW(0);
}

/**
 * @brief  ����ReadCapacity����
 * @param  NONE
 * @return NONE
 */
extern uint8_t Setup[];

void DeviceStorReadCapacity(void)
{
	uint32_t Temp = SDCard_CapacityGet()-1;
	if(!DeviceStorIsCardLink())
	{
		OTG_DeviceStallSend(DEVICE_BULK_IN_EP);
		WaitMs(10);
		OTG_DeviceRequestProcess();
		memset(Setup,0,8);
		DeviceStorSendCSW(1);
		return;
	}

	((uint32_t*)&gCapacityData[0])[0] = CpuToBe32(Temp);
	OTG_DeviceBulkSend(DEVICE_BULK_IN_EP,gCapacityData, sizeof(gCapacityData),1000);
	DeviceStorSendCSW(0);
}

uint8_t CARD_BUF_A[512];
uint8_t CARD_BUF_B[512];

/**
 * @brief  ����Read10����
 * @param  NONE
 * @return NONE
 */
void DeviceStorRead10(void)
{
	uint32_t ReqLBA = Be32ToCpu(*(uint32_t*)(&gCBW[17]));
	uint16_t ReqCnt = Be16ToCpu(*(uint16_t*)(&gCBW[22]));
	uint32_t i;
	for(i=0;i<ReqCnt;i++)
	{
		SDCard_ReadBlock(ReqLBA+i,CARD_BUF_A,1);
		if(OTG_DeviceBulkSend(DEVICE_BULK_IN_EP, CARD_BUF_A, 512,10000) != DEVICE_NONE_ERR)
		{
			DBG("USB ERROR\n");
			return;
		}
	}
	DeviceStorSendCSW(0);
}

/**
 * @brief  ����Write10����
 * @param  NONE
 * @return NONE
 */
void DeviceStorWrite10(void)
{
	uint32_t ReqLBA = Be32ToCpu(*(uint32_t*)(&gCBW[17]));
	uint16_t ReqCnt = Be16ToCpu(*(uint16_t*)(&gCBW[22]));
	uint32_t DataLength = 0;
	uint32_t i;
	for(i=0;i<ReqCnt;i++)
	{
		if(OTG_DeviceBulkReceive(DEVICE_BULK_OUT_EP, CARD_BUF_A, 512,&DataLength,10000) != DEVICE_NONE_ERR)
		{
			DBG("USB ERROR\n");
			return;
		}
		SDCard_WriteBlock(ReqLBA+i,CARD_BUF_A,1);
	}
	DeviceStorSendCSW(0);
}

/**
 * @brief  ����ModeSense����
 * @param  NONE
 * @return NONE
 */
extern uint8_t Setup[];
void DeviceStorModeSense(void)
{
	if(!DeviceStorIsCardLink())
	{
		OTG_DeviceStallSend(DEVICE_BULK_IN_EP);
		WaitMs(10);
		OTG_DeviceRequestProcess();
		memset(Setup,0,8);
		DeviceStorSendCSW(1);
		return;
	}

	((uint32_t*)&gModeSenseAllPage[4])[0] = CpuToBe32(SDCard_CapacityGet());

	switch(gCBW[17])
	{
		case 0x1C:		//mode sense, Timer and Protect Page
			OTG_DeviceBulkSend(DEVICE_BULK_IN_EP,(uint8_t*)gModeSenseProtectPage, sizeof(gModeSenseProtectPage),10000);
			DeviceStorSendCSW(0);
			break;

		case 0x3F:		//mode sense, Return all pages
			OTG_DeviceBulkSend(DEVICE_BULK_IN_EP,gModeSenseAllPage, sizeof(gModeSenseAllPage),10000);
			DeviceStorSendCSW(0);
			break;

		default:
			OTG_DeviceBulkSend(DEVICE_BULK_IN_EP,0, 0,10000);
			DeviceStorSendCSW(0);
			break;
	}
}

/**
 * @brief  �жϵ�ǰ�Ƿ��ڱ���״̬
 * @param  NONE
 * @return 1-������0-�Ǳ���
 */
bool DeviceStorIsPrevent(void)
{
	if((!DeviceStorPreventFlag) || IsTimeOut(&DeviceStorPreventTimer))
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

/**
 * @brief  �ж�PC���Ƿ�ִ���ˡ�����������
 * @param  NONE
 * @return 1-�ѵ�����0-δ����
 */
bool DeviceStorIsStopped(void)
{
	if(DeviceStorStoppedFlag)
	{
		return TRUE;
	}
	else if(DeviceStorCmdFlag && IsTimeOut(&DeviceStorCmdTimer))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/**
 * @brief  ���������ܳ�ʼ��
 * @param  NONE
 * @return NONE
 */
void OTG_DeviceStorInit(void)
{
//	REG_CHIP_CFG_MODE = 0x00;
	sReaderState = READER_INIT;
	OTG_DeviceInit();
	DeviceStorStoppedFlag = FALSE;
	DeviceStorCmdFlag = FALSE;
	sReaderState = READER_READY;
}

/**
 * @brief  ������ģʽ����������
 * @param  NONE
 * @return NONE
 */
extern uint8_t Setup[];
void OTG_DeviceStorProcess(void)
{
	uint32_t DataLen = 0;
//	uint32_t Len;
	if(OTG_DeviceBulkReceive(DEVICE_BULK_OUT_EP,(uint8_t*)&gCBW, 31, &DataLen, 1000) != DEVICE_NONE_ERR)
	{
		return;
	}
	if(memcmp(gCBW, "USBC", 4))
	{
		DBG("(memcmp(gCBW, USBC, 4) != 0\n");
		return;
	}

	// set CSW tag
	gCSW[4] = gCBW[4];
	gCSW[5] = gCBW[5];
	gCSW[6] = gCBW[6];
	gCSW[7] = gCBW[7];

	switch(gCBW[15])
	{
		case INQUIRY:
			sReaderState = READER_INQUIRY;
			OTG_DeviceBulkSend(DEVICE_BULK_IN_EP,gInquiryData, sizeof(gInquiryData),10000);
			OTG_DeviceBulkSend(DEVICE_BULK_IN_EP,gCSW, sizeof(gCSW),10000);
			break;

		case READ_FORMAT_CAPACITY:
			DBG("READ_FORMAT_CAPACITY\n");
			sReaderState = READER_READ_FORMAT_CAPACITY;
			DeviceStorReadFmtCapacity();
			break;

		case READ_CAPACITY:
			DBG("READ_CAPACITY\n");
			sReaderState = READER_READ_CAPACITY;
			DeviceStorReadCapacity();
			break;

		case READ_10:
			//DBG("R\n");//DBG("R10\n");
			sReaderState = READER_READ;
			DeviceStorRead10();
			break;

		case WRITE_10:
			//DBG("W\n");//DBG("W10\n");
			sReaderState = READER_WIRTE;
			DeviceStorWrite10();
			TimeOutSet(&DeviceStorPreventTimer, 2000);
			break;

		case TEST_UNIT_READY:
			//DBG("TEST\n");
			if(!DeviceStorIsCardLink())
			{
				//DBG("1\n");
				sReaderState = READER_UNREADY;
				DeviceStorStoppedFlag = FALSE;	//�����γ��������������־�����Ա��´β��Ͽ�ʱ���ܹ�������ʶ��
				DeviceStorSendCSW(1);
			}
			else
			{
				if(DeviceStorStoppedFlag)		//��δ�γ������ڵ�����ִ���ˡ�����������
				{
					//DBG("2\n");
					sReaderState = READER_UNREADY;
					DeviceStorSendCSW(1);
				}
				else
				{
					//DBG("3\n");
					sReaderState = READER_READY;
					DeviceStorSendCSW(0);
				}
			}
			break;

		case MODE_SENSE:
			DBG("MODE_SENSE\n");
			DeviceStorModeSense();
			break;

		case ALLOW_MEDIUM_REMOVAL:
			DBG("ALLOW_MEDIUM_REMOVAL\n");
			if((gCBW[19] == 0) && DeviceStorIsCardLink())
			{
				//DBG("allow\n");
				sReaderState = READER_NOT_ALLOW_REMOVAL;
				DeviceStorPreventFlag = FALSE;
				DeviceStorSendCSW(0);
			}
			else
			{
				//DBG("prevent\n");
				sReaderState = READER_ALLOW_REMOVAL;
				DeviceStorPreventFlag = TRUE;
				DeviceStorSendCSW(0);
			}
			break;

		case REQUEST_SENSE:
			DBG("REQUEST_SENSE\n");
			if((!DeviceStorIsCardLink()) || DeviceStorStoppedFlag)
			{
				OTG_DeviceBulkSend(DEVICE_BULK_IN_EP,(uint8_t*)gRequestSenseNotReady, sizeof(gRequestSenseNotReady),10000);
			}
			else
			{
				OTG_DeviceBulkSend(DEVICE_BULK_IN_EP,(uint8_t*)gRequestSenseReady, sizeof(gRequestSenseReady),10000);
			}
			DeviceStorSendCSW(0);
			break;

		case VERYFY:
			DBG("VERYFY\n");
			DeviceStorSendCSW(0);
			break;

		case START_STOP_UNIT:
			DBG("START_STOP_UNIT\n");
			DeviceStorSendCSW(0);
			DeviceStorStoppedFlag = TRUE;
			sReaderState = READER_UNREADY;
			break;

		default:
			//DBG("default\n");
			DeviceStorSendCSW(1);
			break;
	}

	//���1.2��û�н��յ��������ΪPC���Ѱ�ȫɾ���豸
	DeviceStorCmdFlag = TRUE;
	TimeOutSet(&DeviceStorCmdTimer, 1500);
}

