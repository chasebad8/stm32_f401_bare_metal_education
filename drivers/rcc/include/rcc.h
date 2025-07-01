#ifndef _RCC_H_
#define _RCC_H_
#include <stdint.h>
#include "stm32f4xx.h"

/* This was taken mostly from the HAL libraries, but I wanted to try out the
   do while macro. Without the do-while it wouldn't execute properly */
#define RCC_GPIOA_CLK_ENABLE()  do { \
                                    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN); \
                                    tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN); \
                                    tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN); \
                                 } while(0U)

#define RCC_GPIOB_CLK_ENABLE()  do { \
                                    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN); \
                                    tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN); \
                                    tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN); \
                                 } while(0U)

#define RCC_GPIOC_CLK_ENABLE()  do { \
                                    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN); \
                                    tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN); \
                                    tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN); \
                                 } while(0U)

#define RCC_GPIOH_CLK_ENABLE()  do { \
                                    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOHEN); \
                                    tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOHEN); \
                                    tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOHEN); \
                                 } while(0U)

/**
  * @brief  RCC Internal/External Oscillator (HSE, HSI, LSE and LSI) config struct
  *
  *         HSE: High Speed External oscillator
  *         HSI: High Speed Internal oscillator
  *         LSE: Low  Speed External oscillator
  *         LSI: Low  Speed Internal oscillator
 **/
typedef struct
{
   uint8_t osc_type;  // Oscillator type: 0 for HSE, 1 for HSI, 2 for LSE, 3 for LSI

} rcc_osc_cfg_t;

#endif