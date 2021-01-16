/*
 * File:   CRC8.c
 * Author: khalid
 *
 * Created on January 10, 2021, 7:27 AM
 */
#include "CRC8_CFG.h"


unsigned char Get_CRC8(unsigned char Data[], unsigned char DataSize)
{
    unsigned char CRC = 0;
    char DataIndex,bitIndex;

    for(DataIndex = 0; DataIndex < DataSize; DataIndex++)
    {
        /* XOR-in the next input byte */
        CRC ^= Data[DataIndex];
        for(bitIndex = 0; bitIndex < 8; bitIndex++)
        {
            if((CRC & 0x80) != 0)
            {
                CRC = (CRC << 1) ^ u8CRCPlynolial;
            }
            else
            {
                CRC <<= 1;
            }
        }
    }
    
    return CRC;
}
