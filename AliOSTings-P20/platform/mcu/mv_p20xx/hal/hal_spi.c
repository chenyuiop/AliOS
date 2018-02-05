#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "hal/soc/soc.h"



int32_t hal_spi_init(spi_dev_t *spi)
{
	return 0;
}


int32_t hal_spi_send(spi_dev_t *spi, const uint8_t *data, uint16_t size, uint32_t timeout)
{
	return 0;
}


int32_t hal_spi_recv(spi_dev_t *spi, uint8_t *data, uint16_t size, uint32_t timeout)
{
	return 0;
}


int32_t hal_spi_send_recv(spi_dev_t *spi, uint8_t *tx_data, uint16_t tx_size,
                          uint8_t *rx_data, uint16_t rx_size, uint32_t timeout)
{
	return 0;
}


int32_t hal_spi_finalize(spi_dev_t *spi)
{
	return 0;
}
