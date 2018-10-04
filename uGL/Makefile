all:  $(TARGET_OBJ)

export BOARD = stm32f429discovery

include $(ROOTDIR)/common.mk
include config.mk
include $(ROOTDIR)/arch/config.mk
include $(ROOTDIR)/FreeRTOS/config.mk

TARGET_SRCS += font.cs
TARGET_SRCS += stm32f429i_discovery.c
#TARGET_SRCS += stm32f429i_discovery_lcd.c
TARGET_SRCS += stm32f429i_discovery_sdram.c

include $(ROOTDIR)/target-rules.mk

clean: clean-generic

