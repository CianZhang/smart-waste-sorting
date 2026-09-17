#include "infrared.h"
#include "UART3_OpenMV.h"
#include "OLED.h"

volatile uint8_t IR_Detected = 0;      			// 红外检测标志位
static volatile uint32_t delay_counter = 0;  	// 延时计数器
static volatile uint8_t detection_enabled = 1;  // 检测使能标志

uint8_t time;									//等待15s步进电机上电复位
uint8_t Start_Flag = 0;							//系统启动标志

void IR_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    
    // 使能GPIOB时钟
    RCC_APB2PeriphClockCmd(IR_RCC_APB2Periph, ENABLE);
    		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/*GPIO初始化为高电平*/
	GPIO_SetBits(GPIOB, GPIO_Pin_6);
	
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
	GPIO_SetBits(GPIOA, GPIO_Pin_5);
	
    // 配置PB13为下拉输入（低电平有效）
    GPIO_InitStructure.GPIO_Pin = IR_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(IR_PORT, &GPIO_InitStructure);
		
//		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource13);
//		EXTI_InitTypeDef EXTI_InitStructure;
//		EXTI_InitStructure.EXTI_Line = EXTI_Line13;
//		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
//		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//		EXTI_Init(&EXTI_InitStructure);
//		
//		NVIC_InitTypeDef NVIC_InitStructure;
//		NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//		NVIC_Init(&NVIC_InitStructure);
}

void Condense(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
	GPIO_ResetBits(GPIOA, GPIO_Pin_5);
	
	Delay_s(10);
//	Delay_ms(500);
	
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);
	GPIO_SetBits(GPIOA, GPIO_Pin_5);
	
	Delay_s(10);
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
	GPIO_SetBits(GPIOA, GPIO_Pin_5);
}

// 红外检测处理函数
void IR_Detection_Process(void)
{
    if (detection_enabled && GPIO_ReadInputDataBit(IR_PORT, IR_PIN) == RESET)  // 检测低电平
    {
        IR_Detected = 1;         // 设置检测标志
        detection_enabled = 0;   // 关闭检测
		
		Delay_ms(50);
    }
}

// TIM7 中断服务函数
void TIM7_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM7, TIM_IT_Update) == SET)
	{
		if(time < 16)
		{
			time++;
		}
		
		if(time == 15)
		{
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);
			Start_Flag = 1;
		}
		
		IR_Detected = 0;         // 在重新检测前置零
		
		if(detection_enabled == 0)
		{
			delay_counter++;
		}
		
        if (delay_counter >= 3)  // 3秒延时完成
        {
            delay_counter = 0;
            detection_enabled = 1;   // 重新开启检测
        }

		TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
	}
}

//void EXTI15_10_IRQHandler(void)
//{
//		if (detection_enabled && GPIO_ReadInputDataBit(IR_PORT, IR_PIN) == RESET)  // 检测低电平
//    {
//        IR_Detected = 1;         // 设置检测标志
//        detection_enabled = 0;   // 关闭检测
//    }
//}
