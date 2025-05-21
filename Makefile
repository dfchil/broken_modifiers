TARGETNAME = brknmv
KOS_CPPSTD	:= -std=c++20
KOS_CSTD := -std=c23
ROMDIR=cdrom/drxlax
CC=kos-cc

# List all of your C files here, but change the extension to ".o"
OBJS := $(shell find ./code/ -name '*.c' -not -path "./.git/*" | sed -e 's/\(.*\).c/\1.o/g')
LHEADERS = $(shell find . -name '*.h' -not -path "./.git/*")
# LDLIBS 	:= -lm -lm -lkosutils -lpthread

DEFINES=	
ifdef DEBUG
	DEFINES += -DDEBUG
endif

KOS_CFLAGS+=\
		-I$(shell pwd)/include \
		-m4-single-only \
		${DEFINES} \


all: rm-elf ${TARGETNAME}.elf

include $(KOS_BASE)/Makefile.rules

rm-elf:
	-rm -f ${TARGETNAME}.elf

clean: rm-elf
	-rm -f $(OBJS) ${TARGETNAME}.cdi


${TARGETNAME}.elf: $(OBJS) $(DTTEXTURES) $(SFXFILES)
	$(CC) $(OBJS) $(KOS_CFLAGS) -L$(KOS_BASE)/lib -o $@ 


${TARGETNAME}.cdi: ${TARGETNAME}.elf
	mkdcdisc -n $(basename $<) -e ${TARGETNAME}.elf -d cdrom/ -N -o $(basename $<).cdi -v 3 -m

flycast: ${TARGETNAME}.cdi
	~/Downloads/Flycast.app/Contents/MacOS/Flycast $<