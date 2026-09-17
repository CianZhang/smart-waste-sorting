#include "hc_sr04.h"
#include "UART3_OpenMV.h"
#include "OLED.h" 

#define FULL_VALUE1 16
#define FULL_VALUE2 16
#define FULL_VALUE3 16
#define FULL_VALUE4 13.8

float distances[4];						// 单独测量距离
float arr[12];							// 三次测量的距离

 /**
 * @brief  微秒延时函数（使用TIM6）
 * @param  延时数
 * @retval None
 */
static void Delay_us(uint32_t us)
{
    TIM_SetCounter(TIM6, 0);            // 清零计数器
    TIM_Cmd(TIM6, ENABLE);              // 启用定时器
    while (TIM_GetCounter(TIM6) < us);  // 等待指定微秒
    TIM_Cmd(TIM6, DISABLE);             // 停止定时器
}

 /**
 * @brief  始化GPIO和TIM6
 * @param  None
 * @retval None
 */
void HC_SR04_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    // 使能GPIOA和TIM6时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);

    // 配置所有Trig引脚为推挽输出
    GPIO_InitStructure.GPIO_Pin = HC_SR04_TRIG1_PIN | HC_SR04_TRIG2_PIN | HC_SR04_TRIG3_PIN | HC_SR04_TRIG4_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(HC_SR04_TRIG1_PORT, &GPIO_InitStructure);

    // 配置所有Echo引脚为浮空输入
    GPIO_InitStructure.GPIO_Pin = HC_SR04_ECHO1_PIN | HC_SR04_ECHO2_PIN | HC_SR04_ECHO3_PIN | HC_SR04_ECHO4_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(HC_SR04_ECHO1_PORT, &GPIO_InitStructure);

    // 配置TIM6用于微秒级计时
    TIM_TimeBaseStructure.TIM_Period = 0xFFFF;          // 最大计数值
    TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1;       // 72MHz / 72 = 1MHz，1us计数一次
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
    TIM_Cmd(TIM6, DISABLE);  // 默认关闭定时器
}

 /**
 * @brief  测量单个模块距离的辅助函数
 * @param  触发IO口
 * 		   回响IO口
 * @retval None
 */
static float MeasureDistance(GPIO_TypeDef* trig_port, uint16_t trig_pin, 
                             GPIO_TypeDef* echo_port, uint16_t echo_pin)
{
    uint32_t timeout = 50000;  // 超时时间（微秒）
    uint32_t time_us = 0;      // 回声持续时间（微秒）
    float distance = 0;        // 距离（厘米）

    // 发送10us触发脉冲
    GPIO_WriteBit(trig_port, trig_pin, Bit_SET);
    Delay_us(10);
    GPIO_WriteBit(trig_port, trig_pin, Bit_RESET);

    // 等待Echo引脚变为高电平（超声波发射）
    timeout = 50000;
    while (GPIO_ReadInputDataBit(echo_port, echo_pin) == Bit_RESET && timeout--)
    {
        if (timeout == 0) return -1;  // 超时返回-1
    }

    // 测量Echo高电平持续时间
    TIM_SetCounter(TIM6, 0);  // 清零计数器
    TIM_Cmd(TIM6, ENABLE);    // 启动定时器
    timeout = 50000;          // 重置超时计数
    while (GPIO_ReadInputDataBit(echo_port, echo_pin) == Bit_SET && timeout--)
    {
        if (timeout == 0)
        {
            TIM_Cmd(TIM6, DISABLE);
            return -1;  // 超时返回-1
        }
    }
    time_us = TIM_GetCounter(TIM6);  // 获取计数值（微秒）
    TIM_Cmd(TIM6, DISABLE);          // 停止定时器

    // 计算距离：距离 = 时间（us） * 声速（0.0343 cm/us） / 2
    distance = (float)time_us * 0.0343 / 2;

    return distance;
}

 /**
 * @brief  获取四个模块的距离（单位：厘米）
 * @param  None
 * @retval 四个距离，指针传递
 */
void HC_SR04_GetDistances(float *distances)
{
    distances[0] = MeasureDistance(HC_SR04_TRIG1_PORT, HC_SR04_TRIG1_PIN, 
                                  HC_SR04_ECHO1_PORT, HC_SR04_ECHO1_PIN);
    Delay_ms(100);  // 等待100ms，避免前一个模块的回波干扰

    distances[1] = MeasureDistance(HC_SR04_TRIG2_PORT, HC_SR04_TRIG2_PIN, 
                                  HC_SR04_ECHO2_PORT, HC_SR04_ECHO2_PIN);
    Delay_ms(100);  // 等待100ms

    distances[2] = MeasureDistance(HC_SR04_TRIG3_PORT, HC_SR04_TRIG3_PIN, 
                                  HC_SR04_ECHO3_PORT, HC_SR04_ECHO3_PIN);
    Delay_ms(100);  // 等待100ms

    distances[3] = MeasureDistance(HC_SR04_TRIG4_PORT, HC_SR04_TRIG4_PIN, 
                                  HC_SR04_ECHO4_PORT, HC_SR04_ECHO4_PIN);
	Delay_ms(100);  // 等待100ms
}

 /**
 * @brief  配合旋转，取四个模块三次测量的平均距离
 * @param  None
 * @retval 四个距离，指针传递
 */
void HC_SR04_Get_Average_Distances(void)
{
	float average_distance[4];
	Horizontal_and_Vertical_Reset();
	Delay_ms(500);
//	Delay_ms(500);
	
	Low_Servo_SetCompareHorizontal(70);
	HC_SR04_GetDistances(distances);
	arr[0] = distances[0];
	arr[1] = distances[1];
	arr[2] = distances[2];
	arr[3] = distances[3];
	Delay_ms(500);
//	Delay_ms(500);
		
	Low_Servo_SetCompareHorizontal(90);
	HC_SR04_GetDistances(distances);
	arr[4] = distances[0];
	arr[5] = distances[1];
	arr[6] = distances[2];
	arr[7] = distances[3];
	Delay_ms(500);
//	Delay_ms(500);
		
	Low_Servo_SetCompareHorizontal(110);
	HC_SR04_GetDistances(distances);
	arr[8] = distances[0];
	arr[9] = distances[1];
	arr[10] = distances[2];
	arr[11] = distances[3];
	Delay_ms(500);
//	Delay_ms(500);
	
	Low_Servo_SetCompareHorizontal(90);
		
	average_distance[0] = (arr[0] + arr[4] + arr[8]) / 3;
	average_distance[1] = (arr[1] + arr[5] + arr[9]) / 3;
	average_distance[2] = (arr[2] + arr[6] + arr[10]) / 3;
	average_distance[3] = (arr[3] + arr[7]) / 2; 	

	if(average_distance[0] < FULL_VALUE1) { UART3_OpenMV_SendString("Four\n"); }
	else { UART3_OpenMV_SendString("Fempty\n"); }
	if(average_distance[1] < FULL_VALUE2) { UART3_OpenMV_SendString("Two\n"); }
	else { UART3_OpenMV_SendString("Tempty\n"); }
	if(average_distance[2] < FULL_VALUE3) { UART3_OpenMV_SendString("Three\n"); }
	else { UART3_OpenMV_SendString("Rempty\n"); }
	if(average_distance[3] < FULL_VALUE4) { UART3_OpenMV_SendString("One\n"); }
	else { UART3_OpenMV_SendString("Oempty\n"); }
	
	OLED_ShowFNum(1, 1, average_distance[0], 8, 4);
	OLED_ShowFNum(2, 1, average_distance[1], 8, 4);
	OLED_ShowFNum(3, 1, average_distance[2], 8, 4);
	OLED_ShowFNum(4, 1, average_distance[3], 8, 4);
}
