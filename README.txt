I wanted to get familiar with linking and flashing an STM32 without all the high level libraries and frameworks. These blogs by Klein Embedded really helped me understand and implement this project.

https://kleinembedded.com/stm32-without-cubeide-part-2-cmsis-make-and-clock-configuration/

Important ST Links
STM32F401 Reference Manual
https://www.st.com/resource/en/reference_manual/rm0368-stm32f401xbc-and-stm32f401xde-advanced-armbased-32bit-mcus-stmicroelectronics.pdf

STM32 Nucleo 64 Dev Board User Manual
(Info on how USART2 is connected to ST Link On-Board Debugger (STM32F103CBT6))
https://www.st.com/resource/en/user_manual/um1724-stm32-nucleo64-boards-mb1136-stmicroelectronics.pdf

I have also been using CubeMX to configure some higher level components/modules that I would like to implement. I then export that to code, and then use that as another method of reference.

DEBUGGING:
To debug I am using the STM32F401re's ST Link HW Debugger connected via openOCD which connects to GDB.
Steps:
1) run a make of your binary.
2) create an openOCD server which will connect to st-link on the board
   openocd -f interface/stlink-v2-1.cfg -f target/stm32f4x.cfg
3) open GDB with your binary
   arm-none-eabi-gdb path/to/your_program.elf
4) from GDB connect to the remote openOCD server
   target remote localhost:3333
5) Reset the board and halt its execution
   monitor reset halt
6) load the fw onto the board
   load
7) add a breakpoint to main and continue
   break main
   continue
8) you should now have full GDB functionality.

Note: All the CMSIS pointer defines are pre-processor macro's so you will not have access to them during debugging. I think -g3 in the CFLAGS will allow it (to test).
If you want to read GPIOA->MODR you could also directly cast and read the address that it corresponds to
p/x ((GPIO_TypeDef*)0x40020000)->MODER
