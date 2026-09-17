#include "stm32f10x.h"
#include "Delay.h"      

/**
 * @brief  LED初始化
 * @param  None
 * @retval None
 */
void LED_Init(void)
{
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);					//开启GPIOA的时钟
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_5 | GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);												//将PA8 PA5 PA4引脚初始化为推挽输出
	
	/*设置GPIO初始化后的默认电平*/
	GPIO_SetBits(GPIOA, GPIO_Pin_4);															//设置PA4引脚为高电平控制蜂鸣器
	GPIO_ResetBits(GPIOA, GPIO_Pin_8 | GPIO_Pin_5);								//设置PA8和PA5引脚为低电平控制LED
}

//蜂鸣器开启
void Buzzer_on(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);
	Delay_ms(10);
}

//蜂鸣器关闭
void Buzzer_off(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
	Delay_ms(10);
}

//LED1开启
void LED1_ON(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_8);															//设置PA8引脚为高电平
}

//LED1关闭
void LED1_OFF(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_8);														//设置PA8引脚为低电平
}

//LED1状态翻转
void LED1_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_8) == 0)						//获取输出寄存器的状态，如果当前引脚输出低电平
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_8);														//则设置PA1引脚为高电平
	}
	else																													//否则，即当前引脚输出高电平
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_8);													//则设置PA1引脚为低电平
	}
}

//LED2开启
void LED2_ON(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_5);														//设置PA5引脚为高电平
}

//LED2关闭
void LED2_OFF(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_5);													//设置PA5引脚为低电平
}

//LED2状态翻转
void LED2_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_5) == 0)					//获取输出寄存器的状态，如果当前引脚输出低电平
	{                                                  
		GPIO_SetBits(GPIOA, GPIO_Pin_5);               						//则设置PA2引脚为高电平
	}                                                  
	else                                               					//否则，即当前引脚输出高电平
	{                                                  
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);             						//则设置PA2引脚为低电平
	}
}
