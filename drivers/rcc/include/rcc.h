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

#define RCC_GET_HSE_READY_FLAG (RCC->CR   & RCC_CR_HSERDY)
#define RCC_GET_HSI_READY_FLAG (RCC->CR   & RCC_CR_HSIRDY)
#define RCC_GET_LSE_READY_FLAG (RCC->BDCR & RCC_BDCR_LSERDY)
#define RCC_GET_LSI_READY_FLAG (RCC->CSR  & RCC_CSR_LSIRDY)
#define RCC_GET_PLL_READY_FLAG (RCC->CR   & RCC_CR_PLLRDY)

#define RCC_GET_SYS_CLK_SRC() ((RCC->CFGR & RCC_CFGR_SWS))
#define RCC_GET_PLL_CLK_SRC() ((RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC))

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
#define RCC_PLL_ON 1
#define RCC_PLL_OFF 0

#define RCC_PLL_SRC_HSI 0
#define RCC_PLL_SRC_HSE 1

 typedef struct
{
   uint8_t  pll_src;   // PLL source clock: 0 for HSI, 1 for HSE
   uint8_t  pll_state; // PLL state: 0 for disabled, 1 for enabled

   uint8_t  pll_m; // Division factor for PLL VCO input clock
   uint16_t pll_n; // Multiplication factor for PLL VCO output clock
   uint8_t  pll_p; // Division factor for main system clock (SYSCLK) from PLL VCO output clock
   uint8_t  pll_q; // Division factor for USB OTG FS, SDIO and RNG clocks from PLL VCO output clock

} rcc_pll_cfg_t;

/************************************************************
 *                RCC CLOCK CONFIGURATION                   *
 ************************************************************/
typedef enum
{
   RCC_CLOCK_SYSCLK = 0, // System clock
   RCC_CLOCK_HCLK,       // AHB  aka CPU clock
   RCC_CLOCK_PCLK1,      // APB1 clock
   RCC_CLOCK_PCLK2       // APB2 clock

} rcc_clock_type_e;

typedef enum
{
   RCC_SYSCLK_SRC_HSI = 0, // System clock source is HSI
   RCC_SYSCLK_SRC_HSE,     // System clock source is HSE
   RCC_SYSCLK_SRC_PLL      // System clock source is PLL

} rcc_sys_clk_src_e;

/**
  * @brief  RCC Clock config struct
  *
  * @param  clock_type:   Clock type: 0 for SYSCLK, 1 for HCLK, 2 for PCLK1, 3 for PCLK2
  * @param  sys_clk_src:  System clock source: 0 for HSI, 1 for HSE, 2 for PLL
  * @param  ahb_clk_div:  AHB clock division factor: 0 for SYSCLK, 1 for SYSCLK/2, 2 for SYSCLK/4, etc.
  * @param  apb1_clk_div: APB1 clock division factor: 0 for HCLK, 1 for HCLK/2, 2 for HCLK/4, etc.
  * @param  apb2_clk_div: APB2 clock division factor: 0 for HCLK, 1 for HCLK/2, 2 for HCLK/4, etc.
 **/
typedef struct
{
   uint8_t clock_type;
   uint8_t sys_clk_src;
   uint8_t ahb_clk_div;
   uint8_t apb1_clk_div;
   uint8_t apb2_clk_div;

} rcc_clock_cfg_t;

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
void rcc_oscillator_init(rcc_osc_cfg_t *osc_cfg);

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
void rcc_pll_init(rcc_pll_cfg_t *pll_cfg);

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
void rcc_clock_init(rcc_clock_cfg_t *clk_cfg);

#endif