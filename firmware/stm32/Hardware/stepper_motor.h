#ifndef __STEPPER_MOTOR_H
#define __STEPPER_MOTOR_H

#include "stm32f10x.h"  

void Stepper_Motor_Init(void);
void Core_XY(uint16_t input_X, uint16_t input_Y, uint16_t speed, uint8_t type);

#endif
