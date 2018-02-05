NAME := board_mv_p20xx


$(info, "here add the debug info")

JTAG := jlink

$(NAME)_TYPE := kernel

MODULE              := P20
HOST_ARCH           := andes
HOST_MCU_FAMILY     := mv_p20xx
SUPPORT_BINS        := no

# todo: remove these after rhino/lwip ready
vcall               ?= rhino

CURRENT_TIME = $(shell /bin/date +%Y%m%d.%H%M)
define get-os-version
"AOS-R"-$(CURRENT_TIME)
endef

CONFIG_SYSINFO_OS_VERSION := $(call get-os-version)
CONFIG_SYSINFO_PRODUCT_MODEL := ALI_AOS_MV_P20XX
CONFIG_SYSINFO_DEVICE_NAME := MV_P20XX

# GLOBAL_CFLAGS += -DSYSINFO_PRODUCT_MODEL=\"$(CONFIG_SYSINFO_PRODUCT_MODEL)\"
 GLOBAL_CFLAGS += -DSYSINFO_DEVICE_NAME=\"$(CONFIG_SYSINFO_DEVICE_NAME)\"

GLOBAL_INCLUDES += .
$(NAME)_SOURCES := board.c


# $(NAME)_INCLUDES := \
# ../../platform/mcu/mv_p20xx/Driver/Driver/Inc \
# ../../platform/mcu/mv_p20xx/Driver/Driver/ \
# ../../platform/mcu/mv_p20xx/Driver/DriverAPI/inc \
# ../../platform/mcu/mv_p20xx/Driver/DriverAPI/src  

# EXTRA_TARGET_MAKEFILES +=  $(SOURCE_ROOT)/platform/mcu/$(HOST_MCU_FAMILY)/gen_crc_bin.mk
