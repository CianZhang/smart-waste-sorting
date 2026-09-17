#ifndef __WORKLED_H
#define __WORKLED_H

#include "stm32f10x.h"

// 定义引脚
#define WORKLED_PORT   GPIOA
#define WORKLED_PIN    GPIO_Pin_12

// 函数声明
void workLED_Init(void);
void workLED_turnOn(void);
void workLED_turnOff(void);

#endif
