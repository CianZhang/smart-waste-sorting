#include "stm32f10x.h"    
#include "Delay.h"  
#include "TIM7_Timer.h" 
#include "stepper_motor.h"
#include "Arm_Servo_App.h"
#include "Low_Servo_App.h"

void Catch_Init(void)
{
	Stepper_Motor_Init();
	
	Arm_Servo_Init();
	
	TIM7_Timer_Init(10000, 0, 1);
}

void Catch(uint16_t point_x, uint16_t point_y, uint16_t angle, uint8_t num)
{	
	Core_XY(point_x, point_y, 1000, 1);		// 机械臂移动到目标上方,输入摄像头坐标
	
	Low_Servo_SetGuard(80);					// 挡板打开
//	
	Arm_Servo_SetCompareRevolve(angle);		// 机械爪旋转
	
	Arm_Servo_SetCompareDown(20);			// 机械爪下降
	
	Delay_ms(500);							// 延时
	
	Arm_Servo_SetCompareGrab(105);			// 机械爪抓取
	
	Delay_ms(1000);							// 延时
	
	Arm_Servo_SetCompareDown(70);			// 机械爪上升
	
	Low_Servo_RotateHorizontal(45);			// 托盘旋转45°
	
	if(num == 4)							// 机械臂移动到对应垃圾桶上方
	{
		Core_XY(50, 50, 1000, 0); 
		Arm_Servo_SetCompareRevolve(85);
		Core_XY(0, 0, 1000, 0); 
	}
	if(num == 3)							// 机械臂移动到对应垃圾桶上方
	{
//		Core_XY(50, 190, 1000, 0);
		Arm_Servo_SetCompareRevolve(85);
		Core_XY(0, 240, 1000, 0); 
	}
	if(num == 1)							// 机械臂移动到对应垃圾桶上方
	{
//		Core_XY(160, 60, 1000, 0);
		Arm_Servo_SetCompareRevolve(170);
		Core_XY(210, 10, 1000, 0); 
	}
	if(num == 2)							// 机械臂移动到对应垃圾桶上方
	{
		Core_XY(160, 190, 1000, 0);
		Arm_Servo_SetCompareRevolve(85);
		Core_XY(210, 240, 1000, 0); 
	}

	Delay_ms(100);							// 延时
	
	Arm_Servo_SetCompareGrab(40);			// 机械爪打开
	
	Delay_ms(500);							// 延时
	
	Low_Servo_RotateReset();				// 托盘旋转90°
	
	if(num == 1 || num == 2) {
		Core_XY(100, 100, 1000, 0);		        // 机械臂运动到中继点
	}
	if(num == 3) {
		Core_XY(50, 190, 1000, 0);
	}

	Arm_Servo_SetCompareRevolve(85);		// 机械爪旋转
	
	Low_Servo_SetGuard(52);					// 挡板关闭
	
	Core_XY(0, 0, 1000, 0);		            // 机械臂回到原点
}
