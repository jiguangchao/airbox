
/*!
*****************************************************************
$Name$
$Revision: 
$Date: 
\file 
\brief  
\author zhoujinbang


<b>Company:</b>\nmenred automation\n
修改记录
1、
2、
3、
4、
5、
6、
*****************************************************************/

/*============================ INCLUDES ======================================*/
#include "platform.h"
#include "BaselibInclude.h"
#include "EnOceanlibInclude.h"
#include "BSP.h"
//#include "KeyLedDipDectTemp.h"
#include "Dataconfigure.h"
#include "Led.h"
#include "Key.h"

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

/*============================ GLOBAL VARIABLES ==============================*/

/*============================ LOCAL VARIABLES ===============================*/

/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/

/* Private variables ---------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

LED_Typedef LED;
/* Private function prototypes -----------------------------------------------*/

/**
  * @brief
  * @param
  * @retval None     
  */
void LED_Tick1ms(LED_Typedef *pLED) //LED定时器
{

    if (pLED->u32LedRunTimer)
    {
        pLED->u32LedRunTimer--;
    }
    if (pLED->u32LedWorkTimer)
    {
        pLED->u32LedWorkTimer--;
    }
}
/**
 * @brief
 * @param
 * @retval None
 */
void LEDPWM(uint8_t eLedID, uint16_t PWMVlue)
{

    switch (eLedID)
    {
    case eLED_RED:
        BSP_LEDPWM_RED(PWMVlue);
        BSP_LEDDark_ORG();
        BSP_LEDDark_Yellow();
        BSP_LEDDark_Green();
        break;
    case eLED_ORANGE:
        BSP_LEDPWM_ORG(PWMVlue);
        BSP_LEDDark_RED();
        BSP_LEDDark_Yellow();
        BSP_LEDDark_Green();
        break;
    case eLED_YELLOW:
        BSP_LEDPWM_Yellow(PWMVlue);
        BSP_LEDDark_ORG();
        BSP_LEDDark_RED();
        BSP_LEDDark_Green();
        break;
    case eLED_GREEN:
        BSP_LEDPWM_Green(PWMVlue);
        BSP_LEDDark_ORG();
        BSP_LEDDark_Yellow();
        BSP_LEDDark_RED();
        break;
    case eLED_ALL:
        BSP_LEDPWM_RED(PWMVlue);
        BSP_LEDPWM_ORG(PWMVlue);
        BSP_LEDPWM_Yellow(PWMVlue);
        BSP_LEDPWM_Green(PWMVlue);
        break;
    case eLED_RED_ORANGE:
        BSP_LEDPWM_RED(PWMVlue);
        BSP_LEDPWM_ORG(PWMVlue);
        BSP_LEDDark_Yellow();
        BSP_LEDDark_RED();
        break;
    case eLED_RED_YELLOW:
        BSP_LEDPWM_RED(PWMVlue);
        BSP_LEDDark_ORG();
        BSP_LEDPWM_Yellow(PWMVlue);
        BSP_LEDDark_Green();
        break;
        /*
    case eLED_MARQUEE_1:
        BSP_LEDPWM_RED(PWMVlue);
        BSP_LEDDark_ORG();
        BSP_LEDDark_Yellow();
        BSP_LEDDark_Green();
    case eLED_MARQUEE_2:
        BSP_LEDPWM_RED(PWMVlue);
        BSP_LEDPWM_ORG(PWMVlue);
        BSP_LEDDark_Yellow();
        BSP_LEDDark_Green();
    case eLED_MARQUEE_3:
        BSP_LEDPWM_RED(PWMVlue);
        BSP_LEDPWM_ORG(PWMVlue);
        BSP_LEDPWM_Yellow(PWMVlue);
        BSP_LEDDark_Green();   
    case eLED_MARQUEE_4:
        BSP_LEDPWM_RED(PWMVlue);
        BSP_LEDPWM_ORG(PWMVlue);
        BSP_LEDPWM_Yellow(PWMVlue);
        BSP_LEDPWM_Green(PWMVlue);
*/
    default:
        BSP_LEDDark_RED();
        BSP_LEDDark_ORG();
        BSP_LEDDark_Yellow();
        BSP_LEDDark_Green();
        break;
    }
}
/**
 * @brief
 * @param
 * @retval None
 */
void LEDLight(uint8_t eLedID)
{

    switch (eLedID)
    {
    case eLED_RED:
        BSP_LEDLight_RED();
        BSP_LEDDark_ORG();
        BSP_LEDDark_Yellow();
        BSP_LEDDark_Green();
        break;
    case eLED_ORANGE:
        BSP_LEDLight_ORG();
        BSP_LEDDark_RED();
        BSP_LEDDark_Yellow();
        BSP_LEDDark_Green();
        break;
    case eLED_YELLOW:
        BSP_LEDLight_Yellow();
        BSP_LEDDark_ORG();
        BSP_LEDDark_RED();
        BSP_LEDDark_Green();
        break;
    case eLED_GREEN:
        BSP_LEDLight_Green();
        BSP_LEDDark_ORG();
        BSP_LEDDark_Yellow();
        BSP_LEDDark_RED();
        break;
    case eLED_ALL:
        BSP_LEDLight_RED();
        BSP_LEDLight_ORG();
        BSP_LEDLight_Yellow();
        BSP_LEDLight_Green();
        break;
    case eLED_RED_ORANGE:
        BSP_LEDLight_RED();
        BSP_LEDLight_ORG();
        BSP_LEDDark_Yellow();
        BSP_LEDDark_Green();
        break;
    case eLED_RED_YELLOW:
        BSP_LEDLight_RED();
        BSP_LEDDark_ORG();
        BSP_LEDLight_Yellow();
        BSP_LEDDark_Green();
        break;
    default:
        BSP_LEDDark_RED();
        BSP_LEDDark_ORG();
        BSP_LEDDark_Yellow();
        BSP_LEDDark_Green();
        break;
    }
}
/**
 * @brief
 * @param
 * @retval None
 */
void LEDDark(uint8_t eLedID)
{

    switch (eLedID)
    {
    case eLED_RED:
        BSP_LEDDark_RED();
        break;
    case eLED_ORANGE:
        BSP_LEDDark_ORG();
        break;
    case eLED_YELLOW:
        BSP_LEDDark_Yellow();
        break;
    case eLED_GREEN:
        BSP_LEDDark_Green();
        break;
    case eLED_ALL:
        BSP_LEDDark_RED();
        BSP_LEDDark_ORG();
        BSP_LEDDark_Yellow();
        BSP_LEDDark_Green();
        break;
    default:
        BSP_LEDDark_RED();
        BSP_LEDDark_ORG();
        BSP_LEDDark_Yellow();
        BSP_LEDDark_Green();
        break;
    }
}
/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/
/**
  * @brief
  * @param
  * @retval None     
  */
void LedRunMode_Breathe(eLed_t eLedID, uint32_t count) //设置LED为呼吸灯模式
{
    if (LED.eRunMode != eLEDRUN_FAULT_ALARM)
    {
        LED.eLedID = eLedID;
        LED.u32RunPWMCount = count;
        LED.eRunMode = eLEDRUN_BREATHEMODE_INIT;
    }
}
/**
  * @brief
  * @param
  * @retval None     
  */
void LedRunMode_Blink(eLed_t eLedID, uint32_t count) //设置LED为闪烁模式
{
    if (LED.eRunMode != eLEDRUN_FAULT_ALARM)
    {
        LED.eLedID = eLedID;
        LED.u32RunBlinkCount = count;
        LED.eRunMode = eLEDRUN_BLINKMODE_INIT;
    }
}
/**
  * @brief
  * @param
  * @retval None     
  */
void LedRunMode_Light(eLed_t eLedID, uint32_t count) //设置LED为常亮模式
{
    if (LED.eRunMode != eLEDRUN_FAULT_ALARM)
    {
        LED.eLedID = eLedID;
        LED.u32RunBlinkCount = count;
        LED.eRunMode = eLEDRUN_LIGHTMODE_INIT;
    }
}
/**
  * @brief
  * @param
  * @retval None     
  */
void LedRunMode_FaultAlarm(eLed_t eLedID) //设置LED故障报警
{

    LED.eLedID = eLedID;
    LED.eRunMode = eLEDRUN_FAULT_ALARM;
}
/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/
/**
  * @brief
  * @param
  * @retval None     
  */
void AirQuality_LED(void) //空气质量LED灯显示
{
    switch (ReportedData.eAirQuality)
    {
    case eAIR_QUALITY_EXCELLENT:
        LED.eLedID = eLED_GREEN;
        break;
    case eAIR_QUALITY_GOOD:
        LED.eLedID = eLED_YELLOW;
        break;
    case eAIR_QUALITY_MODERATE:
        LED.eLedID = eLED_ORANGE;
        break;
    case eAIR_QUALITY_POOR:
        LED.eLedID = eLED_RED;
        break;
    default:
        LED.eLedID = eLED_ALL;
        break;
    }
    LedRunMode_Breathe(LED.eLedID, 1);
}
/**
  * @brief
  * @param
  * @retval None     
  */
void FaultCode_LED(void) //错误码LED灯显示
{
    if (SHT20.eFaultCode == eSHT20_NORMAL || CH2O_CO2.eCH2OFaultCode == eCH2O_NORMAL || CH2O_CO2.eCO2FaultCode == eCO2_NORMAL || PMSA.eFaultCode == ePMSA_NORMAL)
    {
        LED.eLedID = eLED_INITIAL;
    }
    if (SHT20.eFaultCode == eSHT20_ABNORMAL_DATA || CH2O_CO2.eCH2OFaultCode == eCH2O_ABNORMAL_DATA || CH2O_CO2.eCO2FaultCode == eCO2_ABNORMAL_DATA || PMSA.eFaultCode == ePMSA_ABNORMAL_DATA)
    {
        LED.eLedID = eLED_YELLOW;
    }
    if (SHT20.eFaultCode == eSHT20_EXCEPTION_MESSAGE || CH2O_CO2.eCH2OFaultCode == eCH2O_EXCEPTION_MESSAGE || CH2O_CO2.eCO2FaultCode == eCO2_EXCEPTION_MESSAGE || PMSA.eFaultCode == ePMSA_EXCEPTION_MESSAGE)
    {
        LED.eLedID = eLED_ORANGE;
    }
    if (SHT20.eFaultCode == eSHT20_EQUIPMENT_DROPS || CH2O_CO2.eCH2OFaultCode == eCH2O_EQUIPMENT_DROPS || CH2O_CO2.eCO2FaultCode == eCO2_EQUIPMENT_DROPS || PMSA.eFaultCode == ePMSA_EQUIPMENT_DROPS)
    {
        LED.eLedID = eLED_RED;
    }
    LedRunMode_Light(LED.eLedID, 1);
}

/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/
/**
  * @brief
  * @param
  * @retval None     
  */
void LED_runmode(LED_Typedef *pLED) //LED运行模式状态机
{

    if (pLED->eRunMode > 13)
    {
        pLED->eRunMode = eLEDRUN_STANDBY;
    }

    switch (pLED->eRunMode)
    {
    case eLEDRUN_STANDBY: //待机状态
    {
        LEDDark(eLED_ALL);
        break;
    }

        //呼吸灯控制
    case eLEDRUN_BREATHEMODE_INIT: //呼吸灯模式初始化
    {
        LEDDark(pLED->eLedID);
        //LEDPWM(pLED->eLedID,pLED->u32RunPWMValue);
        pLED->u32RunPWMValue = 1000;
        pLED->eRunMode = eLEDRUN_BREATHEMODE_UP;
        break;
    }
    case eLEDRUN_BREATHEMODE_UP: //变亮
    {
        if (pLED->u32LedRunTimer != 0)
        {
            break;
        }
        if (pLED->u32RunPWMValue >= LED_PWM_STEP)
        {
            pLED->u32RunPWMValue -= (pLED->u32RunPWMValue / 100 + 2);
            LEDPWM(pLED->eLedID, pLED->u32RunPWMValue);
            pLED->u32LedRunTimer = LED_PWM_STEP_TIME; //延时50ms
        }
        else
        {
            pLED->u32RunPWMValue = LED_PWM_ON_VALUE;
            LEDPWM(pLED->eLedID, pLED->u32RunPWMValue);
            pLED->eRunMode = eLEDRUN_BREATHEMODE_DOWN;
            pLED->u32LedRunTimer = LED_PWM_STEP_TIME; //延时50ms
        }
        break;
    }
    case eLEDRUN_BREATHEMODE_DOWN: //变暗
    {
        if (pLED->u32LedRunTimer != 0)
        {
            break;
        }
        if (pLED->u32RunPWMValue < LED_PWM_OFF_VALUE)
        {

            pLED->u32RunPWMValue += (pLED->u32RunPWMValue / 100 + 2);
            LEDPWM(pLED->eLedID, pLED->u32RunPWMValue);
            pLED->u32LedRunTimer = LED_PWM_STEP_TIME; //延时50ms
        }
        else
        {
            pLED->u32RunPWMValue = LED_PWM_OFF_VALUE;
            LEDPWM(pLED->eLedID, pLED->u32RunPWMValue);
            pLED->u32LedRunTimer = LED_PWM_SLEEP;
            pLED->eRunMode = eLEDRUN_BREATHEMODE_SLEEP;
        }
        break;
    }
    case eLEDRUN_BREATHEMODE_SLEEP: //变暗之后黑一段时间
    {
        if (pLED->u32LedRunTimer != 0)
        {
            break;
        }
        pLED->u32RunPWMCount--;
        if (pLED->u32RunPWMCount > 0) //有剩余次数
        {
            pLED->eRunMode = eLEDRUN_BREATHEMODE_UP;
        }
        else //没有剩余次数了
        {
            pLED->u32RunPWMCount = 0;
            pLED->eRunMode = eLEDRUN_STANDBY;
        }
        break;
    }

        //闪烁模式控制

    case eLEDRUN_BLINKMODE_INIT:
    {
        if (pLED->u32LedRunTimer != 0)
        {
            break;
        }
        if (pLED->u32BlinkONTime < LED_Blink_TIME)
        {
            pLED->u32BlinkONTime = LED_Blink_TIME;
        }
        if (pLED->u32BlinkOFFTime < LED_Blink_TIME)
        {
            pLED->u32BlinkOFFTime = LED_Blink_TIME;
        }
        LEDLight(pLED->eLedID);
        pLED->u32LedRunTimer = pLED->u32BlinkONTime;
        pLED->eRunMode = eLEDRUN_BLINKMODE_ON;
        break;
    }
    case eLEDRUN_BLINKMODE_ON:
    {
        if (0 == pLED->u32LedRunTimer)
        {
            LEDDark(pLED->eLedID);
            pLED->u32LedRunTimer = pLED->u32BlinkOFFTime;
            pLED->eRunMode = eLEDRUN_BLINKMODE_OFF;
        }
        break;
    }
    case eLEDRUN_BLINKMODE_OFF:
    {
        if (0 == pLED->u32LedRunTimer)
        {
            if (pLED->u32RunBlinkCount > 0)
            {
                //LEDLight(pLED->eLedID);
                pLED->u32RunBlinkCount--;
                pLED->u32LedRunTimer = pLED->u32BlinkONTime;
                pLED->eRunMode = eLEDRUN_BLINKMODE_INIT;
            }
            else
            {
                pLED->u32RunBlinkCount = 0;
                pLED->eRunMode = eLEDRUN_STANDBY;
            }
        }
        break;
    }

    //常亮模式控制
    case eLEDRUN_LIGHTMODE_INIT:
    {
        if (pLED->u32LedRunTimer != 0)
        {
            break;
        }
        LEDLight(pLED->eLedID);
        pLED->u32LedRunTimer = LED_Light_ON_TIME;
        pLED->eRunMode = eLEDRUN_LIGHTMODE_WAIT;
        break;
    }
    case eLEDRUN_LIGHTMODE_WAIT:
    {
        if (pLED->u32LedRunTimer != 0)
        {
            break;
        }
        //LEDDark(pLED->eLedID);
        pLED->u32LedRunTimer = LED_Light_OFF_TIME;
        pLED->eRunMode = eLEDRUN_LIGHTMODE_END;
        break;
    }
    case eLEDRUN_LIGHTMODE_END:
    {
        if (pLED->u32LedRunTimer != 0)
        {
            break;
        }
        if (pLED->u32RunBlinkCount > 0)
        {
            //LEDLight(pLED->eLedID);
            pLED->u32RunBlinkCount--;
            pLED->u32LedRunTimer = pLED->u32LightONTime;
            pLED->eRunMode = eLEDRUN_BLINKMODE_INIT;
        }
        else
        {
            pLED->u32RunBlinkCount = 0;
            pLED->eRunMode = eLEDRUN_STANDBY;
        }
        // pLED->eRunMode = eLEDRUN_STANDBY;
        break;
    }

    case eLEDRUN_FAULT_ALARM:

        LEDLight(pLED->eLedID);
        break;

    default:
        pLED->eRunMode = eLEDRUN_STANDBY;
        break;
    }
}
/**
     * @brief
     * @param
     * @retval None     
     */
void LED_workmode(LED_Typedef *pLED) //LED工作模式状态机
{
    

    if (pLED->eWorkMode > 8)
    {
        pLED->eWorkMode = eLEDWORK_STANDBY;
    }
    if (pLED->eLedID > 7)
    {
        pLED->eLedID = eLED_INITIAL;
    }

    if (pLED->eWorkMode > 0 && pLED->eWorkMode < 6)
    {
        if (Dev.Cfg.u8LedSwtichFalg == 1)
        {
            pLED->eWorkMode = eLEDWORK_SWITCH;
            LEDDark(eLED_ALL);
        }
    }

    //LED工作任务控制
    switch (pLED->eWorkMode)
    {
    case eLEDWORK_STANDBY:
    {
        pLED->u32LedWorkTimer = 1000; // 1秒后开始显示开机动态效果
        if (pLED->eRunMode != eLEDRUN_FAULT_ALARM)
        {
            pLED->eWorkMode = eLEDWORK_WELCOME_START;
            pLED->eLedID = eLED_INITIAL;
        }

        break;
    }
    case eLEDWORK_WELCOME_START: //显示开机动态效果
    {
        LedRunMode_Breathe(eLED_GREEN, 3);
        pLED->u32LedWorkTimer = 15000;           //等待开机效果完成
        pLED->eWorkMode = eLEDWORK_WELCOME_WAIT; //欢迎
        break;
    }
    case eLEDWORK_WELCOME_WAIT:
    {
        if (pLED->u32LedWorkTimer != 0)
        {
            break;
        }
        if (ReportedData.u8PMSTestFlag == 1) //优先检查是否有PMS测试指令
        {
            pLED->eWorkMode = eLEDWORK_PMSTEST_CMDSTART;
            pLED->eRunMode = eLEDRUN_STANDBY;
            pLED->eLedID = eLED_INITIAL;
            ReportedData.u8PMSTestFlag = 0;
            break;
        }
        else
        {
            pLED->eWorkMode = eLEDWORK_AIRQUALITY_SHOW; //进入展示空气质量模式
        }

        //pLED->eWorkMode = eLEDWORK_AIRQUALITY_SHOW;
        break;
    }
    case eLEDWORK_AIRQUALITY_SHOW: //展示空气质量模式
    {

        if (ReportedData.u8PMSTestFlag == 1) //优先检查是否有PMS测试指令
        {
            pLED->eWorkMode = eLEDWORK_PMSTEST_CMDSTART;
            pLED->eRunMode = eLEDRUN_STANDBY;
            pLED->eLedID = eLED_INITIAL;
            ReportedData.u8PMSTestFlag = 0;
            break;
        }
        else if (SHT20.eFaultCode != eSHT20_NORMAL || CH2O_CO2.eCH2OFaultCode != eCH2O_NORMAL || CH2O_CO2.eCO2FaultCode != eCO2_NORMAL || PMSA.eFaultCode != ePMSA_NORMAL  )
        {
            FaultCode_LED();
            pLED->eWorkMode = eLEDWORK_AIRQUALITY_SHOWWAIT;
            pLED->u32LedWorkTimer = 5 * 1000; //5S
            break;            
        }
        else if (SHT20.eFaultCode == eSHT20_NORMAL || CH2O_CO2.eCH2OFaultCode == eCH2O_NORMAL || CH2O_CO2.eCO2FaultCode == eCO2_NORMAL || PMSA.eFaultCode == ePMSA_NORMAL  )
        {
            //仅当空气质量为差的时候展示报警效果，其它情况下，不再展示LED呼吸灯状态
            if (ReportedData.eAirQuality != eAIR_QUALITY_EXCELLENT)
            {
                AirQuality_LED();
            }
            pLED->eWorkMode = eLEDWORK_AIRQUALITY_SHOWWAIT;
            pLED->u32LedWorkTimer = 5 * 1000; //5S
            break;
        }
    }

    case eLEDWORK_AIRQUALITY_SHOWWAIT: //等待本次呼吸灯展示结束
    {
        if (ReportedData.u8PMSTestFlag == 1) //优先检查是否有PMS测试指令
        {
            pLED->eWorkMode = eLEDWORK_PMSTEST_CMDSTART;
            pLED->eRunMode = eLEDRUN_STANDBY;
            pLED->eLedID = eLED_INITIAL;
            ReportedData.u8PMSTestFlag = 0;
            break;
        }
        else
        {
            if (pLED->u32LedWorkTimer != 0)
            {
                break;
            }
            pLED->eWorkMode = eLEDWORK_AIRQUALITY_SHOW;
            break;
        }
    }

    case eLEDWORK_PMSTEST_CMDSTART: //PMS测试命令开始
    {

        LedRunMode_Blink(eLED_ALL, 100);            //呼吸1次
        pLED->u32LedWorkTimer = 10 * 1000;          //5S
        pLED->eWorkMode = eLEDWORK_PMSTEST_WAITEND; 
        break;
    }

    case eLEDWORK_PMSTEST_WAITEND: //等待PMS测试命令结束
    {
        if (pLED->u32LedWorkTimer != 0)
        {
            break;
        }
        LEDDark(eLED_ALL);
        pLED->eRunMode = eLEDRUN_STANDBY;
        pLED->eWorkMode = eLEDWORK_AIRQUALITY_SHOW;
        break;
    }
        /*
        case LedWork_SelfTestReady: //自检测试准备
        {
            LedRunMode_Breathe(eLED_ALL, 2); //呼吸1次
            pLED->eWorkMode = LedWork_SelfTesting;
            pLED->u32LedWorkTimer = 90 * 1000; //等待 90s
            break;
        }

        case LedWork_SelfTesting: //自检中...
        {
            if (pLED->u32LedWorkTimer != 0)
            {
                break;
            }
            pLED->eWorkMode = LedWork_SelfTestShowStart;
        }

        case LedWork_SelfTestShowStart: //开始展示硬件检测结果
        {
            pLED->u8SelfTestCount++;
            if (OK == SelfTestHandler())
            {
                LedRunMode_Light(pLED->eLedID, 1);
            }
            else
            {
                LedRunMode_Breathe(pLED->eLedID, 2); //呼吸1次
            }
            pLED->u32LedWorkTimer = 5 * 1000; //延时5S
            pLED->eWorkMode = LedWork_SelfTestShowing;
        }

        case LedWork_SelfTestShowing: //等待展示硬件检测结果执行结束
        {
            if (pLED->u32LedWorkTimer != 0)
            {
                break;
            }
            if (pLED->u8SelfTestCount > 7)
            {
                pLED->u8SelfTestCount = 0;
            }

            pLED->eWorkMode = LedWork_SelfTestShowStart;
            break;
        }
*/

    case eLEDWORK_SWITCH: //LED开关
    {

        if (Dev.Cfg.u8LedSwtichFalg == 1)
        {
            pLED->eWorkMode = eLEDWORK_SWITCH;
            LEDDark(eLED_ALL);
            break;
        }
        else
        {
            pLED->eWorkMode = eLEDWORK_STANDBY;
            LEDDark(eLED_ALL);
            break;
        }
        break;
    }

    default:
        pLED->eWorkMode = eLEDWORK_STANDBY;
        break;
    }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
