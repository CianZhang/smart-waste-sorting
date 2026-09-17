#ifndef _UART3_OPENMV_H
#define _UART3_OPENMV_H

#include "stm32f10x.h"

typedef struct RXInfo {
	uint16_t x;
	uint16_t y;
	uint8_t angle;
	uint8_t type;
} RxInfo;

//extern float points_x, points_y;
//extern int dx, dy;

void UART3_OpenMV_Init(uint32_t baudRate, uint8_t PreemptionPriority, uint8_t SubPriority);
void UART3_OpenMV_SendByte(uint8_t Byte);
void UART3_OpenMV_SendString(char *String);
uint8_t UART3_GetRxFlag(void);
uint8_t UART3_GetRxData(void);
RxInfo UART3_GetRxInfo(void);

#endif
