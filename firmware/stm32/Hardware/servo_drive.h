
#ifndef __SERVO_DRIVE_H
#define __SERVO_DRIVE_H

#include "stm32f10x.h"

void TIM2_PWM_Init(void);
void TIM2_PWM_SetCompare1(uint16_t COMPARE);
void TIM2_PWM_SetCompare2(uint16_t COMPARE);
void TIM2_PWM_SetCompare3(uint16_t COMPARE);

void TIM3_PWM_Init(void);
void TIM3_PWM_SetCompare1(uint16_t COMPARE);
void TIM3_PWM_SetCompare2(uint16_t COMPARE);
void TIM3_PWM_SetCompare3(uint16_t COMPARE);
void TIM3_PWM_SetCompare4(uint16_t COMPARE);

#endif
