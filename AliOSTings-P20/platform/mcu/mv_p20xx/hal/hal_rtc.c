#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "hal/soc/soc.h"

int32_t hal_rtc_init(rtc_dev_t *rtc)
{
	return 0;
}


int32_t hal_rtc_get_time(rtc_dev_t *rtc, rtc_time_t *time)
{
	return 0;
}


int32_t hal_rtc_set_time(rtc_dev_t *rtc, const rtc_time_t *time)
{
	return 0;
}

int32_t hal_rtc_finalize(rtc_dev_t *rtc)
{
	return 0;
}
