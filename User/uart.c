/**
  ******************************************************************************
  * @file    uart.c
  * @author  PhamVanPhuckks
  * @date    2020
  * @brief   This file contains all the functions definition for uart
  *          firmware library (add-on to CMSIS functions).
  ******************************************************************************
  * @attention
  * This file is used to describe in detail
  * the functions that serve uart
  * All information related to copyright contact phamvanphuckks@gmail.com
  ******************************************************************************
  */
#include "uart.h"

void UART_Init(void)
{
    GPIO_UART_Config();
    UART_Config();
    NVIC_UART_Config();
}

void GPIO_UART_Config(void )
{
    GPIO_InitTypeDef  GPIO_InitStructut;  
    /* Enable GPIO clock */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA , ENABLE);
    
    /* USARTx GPIO configuration -----------------------------------------------*/ 
    /* Connect USART pins to AF7 */
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9,  GPIO_AF_USART1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

    /* Configure USART Tx and Rx as alternate function push-pull */
    GPIO_InitStructut.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructut.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructut.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructut.GPIO_PuPd  = GPIO_PuPd_UP;

    GPIO_InitStructut.GPIO_Pin = GPIO_Pin_9;
    GPIO_Init(GPIOA, &GPIO_InitStructut);

    GPIO_InitStructut.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIOA, &GPIO_InitStructut);    
}
void UART_Config(void)
{
    USART_InitTypeDef USART_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 , ENABLE);
    /* USARTx configuration ----------------------------------------------------*/
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	
    USART_Cmd(USART1, ENABLE);    
}

void NVIC_UART_Config(void)
{
    NVIC_InitTypeDef  NVIC_InitStructut;

    /*NVIC---------------------------------------------------------------*/
    NVIC_InitStructut.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructut.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructut.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructut.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&NVIC_InitStructut);

    NVIC_EnableIRQ(USART1_IRQn);    
}

void UART_SendString(char *data)
{
    while(*data){
        UART_SendChar(*data);
        data++;
    }
}

void UART_SendChar(uint8_t data)
{

    USART1->DR = data;
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

int UART_Available(void)
{
    return ((unsigned int)(MAX_BUFFER + _rx_buffer_head - _rx_buffer_tail)) % MAX_BUFFER;    
}

int UART_Read(void)
{
    if (_rx_buffer_head == _rx_buffer_tail) // no data
    { 
        return -1;
    }
    else
    {
        unsigned char c = _bufferRx[_rx_buffer_tail];
        _rx_buffer_tail = (_rx_buffer_tail + 1) % MAX_BUFFER;
        return c;
    }    
}

void USART1_IRQHandler(void)
{ 
    uint8_t reciver = USART_ReceiveData(USART1);               
    _bufferRx[_rx_buffer_head] = reciver;                    
    _rx_buffer_head = (_rx_buffer_head + 1) % MAX_BUFFER;
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
