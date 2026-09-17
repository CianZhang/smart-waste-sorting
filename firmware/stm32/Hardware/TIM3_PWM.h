#ifndef _TIM3_PWM_H
#define _TIM3_PWM_H

#include "stm32f10x.h" 

void TIM3_PWM_Init(void);
void TIM3_PWM_SetCompare1(uint16_t Compare1);
void TIM3_PWM_SetCompare2(uint16_t Compare2);

#endif
