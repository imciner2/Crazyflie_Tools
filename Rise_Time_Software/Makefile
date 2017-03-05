# This make file is downloaded from:
# https://github.com/adamheinrich/stm32-template/blob/master/src/Makefile
#
# Some minor modifications have been made to it to work with this project.


# Set to @ if you want to suppress command echo
CMD_ECHO = @

# Project name
BIN = RiseTime

# Important directories
BUILD_DIR = ./build
TOOLCHAIN_DIR = /usr/bin

INC = -I./Inc \
      -I./Drivers/STM32F4xx_HAL_Driver/Inc \
      -I./Drivers/STM32F4xx_HAL_Driver/Inc\Legacy \
      -I./Drivers/CMSIS/Include \
      -I./Drivers/CMSIS/Device/ST/STM32F4xx/Include

# ASM and C (e.g. startup) source files and linker script outside src directory
SRC_ASM = ./startup/startup_stm32f401xe.s
SRC_C = ./Src/system_stm32f4xx.c
SRC_LD = ./STM32F401RETx_FLASH.ld

# Sub directories containing source files
SRC_C_DIR = Src Drivers/STM32F4xx_HAL_Driver/Src

# Defines required by included libraries
DEF = -DSTM32F401xE

# Compiler and linker flags
ARCHFLAGS = -mcpu=cortex-m4 -mthumb -mabi=aapcs
ASFLAGS = $(ARCHFLAGS)

# CC: Place functions and data into separate sections to allow dead code removal
# by the linker (-f*-sections). Enable link time optimization (-flto)
CFLAGS = $(ARCHFLAGS) -std=gnu99 -Wall -Wno-format -Werror \
         -ffunction-sections -fdata-sections \
         -Os -flto $(DBGFLAGS)

# LD: Remove unused sections, link with newlib-nano implementation, generate map
LDFLAGS = $(ARCHFLAGS) -Wl,--gc-sections --specs=nano.specs --specs=nosys.specs
LDFLAGS += -Wl,-Map=$(BUILD_DIR)/$(BIN).map $(DBGFLAGS)

# Generate object list from source files and add their dirs to search path
SRC_ASM += $(wildcard *.s) 
FILENAMES_ASM = $(notdir $(SRC_ASM))
OBJS_ASM = $(addprefix $(BUILD_DIR)/, $(FILENAMES_ASM:.s=.o))
vpath %.s $(dir $(SRC_ASM))

# Generate list of C files to compile
SRC_C += $(foreach sdir,$(SRC_C_DIR),$(wildcard $(sdir)/*.c)) 
FILENAMES_C = $(notdir $(SRC_C))
OBJS_C = $(addprefix $(BUILD_DIR)/, $(FILENAMES_C:.c=.o))
vpath %.c $(dir $(SRC_C))

# Tools selection
CC = $(TOOLCHAIN_DIR)/arm-none-eabi-gcc
AS = $(TOOLCHAIN_DIR)/arm-none-eabi-gcc
LD = $(TOOLCHAIN_DIR)/arm-none-eabi-gcc
NM = $(TOOLCHAIN_DIR)/arm-none-eabi-nm
OBJCOPY = $(TOOLCHAIN_DIR)/arm-none-eabi-objcopy
OBJDUMP = $(TOOLCHAIN_DIR)/arm-none-eabi-objdump
SIZE = $(TOOLCHAIN_DIR)/arm-none-eabi-size
GDB = $(TOOLCHAIN_DIR)/arm-none-eabi-gdb

all: $(BUILD_DIR) $(BUILD_DIR)/$(BIN).hex
	@echo ""
	$(CMD_ECHO) @$(SIZE) $(BUILD_DIR)/$(BIN).elf

$(BUILD_DIR):
	$(CMD_ECHO) mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/$(BIN).hex: $(BUILD_DIR)/$(BIN).elf
	@echo "Generating HEX binary: $(notdir $@)"
	$(CMD_ECHO) $(OBJCOPY) -O ihex $< $@

$(BUILD_DIR)/%.o: %.s
	@echo "Compiling ASM file: $(notdir $<)"
	$(CMD_ECHO) $(AS) $(ASFLAGS) $(DEF) $(INC) -c -o $@ $<

$(BUILD_DIR)/%.o: %.c
	@echo "Compiling C file: $(notdir $<)"
	$(CMD_ECHO) $(CC) $(CFLAGS) $(DEF) $(INC) -c -o $@ $<

$(BUILD_DIR)/$(BIN).elf: $(OBJS_ASM) $(OBJS_C)
	@echo "Linking ELF binary: $(notdir $@)"
	$(CMD_ECHO) $(LD) $(LDFLAGS) -T$(SRC_LD) -o $@ $^
	
	@echo "Generating BIN binary: $(BIN).bin"
	$(CMD_ECHO) $(OBJCOPY) -O binary $(BUILD_DIR)/$(BIN).elf $(BUILD_DIR)/$(BIN).bin
	
	@echo "Generating name list: $(BIN).sym"
	$(CMD_ECHO) $(NM) -n $@ > $(BUILD_DIR)/$(BIN).sym

	@echo "Generating disassembly: $(BIN).disasm"
	$(CMD_ECHO) $(OBJDUMP) -S $@ > $(BUILD_DIR)/$(BIN).disasm

flash: $(BUILD_DIR)/$(BIN).bin
	st-flash write $(BUILD_DIR)/$(BIN).bin 0x8000000
	
erase:
	st-flash erase

clean:
	rm -f $(BUILD_DIR)/*.elf $(BUILD_DIR)/*.hex $(BUILD_DIR)/*.map
	rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/*.sym $(BUILD_DIR)/*.disasm
	rm -f $(BUILD_DIR)/*.bin
