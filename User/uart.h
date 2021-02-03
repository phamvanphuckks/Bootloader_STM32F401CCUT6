/**
  ********************************************************************************************
  * @file    name.h
  * @author  PhamVanPhuckks
  * @date    2020
  * @brief   This file contains all the functions prototypes for ...
  *          firmware library functions (add-on to CMSIS functions).
  *********************************************************************************************
  * @attention
  * This file is used to declare function
  * prototypes for the.....
  * All information related to copyright contact phamvanphuckks@gmail.com
  *********************************************************************************************
  */
#ifndef __UART_H__
#define __UART_H__

#include "stm32f4xx.h"

#define MAX_BUFFER 256

static int _rx_buffer_head = 0, _rx_buffer_tail = 0;    
static char _bufferRx[MAX_BUFFER] ;


/*!
 * @brief  function is perform initialization UART
 * @param  none
 */
void UART_Init(void);
/*!
 * @brief  function is perform Configuration  the GPIO periphenal for UART
 * @param  none
 */
static void GPIO_UART_Config(void);
/*!
 * @brief  function is perform Configuration UART
 * @param  none
 */
static void UART_Config(void);
/*!
 * @brief  function is perform Configuration NVIC for UART
 * @param  none
 */
static void NVIC_UART_Config(void);
/*!
 * @brief  function send one bytes
 * @param  [IN]uint8_t data : data need to send
 */
void UART_SendChar(uint8_t data);
/*!
 * @brief  function send one array char
 * @param  [IN]uint8_t *data : data need to send
 */
void UART_SendString(char *data);
/*!
 * @brief  function is Performs check if the buffer has data or not
 * @param  none
 */
int UART_Available(void);
/*!
 * @brief  function is Performs read 1 byte from buffer
 * @param  none 
 */
int UART_Read(void);
#endif
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2020 phamvanphuckks@gmail.com *****END OF FILE****/
