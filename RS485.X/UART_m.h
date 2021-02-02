/* 
 * File:   UART_m.h
 * Author: khalid
 *
 * Created on May 11, 2020, 12:34 AM
 */

#ifndef UART_M_H
#define	UART_M_H

#include "UART_cfg.h"

typedef union
{
	unsigned char DATA_BUFFER[MAX_DATA_SIZE];
	struct
	{
        unsigned char ID : 8;
        
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

#define Set_ID_DataIntoBuffer(Data) (Data_Buffer.ID = Data)

void UART_vidInit(void);

#endif	/* UART_M_H */

