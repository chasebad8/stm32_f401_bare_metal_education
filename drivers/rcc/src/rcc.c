#include "rcc.h"
#include "std_types.h"

/*******************************************************************
 * @name   rcc_oscillator_init
 *
 * @brief  Configure the specified oscillator (HSE, HSI, LSE, or LSI).
 *
 * @param  osc_cfg: pointer to a rcc_osc_cfg_t structure that contains
 *                  the configuration information for the specified oscillator.
 *
 * @return None
 *
 *******************************************************************/
void rcc_oscillator_init(rcc_osc_cfg_t *osc_cfg)
{
   /* HSE and LSE Oscillator can either be in ON, OFF, or BYPASS.
      ON:     Configure a crystal or ceramic resonator with 2 caps, and create a clock.
      BYPASS: OSC_IN receives a clean clock signal.
      OFF:    HSE is disabled.
   */

   /* TODO: ADD READ FLAG READ CHECKS !!! */

   uint8_t curr_sys_clk_cfg = 0;

   if(osc_cfg == NULL)
   {
      return;
   }
   else
   {
      curr_sys_clk_cfg = (RCC->CFGR & RCC_CFGR_SWS);

      switch(osc_cfg->osc_type)
      {
         case RCC_OSC_HSE:
            if(osc_cfg->state == RCC_OSC_ON)
            {
               SET_BIT(RCC->CR, RCC_CR_HSEON);
            }
            else if(osc_cfg->state == RCC_OSC_BYPASS)
            {
               SET_BIT(RCC->CR, RCC_CR_HSEON);
               SET_BIT(RCC->CR, RCC_CR_HSEBYP);
            }
            else if(osc_cfg->state == RCC_OSC_OFF)
            {
               /* If the current sys clock is set to HSE or PLL with HSE reference, the sys clock needs to be changed before turning it off. PLLSRC 1 == HSE */
               if((curr_sys_clk_cfg  == RCC_CFGR_SWS_HSE) ||
                  ((curr_sys_clk_cfg == RCC_CFGR_SWS_PLL) && (RCC->CFGR & RCC_PLLCFGR_PLLSRC)))
               {
                  return;
               }
               else
               {
                  CLEAR_BIT(RCC->CR, RCC_CR_HSEON);
                  CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);
               }
            }
            break;

         case RCC_OSC_HSI:
            if(osc_cfg->state == RCC_OSC_ON)
            {
               SET_BIT(RCC->CR, RCC_CR_HSION);

               /* ADD CALIBRATION IF REQUIRED!! */
            }
            else if(osc_cfg->state == RCC_OSC_OFF)
            {
               /* If the current sys clock is set to HSI or PLL with HSI reference, the sys clock needs to be changed before turning it off  PLLSRC 1 == HSI*/
               if((curr_sys_clk_cfg  == RCC_CFGR_SWS_HSI) ||
                  ((curr_sys_clk_cfg == RCC_CFGR_SWS_PLL) && !(RCC->CFGR & RCC_PLLCFGR_PLLSRC)))
               {
                  return;
               }
               else
               {
                  CLEAR_BIT(RCC->CR, RCC_CR_HSION);
               }
            }
            break;

         case RCC_OSC_LSE:
            if(osc_cfg->state == RCC_OSC_ON)
            {
               SET_BIT(RCC->BDCR, RCC_BDCR_LSEON);
            }
            else if(osc_cfg->state == RCC_OSC_BYPASS)
            {
               SET_BIT(RCC->BDCR, RCC_BDCR_LSEON);
               SET_BIT(RCC->BDCR, RCC_BDCR_LSEBYP);
            }
            else if(osc_cfg->state == RCC_OSC_OFF)
            {
               CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEON);
               CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEBYP);
            }
            break;

         case RCC_OSC_LSI:
            if(osc_cfg->state == RCC_OSC_ON)
            {
               SET_BIT(RCC->CSR, RCC_CSR_LSION);
            }
            else if(osc_cfg->state == RCC_OSC_OFF)
            {
               CLEAR_BIT(RCC->CSR, RCC_CSR_LSION);
            }
            break;
         default:
            return;
      }
   }

   return;
}

/*******************************************************************
 * @name   rcc_pll_init
 *
 * @brief  Configure the on chip PLL
 *
 * @param  pll_cfg: pointer to a rcc_pll_cfg_t structure that contains
 *                  the configuration information for the PLL.
 *
 * @return None
 *
 *******************************************************************/
void rcc_pll_init(rcc_pll_cfg_t *pll_cfg)
{
   if(pll_cfg == NULL)
   {
      return;
   }
   else
   {
      return; // TODO: Implement PLL configuration
   }
}