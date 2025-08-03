#ifndef _RCC_H_
#define _RCC_H_
#include <stdint.h>
#include "stm32f4xx.h"

/* This was taken mostly from the HAL libraries, but I wanted to try out the
   do while macro. Without the do-while it wouldn't execute properly */
#define RCC_GPIOA_CLK_ENABLE()  do { \
                                    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN); \
                                    uint32_t tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN); \
                                    tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN); \
                                    (void)tmpreg; \
                                 } while(0U)

#define RCC_GPIOB_CLK_ENABLE()  do { \
                                    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN); \
                                    uint32_t tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN); \
                                    tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN); \
                                    (void)tmpreg; \
                                 } while(0U)

#define RCC_GPIOC_CLK_ENABLE()  do { \
                                    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN); \
                                    uint32_t tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN); \
                                    tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN); \
                                    (void)tmpreg; \
                                 } while(0U)

#define RCC_GPIOH_CLK_ENABLE()  do { \
                                    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOHEN); \
                                    uint32_t tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOHEN); \
                                    tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOHEN); \
                                    (void)tmpreg; \
                                 } while(0U)

/*******************************************************************
 *                RCC OSCILLATOR CONFIGURATION                     *
 *******************************************************************/
typedef enum
{
   RCC_OSC_HSE = 0, // High Speed External oscillator
   RCC_OSC_HSI,     // High Speed Internal oscillator
   RCC_OSC_LSE,     // Low  Speed External oscillator
   RCC_OSC_LSI      // Low  Speed Internal oscillator

} rcc_osc_e;

typedef enum
{
   RCC_OSC_OFF = 0, // Oscillator is OFF
   RCC_OSC_ON,      // Oscillator is ON
   RCC_OSC_BYPASS   // Oscillator is BYPASS

} rcc_osc_state_e;

/**
  * @brief  RCC Internal/External Oscillator (HSE, HSI, LSE and LSI) config struct
  *
  * @param  osc_type:  Oscillator type: 0 for HSE, 1 for HSI, 2 for LSE, 3 for LSI
  * @param  state:     Oscillator state: 0 for OFF, 1 for ON, 2 for BYPASS
  *
 **/
typedef struct
{
   rcc_osc_e       osc_type;
   rcc_osc_state_e state;

} rcc_osc_cfg_t;

/************************************************************
 *                RCC PLL CONFIGURATION                     *
 ************************************************************/
typedef struct
{
   uint8_t  pll_src; // PLL source clock: 0 for HSI, 1 for HSE

   uint8_t  pll_m; // Division factor for PLL VCO input clock
   uint16_t pll_n; // Multiplication factor for PLL VCO output clock
   uint8_t  pll_p; // Division factor for main system clock (SYSCLK) from PLL VCO output clock
   uint8_t  pll_q; // Division factor for USB OTG FS, SDIO and RNG clocks from PLL VCO output clock

} rcc_pll_cfg_t;

#endif