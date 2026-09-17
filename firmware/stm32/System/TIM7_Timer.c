#include "stm32f10x.h"              // Device header

 /**
 * @brief  TIM7 定时中断初始化
 * @param  ARR 计数周期 
 *         PreemptionPriority 抢占优先级
 *         SubPriority 响应优先级
 * @retval None
 */
void TIM7_Timer_Init(uint32_t ARR, uint8_t PreemptionPriority, uint8_t SubPriority)
{
	/*开启时钟*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);						//开启TIM7的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);						// 开启GPIOB的时钟
	
	/*配置时钟源*/
	TIM_InternalClockConfig(TIM7);											    //选择TIM7为内部时钟，若不调用此函数，TIM默认也为内部时钟
	
	/*时基单元初始化*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;							//定义结构体变量
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;			        //时钟分频，选择不分频，此参数用于配置滤波器时钟，不影响时基单元功能
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;	            //计数器模式，选择向上计数
	TIM_TimeBaseInitStructure.TIM_Period = ARR - 1;						        //计数周期，即ARR的值
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1;					        //预分频器，即PSC的值,1MHz
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;						//重复计数器，高级定时器才会用到
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseInitStructure);							//将结构体变量交给TIM_TimeBaseInit，配置TIM7的时基单元	
	
	/*中断输出配置*/
	TIM_ClearFlag(TIM7, TIM_FLAG_Update);										//清除定时器更新标志位
																				//TIM_TimeBaseInit函数末尾，手动产生了更新事件
																				//若不清除此标志位，则开启中断后，会立刻进入一次中断
																				//如果不介意此问题，则不清除此标志位也可
	
	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);									//开启TIM7的更新中断
	
	/*NVIC中断分组*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);							    //配置NVIC为分组2
																				//即抢占优先级范围：0~3，响应优先级范围：0~3		
																				//若调用多次配置分组的代码，则后执行的配置会覆盖先执行的配置
	/*NVIC配置*/
	NVIC_InitTypeDef NVIC_InitStructure;										//定义结构体变量
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;								//选择配置NVIC的TIM7线
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//指定NVIC线路使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriority;	//指定NVIC线路的抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;		        //指定NVIC线路的响应优先级
	NVIC_Init(&NVIC_InitStructure);												//将结构体变量交给NVIC_Init，配置NVIC外设
	
	/*TIM使能*/
	TIM_Cmd(TIM7, ENABLE);								                        //使能TIM7，定时器开始运行
}
