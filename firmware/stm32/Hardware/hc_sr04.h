#ifndef __HC_SR04_H
#define __HC_SR04_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "Delay.h"
#include "Low_Servo_App.h"

// 定义HC-SR04的引脚（4个模块独立控制）
#define HC_SR04_TRIG1_PORT   GPIOB
#define HC_SR04_TRIG1_PIN    GPIO_Pin_14
#define HC_SR04_ECHO1_PORT   GPIOC
#define HC_SR04_ECHO1_PIN    GPIO_Pin_10

#define HC_SR04_TRIG2_PORT   GPIOB
#define HC_SR04_TRIG2_PIN    GPIO_Pin_12
#define HC_SR04_ECHO2_PORT   GPIOC
#define HC_SR04_ECHO2_PIN    GPIO_Pin_12

#define HC_SR04_TRIG3_PORT   GPIOB
#define HC_SR04_TRIG3_PIN    GPIO_Pin_5
#define HC_SR04_ECHO3_PORT   GPIOC
#define HC_SR04_ECHO3_PIN    GPIO_Pin_11

#define HC_SR04_TRIG4_PORT   GPIOB
#define HC_SR04_TRIG4_PIN    GPIO_Pin_7
#define HC_SR04_ECHO4_PORT   GPIOB
#define HC_SR04_ECHO4_PIN    GPIO_Pin_15

// 函数声明
void HC_SR04_Init(void);
void HC_SR04_GetDistances(float *distances);
void HC_SR04_Get_Average_Distances(void);

#endif
