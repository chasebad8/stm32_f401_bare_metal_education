#include "gpio.h"

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
void gpio_init(GPIO_TypeDef *gpio_p_ptr, gpio_init_cfg_t gpio_init)
{

}