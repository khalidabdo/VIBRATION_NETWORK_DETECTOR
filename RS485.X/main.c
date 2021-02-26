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

void FinishBuffer(void);
void (*ptrFinishBuffer)(void) = FinishBuffer;
unsigned short Get_Tempreture(void);

unsigned short XAVG, YAVG, ZAVG, AVG;
void system_init(void)
{
    TRISC0 = 0;
    TRISC1 = 0;
    TRISC2 = 0;
    OPTION_REGbits.nRBPU = 0;
    TRISB = 0x7F;
    WPUB = 0x7F;
    ANS3 = 1;
    ADCON0 = 0x0D;
    ANSELH = 0x00;
    RC1 = 0;
    RC2 = 1 ;
}

void main(void) 
{
    char XL,XH,YH,YL,ZH,ZL;
    short X, Y, Z;
    
    system_init();
    UART_vidInit();
    
    RC2 = 0 ;
    while(1)
    {
        X = Y = Z = 0;
        //Initialize I2C Port
        I2CInit();
        ini_adxl345();
        
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
        
        AVG = (XAVG/3) + (YAVG/3)+ (ZAVG/3);
        
        AVG = get_average(AVG);  
        FinishBuffer();
        RC2 = ~RC2 ;
    }
}
void FinishBuffer(void)
{
       // Buffer update 
    Set_X_DataIntoBuffer(XAVG);
    Set_Y_DataIntoBuffer(YAVG);
    Set_Z_DataIntoBuffer(ZAVG);
    Set_T_DataIntoBuffer(Get_Tempreture());
    Set_AVG_Vibration_DataIntoBuffer(AVG);
    RS845_ManageState();
}

unsigned short Get_Tempreture(void)
{
    unsigned short Result = 0x0000;
    
    ADCON0 |= 0x02;
    __delay_ms(10);
    Result = ((unsigned short)ADRESH << 2)|((unsigned short)ADRESL >> 6);
    return Result;
}
