/* 
 * File:   ADXL_m.h
 * Author: khalid
 *
 * Created on May 15, 2020, 2:17 PM
 */

#ifndef ADXL_M_H
#define	ADXL_M_H

#include "ADXL_cfg.h"

// Hardware I2C functions
void I2CInit(void);
void I2CStart();
void I2CStop();
void I2CRestart();
void I2CAck();
void I2CNak();
void I2CWait();

void I2CSend(unsigned char dat);
unsigned char I2CRead(void);

void ini_adxl345(void);
char E_Write(int addr, unsigned char ch);
unsigned char E_Read(int addr);
#endif	/* ADXL_M_H */

