#ifndef _USART_H_
#define _USART_H_
#include "stm32f4xx.h"

/*******************************************************************
 * @name   usart_init
 *
 * @brief  Initialize usart. This includes clocks and GPIO.
 *
 * @param  usart_cfg_data: pointer to a USART_HandleTypeDef structure that contains
 *                         the configuration information for the specified USART
 *                         module.
 * @return None
 *
 *******************************************************************/
void usart_init(USART_TypeDef *usart_cfg_data);

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
void usart_write(USART_TypeDef *usart, char tx_char);

#endif