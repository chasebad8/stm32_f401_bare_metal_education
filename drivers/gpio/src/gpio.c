#include "gpio.h"

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
   if((gpio_cfg->pin <  GPIO_PIN_0) ||
      (gpio_cfg->pin >= GPIO_PIN_MAX))
   {
      return false;
   }
   else if((gpio_cfg->mode <  GPIO_MODE_INPUT) ||
           (gpio_cfg->mode >= GPIO_MODE_ANALOG))
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
            gpio_p->PUPDR &= ~(GPIO_OSPEEED_MASK << (gpio_cfg->pin * GPIO_OSPEEED_BIT_MULT));
            gpio_p->PUPDR |= ((gpio_cfg->speed & GPIO_OSPEEED_MASK) << (gpio_cfg->pin * GPIO_OSPEEED_BIT_MULT));

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