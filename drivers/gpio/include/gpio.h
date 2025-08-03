#ifndef _GPIO_H_
#define _GPIO_H_
#include <stdint.h>
#include "stm32f4xx.h"

#define GPIO_MODE_MASK        (0b11)
#define GPIO_MODE_BIT_MULT    (0x2)
#define GPIO_PUPD_MASK        (0b11)
#define GPIO_PUPD_BIT_MULT    (0x2)
#define GPIO_OTYPE_MASK       (0b1)
#define GPIO_OSPEEED_MASK     (0b11)
#define GPIO_OSPEEED_BIT_MULT (0x2)
#define GPIO_AFR_MASK         (0xF)
#define GPIO_AFR_BIT_MULT     (0x4)

#define GPIO_PIN_MASK(gpio_pin) (1U << (gpio_pin))

// typedef enum
// {
//    GPIO_PIN_0  = (1U << 0),  // Pin 0
//    GPIO_PIN_1  = (1U << 1),  // Pin 1
//    GPIO_PIN_2  = (1U << 2),  // Pin 2
//    GPIO_PIN_3  = (1U << 3),  // Pin 3
//    GPIO_PIN_4  = (1U << 4),  // Pin 4
//    GPIO_PIN_5  = (1U << 5),  // Pin 5
//    GPIO_PIN_6  = (1U << 6),  // Pin 6
//    GPIO_PIN_7  = (1U << 7),  // Pin 7
//    GPIO_PIN_8  = (1U << 8),  // Pin 8
//    GPIO_PIN_9  = (1U << 9),  // Pin 9
//    GPIO_PIN_10 = (1U << 10), // Pin 10
//    GPIO_PIN_11 = (1U << 11), // Pin 11
//    GPIO_PIN_12 = (1U << 12), // Pin 12
//    GPIO_PIN_13 = (1U << 13), // Pin 13
//    GPIO_PIN_14 = (1U << 14), // Pin 14
//    GPIO_PIN_15 = (1U << 15),  // Pin 15

//    GPIO_PIN_MAX // Maximum pin value
// }  gpio_pin_e;

typedef enum
{
  GPIO_PIN_CLEAR = 0,
  GPIO_PIN_SET
} gpio_pin_state_e;

typedef enum
{
   GPIO_PIN_0 = 0,
   GPIO_PIN_1,
   GPIO_PIN_2,
   GPIO_PIN_3,
   GPIO_PIN_4,
   GPIO_PIN_5,
   GPIO_PIN_6,
   GPIO_PIN_7,
   GPIO_PIN_8,
   GPIO_PIN_9,
   GPIO_PIN_10,
   GPIO_PIN_11,
   GPIO_PIN_12,
   GPIO_PIN_13,
   GPIO_PIN_14,
   GPIO_PIN_15,

   GPIO_PIN_MAX // Maximum pin value
}  gpio_pin_e;

typedef enum
{
   GPIO_MODE_INPUT     = 0b00, // Input mode
   GPIO_MODE_OUTPUT    = 0b01, // Output mode/.
   GPIO_MODE_ALTERNATE = 0b10, // Alternate function mode
   GPIO_MODE_ANALOG    = 0b11,  // Analog mode

   GPIO_MODE_MAX
} gpio_mode_e;

typedef enum
{
   GPIO_PULL_NONE  = 0b00, // No pull-up or pull-down
   GPIO_PULL_UP    = 0b01, // Pull-up
   GPIO_PULL_DOWN  = 0b10  // Pull-down
} gpio_pull_e;

typedef enum
{
   GPIO_SPEED_LOW       = 0b00, // Low speed
   GPIO_SPEED_MEDIUM    = 0b01, // Medium speed
   GPIO_SPEED_HIGH      = 0b10, // High speed
   GPIO_SPEED_VERY_HIGH = 0b11  // Very high speed
} gpio_speed_e;

typedef enum
{
   GPIO_OTYPE_PP = 0b0, // Push-pull output type
   GPIO_OTYPE_OD = 0b1  // Open-drain output type
} gpio_otype_e;

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
   gpio_mode_e  mode;     // GPIO mode (input, output, alternate, analog)
   gpio_pull_e  pull;     // Pull-up or pull-down configuration
   gpio_speed_e speed;    // GPIO speed (low, medium, high, very high)
   gpio_otype_e otype;    // Output type (push-pull or open-drain)
   uint8_t      alt_func; // Alternate function number (if applicable)

} gpio_init_cfg_t;

/*******************************************************************
 * @name   gpio_init
 *
 * @brief  Configure GPIO.
 *
 * @param  gpio_p: pointer to the selectec GPIO peripheral
 *                 (e.g. GPIOA, GPIOB, etc.)
 * @param  gpio_cfg: structure containing the GPIO configuration
 *                    parameters such as mode, pull-up/pull-down,
 *                    speed, and alternate function.
 * @return None
 *
 *******************************************************************/
void gpio_init(GPIO_TypeDef *gpio_p, gpio_init_cfg_t *gpio_cfg);

/*******************************************************************
 * @name   gpio_deinit
 *
 * @brief  Deinitizalize GPIO. Set values back to defaults.
 *
 * @param  gpio_p: pointer to the selectec GPIO peripheral
 *                 (e.g. GPIOA, GPIOB, etc.)
 * @param  gpio_pin: GPIO pin number (e.g., GPIO_PIN_0, GPIO_PIN_1, etc.)
 *
 * @return None
 *
 *******************************************************************/
void gpio_deinit(GPIO_TypeDef *gpio_p, gpio_pin_e gpio_pin);

/*******************************************************************
 * @name   gpio_read_pin
 *
 * @brief  Read from a GPIO pin.
 *
 * @param  gpio_p: pointer to the selectec GPIO peripheral
 *                 (e.g. GPIOA, GPIOB, etc.)
 * @param  gpio_pin: GPIO pin number (e.g., GPIO_PIN_0, GPIO_PIN_1, etc.)
 *
 * @return gpio_pin_state_e GPIO_PIN_SET (1) or GPIO_PIN_CLEAR (0)
 *
 *******************************************************************/
gpio_pin_state_e gpio_read_pin(GPIO_TypeDef *gpio_p, gpio_pin_e gpio_pin);

/*******************************************************************
 * @name   gpio_write_pin
 *
 * @brief  Write to a GPIO pin.
 *
 * @param  gpio_p: pointer to the selectec GPIO peripheral
 *                 (e.g. GPIOA, GPIOB, etc.)
 * @param  gpio_pin: GPIO pin number (e.g., GPIO_PIN_0, GPIO_PIN_1, etc.)
 * @param  state:    GPIO pin state (GPIO_PIN_SET or GPIO_PIN_CLEAR)
 *
 * @return None
 *
 *******************************************************************/
void gpio_write_pin(GPIO_TypeDef *gpio_p, gpio_pin_e gpio_pin, gpio_pin_state_e state);

/*******************************************************************
 * @name   gpio_toggle_pin
 *
 * @brief  Toggle a GPIO pin.
 *
 * @param  gpio_p: pointer to the selectec GPIO peripheral
 *                 (e.g. GPIOA, GPIOB, etc.)
 * @param  gpio_pin: GPIO pin number (e.g., GPIO_PIN_0, GPIO_PIN_1, etc.)
 *
 * @return None
 *
 *******************************************************************/
void gpio_toggle_pin(GPIO_TypeDef *gpio_p, gpio_pin_e gpio_pin);

#endif