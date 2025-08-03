#include "gpio.h"
#include "std_types.h"

/*******************************************************************
 * @name   gpio_validate_cfg
 *
 * @brief  Validate GPIO config.
 *
 * @param  gpio_cfg: structure containing the GPIO configuration
 *                    parameters such as mode, pull-up/pull-down,
 *                    speed, and alternate function.
 * @return bool
 *
 *******************************************************************/
static bool gpio_validate_cfg(gpio_init_cfg_t *gpio_cfg)
{
   if(gpio_cfg->pin >= GPIO_PIN_MAX)
   {
      return false;
   }
   else if(gpio_cfg->mode >= GPIO_MODE_MAX)
   {
      return false;
   }

   return true;
}

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
void gpio_init(GPIO_TypeDef *gpio_p, gpio_init_cfg_t *gpio_cfg)
{
   if((gpio_p == NULL) || (gpio_cfg == NULL))
   {
      return;
   }
   else if(gpio_validate_cfg(gpio_cfg) == false)
   {
      return;
   }
   else
   {
      /* configure the pin mode */
      gpio_p->MODER &= ~(GPIO_MODE_MASK << (gpio_cfg->pin * GPIO_MODE_BIT_MULT));
      gpio_p->MODER |= ((gpio_cfg->mode & GPIO_MODE_MASK) << (gpio_cfg->pin * GPIO_MODE_BIT_MULT));

      /* configure the pin pull up-down resistor */
      gpio_p->PUPDR &= ~(GPIO_PUPD_MASK << (gpio_cfg->pin * GPIO_PUPD_BIT_MULT));
      gpio_p->PUPDR |= ((gpio_cfg->pull & GPIO_PUPD_MASK) << (gpio_cfg->pin * GPIO_PUPD_BIT_MULT));

      switch(gpio_cfg->mode)
      {
         case GPIO_MODE_INPUT:
            /* nothing to do as of right now */
            break;

         case GPIO_MODE_OUTPUT:
         case GPIO_MODE_ALTERNATE:
            /* configure the output type register */
            gpio_p->OTYPER &= ~(GPIO_OTYPE_MASK << gpio_cfg->pin);
            gpio_p->OTYPER |= (gpio_cfg->pull << gpio_cfg->pin);

            /* configure the output speed registor */
            gpio_p->OSPEEDR &= ~(GPIO_OSPEEED_MASK << (gpio_cfg->pin * GPIO_OSPEEED_BIT_MULT));
            gpio_p->OSPEEDR |= ((gpio_cfg->speed & GPIO_OSPEEED_MASK) << (gpio_cfg->pin * GPIO_OSPEEED_BIT_MULT));

            if(gpio_cfg->mode == GPIO_MODE_ALTERNATE)
            {
               /* configure the alternate function register */
               gpio_p->AFR[gpio_cfg->pin / 8] &= ~(GPIO_AFR_MASK << ((gpio_cfg->pin % 8) * GPIO_AFR_BIT_MULT));
               gpio_p->AFR[gpio_cfg->pin / 8] |= ((gpio_cfg->alt_func & GPIO_AFR_MASK) << ((gpio_cfg->pin % 8) * GPIO_AFR_BIT_MULT));
            }

            break;

         case GPIO_MODE_ANALOG:
            /* clear pupd since it is not in use for analog mode */
            gpio_p->PUPDR &= ~(GPIO_PUPD_MASK << (gpio_cfg->pin * GPIO_PUPD_BIT_MULT));
            break;

         default:
            return; // Invalid mode
      }
   }
}

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
void gpio_deinit(GPIO_TypeDef *gpio_p, gpio_pin_e gpio_pin)
{
   if((gpio_p == NULL) ||
      (gpio_pin > GPIO_PIN_MAX))
   {
      return;
   }
   else
   {
      /* Reset all fields to their defaults (0) for specific pin */
      gpio_p->MODER   &= ~(GPIO_MODE_MASK    << (gpio_pin * GPIO_MODE_BIT_MULT));
      gpio_p->OSPEEDR &= ~(GPIO_OSPEEED_MASK << (gpio_pin * GPIO_OSPEEED_BIT_MULT));
      gpio_p->OTYPER  &= ~(GPIO_OTYPE_MASK   << (gpio_pin));
      gpio_p->PUPDR   &= ~(GPIO_PUPD_MASK    << (gpio_pin * GPIO_PUPD_BIT_MULT));
      gpio_p->AFR[gpio_pin / 8] &= ~(GPIO_AFR_MASK << ((gpio_pin % 8) * GPIO_AFR_BIT_MULT));
   }
}

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
gpio_pin_state_e gpio_read_pin(GPIO_TypeDef *gpio_p, gpio_pin_e gpio_pin)
{
   if((gpio_p == NULL) ||
      (gpio_pin > GPIO_PIN_MAX))
   {
      return GPIO_PIN_CLEAR;
   }
   else
   {
      return ((gpio_p->IDR) & (1 << gpio_pin));
   }
}

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
void gpio_write_pin(GPIO_TypeDef *gpio_p, gpio_pin_e gpio_pin, gpio_pin_state_e state)
{
   if((gpio_p == NULL) ||
      (gpio_pin > GPIO_PIN_MAX))
   {
      return;
   }
   else if(state == GPIO_PIN_SET)
   {
      /* The BSRR reg least significant 16 bits is a set */
      gpio_p->BSRR = gpio_pin;
   }
   else if(state == GPIO_PIN_CLEAR)
   {
      /* The BSRR reg most significant 16 bits is a clear. (it will clear lsb bits) */
      gpio_p->BSRR = (gpio_pin << 16);
   }
}

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
void gpio_toggle_pin(GPIO_TypeDef *gpio_p, gpio_pin_e gpio_pin)
{
   uint32_t odr;

   /* read Output Data Register */
   odr = gpio_p->ODR;

   /* when odr is 1 BSSR ms16b will be 1 and ls16b will be 0.
      since we want to toggle, flip these bits with whatever their
      current value is. */
   gpio_p->BSRR = ((odr & GPIO_PIN_MASK(gpio_pin)) << 16) | (~odr & GPIO_PIN_MASK(gpio_pin));
}