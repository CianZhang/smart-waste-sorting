#include "stm32f10x.h"                  	// Device header

 /**
 * @brief  TIM2 PWM 初始化
 * @param  None
 * @retval None
 */
void TIM2_PWM_Init(void)
{
  //开启时钟
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

  //配置GPIO
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  
  //配置定时器
  TIM_InternalClockConfig(TIM2);

  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
  TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInitStructure.TIM_Period = 20000 - 1;
  TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;
  TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);

  TIM_OCInitTypeDef TIM_OCInitStructure;
  TIM_OCStructInit(&TIM_OCInitStructure);
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;
  TIM_OC1Init(TIM2, &TIM_OCInitStructure);
  TIM_OC2Init(TIM2, &TIM_OCInitStructure);
  TIM_OC3Init(TIM2, &TIM_OCInitStructure);

  TIM_Cmd(TIM2, ENABLE);
}

 /**
 * @brief  TIM2 PWM 输出口1的占空比
 * @param  占空比
 * @retval None
 */
void TIM2_PWM_SetCompare1(uint16_t COMPARE)
{
  TIM_SetCompare1(TIM2, COMPARE);
}

 /**
 * @brief  TIM2 PWM 输出口2的占空比
 * @param  占空比
 * @retval None
 */
void TIM2_PWM_SetCompare2(uint16_t COMPARE)
{
  TIM_SetCompare2(TIM2, COMPARE);
}

 /**
 * @brief  TIM2 PWM 输出口3的占空比
 * @param  占空比
 * @retval None
 */
void TIM2_PWM_SetCompare3(uint16_t COMPARE)
{
  TIM_SetCompare3(TIM2, COMPARE);
}

 /**
 * @brief  TIM3 PWM 初始化
 * @param  None
 * @retval None
 */
void TIM3_PWM_Init(void)
{
  //开启时钟
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

  //配置GPIO
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  //配置定时器
  TIM_InternalClockConfig(TIM3);

  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
  TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInitStructure.TIM_Period = 20000 - 1;
  TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;
  TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);

  TIM_OCInitTypeDef TIM_OCInitStructure;
  TIM_OCStructInit(&TIM_OCInitStructure);
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;
  
  TIM_OC1Init(TIM3, &TIM_OCInitStructure);
  TIM_OC2Init(TIM3, &TIM_OCInitStructure);
  TIM_OC3Init(TIM3, &TIM_OCInitStructure);
  TIM_OC4Init(TIM3, &TIM_OCInitStructure);

  TIM_Cmd(TIM3, ENABLE);
}

 /**
 * @brief  TIM3 PWM 输出口1的占空比
 * @param  占空比
 * @retval None
 */
void TIM3_PWM_SetCompare1(uint16_t COMPARE)
{
  TIM_SetCompare1(TIM3, COMPARE);
}

 /**
 * @brief  TIM3 PWM 输出口2的占空比
 * @param  占空比
 * @retval None
 */
void TIM3_PWM_SetCompare2(uint16_t COMPARE)
{
  TIM_SetCompare2(TIM3, COMPARE);
}

 /**
 * @brief  TIM3 PWM 输出口3的占空比
 * @param  占空比
 * @retval None
 */
void TIM3_PWM_SetCompare3(uint16_t COMPARE)
{
  TIM_SetCompare3(TIM3, COMPARE);
}

 /**
 * @brief  TIM3 PWM 输出口4的占空比
 * @param  占空比
 * @retval None
 */
void TIM3_PWM_SetCompare4(uint16_t COMPARE)
{
  TIM_SetCompare4(TIM3, COMPARE);
}






