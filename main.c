#include <stdint.h>
#include "stm32f4xx.h"
#include "usart.h"
#include "gpio.h"
#include "rcc.h"

#define LED_PIN GPIO_PIN_5

int main(void)
{

   /* Initialize all GPIO peripheral clocks */
   RCC_GPIOA_CLK_ENABLE();
   RCC_GPIOB_CLK_ENABLE();
   RCC_GPIOC_CLK_ENABLE();
   RCC_GPIOH_CLK_ENABLE();

  gpio_init_cfg_t led_cfg = {
    .pin   = LED_PIN,
    .mode  = GPIO_MODE_OUTPUT,
    .pull  = GPIO_PULL_NONE,
    .speed = GPIO_SPEED_HIGH,
    .otype = GPIO_OTYPE_PP,
    .alt_func = 0
  };


  /* initialize GPIOA PIN 5 (On board LED) */
  gpio_init(GPIOA, &led_cfg);

  /* Initialize USART */
  //usart_init(USART2);

  while(1)
  {
    //GPIOA->ODR ^= (1 << LED_PIN);
    gpio_toggle_pin(GPIOA, LED_PIN);

    for (uint32_t i = 0; i < 50000; i++);

    gpio_toggle_pin(GPIOA, LED_PIN);

    for (uint32_t i = 0; i < 50000; i++);

    gpio_toggle_pin(GPIOA, LED_PIN);

    // usart_write(USART2, 'H');
    // usart_write(USART2, 'e');
    // usart_write(USART2, 'l');
    // usart_write(USART2, 'l');
    // usart_write(USART2, 'o');
    // usart_write(USART2, ' ');
    // usart_write(USART2, 'W');
    // usart_write(USART2, 'o');
    // usart_write(USART2, 'r');
    // usart_write(USART2, 'l');
    // usart_write(USART2, 'd');
    // usart_write(USART2, '\n');
    for (uint32_t i = 0; i < 1000000; i++);
  }

  return 0;
}