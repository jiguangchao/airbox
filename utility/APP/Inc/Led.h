
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LED_H_
#define __LED_H_

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */
#include "platform.h"
#include "BaselibInclude.h"
#include "Dataconfigure.h"
#include "BSP_LED.h"
//#include "EnOceanlibInclude.h"

//PWM参数
#define LED_PWM_ARR_VALUE     (999)  // ARR初值（ +1 就是定时器周期，单位us ）
#define LED_PWM_OFF_VALUE     (1000) // 关闭LED PWM值
#define LED_PWM_ON_VALUE      (0)     // 开启LED PWM值
#define LED_PWM_STEP_TIME     (10)   //呼吸灯步进时间
//呼吸灯参数   
#define LED_PWM_STEP          (8)   // PWM步进值
#define LED_PWM_SLEEP         (60) // 呼吸灯休息时
//闪烁参数   
#define LED_Blink_TIME        (80) //闪烁时间
//常亮参数   
#define LED_Light_ON_TIME     (500) //常量时间3S
#define LED_Light_OFF_TIME    (0) //常量时间3S

typedef enum
{
    eLEDRUN_STANDBY = 1, // 待机状态

    //呼吸灯模式
    eLEDRUN_BREATHEMODE_INIT,  // 呼吸灯模式初始化
    eLEDRUN_BREATHEMODE_UP,    // 呼吸灯模式向上计数变亮
    eLEDRUN_BREATHEMODE_DOWN,  // 呼吸灯模式向下计数变暗
    eLEDRUN_BREATHEMODE_SLEEP, // 呼吸灯模式一轮结束后关闭一段时间

    //闪烁模式
    eLEDRUN_BLINKMODE_INIT,    //闪烁模式开始
    eLEDRUN_BLINKMODE_ON,  //闪烁模式开状态
    eLEDRUN_BLINKMODE_OFF, //闪烁模式关状态

    //常亮模式
    eLEDRUN_LIGHTMODE_INIT, //常亮模式开始
    eLEDRUN_LIGHTMODE_WAIT, //常亮模式等待
    eLEDRUN_LIGHTMODE_END,  //常量模式结束

    //故障报警模式
    eLEDRUN_FAULT_ALARM,    //故障报警 

} LedRunMode_t; //LED运行状态

//模块运行状态定义
typedef enum
{
    eLEDWORK_STANDBY = 1, // 待机状态

    //开机效果
    eLEDWORK_WELCOME_START, //开机欢迎使用的效果
    eLEDWORK_WELCOME_WAIT,  //开机欢迎使用的效果

    //空气质量展示
    eLEDWORK_AIRQUALITY_SHOW,     //展示空气质量
    eLEDWORK_AIRQUALITY_SHOWWAIT, //等待展示空气质量

    //PMS测试
    eLEDWORK_PMSTEST_CMDSTART, //PMS测试命令开始
    eLEDWORK_PMSTEST_WAITEND,  //等待PMS测试命令结束
/*
    //硬件自检模式
    LedWork_SelfTestReady,     //自检测试准备
    LedWork_SelfTesting,       //展示自动测试中的效果（四种颜色的LED此起彼伏的亮，表示正在测试）
    LedWork_SelfTestShowStart, //测试结束,开始展示测试结果
    LedWork_SelfTestShowing,   //自检展示中
*/
    //LED关闭
    eLEDWORK_SWITCH, //LED开关

} LedWorkMode_t; //LED工作状态

typedef enum
{
    eLED_INITIAL = 0,
    eLED_RED,    // 红
    eLED_ORANGE, // 橙
    eLED_YELLOW, // 黄
    eLED_GREEN,  // 绿
    eLED_ALL,
    eLED_RED_ORANGE, //红橙
    eLED_RED_YELLOW, //红黄


} eLed_t;

typedef struct
{
    eLed_t eLedID;           // ID
    LedRunMode_t eRunMode;   // 运行模式
    LedWorkMode_t eWorkMode; // 工作模式

    uint32_t u32LedRunTimer;  // 计时器
    uint32_t u32LedWorkTimer; // 计时器

    uint32_t u32RunPWMValue;    // PWM参数
    uint32_t u32RunPWMCount;   // 运行计数（呼吸灯模式下控制呼吸次数）
    uint32_t u32RunBlinkCount; // 运行计数（闪烁时控制闪烁次数）

    uint32_t u32BlinkONTime;  // 闪烁时开启时间
    uint32_t u32BlinkOFFTime; // 闪烁时关闭启时间

    uint32_t u32LightONTime;  //常亮时开启时间
    uint32_t u32LightOFFTime;

    uint8_t u8SelfTestCount; //自检计数
    uint8_t u8LedSwtichFalg; //LED开关标志

    uint8_t u8MarqueeFlag;   //跑马灯标记

    uint32_t u32EnoceanFaultCount; //Enocean故障计数

} LED_Typedef;

extern LED_Typedef LED;

/**
  * @brief
  * @param
  * @retval None
  */
void LED_Tick1ms(LED_Typedef *pLED);
/**
 * @brief
 * @param
 * @retval None
 */
void LEDPWM(uint8_t eLedID, uint16_t PWMVlue);
/**
 * @brief
 * @param
 * @retval None
 */
void LEDLight(uint8_t eLedID);
/**
 * @brief
 * @param
 * @retval None
 */
void LEDDark(uint8_t eLedID);
/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/
/**
  * @brief
  * @param
  * @retval None     
  */
//设置LED为呼吸灯模式
void LedRunMode_Breathe(eLed_t eLedID, uint32_t count);
/**
  * @brief
  * @param
  * @retval None     
  */
//设置LED为闪烁模式
void LedRunMode_Blink(eLed_t eLedID, uint32_t count);
/**
  * @brief
  * @param
  * @retval None     
  */
void LedRunMode_Light(eLed_t eLedID, uint32_t count); //设置LED为常亮模式
/**
  * @brief
  * @param
  * @retval None     
  */
void LedRunMode_FaultAlarm(eLed_t eLedID); //设置LED故障报警
/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/
/**
  * @brief
  * @param
  * @retval None     
  */
void AirQuality_LED(void); //空气质量LED灯显示
/**
  * @brief
  * @param
  * @retval None     
  */
void FaultCode_LED(void);  //错误码LED灯显示

/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/
/**
  * @brief
  * @param
  * @retval None     
  */
void LED_runmode(LED_Typedef *pLED); //LED运行模式状态机
/**
  * @brief
  * @param
  * @retval None     
  */
void LED_workmode(LED_Typedef *pLED); //LED工作模式状态机

#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
