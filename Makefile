OUT_DIR=out

ELF=$(OUT_DIR)/singularityBOOT.elf
HEX=$(OUT_DIR)/singularityBOOT.hex
DIS=$(OUT_DIR)/singularityBOOT.dasm

#===================================================================
# Target specific info
#BOARD=board_rpi3
BOARD=board_rpi4

#===================================================================
# Include Board info to findout the remain information
F_BOARD=$(BOARD)
include $(F_BOARD)/Makefile.include
#===================================================================

#===================================================================
# File to compile

ASMFILES= 	$(BOARD)/start.S					\


CFILES=		$(BOARD)/board.c					\
			$(BOARD)/hal.c						\
			$(SOC)/bcm283x_gpio.c				\
			$(SOC)/bcm283x_uart.c				\
			$(SOC)/bcm283x_gpu_mailbox.c		\
			$(SOC)/bcm283x_clocks.c				\
			$(SOC)/bcm283x_watchdog.c			\
			core/debug/kprint.c					\
			core/debug/string_format.c			\
			core/debug/stdlib.c					\
			core/debug/ctype.c					\
			core/entry.c						\
			core/parse_ihex.c					\



# Create obj files names from source files
ASMOBJS=$(patsubst %.S,%.o,$(ASMFILES))
COBJS=$(patsubst %.c,%.o,$(CFILES))

OBJS=$(ASMOBJS) $(COBJS)

# ==================================================================
# Header flags
HEADERS= -I$(SOC) -I$(BOARD) -Icore -Icore/debug

# Compiler flags
CC_FLAGS= -Wall -Werror -O3 -nostdlib -nostartfiles -ffreestanding -nostdinc -Wno-int-to-pointer-cast -Wno-pointer-sign -Wno-pointer-to-int-cast -Wno-implicit-function-declaration $(CPU_FLAGS) $(HEADERS)

# Linker flags
LD_FLAGS= -T $(BOARD)/linker.ld -Wl,--build-id=none -N

#===================================================================
# all rule
all: directory $(ELF) $(IMG) $(HEX) $(DIS)

#===================================================================
#generate .elf file
$(ELF): $(OBJS)
	$(CC) $(LD_FLAGS) $(CC_FLAGS) -o $@ $(OBJS)


%.o: %.S
	$(CC) $(CC_FLAGS) -c -o $@ $<


%.o: %.c
	$(CC) $(CC_FLAGS) -c -o $@ $<


#generate .img file to use on sd card
$(IMG):
	$(CPY) $(ELF) -O binary $(IMG)

#generate ihex file to use with bootloader
$(HEX):
	$(CPY) $(ELF) -O ihex $(HEX)

#generate disassembly file for debug
$(DIS):
	$(DMP) -D $(ELF) > $(DIS)

directory:
	mkdir -p $(OUT_DIR)

.PHONY: clean
clean:
	rm -f $(OBJS) $(ELF) $(IMG) $(HEX) $(DIS)

#===================================================================
# Debug section
print:
	$(info    OBJS is $(OBJS))
	$(info    SOC is $(SOC))




