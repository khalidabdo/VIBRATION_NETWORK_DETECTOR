/*
 * File:   main.c
 * Author: khalid
 *
 * Created on May 10, 2020, 12:32 PM
 */
#include "system.h"
#include "UART_m.h"
#include "ADXL_m.h"
#include "average_calculations.h"


void UART_Write(unsigned char data)
{
  while(!TRMT);
  TXREG = data;
}


void system_init(void)
{
    TRISC0 = 0;
    TRISA = 0xFF;
    ADCON0 = 0x00;
    ANSEL = 0x00;
}


void main(void) 
{
    int id, pow, bw_rate;
    char XL,XH,YH,YL,ZH,ZL;
    short X, Y, Z;
    unsigned short XAVG, YAVG, ZAVG;
    int i;
    system_init();
    UART_vidInit();
    
    //Initialize I2C Port
    I2CInit();
    //Initialize ADXL345 Accelerometer
    ini_adxl345();
    
    id = E_Read(IDDV);  // should be 229 for ADXL1345
    UART_Write(id);
    __delay_ms(10);
    pow = E_Read(0x2D);  //should be 8 to activate
    UART_Write(pow);
    __delay_ms(10);
    bw_rate = E_Read(0x2C);  //BW_RATE 0x2C is 13
    UART_Write(bw_rate);
    
    
    while(1)
    {
        X = Y = Z = 0;
        
        I2CStart();
        I2CSend(CHIP_Write);
        I2CSend(DATAX0);    // DATAX0 is the first of 6 bytes
        I2CRestart();
        I2CSend(CHIP_Read);                            //
        XL = I2CRead();                                // read character
        I2CAck();
        XH = I2CRead();                                // read character
        I2CAck();
        YL = I2CRead();                                // read character
        I2CAck();
        YH = I2CRead();                                // read character
        I2CAck();
        ZL = I2CRead();                                // read character
        I2CAck();
        ZH = I2CRead();                                // read character
        I2CNak();
        I2CStop();
            
        X = ((XH<<8) | XL); 
        Y = ((YH<<8) | YL);
        Z = ((ZH<<8) | ZL);
        
        //average calculation 
        XAVG =  get_averageX(X);
        YAVG =  get_averageY(Y);
        ZAVG =  get_averageZ(Z);
        // Buffer update 
        Set_X_DataIntoBuffer(XAVG);
        Set_Y_DataIntoBuffer(YAVG);
        Set_Z_DataIntoBuffer(ZAVG);
        //Set_T_DataIntoBuffer();
        
        
    }
}



