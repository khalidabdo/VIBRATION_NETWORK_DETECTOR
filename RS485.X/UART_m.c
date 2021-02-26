#include "system.h"
#include "UART_m.h"
#include "UART_cfg.h"
#include "CRC8.h"

extern void (*ptrFinishBuffer)(void);

unsigned char RECEIVED_ECU_ID[MAX_ALLOWED_RECEIVED_ID];

static void UART_vidSend(unsigned char const * const data,const unsigned char Len);

unsigned char UART_u8GetNodeID(void);

unsigned char ECU_ID;

static unsigned char IDCounter = 0;
static unsigned char BufferID[4];
    
_tRequestState RequestState;


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
    RequestState = NoRequiest;
    ECU_ID = UART_u8GetNodeID();
    //UART_vidSend(&ECU_ID,1);
}

void interrupt UART_vidNewDataReceived()
{
    if(RCIF == 1)
    {
        if(IDCounter <= 3)
        {
            BufferID[IDCounter] = RCREG;
            IDCounter++;
        }
        if(IDCounter == 4)
        {
            IDCounter = 0;
            if((BufferID[0] == ECU_ID) &&
               (BufferID[1] == 0x55) &&
               (BufferID[2] == ECU_ID) &&
               (BufferID[3] == 0xAA))
            {
                RequestState = Requiest;
            }
        }
        RCIF = 0;
    }  
    else
    {
        
    }
}

void RS845_ManageState(void)
{
    if(RequestState == Requiest)
    {
        RC1 = 1;
        Data_Buffer.CRC = Get_CRC8(&Data_Buffer.DATA_BUFFER[0],MAX_DATA_SIZE - 1);
        UART_vidSend(&Data_Buffer.DATA_BUFFER[0],MAX_DATA_SIZE);
        RequestState = NoRequiest;
        RC1 = 0;
    }
}
static void UART_vidSend(unsigned char const * const data,const unsigned char Len)
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
    Data_Buffer.ID = (PORTB & 0x7F);
    return Data_Buffer.ID;
}
