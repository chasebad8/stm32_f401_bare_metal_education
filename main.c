#include <stdint.h>
#include "stm32f4xx.h"
#include "usart.h"
#include "gpio.h"
#include "rcc.h"
#include "std_types.h"

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

  rcc_osc_cfg_t osc_cfg = {
    .osc_type = RCC_OSC_HSE,
    .state    = RCC_OSC_BYPASS
  };

  rcc_pll_cfg_t pll_cfg = {
    .pll_src   = RCC_PLL_SRC_HSE,
    .pll_state = RCC_PLL_ON,
    .pll_m = 8,
    .pll_n = 128,
    .pll_p = 4,
    .pll_q = 7
  };

  rcc_clock_cfg_t clk_cfg = {
    .clock_type    = RCC_CLOCK_SYSCLK,
    .sys_clk_src   = RCC_SYSCLK_SRC_PLL,
    .flash_latency = FLASH_ACR_LATENCY_1WS,
    .ahb_clk_div   = RCC_CFGR_HPRE_DIV1
  };

  /* initialize GPIOA PIN 5 (On board LED) */
  gpio_init(GPIOA, &led_cfg);

  /* initialize the HSE oscillator */
  rcc_oscillator_init(&osc_cfg);

  //while(RCC_GET_HSE_READY_FLAG == RESET) {};

  for (uint32_t i = 0; i < 10000; i++);

  /* initialize the PLL */
  rcc_pll_init(&pll_cfg);

  for (uint32_t i = 0; i < 10000; i++);

  /* set the sys clock to PLL */
  rcc_clock_init(&clk_cfg);

  for (uint32_t i = 0; i < 10000; i++);

  /* TEMPORARY */

  rcc_pll_enable(false);

  RCC->APB1ENR |= RCC_APB1ENR_PWREN_Msk;

  for (uint32_t i = 0; i < 10000; i++);

  PWR->CR |= (0b01 << PWR_CR_VOS_Pos);

  rcc_pll_enable(true);

  /* set the ahb_prescaler to 1 and configure the flash wait states */
  clk_cfg.clock_type = RCC_CLOCK_HCLK;
  rcc_clock_init(&clk_cfg);

  /* Set the system clock to use PLL as source */
  /* Initialize USART */
  //usart_init(USART2);
  for (uint32_t i = 0; i < 10000; i++);

  while(1)
  {
    //GPIOA->ODR ^= (1 << LED_PIN);
    gpio_toggle_pin(GPIOA, LED_PIN);

    for (uint32_t i = 0; i < 1000000; i++);

    gpio_toggle_pin(GPIOA, LED_PIN);

    for (uint32_t i = 0; i < 1000000; i++);

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
    for (uint32_t i = 0; i < 3200000; i++);
  }

  return 0;
}