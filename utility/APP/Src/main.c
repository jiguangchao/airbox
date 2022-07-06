
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
/* User App */
#include "Dataconfigure.h"

#include "main.h"

//#include "stm32g0xx_ll_gpio.h"

#include "RS485Modbus.h"
#include "PMSA003.h"
#include "CH2O_CO2.h"
#include "Led.h"
#include "Key.h"

#include "HWTest.h"

#include "EnOceanCascade.h"
#include "EnOceanMSCCascade.h"

//#include "SysError.h"

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

/*============================ GLOBAL VARIABLES ==============================*/
Timer_Flag_Typedef TimerFlag;
/*============================ LOCAL VARIABLES ===============================*/

/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/

/* Private variables ---------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void RamInit(void);

/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void SystemTimeTick_1000ms(void);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void SystemTimeTick_100ms(void);

/* Private function prototypes -----------------------------------------------*/
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void RamInit(void)
{
    /* !!! Must attention !!!*/
    /* EnOcean reman function must be used the Dev.u32RemanCode */
    ResetDefaultData();

    //EnOceanHardware.u8DOMaxNums = 0;
    //EnOceanHardware.pu8Reapter = &Dev.Cfg.u8Repeater;
    //EnOceanHardware.pu32RemanCode = &Dev.Cfg.u32RemanCode;

    EnOceanRun.u16SendPeriod = 100; //RADIO_SEND_MIN_INTERVAl_DEFAULT;
    EnOceanRun.u8Lock = RM_UNLOCK;
    EnOceanRun.u16LockCount = RM_AUTO_LOCK_TIME;
    EnOceanInit();

    Dev.u16HWVersion = AIRBOX_HW_VERSION;
    Dev.u16FWVersion = AIRBOX_FW_VERSION;

    //Key.pDev                      = &Dev;
    /* Init the ram var ,then read from the NVM area */
    
}
/**
  * @brief
  * @param
  * @retval None
  */
void RS485_GetConfigParameter(void)
{
    /* Modbus */
    RS485Modbus.Frame.pu8PhyAddress = &Dev.Cfg.u8ModbusPhyAdd;
    RS485Modbus.Frame.eParity = Dev.Cfg.eParity;
    RS485Modbus.Frame.eBaudID = Dev.Cfg.eBaudRateID;
    RS485Modbus.Frame.eStop = Dev.Cfg.eStops;
}
/**
  * @brief  initial value
  * @param
  * @retval None
  */
void RS485_InitialValue(void)
{
    /* Modbus */
    RS485Modbus.Frame.pu8PhyAddress = &Dev.Cfg.u8ModbusPhyAdd;
    RS485Modbus.Frame.eParity = ePARITY_NONE;
    RS485Modbus.Frame.eBaudID = eBAUD_9600_ID;
    RS485Modbus.Frame.eStop = eSTOP_1;
}
/**
  * @brief
  * @param
  * @retval None
  */
void PMSA_InitialValue(void)
{
    /* Modbus */
    PMSA_UART.Frame.pu8PhyAddress           = NULL;
    PMSA_UART.Frame.eParity = ePARITY_NONE;
    PMSA_UART.Frame.eBaudID = eBAUD_9600_ID;
    PMSA_UART.Frame.eStop   = eSTOP_1;
}
/**
  * @brief
  * @param
  * @retval None
  */
void CH2O_CO2_InitialValue(void)
{
    /* Modbus */
    CH2O_CO2_UART.Frame.pu8PhyAddress           = NULL;
    CH2O_CO2_UART.Frame.eParity = ePARITY_NONE;
    CH2O_CO2_UART.Frame.eBaudID = eBAUD_9600_ID;
    CH2O_CO2_UART.Frame.eStop = eSTOP_1;
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void AirBoxInit(void)
{

    /* Must init after */
    /* Must call RamInit() Before the NVM_LoadSettings() */
    RamInit();
    BuildComplierDateTime(&Dev.u32BuildYYMMDD, &Dev.u32BuildHHMMSS);

    /* Load EEPROM config the Enocean,rs485 usart parameter */
    //NVM_LoadSettings();
    RS485_InitialValue();
    PMSA_InitialValue();
    CH2O_CO2_InitialValue();
    /* Init must be after the read NVM, Because the remancode and repeater setting save the NVM */

    BSP_DMA_ChannelEnable();

   
    PMSAInit(&PMSA_UART);
    CH2O_CO2Init(&CH2O_CO2_UART);
    SHT20_InterfaceInit();

    HardwareSelfTest(&HWTest);
    
    Dev.Log.u32PowerOnCount++;
    Dev.u8EraseFlag = 1;
    FLASH_ReadWrite_LOG();
    FLASH_Write_FactorySettings();
    
    RS485_GetConfigParameter();
    RS485ModbusInit(&RS485Modbus);

    EnOceanModuleInit();
    EnOceanGetHWChipID(&Dev.Cfg.u32EnOceanChipID);
    EnOceanGetHWBaseID(&Dev.Cfg.u32EnOceanBaseID);
    
    //RS485_GetConfigParameter();
    //RS485ModbusInit(&RS485Modbus);

#ifdef HW_DEBUG
    //LearnTabDebug();
#endif
}

uint16_t TimeCountTest;

#if 0
uint8_t LedFlag;
uint32_t u32LEDTime;

int main(void)
{
    //SCB->VTOR = FLASH_BASE | 0x00006000; /* Vector Table Relocation in Internal FLASH */
    SystemClock_Config();
    GPIO_Light_Init_Test();
    MX_TIM_Init();
    
   __enable_irq(); //打开全局中断

    
    LedFlag = 1;
    while (1)
    {
        SystemTimeTick_10ms();
        SystemTimeTick_100ms();
        SystemTimeTick_1000ms();

        switch (LedFlag)
        {
        case 1:
            LL_GPIO_SetOutputPin(LED_RED_GPIO, LED_RED_PIN);
            LL_GPIO_SetOutputPin(LED_GREEN_GPIO, LED_GREEN_PIN);
            LL_GPIO_SetOutputPin(LED_ORG_GPIO, LED_ORG_PIN);
            LL_GPIO_SetOutputPin(LED_YELLOW_GPIO, LED_YELLOW_PIN);                  

            u32LEDTime = 50;
            LedFlag = 2;
            break;

        case 2:
            if (u32LEDTime != 0)
            {
                break;
            }
            LedFlag = 3;
            break;

        case 3:
            LL_GPIO_ResetOutputPin(LED_RED_GPIO, LED_RED_PIN);
            LL_GPIO_ResetOutputPin(LED_GREEN_GPIO, LED_GREEN_PIN);
            LL_GPIO_ResetOutputPin(LED_ORG_GPIO, LED_ORG_PIN);
            LL_GPIO_ResetOutputPin(LED_YELLOW_GPIO, LED_YELLOW_PIN); 
            
            u32LEDTime = 50;
            LedFlag = 4;
            break;
        case 4:
            if (u32LEDTime != 0)
            {
                break;
            }
            LedFlag = 1;
            break;

        default:
            break;
        }
    }
    
}
#endif

//#if 0
int main(void)
{
    SCB->VTOR = APP_ADDRESS_START; /* Vector Table Relocation in Internal FLASH */
    __ASM("CPSIE  I");  //关闭全局中断
 
    /* Initialize all configured peripherals */
    /* MCU Configuration */
    /* Configure the system clock */
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_TIM_Init();
    
    
    /* Timer */
    // FLASH_Remove_Page(FLASH_CFG_ADD);
    // FLASH_Remove_Page(FLASH_LOG_ADD);
    // FLASH_Remove_Page(FLASH_FACTORY_SET);

    AirBoxInit();

    __enable_irq(); //打开全局中断

    SwitchReadPinStatus(&Dev.Cfg.u8ModbusPhyAdd);

#ifndef HW_DEBUG
    MX_IWDG_Init();
#endif

    while (1)
    {

#ifndef HW_DEBUG
        IWDG_Reload(); //喂狗
#endif

        FLASH_Write_Cfg();
        FLASH_Write_Log();

        KeyEvent_Scanning(&KEY);
        LED_runmode(&LED);
        LED_workmode(&LED);

        SystemTimeTick_10ms();
        SystemTimeTick_100ms();
        SystemTimeTick_1000ms();
        
        USART_StateMachineHandler(&RS485Modbus);
        USART_StateMachineHandler(&CH2O_CO2_UART);
        USART_StateMachineHandler(&PMSA_UART);
        
        EnOceanHandler(Dev.Cfg.u8RadioInterval);
        EnOceanProactiveReporting(&ReportedData);
        EnOceanDifferenceReport(&ReportedData);
        
        CH2O_CO2_OperationTask(&CH2O_CO2, (18 * 1000)); //周期必须大于1分钟
        SHT20_OperationTask(&SHT20, (10 * 1000)); //10S
        PMSA_OperationTask(&PMSA, (30 * 1000), (30 * 1000));
        

    }
    /* USER CODE END 3 */
}
//#endif
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void SystemWait(uint32_t u32WaitSet)
{
    TimerFlag.u32ms = u32WaitSet;
    while (TimerFlag.u32ms)
    {
        Nop_Delay(1);
    }
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */

void SystemTimeTick_1000ms(void)
{
    //TimeCountTest++;

    if (1 == TimerFlag.u8Timer_1s)
    {
        TimerFlag.u8Timer_1s = 0;
        FLASH_DevRunSave();
    }
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void SystemTimeTick_100ms(void)
{
    if (TimerFlag.u8Timer_100ms)
    {
        TimerFlag.u8Timer_100ms = 0;

        EnOceanTime_100ms();

        if (Dev.u8LearnSuccessTime)
        {
            Dev.u8LearnSuccessTime--;
        }

        if (Dev.u8LearnAutoSendEEPTime)
        {
            Dev.u8LearnAutoSendEEPTime--;
        }
    }
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void SystemTimeTick_10ms(void)
{
    if (TimerFlag.u8Timer_10ms)
    {
        TimerFlag.u8Timer_10ms = 0;
        /*   
        if (u32LEDTime)
        {
            u32LEDTime--;
        } 
        */
        //LED_Time_10ms();
    }
}

/* USER CODE BEGIN 4 */
/**
  * @brief  Period elapsed callback in non blocking mode 
  * @param  htim : TIM handle
  * @retval None
  */
void TIM14_Interrupt_1ms(void)
{
    USART_Time_1ms(&RS485Modbus);
    USART_Time_1ms(&PMSA_UART);
    USART_Time_1ms(&CH2O_CO2_UART);

    CH2O_CO2_Tick1ms(&CH2O_CO2);
    PMSA_Tick1ms(&PMSA);
    Enocean_Tick1ms(&ReportedData);
    LED_Tick1ms(&LED);
    Key_Tick1ms(&KEY);

    HardwareSelfTest_Tick1ms(&HWTest);

    EnOceanTime_1ms();

    SHT20_Tick10ms(&SHT20);

    if (TimerFlag.u32ms)
    {
        TimerFlag.u32ms--;
    }

    TimerFlag.u8Cnt_1ms++;
    if (TimerFlag.u8Cnt_1ms >= 10)
    {
        TimerFlag.u8Cnt_1ms = 0;

        TimerFlag.u8Timer_10ms = 1;

        //SystemTimeTick_10ms();

        TimerFlag.u8Cnt_10ms++;
        if (TimerFlag.u8Cnt_10ms >= 10)
        {
            TimerFlag.u8Cnt_10ms = 0;

            TimerFlag.u8Timer_100ms = 1;

            TimerFlag.u8Cnt_100ms++;

            if (TimerFlag.u8Cnt_100ms >= 10)
            {
                TimerFlag.u8Cnt_100ms = 0;
                TimerFlag.u8Timer_1s = 1;
            }
        }
    }
}
/**
  * @brief  Period elapsed callback in non blocking mode 
  * @param  htim : TIM handle
  * @retval None
  */
void TIM6_Interrupt_100us(void)
{
    TimerFlag.u8Timer_100us = 1;

    EnOceanTime_100us();

    SHT20_Tick100us(&SHT20);
}


#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
/**
  * @brief  The application entry point.
  * 
  * @retval None
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
