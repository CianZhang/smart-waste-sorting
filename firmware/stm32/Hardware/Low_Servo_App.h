#ifndef __LOW_SERVO_APP_H
#define __LOW_SERVO_APP_H

#include <stdint.h>

void Low_Servo_Init(void);
void Low_Servo_Reset(void);
void Horizontal_and_Vertical_Reset(void);
void Low_Servo_SetGuard(float DEGREE);
void Low_Servo_RotateHorizontal(float DEGREE);
void Low_Servo_RotateReset(void);
void Low_Servo_SetCompareHorizontal(float DEGREE);
void Low_Servo_SetCompareVertical(float DEGREE);
void Low_Servo_React(uint8_t NUM);


#endif
