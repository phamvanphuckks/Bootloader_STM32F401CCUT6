/**
  ******************************************************************************
  * @file    record_hex.c
  * @author  PhamVanPhuckks
  * @date    2020
  * @brief   This file contains all the functions definition for handle file .hex
  *          firmware library (add-on to CMSIS functions).
  ******************************************************************************
  * @attention
  * This file is used to describe in detail
  * the functions that serve handle file .hex
  * All information related to copyright contact phamvanphuckks@gmail.com
  ******************************************************************************
  */
#include "record_hex.h"

uint32_t String2Hex32(char *data, uint8_t length)
{
    uint32_t datahex = 0;
    uint8_t Niddle[length], nbytecount = 0;
    for (int i = 0; i < length; i++)
    {
        if (data[i] >= '0' && data[i] <= '9')
        {
            Niddle[i] = data[i] - 48;
        }
        else if (data[i] >= 'A' && data[i] <= 'F')
        {
            Niddle[i] = data[i] - 65 + 10;
        }
        if (i % 2 != 0)
        {
            uint8_t byte = ((Niddle[i-1] << 4) | Niddle[i]);
            datahex |= (uint32_t)byte << (nbytecount)*8;
            nbytecount++;
        }
    }
    return datahex;
}
uint16_t String2Hex16(char *data, uint8_t length)
{
    uint32_t datahex = 0;
    uint8_t Niddle[length], nbytecount = 0;
    for (int i = 0; i < length; i++)
    {
        if (data[i] >= '0' && data[i] <= '9')
        {
            Niddle[i] = data[i] - 48;
        }
        else if (data[i] >= 'A' && data[i] <= 'F')
        {
            Niddle[i] = data[i] - 65 + 10;
        }
        if (i % 2 != 0)
        {
            uint8_t byte = ((Niddle[i - 1] << 4) | Niddle[i]);
            datahex = (uint32_t)byte | datahex << (nbytecount)*8;
            nbytecount++;
        }
    }
    return datahex;
}

uint8_t String2Hex8(char *data, uint8_t length)
{
    uint32_t datahex = 0;
    uint8_t Niddle[length], nbytecount = 0;
    for (int i = 0; i < length; i++)
    {
        if (data[i] >= '0' && data[i] <= '9')
        {
            Niddle[i] = data[i] - 48;
        }
        else if (data[i] >= 'A' && data[i] <= 'F')
        {
            Niddle[i] = data[i] - 65 + 10;
        }
        if (i % 2 != 0)
        {
            uint8_t byte = ((Niddle[i-1] << 4) | Niddle[i]);
            datahex |= (uint32_t)byte << (nbytecount)*8;
            nbytecount++;
        }
    }
    return datahex;
}

uint8_t isCheckSum(char *data, uint8_t vauleCheckSum, RowHex row)
{
    uint8_t calCheckSum = 0;
    calCheckSum = row.address + row.byteCount + (uint8_t)row.offsetAddress + (uint8_t)(row.offsetAddress>>8);
    
    for(int i = row.posStart; i<row.posStart+ row.byteCount; i +=2)
    {
        calCheckSum += String2Hex8(&data[i], 2);
    }
   
    calCheckSum = ~calCheckSum+1;
    
    return ((calCheckSum==vauleCheckSum) ?  1 :  0);
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
