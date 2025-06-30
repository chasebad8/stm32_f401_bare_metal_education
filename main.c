#include <stdint.h>
#include "stm32f4xx.h"
#include "usart.h"
#include "rcc.h"

#define LED_PIN 5

void main(void)
{
  /* Initialize USART */
  usart_init(USART2);

  //rcc_init();

  /* initialize GPIOA PA5 (Onboard LED) */
  RCC->AHB1ENR |= (1 << RCC_AHB1ENR_GPIOAEN_Pos);

  // do two dummy reads after enabling the peripheral clock, as per the errata
  volatile uint32_t dummy;
  dummy = RCC->AHB1ENR;
  dummy = RCC->AHB1ENR;

  GPIOA->MODER |= (1 << GPIO_MODER_MODER5_Pos);



  while(1)
  {
    GPIOA->ODR ^= (1 << LED_PIN);
    usart_write(USART2, 'H');
    usart_write(USART2, 'e');
    usart_write(USART2, 'l');
    usart_write(USART2, 'l');
    usart_write(USART2, 'o');
    usart_write(USART2, ' ');
    usart_write(USART2, 'W');
    usart_write(USART2, 'o');
    usart_write(USART2, 'r');
    usart_write(USART2, 'l');
    usart_write(USART2, 'd');
    usart_write(USART2, '\n');
    for (uint32_t i = 0; i < 1000000; i++);
  }
}