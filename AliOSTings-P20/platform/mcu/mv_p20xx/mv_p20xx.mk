HOST_OPENOCD := mv_p20xx

NAME := mv_p20xx

$(NAME)_TYPE := kernel 

$(NAME)_COMPONENTS :=  
$(NAME)_COMPONENTS += rhino hal  cli modules.fs.kv 
vcall               ?= rhino

$(info  in mv_p20xx.mk )
GLOBAL_DEFINES += CONFIG_NO_TCPIP
GLOBAL_DEFINES += CONFIG_AOS_CLI

MVSP20_INC_PATH     := .
GLOBAL_INCLUDES  += $(MVSP20_INC_PATH)
GLOBAL_INCLUDES  += $(MVSP20_INC_PATH)/Driver/Driver
GLOBAL_INCLUDES  += $(MVSP20_INC_PATH)/Driver/Driver/inc
GLOBAL_INCLUDES  += $(MVSP20_INC_PATH)/Driver/DriverAPI/src
GLOBAL_INCLUDES  += $(MVSP20_INC_PATH)/Driver/DriverAPI/inc
GLOBAL_INCLUDES  += $(MVSP20_INC_PATH)/Driver/DriverAPI/inc/otg
GLOBAL_INCLUDES  += $(MVSP20_INC_PATH)/Driver/DriverAPI/src/otg
GLOBAL_INCLUDES  += $(MVSP20_INC_PATH)/Driver/DriverAPI/src/otg/device
GLOBAL_INCLUDES  += $(MVSP20_INC_PATH)/Driver/DriverAPI/src/otg/host
GLOBAL_INCLUDES  += $(MVSP20_INC_PATH)/Middleware/MVUtils/inc
GLOBAL_INCLUDES  += $(MVSP20_INC_PATH)/startup
GLOBAL_INCLUDES  += $(MVSP20_INC_PATH)/hal

GLOBAL_CFLAGS    += -ffunction-sections -fdata-sections -fstrict-volatile-bitfields 
GLOBAL_LDFLAGS   +=  -Lplatform/mcu/mv_p20xx/Driver/Driver  
GLOBAL_LDFLAGS   +=  -lm -lDriver #-lgcc -lstdc++ -lgcov

#GLOBAL_LDS_FILES += platform/mcu/mv_p20xx/startup/memory.ld
GLOBAL_LDS_FILES += platform/mcu/mv_p20xx/startup/nds32-ae210p.ld
#GLOBAL_LDFLAGS   += -Lplatform/mcu/mv_p20xx/startup/memory.ld
GLOBAL_LDFLAGS   += -Lplatform/mcu/mv_p20xx/startup/nds32-ae210p.ld 


GLOBAL_DEFINES   += CONFIG_AOS_KV_BUFFER_SIZE=8192
#GLOBAL_DEFINES   += CONFIG_AOS_CLI_BOARD

GLOBAL_CFLAGS    += -DXT_USE_THREAD_SAFE_CLIB=0
$(NAME)_SOURCES  := startup/retarget.c
$(NAME)_SOURCES  += startup/interrupt.c
$(NAME)_SOURCES  += startup/init-default.c
#$(NAME)_SOURCES  += startup/crt0.S
$(NAME)_SOURCES  += Driver/DriverAPI/src/uarts_interface.c
$(NAME)_SOURCES  += hal/hal_adc.c
$(NAME)_SOURCES  += hal/hal_flash.c
$(NAME)_SOURCES  += hal/hal_gpio.c
$(NAME)_SOURCES  += hal/hal_i2c.c
$(NAME)_SOURCES  += hal/hal_pwm.c
$(NAME)_SOURCES  += hal/hal_rtc.c
$(NAME)_SOURCES  += hal/hal_spi.c
$(NAME)_SOURCES  += hal/hal_uart.c
$(NAME)_SOURCES  += hal/hal_wdg.c
$(NAME)_SOURCES  += hal/hal_init.c

$(NAME)_SOURCES  += p20_example.c
$(NAME)_CFLAGS   := -std=gnu99

ifneq ($(wifi),0)
#$(NAME)_CFLAGS   += -DENABLE_WIFI
endif
$(NAME)_CFLAGS	 += -Iplatform/mcu/mv_p20xx/Driver/Driver/inc

ifeq (0,1)
libs := $(wildcard platform/mcu/Driver/Driver/*.a)
libs := $(foreach lib,$(libs),lib/$(notdir $(lib)))
$(NAME)_PREBUILT_LIBRARY := $(libs)
endif

ifeq ($(vcall),freertos)
GLOBAL_CFLAGS            += -I $(MVSP20_INC_PATH)/Middleware/FreeRTOS
$(NAME)_PREBUILT_LIBRARY += lib/Driver.a
else
$(NAME)_COMPONENTS       += rhino platform/arch/andes/n968a
$(NAME)_SOURCES          += aos/hook_impl.c
$(NAME)_SOURCES          += aos/soc_impl.c
$(NAME)_SOURCES          += aos/trace_impl.c
endif

ifneq ($(mesh),0)
endif


$(info  out mv_p20xx.mk )
