/* 
 * File:   UART_m.h
 * Author: khalid
 *
 * Created on May 11, 2020, 12:34 AM
 */

#ifndef UART_M_H
#define	UART_M_H

#include "UART_cfg.h"

unsigned char ECU_ID;
typedef union
{
	unsigned char DATA_BUFFER[MAX_DATA_SIZE];
	struct
	{
        unsigned char ID : 7;
        unsigned char SwitchStatus : 1;
        unsigned char HT : 8;
        unsigned char LT : 8;
        
		unsigned char HX : 8;
        unsigned char LX : 8;

		unsigned char HY : 8;
        unsigned char LY : 8;
        
		unsigned char HZ : 8;
        unsigned char LZ : 8;
        
        unsigned char AVG_VibrationH : 8;
        unsigned char AVG_VibrationL : 8;
        
        unsigned char CRC : 8;
	};
}_DATA_BUFFER;

typedef enum
{
	RS485_Init = 0,
	RS485_ID_CHECK,
	RS485_BUFFER_SEND
}RS485_Stack_States;

_DATA_BUFFER Data_Buffer;

#define Set_X_DataIntoBuffer(Data) Data_Buffer.HX = Data>>8; \
                                   Data_Buffer.LX=Data

#define Set_Y_DataIntoBuffer(Data) Data_Buffer.HY = Data>>8; \
                                   Data_Buffer.LY=Data

#define Set_Z_DataIntoBuffer(Data) Data_Buffer.HZ = Data>>8; \
                                   Data_Buffer.LZ=Data

#define Set_AVG_Vibration_DataIntoBuffer(Data) Data_Buffer.AVG_VibrationH = Data>>8; \
                                   Data_Buffer.AVG_VibrationL = Data

#define Set_T_DataIntoBuffer(Data) Data_Buffer.HT = Data>>8;\
                                   Data_Buffer.LT = Data

#define Set_SwitchStatus_DataIntoBuffer(Data) (Data_Buffer.SwitchStatus = Data)

#define Set_ID_DataIntoBuffer(Data) (Data_Buffer.ID = Data)

void UART_vidInit(void);

void RS845_ManageState(void);

void UART_vidSend(unsigned char* const data,const unsigned short Len);

void UART_vidReceive(unsigned char* data);

#endif	/* UART_M_H */

