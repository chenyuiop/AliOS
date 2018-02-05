//maintainer lilu

/**
* @addtogroup FileSystem
* @{
* @defgroup fat fat.h
* @{
*/

#ifndef __FAT_H__
#define __FAT_H__

#ifdef __cplusplus
extern "C" {
#endif//__cplusplus


// Define EOF flag for FAT16 and FAT32
#define EOF_FAT32				0x0FFFFFF8
#define	EOF_FAT16				0xFFF8


// Get the sector number
uint32_t GetSecNum(FS_CONTEXT* FsContext, uint32_t clusNum);

// Get the cluster number
uint32_t GetClusNum(FS_CONTEXT* FsContext, uint32_t secNum);

//read one secter data to io buffer,this function will alloc one io buffer
bool ReadOneSec(FS_CONTEXT* FsContext, uint32_t SecNum);

//save io buffer,write the changed IoBuffer to disk
bool SaveOneSec(FS_CONTEXT* FsContext);

// Save one DIR sector
bool SaveDirSec(FS_CONTEXT* FsContext);

// Load one directory sector
bool ReadDirSec(FS_CONTEXT* FsContext, uint32_t secNum);

// Save one FAT sector
bool SaveFatSec(FS_CONTEXT* FsContext);

// Load one FAT sector
bool ReadFATSec(FS_CONTEXT* FsContext, uint32_t secNum);

// Get next cluster number
uint32_t GetNextClusNum(FS_CONTEXT* FsContext, uint32_t ClusNum);

// Get next sector number
uint32_t GetNextSecNum(FS_CONTEXT* FsContext, uint32_t SecNum);

//����FAT����
bool ModifyFatItem(FS_CONTEXT* FsContext, uint32_t ClusNum, uint32_t WriteData);

//�жϴ��Ƿ����
bool IsFreeClus(FS_CONTEXT* FsContext, uint32_t ClusNum);

//���㵱ǰ����ʣ��Ŀ�����������
uint8_t FreeSectorOfClus(FS_CONTEXT* FsContext, uint32_t CurSectorNum);

//����һ����
uint32_t FreeClusAlloc(FS_CONTEXT* FsContext, uint32_t StartClusNum);

//ɾ��һ������
void DeleteClusterChain(FS_CONTEXT* FsContext, uint32_t StartClusNum);

//��һ�������ĵ�ǰλ������������ɸ���
//bool SeekClusterChain(uint32_t StartClusNum, uint32_t ClusCnt);

extern uint8_t DiskExistFlag;

bool ValidityCheck(void);

void ParseFat(FS_CONTEXT* FsContext);

#ifdef  __cplusplus
}
#endif//__cplusplus

#endif
