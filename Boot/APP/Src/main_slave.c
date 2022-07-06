
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
#include "BSP.h"
/* User App */
#include "Dataconfigure.h"

#include "main.h"
#include "LedAndButton.h"
#include "EnOceanFun.h"
#include "RS485Cascade.h"


/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

/*============================ GLOBAL VARIABLES ==============================*/ 
Timer_Flag_Typedef TimerFlag;
uint8_t u8ModbusPhyAdd;
uint8_t u8Parity;
uint8_t u8Stops;
uint8_t u8BaudID;
uint8_t  u8UpdatePort;
uint8_t u8CascadePhyAdd;
uint16_t u16CascadeOnlineMask;
uint8_t u8CascadeNums;

uint32_t u32EnOceanChipID;
uint32_t u32EnOceanBaseID;
uint8_t u8EnOceanRepeater;
uint32_t u32EnOceanRemanCode;
uint32_t u32EnOceanDstID;
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
void SystemTimeTick_100ms(void);

/* Private function prototypes -----------------------------------------------*/
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void RamInit(void)
{                     
    /*!!! Must attention !!!*/
    
    
}

/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void RPL4xInit(void)
{
    /* Must init after */
    RamInit();

    /* Must call RamInit() Before the NVM_LoadSettings() */

    
    
    RS485CascadeInit(&RS485Cascade);
#ifdef HW_DEBUG
    //LearnTabDebug();
#endif    
}
/**
  * @brief  The application entry point.
  * 
  * @retval None
  */
int main(void) 
{
    uint8_t u8DevCascadeAdd;
    /* Initialize all configured peripherals */
    /* MCU Configuration */

    uint8_t  u8UpdateSuccess;
    uint32_t u32UpgradeStatus;
    

    /* app code check ok */
    if ( OK == UpgradeModbus_GetStatus(&u32UpgradeStatus) )
    {
        UpgradeModbus_BootJumpToApp();
    }
    else
    {
        /* Configure the system clock */
        SystemClock_Config();

        //MX_RNG_Init();
        MX_GPIO_Init();
        /* Timer */
        MX_TIM3_Init();
        MX_TIM14_Init();
        /* OPWM */
        MX_TIM1_Init();
        MX_TIM16_Init();
        //BSP_TM16XXInterfaceInit();
        BSP_DMA_ChannelEnable();
        RPL4xInit();
        
        //SlaverSwitchReadAdd(&u8DevCascadeAdd);
        if ( u8DevCascadeAdd > CASCADE_DEV_ADD_MAX )
        {
            u8DevCascadeAdd = CASCADE_DEV_ADD_MAX;
        }


    
        UpgradeModbus_GetDefaultHardwareInfo(&u8ModbusPhyAdd, &u8BaudID, &u8Stops, &u8Parity,&u8UpdatePort,&u32EnOceanDstID);
        if ( APP_NEED_UPGRADE_UPDATING == u32UpgradeStatus )
        {
            if ( 0 == u8UpdatePort )
            {                
                //UpgradeModbusResetReply(RS485Modbus.Frame.pu8Send,u8ModbusPhyAdd,&RS485Modbus.Frame.u16SendBytesMax);
                //USART_StateSetSend(&RS485Modbus.Frame,RS485Modbus.Frame.u16SendBytesMax,0,500);
            }            
        }
    #ifndef HW_DEBUG
        MX_IWDG_Init();
    #endif    
        while (1)
        {
            IWDG_Reload();
            SystemTimeTick_10ms();
            SystemTimeTick_100ms();
            USART_CascadeHandler(&RS485Cascade);            
            LED_State();

            //if ( u8UpdateSuccess )
            {
                UpgradeModbus_WriteAppInfomationAndReset(u8ModbusPhyAdd, u8BaudID, u8Stops, u8Parity,u8UpdatePort);
            }    
        }
    }
    
    /* USER CODE END 3 */
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void SystemTimeTick_100ms(void)
{    
    //static uint8_t u8Timer_500ms;
    if ( TimerFlag.u8Timer_100ms )
    {
        TimerFlag.u8Timer_100ms = 0;

        USART_CascadeTime_100ms(&RS485Cascade);
        
    }
}
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void SystemTimeTick_10ms(void)
{     
    if ( TimerFlag.u8Timer_10ms )
    {

        LED_Time_10ms();

        TimerFlag.u8Timer_10ms = 0;
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
    USART_CascadeTime_1ms(&RS485Cascade);


    if ( TimerFlag.u32ms )
    {
        TimerFlag.u32ms--;
    }

    TimerFlag.u8Cnt_1ms++;
    if (TimerFlag.u8Cnt_1ms >= 10)
    {
        TimerFlag.u8Cnt_1ms = 0;

        TimerFlag.u8Timer_10ms = 1;
                    
        TimerFlag.u8Cnt_10ms++;
        if (TimerFlag.u8Cnt_10ms >= 10)
        {
            TimerFlag.u8Cnt_10ms = 0;

            TimerFlag.u8Timer_100ms = 1;

        }
    }
}
/**
  * @brief  Period elapsed callback in non blocking mode 
  * @param  htim : TIM handle
  * @retval None
  */
void TIM3_Interrupt_100us(void)
{    

#ifdef CASCADE_MASTER
    EnOceanTime_100us();
#endif

}


#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
    /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


