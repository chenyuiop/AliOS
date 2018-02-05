/*
 * Copyright (C) 2015-2017 Alibaba Group Holding Limited
 */

#include "hal/soc/soc.h"
#include "mico_rtos.h"

typedef uint32_t UINT32;
#define VOID void
#define ASSERT(exp)

#include "gpio.h"


typedef enum
{
    GIRQ_TRIGGER_LOW_LEVEL = 0x0,	/* Interrupt triggered at input signal's LOW LEVEL  */
    GIRQ_TRIGGER_HGIH_LEVEL = 0x1,	/* Interrupt triggered at input signal's HIGH LEVEL  */
    GIRQ_TRIGGER_RISING_EDGE  = 0x2, /* Interrupt triggered at input signal's rising edge  */
    GIRQ_TRIGGER_FALLING_EDGE = 0x3 /* Interrupt triggered at input signal's falling edge */
}en_GIRQ_TRIGGER;

typedef struct
{
    void *arg;
    gpio_irq_handler_t handler;
} gpio_int_hdl;



int32_t hal_gpio_init(gpio_dev_t *gpio)
{


    return 0;
}

int32_t hal_gpio_finalize(gpio_dev_t *gpio)
{


    return 0;
}

int32_t hal_gpio_output_high(gpio_dev_t *gpio)
{

    return 0;
}

int32_t hal_gpio_output_low(gpio_dev_t *gpio)
{

    return 0;
}

int32_t hal_gpio_output_toggle(gpio_dev_t *gpio)
{

    return 0;
}

int32_t hal_gpio_input_get(gpio_dev_t *gpio, uint32_t *value)
{

    return 0;
}



int32_t hal_gpio_enable_irq(gpio_dev_t *gpio, gpio_irq_trigger_t trigger,
                                     gpio_irq_handler_t handler, void *arg)
{

    return 0;
}

int32_t hal_gpio_disable_irq(gpio_dev_t *gpio)
{

    return 0;
}

int32_t hal_gpio_clear_irq(gpio_dev_t *gpio)
{


    return 0;
}
