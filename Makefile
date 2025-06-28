#Compile for STM32F401RE using ARM GCC toolchain
CC=arm-none-eabi-gcc

#Compiler flags
# -mcpu=cortex-m4: Target Cortex-M4 architecture
# -mthumb: Generate Thumb instructions (16 bit instructions for ARM Cortex-M instead of usual 32 bit)
# -nostdlib: Do not use standard libraries,
CFLAGS=-mcpu=cortex-m4 -mthumb -nostdlib

#Preprocessor flags
# -DSTM32F401xE: Define the STM32F401xE series as the target
# -I: Include directories for header files
CPPFLAGS=-DSTM32F401xE \
			-Ivendor/CMSIS/Device/ST/STM32F4/Include \
			-Ivendor/CMSIS/CMSIS/Core/Include

#Linker script file name
LINKER_FILE=linker_script.ld

#Linker flags
LDFLAGS=-T $(LINKER_FILE)

#desired output binary name
BINARY = blink.elf

#OPENOCD programmer settings for flashing the binary to STM32F401RE
PROGRAMMER = openocd
PROGRAMMER_FLAGS = -f interface/stlink-v2-1.cfg -f target/stm32f4x.cfg

all: $(BINARY)

#Linking the object files to create the final binary
$(BINARY): main.o startup.o system_stm32f4xx.o
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ -o $(BINARY)

#main.o object file for main.c
main.o: main.c
	$(CC) $(CFLAGS) $(CPPFLAGS) main.c -c

#startup.o object file for startup.c
startup.o: startup.c
	$(CC) $(CFLAGS) $(CPPFLAGS) startup.c -c

#system_stm32f4xx.o object file for system_stm32f4xx.c
system_stm32f4xx.o: vendor/CMSIS/Device/ST/STM32F4/Source/Templates/system_stm32f4xx.c
	$(CC) $(CFLAGS) $(CPPFLAGS) vendor/CMSIS/Device/ST/STM32F4/Source/Templates/system_stm32f4xx.c -c

# Clean up the generated object files and binary
.PHONY: clean
clean:
	rm -f *.o *.elf

# Flash the binary to STM32F401RE using OpenOCD
flash: $(BINARY)
	$(PROGRAMMER) $(PROGRAMMER_FLAGS) -c "program blink.elf verify reset exit"