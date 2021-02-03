/**
  ********************************************************************************************
  * @file    record_hex.h
  * @author  PhamVanPhuckks
  * @date    2020
  * @brief   This file contains all the functions prototypes for handle file .hex
  *          firmware library functions (add-on to CMSIS functions).
  *********************************************************************************************
  * @attention
  * This file is used to declare function
  * prototypes for the handle file .hex
  * All information related to copyright contact phamvanphuckks@gmail.com
  *********************************************************************************************
  */
#ifndef __RECORD_HEX_H__
#define __RECORD_HEX_H__

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"

typedef enum
{
    START_CODE = 0U, /*Start code*/
    BYTE_COUNT = 1U, /*Byte count */
    ADDRESS    = 2U, /*Address*/
    RECORD_TYPE= 3U, /*Record type*/
    DATA       = 4U, /*Data*/
    CHECKSUM   = 5U, /*Checksum*/
}FieldHex;

typedef struct
{
    uint8_t   byteCount;
    uint32_t  address;
    uint16_t  offsetAddress;
    uint8_t   recordType;
    uint8_t   data[256];
    uint8_t   checkSum;
    uint32_t  posStart;
} RowHex;

/*!
 * @brief  function conver from string to hex
 * @param  [IN]char *data      : data in the array  need convert
 * @param  [IN]uint8_t length  : length of array 
 */
uint32_t String2Hex32(char *data, uint8_t length);
/*!
 * @brief  function conver from string to hex
 * @param  [IN]char *data      : data in the array  need convert
 * @param  [IN]uint8_t length  : length of array 
 */
uint16_t String2Hex16(char *data, uint8_t length);
/*!
 * @brief  function conver from string to hex
 * @param  [IN]char *data      : data in the array  need convert
 * @param  [IN]uint8_t length  : length of array 
 */
uint8_t  String2Hex8(char *data, uint8_t length);
/*!
 * @brief  function check the checkSum value
 * @param  [IN]char *data : buffer of data   
 * @param  [IN]uint16_t vauleCheckSum : checksum value need to compare
 * @param  [IN]RowHex  row : struct describe info about line data of file hex
 */
uint8_t  isCheckSum(char *data, uint8_t vauleCheckSum, RowHex row);
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
