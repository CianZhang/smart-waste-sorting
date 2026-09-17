#include "workLED.h"

 /**
 * @brief  始化GPIO
 * @param  None
 * @retval None
 */
void workLED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // 使能GPIO
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // 配置引脚为推挽输出
    GPIO_InitStructure.GPIO_Pin = WORKLED_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(WORKLED_PORT, &GPIO_InitStructure);
	
		GPIO_SetBits(WORKLED_PORT, WORKLED_PIN);
}

 /**
 * @brief  开启工作灯
 * @param  None
 * @retval None
 */
void workLED_turnOn(void)
{
    GPIO_SetBits(WORKLED_PORT, WORKLED_PIN);
}

 /**
 * @brief  关闭工作灯
 * @param  None
 * @retval None
 */
void workLED_turnOff(void)
{
    GPIO_ResetBits(WORKLED_PORT, WORKLED_PIN);
}
