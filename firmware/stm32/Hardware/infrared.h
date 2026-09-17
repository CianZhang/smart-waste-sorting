#ifndef __INFRARED_H
#define __INFRARED_H

#include "stm32f10x.h"
#include "Delay.h" 
#include "hc_sr04.h"

#define IR_PIN                  GPIO_Pin_13
#define IR_PORT                 GPIOB
#define IR_RCC_APB2Periph       RCC_APB2Periph_GPIOB

extern volatile uint8_t IR_Detected;
extern uint8_t Start_Flag;
 
void IR_Init(void);
void Condense(void);
void IR_Detection_Process(void);


#endif
