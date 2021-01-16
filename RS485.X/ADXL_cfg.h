/* 
 * File:   ADXL_cfg.h
 * Author: khalid
 *
 * Created on May 15, 2020, 2:17 PM
 */
#ifndef ADXL_CFG_H
#define	ADXL_CFG_H
#include "system.h"

#define  BW_RATE            44    //0x2C
#define  POWER_CTL          45    //0x2D
#define  DATA_FORMAT        49    //0x31
#define  DATAX0             50    //0x32
#define  DATAX1             51    //0x33
#define  DATAY0             52    //0x34
#define  DATAY1             53    //0x35
#define  DATAZ0             54    //0x36
#define  DATAZ1             55    //0x37
#define  FIFO_CTL           56    //0x38            ADXL1345    1010011   0x53   Device
#define  CHIP_Write         0xA6  // adxl345 address for writing    10100110  0xA6   Write
#define  CHIP_Read          0xA7  // and reading                    10100111  0xA7   Read
#define  IDDV 0


#endif	/* ADXL_CFG_H */

