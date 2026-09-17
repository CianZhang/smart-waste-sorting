#include "stm32f10x.h"
#include "Delay.h"
#include "LED.h"

uint8_t function_running_num = 0;
uint8_t flag_key = 0;

/***********************************************************************************************************/
/**
 * @brief  按键初始化
 * @param  None
 * @retval None
 */
void Key_Init(void)
{
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);				//开启GPIOC的时钟
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);											//将PC0 PC1 PC2 PC3 PC4 PC5引脚初始化为上拉输入
}

/**
 * @brief  按键获取键码
 * @param  None
 * @retval 按下按键的键码值
 */
uint8_t Key_GetNum(void)
{
	uint8_t KeyNum = 0;
	
	if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0) == 0) KeyNum = 1;
	if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1) == 0) KeyNum = 2;
	if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2) == 0) KeyNum = 3;
	if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3) == 0) KeyNum = 4;
	if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4) == 0) KeyNum = 5;
	if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5) == 0) KeyNum = 6;

	return KeyNum;
}

/*************************************************************************************************************/
//uint8_t keypad_map[3][3] = {
//    		{1, 2, 3},
//    		{4, 5, 6},
//    		{7, 8, 9}
//};

///**
// * @brief  按键初始化
// * @param  None
// * @retval None
// */
//void Key_Init(void)
//{
//	/*开启时钟*/
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);				//开启GPIOC的时钟
//	
//	/*GPIO初始化*/
//	GPIO_InitTypeDef GPIO_InitStructure;
//	
//	/*配置行PC0 PC1 PC2为推挽输出*/
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOC, &GPIO_InitStructure);
//	
//	/*配置列PC3 PC4 PC5为上拉输入*/
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
//  GPIO_Init(GPIOC, &GPIO_InitStructure);
//}

///**
// * @brief  扫描矩阵键盘
// * @param  None
// * @retval None
// */
//uint8_t Key_GetNum(void) 
//{
//    for (int row = 0; row < 3; row++) 
//		{
//        // 将所有行设置为高电平
//        GPIO_SetBits(GPIOC, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);

//        // 将当前行设置为低电平
//        GPIO_ResetBits(GPIOC, GPIO_Pin_0 << row);

//        for (int col = 0; col < 3; col++) 
//				{
//            // 检查当前列的输入状态
//            if (!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3 << col)) 
//						{
//                // 等待按键释放
//                while (!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3 << col));
//                return keypad_map[row][col];
//            }
//        }
//    }
//    return 0; // 没有按键按下
//}
/***************************************************************************************************************/

/**
 * @brief  按键读取函数
 *				 按键按下会将LED1开启，相应的程序运行之后，LED1才会关闭
 *         无返回值，直接赋值全局变量，若无修改，只有另一个按键按下，全局变量才会改变
 * @param  None
 * @retval 无返回值，直接赋值全局变量
 */
void read_key(void)
{
	uint8_t KEY = Key_GetNum();

	if(KEY == 1 && flag_key == 0)
	{
		if(KEY == 1)
		{
			LED1_ON();
			function_running_num = 1;
			flag_key =	1;			
		}
	}
	
	if(KEY == 2 && flag_key == 0)
	{
		if(KEY == 2)
		{
			LED1_ON();
			function_running_num = 2;
			flag_key =	1;
		}			
	}

	if(KEY == 3 && flag_key == 0)
	{
		if(KEY == 3)
		{
			LED1_ON();
			function_running_num = 3;
			flag_key =	1;
		}			
	}
	
	if(KEY == 4 && flag_key == 0)
	{
		if(KEY == 4)
		{
			LED1_ON();
			function_running_num = 4;
			flag_key =	1;
		}			
	}
	
	if(KEY == 5 && flag_key == 0)
	{
		if(KEY == 5)
		{
			LED1_ON();
			function_running_num = 5;
			flag_key =	1;
		}			
	}
	
	if(KEY == 6 && flag_key == 0)
	{
		if(KEY == 6)
		{
			LED1_ON();
			function_running_num = 6;
			flag_key =	1;
		}			
	}
	
	if(KEY == 7 && flag_key == 0)
	{
		if(KEY == 7)
		{
			LED1_ON();
			function_running_num = 7;
			flag_key =	1;
		}			
	}
	
	if(KEY == 8 && flag_key == 0)
	{
		if(KEY == 8)
		{
			LED1_ON();
			function_running_num = 8;
			flag_key =	1;
		}			
	}
	
	if(KEY == 9 && flag_key == 0)
	{
		if(KEY == 9)
		{
			LED1_ON();
			function_running_num = 9;
			flag_key =	1;
		}			
	}
	
	if(KEY == 0 && flag_key == 1)								//按键标志位复位，确保只识别一次
	{								
		if(KEY == 0)
		{
			flag_key = 0;
		}
	}
}








