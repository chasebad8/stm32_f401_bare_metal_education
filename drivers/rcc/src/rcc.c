#include "rcc.h"

/*******************************************************************
 * @name   rcc_oscillator_config_hse
 *
 * @brief  Configure the specified oscillator (HSE, HSI, LSE, or LSI).
 *
 * @param  osc_cfg: pointer to a rcc_osc_cfg_t structure that contains
 *                  the configuration information for the specified oscillator.
 *
 * @return None
 *
 *******************************************************************/
static void rcc_oscillator_config_hse(rcc_osc_state_e hse_state)
{
   switch(hse_state)
   {
      case RCC_OSC_ON:
         SET_BIT(RCC->CR, RCC_CR_HSEON);
         break;

      case RCC_OSC_BYPASS:
         SET_BIT(RCC->CR, RCC_CR_HSEON);
         SET_BIT(RCC->CR, RCC_CR_HSEBYP);
         break;

      case RCC_OSC_OFF:
         /* If the current sys clock is set to HSE or PLL with HSE reference, the sys clock needs to be changed before turning it off. PLLSRC 1 == HSE */
         if((RCC_GET_SYS_CLK_SRC()  == RCC_CFGR_SWS_HSE) ||
            ((RCC_GET_SYS_CLK_SRC() == RCC_CFGR_SWS_PLL) &&
             (RCC_GET_PLL_CLK_SRC() == 1)))
         {
            return;
         }
         else
         {
            CLEAR_BIT(RCC->CR, RCC_CR_HSEON);
            CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);
         }

         break;
      default:
         return; // Invalid state
   }
   return;
}

/*******************************************************************
 * @name   rcc_oscillator_config_hsi
 *
 * @brief  Configure the specified oscillator (HSE, HSI, LSE, or LSI).
 *
 * @param  osc_cfg: pointer to a rcc_osc_cfg_t structure that contains
 *                  the configuration information for the specified oscillator.
 *
 * @return None
 *
 *******************************************************************/
static void rcc_oscillator_config_hsi(rcc_osc_state_e hsi_state)
{
   switch(hsi_state)
   {
      case RCC_OSC_ON:
         SET_BIT(RCC->CR, RCC_CR_HSION);
         break;

      case RCC_OSC_OFF:
         /* If the current sys clock is set to HSI or PLL with HSI reference, the sys clock needs to be changed before turning it off  PLLSRC 0 == HSI*/
         if((RCC_GET_SYS_CLK_SRC()  == RCC_CFGR_SWS_HSI) ||
            ((RCC_GET_SYS_CLK_SRC() == RCC_CFGR_SWS_PLL) &&
             (RCC_GET_PLL_CLK_SRC() == 0)))
         {
            return;
         }
         else
         {
            CLEAR_BIT(RCC->CR, RCC_CR_HSION);
         }
         break;

      case RCC_OSC_BYPASS:
      default:
         return; // Invalid state
   }
   return;
}

/*******************************************************************
 * @name   rcc_oscillator_config_lse
 *
 * @brief  Configure the specified oscillator (HSE, HSI, LSE, or LSI).
 *
 * @param  osc_cfg: pointer to a rcc_osc_cfg_t structure that contains
 *                  the configuration information for the specified oscillator.
 *
 * @return None
 *
 *******************************************************************/
static void rcc_oscillator_config_lse(rcc_osc_state_e lse_state)
{
   switch(lse_state)
   {
      case RCC_OSC_ON:
         SET_BIT(RCC->BDCR, RCC_BDCR_LSEON);
         break;

      case RCC_OSC_BYPASS:
         SET_BIT(RCC->BDCR, RCC_BDCR_LSEON);
         SET_BIT(RCC->BDCR, RCC_BDCR_LSEBYP);
         break;

      case RCC_OSC_OFF:
         CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEON);
         CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEBYP);
         break;

      default:
         return; // Invalid state
   }
   return;
}

/*******************************************************************
 * @name   rcc_oscillator_config_lsi
 *
 * @brief  Configure the specified oscillator (HSE, HSI, LSE, or LSI).
 *
 * @param  osc_cfg: pointer to a rcc_osc_cfg_t structure that contains
 *                  the configuration information for the specified oscillator.
 *
 * @return None
 *
 *******************************************************************/
static void rcc_oscillator_config_lsi(rcc_osc_state_e lsi_state)
{
   switch(lsi_state)
   {
      case RCC_OSC_ON:
         SET_BIT(RCC->CSR, RCC_CSR_LSION);
         break;

      case RCC_OSC_OFF:
         CLEAR_BIT(RCC->CSR, RCC_CSR_LSION);
         break;

      case RCC_OSC_BYPASS:
      default:
         return; // Invalid state
   }
   return;
}

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

   if(osc_cfg == NULL)
   {
      return;
   }
   else
   {
      switch(osc_cfg->osc_type)
      {
         case RCC_OSC_HSE:
            rcc_oscillator_config_hse(osc_cfg->state);

            break;
         case RCC_OSC_HSI:
            /* TODO! Add calibration of the oscillator to mitigate ppm deviation */
            rcc_oscillator_config_hsi(osc_cfg->state);
            break;

         case RCC_OSC_LSE:
            /* TODO! Add config to briefly enable Backup Domain control register*/
            rcc_oscillator_config_lse(osc_cfg->state);
            break;

         case RCC_OSC_LSI:
            rcc_oscillator_config_lsi(osc_cfg->state);
            break;
         default:
            return;
      }
   }

   return;
}

/*******************************************************************
 * @name   rcc_pll_enable
 *
 * @brief  enable or disable the on chip PLL
 *
 * @param  pll_enable: true to enable, false to disable
 *
 * @return None
 *
 *******************************************************************/
void rcc_pll_enable(bool pll_enable)
{
   if(pll_enable == true)
   {
      SET_BIT(RCC->CR, RCC_CR_PLLON);
   }
   else
   {
      CLEAR_BIT(RCC->CR, RCC_CR_PLLON);
   }

   /* TODO: Add a sys_tick timeout here !! */
   /* wait until PLL is disabled */
   //while(RCC_GET_PLL_READY_FLAG != RESET) {};
   for (uint32_t i = 0; i < 1000000; i++);

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
   /* Do not change the re-config PLL if it is currently used as sys clock */
   else if(RCC_GET_SYS_CLK_SRC() == RCC_CFGR_SWS_PLL)
   {
      return;
   }
   else if(pll_cfg->pll_state == RCC_PLL_ON)
   {
      /* disable the PLL. The PLL cannot be modified while it is enabled. */
      rcc_pll_enable(false);

      WRITE_REG(RCC->PLLCFGR, ((pll_cfg->pll_src << RCC_PLLCFGR_PLLSRC_Pos) | \
                               (pll_cfg->pll_m   << RCC_PLLCFGR_PLLM_Pos)   | \
                               (pll_cfg->pll_n   << RCC_PLLCFGR_PLLN_Pos)   | \
                               (pll_cfg->pll_p   << RCC_PLLCFGR_PLLP_Pos)   | \
                               (pll_cfg->pll_q   << RCC_PLLCFGR_PLLQ_Pos)));

      /* re-enable PLL */
      rcc_pll_enable(true);
   }
   else /* RCC_PLL_OFF */
   {
      rcc_pll_enable(false);

      while(RCC_GET_PLL_READY_FLAG != RESET) {};
   }

   return;
}

/*******************************************************************
 * @name   rcc_clock_cfg_sys_clk
 *
 * @brief  Configure the system clock
 *
 * @param  sys_clk_src: source of the system clock.
 *
 * @return None
 *
 *******************************************************************/
static void rcc_clock_cfg_sys_clk(rcc_sys_clk_src_e sys_clk_src)
{
   uint32_t sys_clk_arr[] = { RCC_CFGR_SW_HSI,
                              RCC_CFGR_SW_HSE,
                              RCC_CFGR_SW_PLL };

   bool clk_ready_arr[] = { RCC_GET_HSI_READY_FLAG,
                            RCC_GET_HSE_READY_FLAG,
                            RCC_GET_PLL_READY_FLAG };

   /* If the ready flag is set for the oscillator or PLL, we can set it as the sys clock */
   if(clk_ready_arr[sys_clk_src] == true)
   {
      MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, (sys_clk_arr[sys_clk_src] << RCC_CFGR_SW_Pos));
   }

   return;
}

/*******************************************************************
 * @name   rcc_clock_cfg_h_clk
 *
 * @brief  Configure the h clock. This is the CPU clock which is
 *         derived from the sys clock and has an AHB prescaler.
 *
 * @param  osc_cfg: pointer to a rcc_osc_cfg_t structure that contains
 *                  the configuration information for the specified oscillator.
 *
 * @return None
 *
 *******************************************************************/
static void rcc_clock_cfg_h_clk(uint8_t ahb_clk_div)
{
   if((ahb_clk_div != RCC_CFGR_HPRE_DIV1)   &&
      ((ahb_clk_div > RCC_CFGR_HPRE_DIV512) ||
       (ahb_clk_div < RCC_CFGR_HPRE_DIV2)))
   {
      return; // Invalid division factor
   }
   else
   {
      MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE, (ahb_clk_div << RCC_CFGR_HPRE_Pos));
   }

   return;
}

/*******************************************************************
 * @name   rcc_clock_init
 *
 * @brief  Configure the specified clock
 *
 * @param  clk_cfg: pointer to a rcc_clock_cfg_t structure that contains
 *                  the configuration information a clock
 *
 * @return None
 *
 *******************************************************************/
void rcc_clock_init(rcc_clock_cfg_t *clk_cfg)
{
   if(clk_cfg == NULL)
   {
      return;
   }
   else
   {
      /* If increasing our flash latency wait states, assume it means the frequency
         of the CPU clock (hclk) is being increased. Therefore change wait states now. */
      if(READ_BIT(FLASH->ACR, FLASH_ACR_LATENCY) < clk_cfg->flash_latency)
      {
         MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, (clk_cfg->flash_latency << FLASH_ACR_LATENCY_Pos));
      }

      switch(clk_cfg->clock_type)
      {
         case RCC_CLOCK_SYSCLK:
            rcc_clock_cfg_sys_clk(clk_cfg->sys_clk_src);
            break;

         case RCC_CLOCK_HCLK:
            rcc_clock_cfg_h_clk(clk_cfg->ahb_clk_div);
            break;

         case RCC_CLOCK_PCLK1:
         case RCC_CLOCK_PCLK2:
         default:
            return;
      }

      /* If decreasing our flash lateny, assume CPU frequency is being lowered, change wait states last. */
      if(READ_BIT(FLASH->ACR, FLASH_ACR_LATENCY) > clk_cfg->flash_latency)
      {
         MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, (clk_cfg->flash_latency << FLASH_ACR_LATENCY_Pos));
      }
   }

   return;
}