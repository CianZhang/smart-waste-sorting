#include "stm32f10x.h"    
#include "Delay.h" 
#include "OLED.h" 
#include "Low_Servo_App.h"
#include "Catch.h"
#include "stepper_motor.h"
#include "Arm_Servo_App.h"
#include "hc_sr04.h"
#include "infrared.h"
#include "UART3_OpenMV.h"
#include "workLED.h"

//uint8_t test_num;

uint8_t break_flag = 0;
uint8_t check_flag = 0;

int main(void)
{	
	workLED_Init();
	OLED_Init();
	UART3_OpenMV_Init(115200, 0, 1);		// 树莓派5通信，优先级最高
	Catch_Init();							// 机械臂初始化
	Low_Servo_Init();						// 下半部分舵机控制
	IR_Init();   							// 光幕检测初始化
	HC_SR04_Init();							// 超声波初始化
	
	Low_Servo_Reset();						// 下部分舵机复位

	Delay_s(1);	
	
	while(!UART3_GetRxFlag());
	
	while(1)
	{
		if(Start_Flag)
		{
			break;
		}
	}
		
	while(1)	
	{
		uint8_t react_data;
		
		if(!(break_flag || check_flag)) {
			workLED_turnOff();
		}
		
		while(1)
		{
			IR_Detection_Process();
        
			if (IR_Detected || break_flag || check_flag)
			{
				workLED_turnOn();
				break;
			}
		}
		
		if(!(break_flag || check_flag)) Delay_s(2);

//		Delay_s(1);
		if(check_flag == 1) {
			UART3_OpenMV_SendString("Check\n");
		}
		else {
			UART3_OpenMV_SendString("Start\n");
		}
		
		while(!UART3_GetRxFlag());

		react_data = UART3_GetRxData();
		
		if(react_data == '6') {
//			OLED_ShowNum(1, 1, test_num++, 3);
			continue;
		}
		
		Delay_ms(100);
		
		Low_Servo_SetGuard(80);
		
		if(react_data == '9') {
			HC_SR04_Get_Average_Distances();

			check_flag = 0;
			Low_Servo_Reset();
			continue;
		}
		else if(react_data != '\n') {
			Low_Servo_React(react_data & 0x0F);
			Delay_s(1);
			

			break_flag = 0;
			check_flag = 1;
		}
		else {
			RxInfo info = UART3_GetRxInfo();
			Catch(info.x, info.y, 85, info.type);
			if(check_flag == 0) {
				break_flag = 1;
			}

		}
		
		
		
		Low_Servo_Reset();
		
	}
}	



