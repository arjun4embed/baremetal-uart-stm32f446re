# ===============================
# Toolchain
# ===============================

CC      = arm-none-eabi-gcc
AS      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size

# ===============================
# MCU Configuration
# ===============================

MCU     = -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard

# ===============================
# Compiler Flags
# ===============================

CFLAGS  = $(MCU) -std=gnu11 -O0 -g3 -Wall \
           -ffunction-sections -fdata-sections

CFLAGS += -DSTM32F446xx
CFLAGS += -DUSE_FULL_LL_DRIVER


# Include paths
CFLAGS +=  \
-I./core \
-I./Driver/Rcc \
-I./Driver/Gpio \
-I./Driver/Nvic \
-I./Driver/Uart \


# ===============================
# Linker Flags
# ===============================

LDFLAGS = $(MCU) \
          -T core/STM32F446RETX_FLASH.ld \
          -Wl,--gc-sections \
          -Wl,-Map=output.map

# ===============================
# Source Files
# ===============================

SRCS = \
core/main.c \
Driver/Uart/uart.c \
Driver/Gpio/gpio.c \
Driver/Rcc/rcc.c \
Driver/Nvic/nvic.c \


ASMS = core/startup_stm32f446retx.s

OBJS = $(SRCS:.c=.o) $(ASMS:.s=.o)

# ===============================
# Target
# ===============================

TARGET = output.elf

all: $(TARGET)

# Compile C files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Assemble startup file
%.o: %.s
	$(AS) $(MCU) -c $< -o $@

# Link
$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)
	$(SIZE) $(TARGET)

# Flash (requires st-flash installed)
flash: $(TARGET)
	openocd -f interface/stlink.cfg \
	         -f target/stm32f4x.cfg \
	         -c "program $(TARGET) verify reset exit"


# Clean
clean:
	rm -f $(OBJS) $(TARGET) output.map
