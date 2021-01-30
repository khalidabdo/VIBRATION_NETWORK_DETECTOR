#include "system.h"
#include "UART_m.h"
#include "UART_cfg.h"
#include "CRC8.h"

extern void (*ptrFinishBuffer)(void);

unsigned char RECEIVED_ECU_ID[MAX_ALLOWED_RECEIVED_ID];

void UART_vidSend(unsigned char* const data,const unsigned short Len);

void UART_vidReceive(unsigned char* data);

unsigned char UART_u8GetNodeID(void);



void UART_vidInit(void)
{
    BRGH = 0;
    SPBRG = (unsigned char)((((unsigned long)_XTAL_FREQ / 9600)/64) - 1);
    SYNC = 0;
    SPEN = 1;
    TRISC6 = 1;
    TRISC7 = 1;
    TXEN = 1;
    RCIE = 1;
    PEIE = 1;
    GIE = 1;
    CREN = 1; 
    
    ECU_ID = UART_u8GetNodeID();
}

void interrupt UART_vidNewDataReceived()
{
    if(RCIF == 1)
    {
        GIE = 0;
        ptrFinishBuffer();
        Data_Buffer.CRC = Get_CRC8(&Data_Buffer.DATA_BUFFER[0],10);
        RS845_ManageState();
        GIE = 1;
        RCIF = 0;
        RC0 ^= 1;
    }
    else
    {
        
    }
}

void RS845_ManageState(void)
{
    if(RCREG == (unsigned char)ECU_ID)
    {
        UART_vidSend(&Data_Buffer.DATA_BUFFER[0],MAX_DATA_SIZE);
    }
    else
    {
        /* Do nothing */
    }
}
void UART_vidSend(unsigned char* const data,const unsigned short Len)
{
    unsigned short UART_u16Index = 0;

	for(UART_u16Index = 0; UART_u16Index < Len; UART_u16Index++)
	{
        while(PIR1bits.TXIF == 0);
        TXREG = data[UART_u16Index];
	}
    PIR1bits.TXIF = 0;
}  

unsigned char UART_u8GetNodeID(void)
{
    return Data_Buffer.ID = 0x35;
}