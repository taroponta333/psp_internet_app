TARGET = 3ds_receiver

OBJS = main.o network.o receiver.o

CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBS = \
-lpspdebug \
-lpspdisplay \
-lpspctrl \
-lpspnet \
-lpspnet_inet \
-lpspnet_apctl \
-lpspnet_resolver

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = 3DS File Managerv0.5.4

PSPSDK := $(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
