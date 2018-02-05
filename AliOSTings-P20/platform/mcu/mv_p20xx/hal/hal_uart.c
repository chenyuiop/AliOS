/*
 * Copyright (C) 2015-2017 Alibaba Group Holding Limited
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "aos/kernel.h"
#include "hal/soc/soc.h"
#include "mico_rtos.h"
#include "gpio.h"
#include "uarts_interface.h"

typedef struct usart_dev_s {
    int     crefs;                      /* The number of USARTs the device has been opened */
    mico_semaphore_t ksem_excl;          /* Mutual exclusion semaphore */
//    usart_handle_t usart_handle;

//    ringbuffer_t *read_buffer;
    /* I/O buffers */
    mico_semaphore_t       ksem_write;
    mico_semaphore_t       ksem_read;
//    usart_event_e          usart_txevent;
//    usart_event_e          usart_rxevent;
    uint8_t                stat_txmit;
    uint8_t                stat_rxmit;
    uint32_t               read_num;
    uint8_t                flowctrl;
    mico_mutex_t           tx_mutex;
} usart_dev_t;

//static usart_dev_t usart_devs[MAX_UART_NUM];






int32_t hal_uart_init(uart_dev_t *uart)
{

	GPIO_UartTxIoConfig(uart->port, 1);
	GPIO_UartRxIoConfig(uart->port, 1);
	UARTS_Init(uart->port,  \
			   uart->config.baud_rate, \
			   uart->config.data_width,  \
			   uart->config.parity,  \
			   uart->config.stop_bits);

	 return 0;
}

int32_t hal_uart_finalize(uart_dev_t *uart)
{


    return 0;
}

int32_t hal_uart_send(uart_dev_t *uart, const void *data, uint32_t size, uint32_t timeout)
{
	UARTS_Send(uart->port,(uint8_t*)data,size);
    return 0;

}

int32_t hal_uart_recv(uart_dev_t *uart, void *data, uint32_t expect_size, uint32_t *recv_size, uint32_t timeout)
{
#if 1    //DMA
	int32_t rxCnt = 0;
	uint8_t i;
	uint32_t tmpCnt;
	uint8_t buf[32];

	while(rxCnt < expect_size)
	{
		tmpCnt = expect_size - rxCnt;
		if(tmpCnt >= 32)
		{
			tmpCnt = 32;
		}
		tmpCnt = UARTS_DMA_Recv(uart->port,&buf[0],tmpCnt,0);
		if(tmpCnt > 0)
		{
			for(i=0;i<tmpCnt;i++)
			{
				*((uint8_t*)data++) = buf[i];
				rxCnt++;
			}
		}
		else
		{
			aos_msleep(4);
		}
	}
#else  //ÂÖÑ­
	int32_t rxCnt = 0;
	uint8_t byte;

	while(rxCnt < expect_size)
	{
		if(UARTS_RecvByte(uart->port,&byte))
		{
			*((uint8_t*)data++) = byte;
			rxCnt++;
		}
		else
		{
			aos_msleep(1);
		}
	}
#endif


    return 0;

}

