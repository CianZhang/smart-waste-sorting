#include "servo_drive.h"
#include "Delay.h"

#define DEGREE_ 46
#define DEGREE_HORIZONTAL 90
#define DEGREE_VERTICAL 94
#define DEGREE_GUARD 52
#define ROTATE_DELAY 20

 /**
 * @brief  设置水平舵机角度
 * @param  角度
 * @retval None
 */
void Low_Servo_SetCompareHorizontal(float DEGREE)
{
  TIM2_PWM_SetCompare1(DEGREE / 180 * 2000 + 500);
}

 /**
 * @brief  设置竖直舵机角度
 * @param  角度
 * @retval None
 */
void Low_Servo_SetCompareVertical(float DEGREE)
{
  TIM2_PWM_SetCompare2(DEGREE / 180 * 2000 + 500);
}

 /**
 * @brief  设置挡板舵机角度
 * @param  角度
 * @retval None
 */
void Low_Servo_SetGuard(float DEGREE)
{
  TIM2_PWM_SetCompare3(DEGREE / 180 * 2000 + 500);
}

 /**
 * @brief  角度延时旋转
 * @param  角度
 * @retval None
 */
void Low_Servo_RotateHorizontal(float DEGREE)
{
  uint8_t i;
  if(DEGREE > 90){
    for(i = 91; i <= DEGREE; i ++){
      Low_Servo_SetCompareHorizontal(i);
      Delay_ms(ROTATE_DELAY);
    }
  }
  else{
    for(i = 89; i >= DEGREE; i --){
      Low_Servo_SetCompareHorizontal(i);
      Delay_ms(ROTATE_DELAY);
    }
  }
}

void Low_Servo_RotateReset(void)
{
	uint8_t i;
	for(i = 46; i <= 90; i ++){
      Low_Servo_SetCompareHorizontal(i);
      Delay_ms(ROTATE_DELAY);
    }
}

 /**
 * @brief  Low_Servo 舵机复位
 * @param  None
 * @retval None
 */
void Horizontal_and_Vertical_Reset(void)
{
  Low_Servo_SetCompareHorizontal(DEGREE_HORIZONTAL);
  Low_Servo_SetCompareVertical(DEGREE_VERTICAL);
}

 /**
 * @brief  Low_Servo 舵机复位
 * @param  None
 * @retval None
 */
void Low_Servo_Reset(void)
{
  Low_Servo_SetCompareHorizontal(DEGREE_HORIZONTAL);
  Low_Servo_SetCompareVertical(DEGREE_VERTICAL);
	Delay_ms(200);
  Low_Servo_SetGuard(DEGREE_GUARD);
}

 /**
 * @brief  Low_Servo 舵机初始化
 * @param  None
 * @retval None
 */
void Low_Servo_Init(void)
{
  TIM2_PWM_Init();
  Low_Servo_Reset();
}

 /**
 * @brief  Low_Servo 对输入不同数字倾斜不同角度
 * @param  1234 数字
 * @retval None
 */
void Low_Servo_React(uint8_t NUM)
{
  if(NUM == 0){
    Low_Servo_Reset();
  }
  else if(NUM == 1){
    Low_Servo_RotateHorizontal(DEGREE_HORIZONTAL - 45);
    Low_Servo_SetCompareVertical(DEGREE_VERTICAL + DEGREE_);
  }
  else if(NUM == 2){
    Low_Servo_RotateHorizontal(DEGREE_HORIZONTAL + 45);
    Low_Servo_SetCompareVertical(DEGREE_VERTICAL + DEGREE_);
  }
  else if(NUM == 3){
    Low_Servo_RotateHorizontal(DEGREE_HORIZONTAL - 45);
    Low_Servo_SetCompareVertical(DEGREE_VERTICAL - DEGREE_);
  }
  else if(NUM == 4){
    Low_Servo_RotateHorizontal(DEGREE_HORIZONTAL + 45);
    Low_Servo_SetCompareVertical(DEGREE_VERTICAL - DEGREE_);
  }
}
