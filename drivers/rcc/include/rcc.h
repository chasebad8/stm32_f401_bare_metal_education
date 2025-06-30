#ifndef _RCC_H_
#define _RCC_H_
#include <stdint.h>
#include "stm32f4xx.h"

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