#include "usart.h"

/*******************************************************************
 * @name   usart_cfg
 *
 * @brief  Configure usart. This includes clocks and GPIO.
 *
 * @param  usart: pointer to a USART_HandleTypeDef structure that contains
 *                the configuration information for the specified USART
 *                module.
 * @return None
 *
 *******************************************************************/
static void usart_cfg(USART_TypeDef *usart)
{
   /* Configure and enable USARTx */
   //usart->BRR = 365; // 115200 baud @ 42 MHz APB1 clock and 16x oversampling
   usart->BRR = 69; // 115200 baud @ 42 MHz APB1 clock and 16x oversampling
   usart->CR1 |= (USART_CR1_UE | USART_CR1_TE); // USART enable and transmitter enable
   usart->CR2 |= USART_CR2_STOP_1; // 1 stop bit

   // Dummy write, because the first byte seems to always be dropped
   usart->DR = 0;
   while (!(usart->SR & USART_SR_TC));
}

/*******************************************************************
 * @name   usart_init
 *
 * @brief  Initialize usart. This includes clocks and GPIO.
 *
 * @param  usart: pointer to a USART_HandleTypeDef structure that contains
 *                the configuration information for the specified USART
 *                module.
 * @return None
 *
 *******************************************************************/
void usart_init(USART_TypeDef *usart)
{
   /* enable the usart2 peripheral clock (6.3.11 bit 17) */
   RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

   /* delay for 2 reads after enabling the clock  due to errata */
   volatile uint32_t tmp_reg;
   tmp_reg = RCC->APB1ENR;
   tmp_reg = RCC->APB1ENR;
   /* make gcc unused-but-set-variable happy */
   (void)tmp_reg;

   /* Enable GPIOA clock*/
   RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
   /* delay for 2 reads after enabling the clock  due to errata */
   tmp_reg = RCC->AHB1ENR;
   tmp_reg = RCC->AHB1ENR;
   (void)tmp_reg;

   /* Set the GPIO pins PA2 and PA3 (MODE2 and MODE3 respectively) to alternate modes */
   GPIOA->MODER &= ~(GPIO_MODER_MODE2_Msk | GPIO_MODER_MODE3_Msk);
   GPIOA->MODER |=  (0b10 << GPIO_MODER_MODE2_Pos) | (0b10 << GPIO_MODER_MODE3_Pos);

   /* Clear output types for PA2 and PA3 setting the type to push-pull */
   GPIOA->OTYPER  &= ~(GPIO_OTYPER_OT2 | GPIO_OTYPER_OT3);

   /* Set GPIOA PA2 and PA3 to low speed */
   GPIOA->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED2_Msk | GPIO_OSPEEDR_OSPEED3_Msk);

   /* USART2 is AF7 (GPIO Alternate Function Register). 8.3.2 tells us AF7 is USART2 for these pins */
   GPIOA->AFR[0] &= ~(GPIO_AFRL_AFRL2 | GPIO_AFRL_AFRL3);
   GPIOA->AFR[0] |= (7 << GPIO_AFRL_AFSEL2_Pos) | (7 << GPIO_AFRL_AFSEL3_Pos);

   usart_cfg(usart);
}

/*******************************************************************
 * @name   usart_write
 *
 * @brief  Write a character to the USART.
 *
 * @param  usart: pointer to a USART_TypeDef structure that contains
 *                the configuration information for the specified USART
 * @return None
 *
 *******************************************************************/
void usart_write(USART_TypeDef *usart, char tx_char)
{
   /* send a single 8 bit ASCII character */
   usart->DR = tx_char;
   while (!(usart->SR & USART_SR_TC)); // wait until transmission complete
}