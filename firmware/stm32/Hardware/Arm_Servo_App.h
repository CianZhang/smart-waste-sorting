#ifndef __ARM_SERVO_APP_H
#define __ARM_SERVO_APP_H

#include <stdint.h>

void Arm_Servo_Init(void);
void Arm_Servo_SetCompareRevolve(float DEGREE);
void Arm_Servo_SetCompareGrab(float DEGREE);
void Arm_Servo_SetCompareDown(float DEGREE);

#endif
