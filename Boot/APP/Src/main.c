
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

#include "RS485Modbus.h"
#include "RS485Cascade.h"
#include "EnOceanFun.h"

#include "LedAndButton.h"




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
void SystemTimeTick_100ms(void);

/* Private function prototypes -----------------------------------------------*/
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
uint32_t u32ResetDstID;
uint16_t u16EnOceanSendLastWaitTime;
/**
  * @brief
  * @param
  * @retval None
  */
void RS485_GetConfigParameter(void)
{
    /* Modbus */
    u8Parity                           = 0;
    u8BaudID                           = 3;
    u8Stops                            = 0;
    u8ModbusPhyAdd                     = 1;
    RS485Modbus.Frame.pu8PhyAddress    = &u8ModbusPhyAdd;
    RS485Modbus.Frame.u8Parity         = u8Parity;
    RS485Modbus.Frame.u8BaudID         = u8BaudID;
    RS485Modbus.Frame.u8Stop           = u8Stops;


}
/**
  * @brief  The application entry point.
  * 
  * @retval None
  */
int main(void)
{   
    
    //uint8_t  u8UpdateSuccess;
    uint32_t u32UpgradeStatus;
    
    //UpgradeModbus_BootJumpToApp();
        
    /* app code check ok */
    if ( OK == UpgradeModbus_GetStatus(&u32UpgradeStatus) )
    {
        UpgradeModbus_BootJumpToApp();
    }
    else
    {   
        //__ASM("CPSID  I");
        HAL_Init();
        /* Initialize all configured peripherals */
        /* MCU Configuration */
        /* Configure the system clock */
        SystemClock_Config();    

        //MX_RNG_Init();
        MX_GPIO_Init();
        
        /* Timer */
        //MX_TIM3_Init();
        MX_TIM14_Init();
        
        //BSP_TM16XXInterfaceInit();

        RS485_GetConfigParameter();    
        /* Init must be after the read NVM, Because the remancode and repeater setting save the NVM */
        BSP_DMA_ChannelEnable();
        /*
        EnOceanModuleInit();
        EnOceanGetHWChipID ( &u32EnOceanChipID );
        EnOceanGetHWBaseID ( &u32EnOceanBaseID );
        */          
        UpgradeModbus_GetDefaultHardwareInfo(&u8ModbusPhyAdd, &u8BaudID, &u8Stops, &u8Parity,&u8UpdatePort,&u32ResetDstID);
        RS485ModbusInit(&RS485Modbus);    
        if ( APP_NEED_UPGRADE_UPDATING == u32UpgradeStatus )
        {
            if ( 0 == u8UpdatePort )
            {                
                UpgradeModbusResetReply(RS485Modbus.Frame.pu8Send,u8ModbusPhyAdd,&RS485Modbus.Frame.u16SendBytesMax);
                USART_StateSetSend(&RS485Modbus.Frame,RS485Modbus.Frame.u16SendBytesMax,0,500);
            }
            /*
            else if ( 1 == u8UpdatePort )
            {                
                UpgradeModbusResetReply(RS485Modbus.Frame.pu8Send,u8ModbusPhyAdd,&RS485Modbus.Frame.u16SendBytesMax);
                EnOceanRemanResetReply(RS485Modbus.Frame.pu8Send,&Radio,u32ResetDstID);
            }
            */         
        }

    #ifndef HW_DEBUG
        MX_IWDG_Init();
    #endif

        while (1)
        {
     #ifndef HW_DEBUG      
            IWDG_Reload();
     #endif   
            SystemTimeTick_10ms();
            SystemTimeTick_100ms();
        
            if ( OK == USART_StateMachineHandler(&RS485Modbus) )
            {
                u16EnOceanSendLastWaitTime = 1000;
            }

            //EnOceanHandler(100);
            LED_State();
            
            if ( 0 == u16EnOceanSendLastWaitTime ) 
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
    if ( TimerFlag.u8Timer_100ms )
    {
        TimerFlag.u8Timer_100ms = 0;

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
        TimerFlag.u8Timer_10ms = 0;

        LED_Time_10ms();        
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

    EnOceanTime_1ms();
    
    
    if (u16EnOceanSendLastWaitTime)
    {
        u16EnOceanSendLastWaitTime--;
    }
    
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
void TIM3_Interrupt_100us(void)
{    
    TimerFlag.u8Timer_100us = 1;
    EnOceanTime_100us();    
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
