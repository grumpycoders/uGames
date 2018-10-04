export BOARD = stm32f429discovery
export ROOTDIR = $(CURDIR)/uC-sdk
export VERBOSE = true

TARGET = bootloader.bin
TARGET_SRCS = bootloader.c uGL/uGL.c uGL/stm32f429i_discovery.c uGL/stm32f429i_discovery_sdram.c uGL/fonts.c

LIBDEPS = \
$(ROOTDIR)/FreeRTOS/libFreeRTOS.a \
$(ROOTDIR)/arch/libarch.a \
$(ROOTDIR)/os/libos.a \
$(ROOTDIR)/libc/libc.a \
$(ROOTDIR)/libm/libm.a \
$(ROOTDIR)/acorn/libacorn.a \
$(ROOTDIR)/hardware/libhardware.a \

LIBS = -Wl,--start-group $(LIBDEPS) -Wl,--end-group
TARGET_INCLUDES = include

export MAINDIR = $(CURDIR)

include $(MAINDIR)/uGL/config.mk
include $(ROOTDIR)/common.mk

all: uC-sdk uGL $(TARGET)

clean: clean-generic
	$(Q)$(MAKE) $(MAKE_OPTS) -C $(ROOTDIR) clean
	$(Q)$(MAKE) $(MAKE_OPTS) -C uGL clean

.PHONY: uC-sdk uGL

$(ROOTDIR)/FreeRTOS/libFreeRTOS.a: uC-sdk
$(ROOTDIR)/arch/libarch.a: uC-sdk
$(ROOTDIR)/os/libos.a: uC-sdk
$(ROOTDIR)/libc/libc.a: uC-sdk
$(ROOTDIR)/libm/libm.a: uC-sdk
$(ROOTDIR)/acorn/libacorn.a: uC-sdk
$(ROOTDIR)/hardware/libhardware.a: uC-sdk

uGL:
	$(E) "[MAKE]   Entering uGL"
	$(Q)$(MAKE) $(MAKE_OPTS) -C uGL

uC-sdk:
	$(E) "[MAKE]   Entering uC-sdk"
	$(Q)$(MAKE) $(MAKE_OPTS) -C $(ROOTDIR)

deps: ldeps
	$(E) "[DEPS]   Creating dependency tree for uC-sdk"
	$(Q)$(MAKE) $(MAKE_OPTS) -C $(ROOTDIR) ldeps
	$(E) "[DEPS]   Creating dependency tree for uGL"
	$(Q)$(MAKE) $(MAKE_OPTS) -C uGL ldeps

include $(ROOTDIR)/FreeRTOS/config.mk
include $(ROOTDIR)/arch/config.mk
include $(ROOTDIR)/os/config.mk
include $(ROOTDIR)/libc/config.mk
include $(ROOTDIR)/libm/config.mk
include $(ROOTDIR)/acorn/config.mk
include $(ROOTDIR)/hardware/config.mk
include $(ROOTDIR)/target-rules.mk

