#include "ADXL_m.h"
#include "ADXL_cfg.h"
#include "system.h"
#include "UART_m.h"

void ini_adxl345()
{
    E_Write(FIFO_CTL,0x9f);
    __delay_ms(10);    
    E_Write(DATA_FORMAT,0x09);
    __delay_ms(10);  
    E_Write(BW_RATE,0x0d);
    __delay_ms(10);        
    E_Write(POWER_CTL,0x08);  // activate  
}

/*
Function: I2CInit
Return:
Arguments:
Description: Initialize I2C in master mode, Sets the required baudrate
*/
void I2CInit(void)
{
    TRISCbits.TRISC3 = 1; /* SDA and SCL as input pin */
    TRISCbits.TRISC4 = 1; /* these pins can be configured either i/p or o/p */
    SSPSTAT |= 0x80; /* Slew rate disabled */
    SSPCON = 0x28;//Enable SDA and SCL, I2C Master mode, clock = FOSC/(4 * (SSPADD + 1))
                /* SSPEN = 1, I2C Master mode, clock = FOSC/(4 * (SSPADD + 1)) */
    SSPCON2 = 0x00;      // Reset MSSP Control Register
    SSPADD = 49;      //20000000 / 4= 5000000, 5000000/ 100000= 50 50-1=49
    PIR1bits.SSPIF = 0;    // Clear MSSP Interrupt Flag
    PIR2bits.BCLIF = 0;
/* *** For different Frequencies ***
FOSC     FCY  SSPADD Value  FCLOCK
40 MHz 10 MHz     63h         100 kHz
32 MHz     8 MHz    4Fh         100 kHz
20 MHz     5 MHz    31h, 49d     100 kHz
16 MHz     4 MHz     27h         100 kHz
8 MHz     2 MHz     13h, 19d    100 kHz
4 MHz     1 MHz     09h         100 kHz
*/
}

/*
Function: I2CStart
Return:
Arguments:
Description: Send a start condition on I2C Bus
*/
void I2CStart()
{
    SEN = 1;         /* Start condition enabled */
    while(SEN);      /* automatically cleared by hardware */
                     /* wait for start condition to finish */
}

/*
Function: I2CStop
Return:
Arguments:
Description: Send a stop condition on I2C Bus
*/
void I2CStop()
{
    PEN = 1;         /* Stop condition enabled */
    while(PEN);      /* Wait for stop condition to finish */
                     /* PEN automatically cleared by hardware */
}

/*
Function: I2CRestart
Return:
Arguments:
Description: Sends a repeated start condition on I2C Bus
*/
void I2CRestart()
{
    RSEN = 1;        /* Repeated start enabled */
    while(RSEN);     /* wait for condition to finish */
}

/*
Function: I2CAck
Return:
Arguments:
Description: Generates acknowledge for a transfer
*/
void I2CAck()
{
    ACKDT = 0;       /* Acknowledge data bit, 0 = ACK */
    ACKEN = 1;       /* Ack data enabled */
    while(ACKEN);    /* wait for ack data to send on bus */
}

/*
Function: I2CNck
Return:
Arguments:
Description: Generates Not-acknowledge for a transfer
*/
void I2CNak()
{
    ACKDT = 1;       /* Acknowledge data bit, 1 = NAK */
    ACKEN = 1;       /* Ack data enabled */
    while(ACKEN);    /* wait for ack data to send on bus */
}

/*
Function: I2CWait
Return:
Arguments:
Description: wait for transfer to finish
*/
void I2CWait()
{
    while ((SSPCON2 & 0x1F ) || ( SSPSTAT & 0x04 ) );
    /* wait for any pending transfer */
}
 
/*
Function: I2CSend
Return:
Arguments: dat - 8-bit data to be sent on bus
           data can be either address/data byte
Description: Send 8-bit data on I2C bus
*/
void I2CSend(unsigned char dat)
{
    SSPBUF = dat;    /* Move data to SSPBUF */
    while(BF);       /* wait till complete data is sent from buffer */
    I2CWait();       /* wait for any pending transfer */
}
 
/*
Function: I2CRead
Return:    8-bit data read from I2C bus
Arguments:
Description: read 8-bit data from I2C bus
*/
unsigned char I2CRead(void)
{
    unsigned char temp;
/* Reception works if transfer is initiated in read mode */
    RCEN = 1;        /* Enable data reception */
    while(!BF);      /* wait for buffer full */
    temp = SSPBUF;   /* Read serial buffer and store in temp register */
    I2CWait();       /* wait to check any pending transfer */
    return temp;     /* Return the read data from bus */
}
 
 
// This is random writing. Write to a specified address
char E_Write(int addr, unsigned char ch)
{
    /* Send Start condition */
    I2CStart();
    /* Send ADXL1345 slave address with write operation */
    I2CSend(CHIP_Write);
    /* Send subaddress, we are writing to this location */
    I2CSend(addr);
    /* send I2C data one by one */
    I2CSend(ch);
    /* Send a stop condition - as transfer finishes */
    I2CStop();
    return 1;                                        // All went well
}
 
// The function takes an address and Returns a character
// This is random reading. Read from a specified addess
unsigned char E_Read(int addr)
{
    unsigned char ch;
    /* Send Start condition */
    I2CStart();
    /* Send ADXL1345 slave address with write operation */
    I2CSend(CHIP_Write);
    /* this address is actually where we are going to read from */
    I2CSend(addr);
    /* Send a repeated start, after a dummy write to start reading */
    I2CRestart();
    /* send slave address with read bit set */
    I2CSend(CHIP_Read);
 
    ch = I2CRead();                                // read character
    I2CNak();
    I2CStop();
    return ch;
}