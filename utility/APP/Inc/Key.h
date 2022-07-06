
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DATA_REPORT_H
#define __DATA_REPORT_H

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */
#include "platform.h"
#include "BaselibInclude.h"
#include "Dataconfigure.h"



//按键处理参数
#define KEY_HANDL_FUNC_MAX       (5)                      //按键处理函数最大允许的注册数量
#define KEY_JITTER_LIMIT_TIME    (30)                      //按键抖动极限时间（单位：1ms）
#define KEY_SHORT_PRESS_TIME     (80)                      //按键短按有效的最短时间（单位：1ms）
#define KEY_LONG_PRESS_TIME      (2000)                    //按键长按有效的最短时间（单位：1ms）

#define KEY_RESET_TIME           (10*1000)                  //一键恢复出厂设置（单位：1ms）


//按键事件
typedef enum
{
    eKEYEVENT_NONE = 0,       //没有按键按下
    eKEYEVENT_PRESS,          //按键按下
    eKEYEVENT_JITTER,         //按键消抖
    eKEYEVENT_COUNT,          //按键计时
    eKEYEVENT_END,            //按键结束 

}keyevent_t;

//硬件测试
typedef enum
{
    eHWTESTMODE_No  = 0, //非硬件测试模式
    eHWTESTMODE_YES = 1, //硬件测试模式
} hwtest_t;


typedef struct
{
  keyevent_t          eKeyEvent;
  hwtest_t            eHardWareTest;//硬件测试控制


  uint32_t            u32KeyTimer;       // 计时器
  uint16_t            u16KeyStartCount;
  uint16_t            u16KeyPressTimer;   // 按下计时

  uint8_t             u8KeyState;

//  uint8_t             HWTestMode;
//  uint16_t            IntoPMSMode;      //进入PMS模式

}Key_Typedef;

extern Key_Typedef KEY;

/**
  * @brief
  * @param
  * @retval None     
  */
void Key_Tick1ms(Key_Typedef *pKEY);   //Key定时器
/**
  * @brief
  * @param
  * @retval None     
  */
void KeyEvent_Scanning(Key_Typedef *pKEY);  //Key事件扫描


#endif