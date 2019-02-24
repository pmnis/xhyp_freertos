
CROSS_COMPILE := arm-linux-gnueabihf-
CROSS_COMPILE := arm-none-linux-gnueabi-
CC := $(CROSS_COMPILE)gcc
LDSCRIPT := xhyp.ld

LOADADDR := 0x02100000

INCLUDES := -I../Common/include -I../../Source/include -I../../Source/portable/GCC/XHYP -I include -nostdinc
WARNINGS := -Wall -Wextra -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wno-unused-parameter

CFLAGS := -fno-common -ffixed-r8 -msoft-float  -D__KERNEL__ -DTEXT_BASE=${LD_ADDR} -fno-builtin -ffreestanding -pipe  -DCONFIG_ARM -D__ARM__ -marm  -mabi=aapcs-linux -mno-thumb-interwork -march=armv5te -Wall -Wstrict-prototypes -fno-stack-protector -Wall -Werror $(INCLUDES)

AFLAGS := -D__ASSEMBLY__ -Os   -fno-common -ffixed-r8 -msoft-float  -D__KERNEL__ -DTEXT_BASE=${LD_ADDR} -fno-builtin -ffreestanding -pipe  -DCONFIG_ARM -D__ARM__ -marm  -mabi=aapcs-linux -mno-thumb-interwork -march=armv5te $(INCLUDES)

LDFLAGS := -Bstatic -T $(LDSCRIPT) -nostartfiles -nostdlib

SOURCE_BASE := ../../Source

PORT_XHYP := portable/GCC/XHYP

PORT_BASE := $(SOURCE_BASE)/$(PORT_XHYP)

OBJCOPY :=$(CROSS_COMPILE)objcopy

CORE := $(SOURCE_BASE)/tasks.c $(SOURCE_BASE)/queue.c $(SOURCE_BASE)/list.c $(SOURCE_BASE)/$(PORT_XHYP)/port.c

MEMMANG := $(SOURCE_BASE)/portable/MemMang/heap_2.c

LIB := stdlib.c

TEST := ParTest/ParTest.c

CORE_OBJ := $(CORE:.c=.o) $(PORT_BASE)/port_context.o

MEMMANG_OBJ := $(MEMMANG:.c=.o)

LIB_OBJ := $(LIB:.c=.o)

TEST_OBJ := $(TEST:.c=.o)


OBJS := start.o main.o _udivsi3.o $(CORE_OBJ) $(MEMMANG_OBJ) $(TEST_OBJ) $(LIB_OBJ)

all: xhypdemo

start.o: start.S
	$(CC) -c $(AFLAGS) start.S

$(PORT_BASE)/port_context.o: $(PORT_BASE)/port_context.S
	$(CC) -c $(AFLAGS) $(PORT_BASE)/port_context.S -o $(PORT_BASE)/port_context.o


#xhypdemo.bin: xhypdemo
#	$(OBJCOPY) xhypdemo -O binary xhypdemo.bin

xhypdemo: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o xhypdemo


clean:
	rm -f $(OBJS)
	rm -f xhypdemo
	rm -f xhypdemo.bin

