#include "UART3_OpenMV.h"
#include "infrared.h"
#include "hc_sr04.h"
#include "Low_Servo_App.h"
#include <stdio.h>
#include <stdarg.h>

//OpenMVï¿½ï¿½ï¿½Í¸ï¿½STM32ï¿½ï¿½ï¿½ï¿½ï¿½Ýµï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ò»ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ò»ï¿½ï¿½ï¿½Ö½Ú£ï¿½
#define OpenMV_data 7

//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Õµï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ý£ï¿½ï¿½ï¿½ï¿½ï¿½ÎªÈ«ï¿½Ö±ï¿½ï¿½ï¿½
//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ï´ï¿½ï¿½ï¿½Ê¾ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½256ï¿½ï¿½ï¿½ï¿½ï¿½Ý£ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ö½ï¿½ï¿½ï¿½ï¿½ï¿½ÎªÊµï¿½ï¿½Öµ
//		uint16_t X1 = (UART3_receive_data[1] << 8) | UART3_receive_data[0];
//		points_x = (float)X1;

//float points_x, points_y;						 //Ð¡ï¿½ï¿½ï¿½ÊµÊ±Î»ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
//int dx, dy;										 //Ð¡ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Öµ

extern uint8_t break_flag;

/*******************************************************************************************************/
uint16_t UART3_receive_data[OpenMV_data];        //ï¿½ï¿½ï¿½Õµï¿½ï¿½ï¿½ï¿½ï¿½
uint8_t UART3_RxFlag;                   		     //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ý°ï¿½ï¿½ï¿½Ö¾Î»
uint8_t RxData;

/**
 * @brief  USART3 ï¿½ï¿½Ê¼ï¿½ï¿½
 *         PB10 -> TXï¿½ï¿½PB11 -> RX
 * @param  baudRate ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
 *         PreemptionPriority ï¿½ï¿½Õ¼ï¿½ï¿½ï¿½È¼ï¿½
 *         SubPriority ï¿½ï¿½Ó¦ï¿½ï¿½ï¿½È¼ï¿½
 * @retval None
 */
void UART3_OpenMV_Init(uint32_t baudRate, uint8_t PreemptionPriority, uint8_t SubPriority)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;        
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
    
    USART_InitTypeDef USART_InitStructure ;
    USART_InitStructure.USART_BaudRate= baudRate;
    USART_InitStructure.USART_HardwareFlowControl= USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART3,&USART_InitStructure);
 
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriority;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;
    NVIC_Init(&NVIC_InitStructure);
	
    USART_Cmd(USART3,ENABLE);
}

/**
 * @brief  ï¿½ï¿½ï¿½Ú·ï¿½ï¿½ï¿½Ò»ï¿½ï¿½ï¿½Ö½ï¿½
 * @param  Byte Òªï¿½ï¿½ï¿½Íµï¿½Ò»ï¿½ï¿½ï¿½Ö½ï¿½
 * @retval None
 */
void UART3_OpenMV_SendByte(uint8_t Byte)
{
    USART_SendData(USART3, Byte);        									//ï¿½ï¿½ï¿½Ö½ï¿½ï¿½ï¿½ï¿½ï¿½Ð´ï¿½ï¿½ï¿½ï¿½ï¿½Ý¼Ä´ï¿½ï¿½ï¿½ï¿½ï¿½Ð´ï¿½ï¿½ï¿½USARTï¿½Ô¶ï¿½ï¿½ï¿½ï¿½ï¿½Ê±ï¿½ï¿½ï¿½ï¿½
    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);    		//ï¿½È´ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
    /*ï¿½Â´ï¿½Ð´ï¿½ï¿½ï¿½ï¿½ï¿½Ý¼Ä´ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ô¶ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½É±ï¿½Ö¾Î»ï¿½ï¿½ï¿½Ê´ï¿½Ñ­ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ö¾Î»*/
}
	
/**
  * º¯    Êý£º´®¿Ú·¢ËÍÒ»¸ö×Ö·û´®
  * ²Î    Êý£ºString Òª·¢ËÍ×Ö·û´®µÄÊ×µØÖ·
  * ·µ »Ø Öµ£ºÎÞ
  */
void UART3_OpenMV_SendString(char *String)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i ++)//±éÀú×Ö·ûÊý×é£¨×Ö·û´®£©£¬Óöµ½×Ö·û´®½áÊø±êÖ¾Î»ºóÍ£Ö¹
	{
		UART3_OpenMV_SendByte(String[i]);		//ÒÀ´Îµ÷ÓÃSerial_SendByte·¢ËÍÃ¿¸ö×Ö½ÚÊý¾Ý
	}
}

/**
 * @brief  ï¿½ï¿½È¡ï¿½ï¿½ï¿½Ú½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ý°ï¿½ï¿½ï¿½Ö¾Î»
 * @param  Byte Òªï¿½ï¿½ï¿½Íµï¿½Ò»ï¿½ï¿½ï¿½Ö½ï¿½
 * @retval ï¿½ï¿½ï¿½Ú½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ý°ï¿½ï¿½ï¿½Ö¾Î»ï¿½ï¿½ï¿½ï¿½Î§ï¿½ï¿½0~1ï¿½ï¿½ï¿½ï¿½ï¿½Õµï¿½ï¿½ï¿½ï¿½Ý°ï¿½ï¿½ó£¬±ï¿½Ö¾Î»ï¿½ï¿½1ï¿½ï¿½ï¿½ï¿½È¡ï¿½ï¿½ï¿½Ö¾Î»ï¿½Ô¶ï¿½ï¿½ï¿½ï¿½ï¿½
 */
uint8_t UART3_GetRxFlag(void)
{
    if (UART3_RxFlag == 1)            	//ï¿½ï¿½ï¿½ï¿½ï¿½Ö¾Î»Îª1
    {
        UART3_RxFlag = 0;
        return 1;                    	//ï¿½ò·µ»ï¿½1ï¿½ï¿½ï¿½ï¿½ï¿½Ô¶ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ö¾Î»
    }
    return 0;                        	//ï¿½ï¿½ï¿½ï¿½ï¿½Ö¾Î»Îª0ï¿½ï¿½ï¿½ò·µ»ï¿½0
}
uint8_t UART3_GetRxData(void)
{
    return RxData;
}

RxInfo UART3_GetRxInfo(void)
{
		RxInfo info;
		info.x = (UART3_receive_data[0] & 0xf) * 100 + (UART3_receive_data[1] & 0xf) * 10 + (UART3_receive_data[2] & 0xf);
		info.y = (UART3_receive_data[3] & 0xf) * 100 + (UART3_receive_data[4] & 0xf) * 10 + (UART3_receive_data[5] & 0xf);
//		info.angle = ;
		info.type = UART3_receive_data[6] & 0xf;
    return info;
}

/**
 * @brief  USART3 ï¿½Ð¶Ïºï¿½ï¿½ï¿½
 * @param  None
 * @retval None
 */
void USART3_IRQHandler(void)
{
			static uint8_t RxState = 0;        								//ï¿½ï¿½ï¿½ï¿½ï¿½Ê¾ï¿½ï¿½Ç°×´Ì¬ï¿½ï¿½×´Ì¬ï¿½Ä¾ï¿½Ì¬ï¿½ï¿½ï¿½ï¿½
			static uint8_t pRxPacket = 0;      								//ï¿½ï¿½ï¿½ï¿½ï¿½Ê¾ï¿½ï¿½Ç°ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Î»ï¿½ÃµÄ¾ï¿½Ì¬ï¿½ï¿½ï¿½ï¿½
    if (USART_GetITStatus(USART3, USART_IT_RXNE) == SET)        	//ï¿½Ð¶ï¿½ï¿½Ç·ï¿½ï¿½ï¿½USART3ï¿½Ä½ï¿½ï¿½ï¿½ï¿½Â¼ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ð¶ï¿½
    {
        RxData = USART_ReceiveData(USART3);                 //ï¿½ï¿½È¡ï¿½ï¿½ï¿½Ý¼Ä´ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ú½ï¿½ï¿½Õµï¿½ï¿½ï¿½ï¿½Ý±ï¿½ï¿½ï¿½
				
				if(RxState == 0) {
					if(RxData == '6') {
						RxState = 1;
						UART3_RxFlag = 1;
					}
				}
				else if(RxState == 1) {
					
					if(RxData == '7') {
						Condense();
					}
					else if(RxData == '8') {
						Low_Servo_SetGuard(80);
						HC_SR04_Get_Average_Distances();
						Low_Servo_Reset();
					}
					else if(RxData != '5') {
						UART3_RxFlag = 1;
					}
					else {
						RxState = 2;
					}
				}
				else if(RxState == 2) {
					UART3_receive_data[pRxPacket] = RxData;
					pRxPacket++;
					if(pRxPacket == OpenMV_data) {
						RxState = 3;
					}
				}
				else if(RxState == 3) {
					if(RxData == '\n') {
						RxState = 1;
						pRxPacket = 0;
						UART3_RxFlag = 1;
					}
				}
			
        USART_ClearITPendingBit(USART3, USART_IT_RXNE);				//ï¿½ï¿½ï¿½ï¿½ï¿½Ö¾Î»
    }
}
