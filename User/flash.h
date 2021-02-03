/**
  ********************************************************************************************
  * @file    flash.h
  * @author  PhamVanPhuckks
  * @date    2020
  * @brief   This file contains all the functions prototypes for the miscellaneous
  *          firmware library functions (add-on to CMSIS functions).
  *********************************************************************************************
  * @attention
  * This file is used to declare function
  * prototypes for the flash memory
  * All information related to copyright contact phamvanphuckks@gmail.com
  *********************************************************************************************
  */
#ifndef __FLASH_H__
#define __FLASH_H__
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "string.h"

#define ADDR_FLASH_SECTOR_1   ((uint32_t)0x08004000)
#define ADDR_FLASH_SECTOR_2   ((uint32_t)0x08006000)
#define ADDR_FLASH_SECTOR_3   ((uint32_t)0x08008000)
#define ADDR_FLASH_SECTOR_4   ((uint32_t)0x0800A000)

/*!
 * @brief  function erase sector in   flash memory
 * @param  [IN]uint16_t FLASH_Sector    address of Sector is earse range from 1 to 8 
 */
void flashEarseSector(uint16_t FLASH_Sector);

/*!
 * @brief  function flashLock flash
 * @param  none
 */
void flashLock(void);
/*!
 * @brief  function flash Unlock flash
 * @param  none
 */
void flashUnlock(void);
/*!
 * @brief  function erase page flash
 * @param  [IN]uint32_t addr : address in flash memory 
 */
uint32_t   flashReadInt(uint32_t addr);
/*!
 * @brief  function read 4 byte from flash memory at addr
 * @param  [IN]uint32_t addr : address in flash memory
 */
uint16_t flashReadShort(uint32_t addr);
/*!
 * @brief  function read 2 byte from flash memory at addr
 * @param  [IN]uint32_t addr : address in flash memory
 */
uint8_t  flashReadChar(uint32_t addr);

/*!
 * @brief  function read 1 byte from flash memory at addr
 * @param  [IN]uint32_t addr  : address in flash memory
 * @param  [IN]]char data     : data to be written in the memory
 */
void flashWriteChar(uint32_t addr, uint8_t data);
/*!
 * @brief  function write  2 byte into flash memory at addr
 * @param  [IN]uint32_t addr   : address in flash memory
 * @param  [IN]]short data     : data to be written in the memory
 */
void flashWriteShort(uint32_t addr, uint16_t data);
/*!
 * @brief  function write  4 byte into flash memory at addr
 * @param  [IN]uint32_t addr      : address in flash memory
 * @param  [IN]]uint32_t data     : data to be written in the memory
 */
void flashWriteInt(uint32_t addr, uint32_t data);

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
