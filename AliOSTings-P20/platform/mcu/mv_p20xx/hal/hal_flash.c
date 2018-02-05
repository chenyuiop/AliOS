/*
 * Copyright (C) 2015-2017 Alibaba Group Holding Limited
 */

#include "hal/soc/soc.h"
#include "mico_rtos.h"

#include "spi_flash.h"


#define SECTOR_SIZE 0x1000 /* 4 K/sector */


extern const hal_logic_partition_t hal_partitions[];
hal_logic_partition_t *hal_flash_get_info(hal_partition_t in_partition)
{
    hal_logic_partition_t *logic_partition;

    logic_partition = (hal_logic_partition_t *)&hal_partitions[ in_partition ];

    return logic_partition;
}

int32_t hal_flash_erase(hal_partition_t in_partition, uint32_t off_set, uint32_t size)
{
    hal_logic_partition_t *partition_info;

#ifdef CONFIG_AOS_KV_MULTIPTN_MODE
        if (in_partition == CONFIG_AOS_KV_PTN) {
            if (off_set >= CONFIG_AOS_KV_PTN_SIZE) {
                in_partition = CONFIG_AOS_KV_SECOND_PTN;
                off_set -= CONFIG_AOS_KV_PTN_SIZE;
            }
        }
#endif

	partition_info = hal_flash_get_info( in_partition );
	if(size + off_set > partition_info->partition_length)
		return -1;

	char cmd[3] = "\x35\xBA\x69";// FlashUnlock()
	if(SpiFlashIOCtrl(IOCTL_FLASH_UNPROTECT, cmd, sizeof(cmd)) != FLASH_NONE_ERR)
	{
		return -1;
	}
	SpiFlashErase(SECTOR_ERASE,(partition_info->partition_start_addr + off_set)/4096,0);
    
    return 0;
}
                        
int32_t hal_flash_write(hal_partition_t in_partition, uint32_t *off_set, const void *in_buf , uint32_t in_buf_len)
{
    uint32_t start_addr;
    hal_logic_partition_t *partition_info;

#ifdef CONFIG_AOS_KV_MULTIPTN_MODE
        if (in_partition == CONFIG_AOS_KV_PTN) {
            if ((*off_set) >= CONFIG_AOS_KV_PTN_SIZE) {
                in_partition = CONFIG_AOS_KV_SECOND_PTN;
                *off_set = (*off_set) - CONFIG_AOS_KV_PTN_SIZE;
            }
        }
#endif
	partition_info = hal_flash_get_info( in_partition );
	start_addr = partition_info->partition_start_addr + *off_set;
	if (FLASH_NONE_ERR != SpiFlashWrite(start_addr, (uint8_t *)in_buf, in_buf_len,20)) {
		printf("FLASH_update failed!\n");
	}
	*off_set += in_buf_len;
	return 0;
}

int32_t hal_flash_read(hal_partition_t in_partition, uint32_t *off_set, void *out_buf, uint32_t out_buf_len)
{
    uint32_t start_addr;
    hal_logic_partition_t *partition_info;

#ifdef CONFIG_AOS_KV_MULTIPTN_MODE
    if (in_partition == CONFIG_AOS_KV_PTN) {
        if ((*off_set) >=  CONFIG_AOS_KV_PTN_SIZE) {
            in_partition = CONFIG_AOS_KV_SECOND_PTN;
            *off_set = (*off_set) - CONFIG_AOS_KV_PTN_SIZE;
        }
    }
#endif

    partition_info = hal_flash_get_info( in_partition );

    if(off_set == NULL || out_buf == NULL || *off_set + out_buf_len > partition_info->partition_length)
        return -1;
    start_addr = partition_info->partition_start_addr + *off_set;
    SpiFlashRead(start_addr, out_buf, out_buf_len,20);
    *off_set += out_buf_len;

    return 0;
}

int32_t hal_flash_enable_secure(hal_partition_t partition, uint32_t off_set, uint32_t size)
{
    return 0;
}

int32_t hal_flash_dis_secure(hal_partition_t partition, uint32_t off_set, uint32_t size)
{
    return 0;
}
