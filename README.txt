I wanted to get familiar with linking and flashing an STM32 without all the high level libraries and frameworks. These blogs by Klein Embedded really helped me understand and implement this project.

https://kleinembedded.com/stm32-without-cubeide-part-2-cmsis-make-and-clock-configuration/

Important ST Links
STM32F401 Reference Manual
https://www.st.com/resource/en/reference_manual/rm0368-stm32f401xbc-and-stm32f401xde-advanced-armbased-32bit-mcus-stmicroelectronics.pdf

STM32 Nucleo 64 Dev Board User Manual
(Info on how USART2 is connected to ST Link On-Board Debugger (STM32F103CBT6))
https://www.st.com/resource/en/user_manual/um1724-stm32-nucleo64-boards-mb1136-stmicroelectronics.pdf

I have also been using CubeMX to configure some higher level components/modules that I would like to implement. I then export that to code, and then use that as another method of reference.
