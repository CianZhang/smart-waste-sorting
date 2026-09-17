#include "servo_drive.h"

#define DEGREE_REVOLVE 85
#define DEGREE_GRAB 40
#define DEGREE_DOWN 70

 /**
 * @brief  设置旋转舵机角度
 * @param  角度
 * @retval None
 */
void Arm_Servo_SetCompareRevolve(float DEGREE)
{
  TIM3_PWM_SetCompare1(DEGREE / 180 * 2000 + 500);
}

 /**
 * @brief  设置抓夹舵机角度
 * @param  角度
 * @retval None
 */
void Arm_Servo_SetCompareGrab(float DEGREE)
{
  TIM3_PWM_SetCompare2(DEGREE / 180 * 2000 + 500);
}
       
 /**
 * @brief  设置下降舵机角度
 * @param  角度
 * @retval None
 */
void Arm_Servo_SetCompareDown(float DEGREE)
{
  TIM3_PWM_SetCompare3(DEGREE / 180 * 2000 + 500);
  TIM3_PWM_SetCompare4(DEGREE / 180 * 2000 + 500);
}

 /**
 * @brief  Arm_Servo 舵机复位
 * @param  None
 * @retval None
 */
void Arm_Servo_Reset(void)
{
  Arm_Servo_SetCompareRevolve(DEGREE_REVOLVE);
  Arm_Servo_SetCompareGrab(DEGREE_GRAB);
  Arm_Servo_SetCompareDown(DEGREE_DOWN);
}

 /**
 * @brief  Arm_Servo 舵机初始化
 * @param  None
 * @retval None
 */
void Arm_Servo_Init(void)
{
  TIM3_PWM_Init();
  Arm_Servo_Reset();
}

