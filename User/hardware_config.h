/**
  ******************************************************************************
  * @file    hardware-config.c
  * @author  PhamVanPhuckks
  * @date    2020
  * @brief   This file contains all the functions definition for GPIO, BUTTON
  *          firmware library (add-on to CMSIS functions).
  ******************************************************************************
  * @attention
  * This file is used to describe in detail
  * the functions that serve GPIO, BUTTON
  * All information related to copyright contact phamvanphuckks@gmail.com
  ******************************************************************************
  */
#ifndef __HARDWARECONFIG_H__
#define __HARDWARECONFIG_H__

#include "stm32f4xx.h"

#define MODE_APPLICATION    GPIO_WriteBit(GPIOC, GPIO_Pin_13, 1)
#define MODE_LOADCODE       GPIO_WriteBit(GPIOC, GPIO_Pin_13, 0)

/*!
* @brief  function configuration for LED, GPIOC_Pin_13
 * @param  none
 */
void GPIO_LedConfiguration(void);
/*!
 * @brief  function configuration for BUTTON, GPIOA_Pin_5
 * @param  none
 */
void GPIO_ButtonConfiguration(void);
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
