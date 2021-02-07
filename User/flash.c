/**
  ******************************************************************************
  * @file    flash.c
  * @author  PhamVanPhuckks
  * @date    2020
  * @brief   This file contains all the functions definition for flash memory
  *          firmware library (add-on to CMSIS functions).
  ******************************************************************************
  * @attention
  * This file is used to describe in detail
  * the functions that serve flash memory
  * All information related to copyright contact phamvanphuckks@gmail.com
  ******************************************************************************
  */
#include "flash.h"
#include "delay.h"

void flashLock()
{
	FLASH->CR |= FLASH_CR_LOCK;
}

void flashUnlock()
{
  if((FLASH->CR & FLASH_CR_LOCK) != RESET)
  {
    /*Authorize the FLASH Registers access*/
    FLASH->KEYR = FLASH_KEY1;
    FLASH->KEYR = FLASH_KEY2;
  } 
}

// read
uint32_t flashReadInt(uint32_t addr)
{
	uint32_t* val = (uint32_t *)addr;
	return *val;
}

uint16_t flashReadShort(uint32_t addr)
{
    return 0;
}

uint8_t flashReadByte(uint32_t addr)
{
	uint8_t* val = (uint8_t *)addr;
	return *val;    
}

void flashWriteChar(uint32_t addr, uint8_t  data)
{
    flashUnlock();
    FLASH->CR |= FLASH_PSIZE_BYTE;
    FLASH->CR |= FLASH_CR_PG;
    while((FLASH->SR&FLASH_SR_BSY));
    *(__IO uint8_t*)(addr) = data; // con tro kieu (uint8_t *), co size la 4byte de chua dia chia
    while((FLASH->SR&FLASH_SR_BSY)){};
    FLASH->CR &= (~FLASH_CR_PG);
    flashLock();
}
void flashWriteShort(uint32_t addr, uint16_t  data)
{
    flashUnlock();
    FLASH->CR |= FLASH_PSIZE_HALF_WORD;
    FLASH->CR |= FLASH_CR_PG;
    while((FLASH->SR&FLASH_SR_BSY));
    *(__IO uint8_t*)(addr) = data; // con tro kieu (uint8_t *), co size la 4byte de chua dia chia
    while((FLASH->SR&FLASH_SR_BSY)){};
    FLASH->CR &= (~FLASH_CR_PG);
    flashLock();
}
void flashWriteInt(uint32_t addr, uint32_t data)
{
	flashUnlock();
    FLASH->CR |= FLASH_PSIZE_WORD;
	FLASH->CR |= FLASH_CR_PG;				/*!< Programming */
	while((FLASH->SR & FLASH_SR_BSY));
	*(__IO uint32_t*)addr = data;
	while((FLASH->SR & FLASH_SR_BSY));
	FLASH->CR &= ~FLASH_CR_PG;
	flashLock();
}

void flashWriteString(uint32_t addr, char* data, int length)
{
    flashUnlock();
    //FLASH->CR |= FLASH_CR_PG;
    for(int i = 0; i < length; i += 1)
    {
        FLASH->CR |= FLASH_CR_PG;
        while((FLASH->SR&FLASH_SR_BSY));
        *(__IO uint8_t*)(addr+i) = data[i]; // con tro kieu (uint8_t *), co size la 4byte de chua dia chia
        while((FLASH->SR&FLASH_SR_BSY)){};
        FLASH->CR &= (~FLASH_CR_PG);
    }
    while((FLASH->SR&FLASH_SR_BSY)){};
    FLASH->CR &= ~FLASH_CR_PG;
    FLASH->CR |= FLASH_CR_LOCK;
}

void flashEarseSector(uint16_t FLASH_Sector)
{
    flashUnlock();
    while((FLASH->SR&FLASH_SR_BSY)){};
    FLASH->CR |= FLASH_CR_SER | FLASH_Sector;
    FLASH->CR |= FLASH_CR_STRT;
    while((FLASH->SR & FLASH_SR_BSY)){};
    flashLock();
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

