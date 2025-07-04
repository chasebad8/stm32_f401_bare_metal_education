#ifndef _GPIO_H_
#define _GPIO_H_
#include <stdint.h>
#include "stm32f4xx.h"

typedef enum
{
   GPIO_PIN_0  = (1U << 0),  // Pin 0
   GPIO_PIN_1  = (1U << 1),  // Pin 1
   GPIO_PIN_2  = (1U << 2),  // Pin 2
   GPIO_PIN_3  = (1U << 3),  // Pin 3
   GPIO_PIN_4  = (1U << 4),  // Pin 4
   GPIO_PIN_5  = (1U << 5),  // Pin 5
   GPIO_PIN_6  = (1U << 6),  // Pin 6
   GPIO_PIN_7  = (1U << 7),  // Pin 7
   GPIO_PIN_8  = (1U << 8),  // Pin 8
   GPIO_PIN_9  = (1U << 9),  // Pin 9
   GPIO_PIN_10 = (1U << 10), // Pin 10
   GPIO_PIN_11 = (1U << 11), // Pin 11
   GPIO_PIN_12 = (1U << 12), // Pin 12
   GPIO_PIN_13 = (1U << 13), // Pin 13
   GPIO_PIN_14 = (1U << 14), // Pin 14
   GPIO_PIN_15 = (1U << 15),  // Pin 15

   GPIO_PIN_MAX // Maximum pin value
}  gpio_pin_t;

typedef enum
{
   GPIO_MODE_INPUT     = 0b00, // Input mode
   GPIO_MODE_OUTPUT    = 0b01, // Output mode/.
   GPIO_MODE_ALTERNATE = 0b10, // Alternate function mode
   GPIO_MODE_ANALOG    = 0b11  // Analog mode
} gpio_mode_t;

typedef enum
{
   GPIO_PULL_NONE  = 0b00, // No pull-up or pull-down
   GPIO_PULL_UP    = 0b01, // Pull-up
   GPIO_PULL_DOWN  = 0b10  // Pull-down
} gpio_pull_t;

typedef enum
{
   GPIO_SPEED_LOW       = 0b00, // Low speed
   GPIO_SPEED_MEDIUM    = 0b01, // Medium speed
   GPIO_SPEED_HIGH      = 0b10, // High speed
   GPIO_SPEED_VERY_HIGH = 0b11  // Very high speed
} gpio_speed_t;

typedef enum
{
   GPIO_OTYPE_PP = 0b0, // Push-pull output type
   GPIO_OTYPE_OD = 0b1  // Open-drain output type
} gpio_otype_t;

/**
  * @brief  GPIO initialization configuration structure
  *
  * @param  pin: GPIO pin number (e.g., B1, GPIO_PIN_0, GPIO_PIN_1, etc.)
  * @param  mode: GPIO mode (input, output, alternate, analog)
  * @param  pull: Pull-up or pull-down configuration
  * @param  speed: GPIO speed (low, medium, high, very high)
  * @param  otype: Output type (push-pull or open-drain)
  * @param  alt_func: Alternate function number (if applicable)
  *
 **/
typedef struct
{
   uint8_t      pin;      // GPIO pin number (e.g., B1, GPIO_PIN_0, GPIO_PIN_1, etc.)
   gpio_mode_t  mode;     // GPIO mode (input, output, alternate, analog)
   gpio_pull_t  pull;     // Pull-up or pull-down configuration
   gpio_speed_t speed;    // GPIO speed (low, medium, high, very high)
   gpio_otype_t otype;    // Output type (push-pull or open-drain)
   uint8_t      alt_func; // Alternate function number (if applicable)

} gpio_init_cfg_t;

/*******************************************************************
 * @name   gpio_init
 *
 * @brief  Configure GPIO.
 *
 * @param  gpio_p: pointer to the selectec GPIO peripheral
 *                 (e.g. GPIOA, GPIOB, etc.)
 * @param  gpio_init: structure containing the GPIO configuration
 *                    parameters such as mode, pull-up/pull-down,
 *                    speed, and alternate function.
 * @return None
 *
 *******************************************************************/
void gpio_init(GPIO_TypeDef *gpio_p_ptr, gpio_init_cfg_t gpio_init);

#endif