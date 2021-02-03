/**
  ********************************************************************************************
  * @file    hardware-config.h
  * @author  PhamVanPhuckks
  * @date    2020
  * @brief   This file contains all the functions prototypes for GPIO, BUTTON
  *          firmware library functions (add-on to CMSIS functions).
  *********************************************************************************************
  * @attention
  * This file is used to declare function
  * prototypes for the GPIO, BUTTON
  * All information related to copyright contact phamvanphuckks@gmail.com
  *********************************************************************************************
  */
#include "hardware_config.h"

void GPIO_LedConfiguration(void)
{ 
    GPIO_InitTypeDef GPIO_InitStructut;
    /* Enable GPIO clock */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC , ENABLE);    
    
    /* Configure LED- PC13*/
    GPIO_InitStructut.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructut.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructut.GPIO_Speed = GPIO_Speed_25MHz;
    GPIO_InitStructut.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructut);    
}

void GPIO_ButtonConfiguration(void)
{
    GPIO_InitTypeDef GPIO_InitStructut;
    /* Enable GPIO clock */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA , ENABLE);    
    
    /* Configure LED- PC13*/
    GPIO_InitStructut.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructut.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructut.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructut.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructut);       
}
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
