#include "stm32f10x.h"                  								// Device header

//存储机械臂坐标的结构体
typedef struct point{
		uint16_t x;
		uint16_t y;
} Point;

int16_t X_current = 0;
int16_t Y_current = 0;

 /**
 * @brief  机械臂步进电机控制初始化
 * @param  PCO和PC1用于输出脉冲
 *         PC2和PC3用于控制方向
 * @retval None
 */
void Stepper_Motor_Init(void)
{
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);				// 开启GPIOC的时钟
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;					// 配置推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);	

	/*GPIO初始化为低电平*/
	GPIO_ResetBits(GPIOC, GPIO_Pin_0);
	GPIO_ResetBits(GPIOC, GPIO_Pin_1);
	GPIO_ResetBits(GPIOC, GPIO_Pin_2);
	GPIO_ResetBits(GPIOC, GPIO_Pin_3);
}

void TIM_Config(uint16_t prescaler, uint16_t period) 
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period = period;
	TIM_TimeBaseStructure.TIM_Prescaler = prescaler;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
	TIM_Cmd(TIM4, ENABLE);
}

 /**
 * @brief  左边步进电机控制
 * @param  stp 用于输入运动多少步（步进电机32细分，6400个脉冲旋转一圈）
 *         dir 用于控制方向，0顺时针，1逆时针
 * @retval None
 */
void Stepper_Motor_Left(uint32_t steps, uint8_t dir, uint16_t speed)
{	
	if (dir == 0)
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_2);
	}
	if (dir == 1)
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_2);
	}
	
	uint16_t prescaler = (SystemCoreClock / 1000000) * (1000 / speed) - 1;		//设置预分配系数
	
	TIM_Config(prescaler, 50 - 1);			//配置定时器系数prescale,period
	while(steps > 0) 
	{
		if(TIM_GetFlagStatus(TIM4, TIM_FLAG_Update) != RESET) 
		{
			TIM_ClearFlag(TIM4, TIM_FLAG_Update);
			GPIO_SetBits(GPIOC, GPIO_Pin_0);
			for (int i = 0; i < 50; i++) __NOP();//模拟PWM波
			GPIO_ResetBits(GPIOC, GPIO_Pin_0);
			steps--;
		}
	}
}

 /**
 * @brief  右边步进电机控制
 * @param  stp 用于输入运动多少步（步进电机32细分，6400个脉冲旋转一圈）
 *         dir 用于控制方向，0顺时针，1逆时针
 * @retval None
 */
void Stepper_Motor_Right(uint32_t steps, uint8_t dir, uint16_t speed)
{
	if (dir == 0)
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_3);
	}
	if (dir == 1)
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_3);
	}	
	
	uint16_t prescaler = (SystemCoreClock / 1000000) * (1000 / speed) - 1;		//设置预分配系数
	
	TIM_Config(prescaler, 50 - 1);			//配置定时器系数prescale,period
	while(steps > 0) 
	{
		if(TIM_GetFlagStatus(TIM4, TIM_FLAG_Update) != RESET) 
		{
			TIM_ClearFlag(TIM4, TIM_FLAG_Update);
			GPIO_SetBits(GPIOC, GPIO_Pin_1);
			for (int i = 0; i < 50; i++) __NOP();//模拟PWM波
			GPIO_ResetBits(GPIOC, GPIO_Pin_1);
			steps--;
		}
	}
}

 /**
 * @brief  左右步进电机同时运动，在循环里面，运动完成才会执行下一步操作
 * @param  steps_left 左步进步数
 *         dir_left 左步进方向
 * 		   steps_right 右步进步数
 *         dir_right 右步进方向
 *         speed 速度范围0到1000
 * @retval None
 */
void Stepper_Motor(uint32_t steps_left, uint8_t dir_left, uint32_t steps_right, uint8_t dir_right, uint16_t speed)
{
	if (dir_left == 0)
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_2);
	}
	if (dir_left == 1)
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_2);
	}	
	if (dir_right == 0)
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_3);
	}
	if (dir_right == 1)
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_3);
	}	

	uint16_t prescaler = (SystemCoreClock / 1000000) * (1000 / speed) - 1;		//设置预分配系数
	
	TIM_Config(prescaler, 50 - 1);			//配置定时器系数prescale,period
	while(steps_left > 0 || steps_right > 0) 
	{
		if(steps_right > 0)		
		{
			if(TIM_GetFlagStatus(TIM4, TIM_FLAG_Update) != RESET) 
			{
				TIM_ClearFlag(TIM4, TIM_FLAG_Update);
				GPIO_SetBits(GPIOC, GPIO_Pin_1);
				for (int i = 0; i < 50; i++) __NOP();//模拟PWM波
				GPIO_ResetBits(GPIOC, GPIO_Pin_1);
				steps_right--;
			}
		}
		
		if(steps_left > 0)
		{
			if(TIM_GetFlagStatus(TIM4, TIM_FLAG_Update) != RESET) 
			{
				TIM_ClearFlag(TIM4, TIM_FLAG_Update);
				GPIO_SetBits(GPIOC, GPIO_Pin_0);
				for (int i = 0; i < 50; i++) __NOP();//模拟PWM波
				GPIO_ResetBits(GPIOC, GPIO_Pin_0);
				steps_left--;
			}			
		}
	}	
}

 /**
 * @brief  XY坐标转换，将摄像头坐标转换为机械臂坐标
 * @param  X_prime 摄像头X坐标
 *         Y_prime 摄像头Y坐标
 * @retval point 存储机械臂坐标的结构体
 */
Point transform_coordinates(double x_prime, double y_prime) 
{
	Point point;
	
    point.x = -0.442060 * x_prime + -0.001511 * y_prime + 204.414347;
    point.y = -0.002453 * x_prime + 0.447338 * y_prime + 18.974381;
		
	return point;
}

 /**
 * @brief  XY坐标控制，右上角为原点
 * @param  X_target 目标X坐标
 *         Y_target 目标Y坐标
 *         speed    速度范围0到1000
 *         type     运动类型，0表示步进电机坐标，1表示摄像头坐标
 * @retval None
 */
void Core_XY(uint16_t input_X, uint16_t input_Y, uint16_t speed, uint8_t type)
{
	uint8_t dir_1;
	uint8_t dir_2;
	
	uint16_t X_target;
	uint16_t Y_target;
	
	if(type == 0)
	{
		X_target = input_X;
		Y_target = input_Y;
	}
	if(type == 1)
	{
		Point point = transform_coordinates(input_X, input_Y);
		X_target = point.x + 44;
		Y_target = point.y - 22;
	}
	
	int16_t dx = X_target - X_current;
	int16_t dy = Y_target - Y_current; 

	int32_t stp_1 = (dx - dy) * 160;
	int32_t stp_2 = (dx + dy) * 160;
	
	if (stp_1 > 0 && stp_2 > 0)
	{
		dir_1 = 1;
		dir_2 = 1;
	}
	else if (stp_1 > 0 && stp_2 < 0)
	{
		stp_2 = - stp_2;
		dir_1 = 1;
		dir_2 = 0;
	}		
	else if (stp_1 < 0 && stp_2 > 0)
	{
		stp_1 = - stp_1;
		dir_1 = 0;
		dir_2 = 1;
	}
	else if (stp_1 < 0 && stp_2 < 0)
	{
		stp_1 = - stp_1;
		stp_2 = - stp_2;
		dir_1 = 0;
		dir_2 = 0;
	}
	else if (stp_1 == 0 && stp_2 < 0)
	{
		stp_2 = - stp_2;
		dir_1 = 0;
		dir_2 = 0;
	}
	else if (stp_1 == 0 && stp_2 > 0)
	{
		dir_1 = 0;
		dir_2 = 1;
	}
	else if (stp_1 < 0 && stp_2 == 0)
	{
		stp_1 = - stp_1;
		dir_1 = 1;
		dir_2 = 0;
	}
	else if (stp_1 > 0 && stp_2 == 0)
	{
		dir_1 = 1;
		dir_2 = 0;
	}

	Stepper_Motor(stp_1, dir_1, stp_2, dir_2, speed);

	X_current = X_target;
	Y_current = Y_target;
}
