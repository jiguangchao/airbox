#ifndef _COMMON_H_
#define _COMMON_H_


#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <intrinsics.h>

#ifdef CASCADE_MASTER
    #define ESP3_RX_BUF_MAX                                        (180)
    #define ESP3_TX_BUF_MAX                                        (180)
    #define RADIO_BUFF_LENGTH                                      (180)
    #define ESP3_RX_QUEUE                                          (8)
    #define ESP3_TX_QUEUE                                          (10)
    #define LRN_TAB_CHANNEL_MAX                                    (10)
/*
    #define RS485_MODBUS_TX_BUFF                                   (255)
    #define RS485_MODBUS_RX_BUFF                                   (255)

    #define RS485_EXPAND_TX_BUFF                                   (128)
    #define RS485_EXPAND_RX_BUFF                                   (128)
*/
    #define CASCADE_TX_QUEUE_MAX                                   (0)
    
#else
    #define ESP3_RX_BUF_MAX                                        (1)
    #define ESP3_TX_BUF_MAX                                        (128)
    #define RADIO_BUFF_LENGTH                                      (80)
    #define ESP3_RX_QUEUE                                          (1)
    #define ESP3_TX_QUEUE                                          (20)
    #define LRN_TAB_CHANNEL_MAX                                    (4)     
    #define CASCADE_TX_QUEUE_MAX                                   (5)
#endif

#define CASCADE_BUFF_MAX                                              (128)
//#define CASCADE_MASTER_BUFF_MAX                                       (128)
//#define CASCADE_SLAVER_BUFF_MAX                                       (80)
/* 1ms unit */
#define ENOCEAN_SEND_INTERVAl_DEFAULT                                 (100)

#define RS485_MODBUS_TX_BUFF (256)
#define RS485_MODBUS_RX_BUFF (256)

/****************************************************************************/
#define CLOVER_TOUCH_EEP                                   (0xF60201)
#define CLOVER_RELAY_EEP                                   (0xD20115)
#define CLOVER_GATEWAY_EEP                                 (0xD1010A)
#define CLOVER_LIGHT_EEP                                   (0xD1010B)
#define RPL4X_EEP                                          (0xD1010D)
#define ACTIVE_IR_EEP                                      (0xD1010E)
/* the learn dev eep is used to other sensor device like: ptm210(RPS),4bs,1bs */
#define LEARN_LIGHT_EEP                                    (RPL4X_EEP)
#define LEARN_AIR_CONDITION_EEP                            (0xD10106)
#define LEARN_FLOOR_HEATING_EEP                            (0xD10107) 
#define LEARN_VENTILATION_EEP                              (0xD10108)
#define LEARN_ROOM_EEP                                     (0xD10109)
//#define LEARN_CLOVER_EEP                                   (0xD1FF01)

#define LEARN_COLOR_EEP                                    (0xD1010C)


#define AIRBOX_1_EEP                                       (0xD10104)
/****************************************************************************/
#define OVF_UINT32_VALUE                                   (0xFFFFFFFF)
#define OVF_UINT16_VALUE                                   (0xFFFF)
#define OVF_UINT8_VALUE                                    (0xFF)
/****************************************************************************/


/*********************************************************************************/
/* All temperature need to /10 */
#define TEMPERATURE_PRECISION                              (5)
#define TEMPERATURE_OFFSET                                 (200)
#define TEMPERATURE_OFFSET_RANGE_MAX                       (TEMPERATURE_OFFSET + 95)//  9.5
#define TEMPERATURE_OFFSET_RANGE_MIN                       (TEMPERATURE_OFFSET - 95)// -9.5

#define TEMPERATURE_SET_TOP                                (350+TEMPERATURE_OFFSET)
#define TEMPERATURE_SET_BOTTOM                             (50+TEMPERATURE_OFFSET)

#define TEMPERATURE_DEAD_DEFAULT                           (10)
#define TEMPERATURE_DEAD_DEFAULT_MAX                       (100)
#define TEMPERATURE_DEAD_DEFAULT_MIN                       (TEMPERATURE_PRECISION)

#define TEMPERATURE_AIR_CONDITION_SET_DEFAULT              (250+TEMPERATURE_OFFSET)
#define TEMPERATURE_FLOOR_HEATING_SET_DEFAULT              (200+TEMPERATURE_OFFSET)

#define HUMIDUTY_OFFSET                                    (20)
#define CO2_OFFSET                                         (500)
#define VOC_OFFSET                                         (500)

#define MODBUS_PHY_ADDRESS_DEFAULT                         (1)
#define MODBUS_PHY_ADDRESS_MAX                             (31)
#define MODBUS_PHY_ADDRESS_MIN                             (1)
   
#define REMOTE_UPDATE_SENSOR_TIME                          (180)
#define AIR_CONDITION_FAN_SPEED_DELAY_MAX                  (900)
/*********************************************************************************/
typedef enum
{
    eBAUD_1200_ID = 0,
    eBAUD_2400_ID, 
    eBAUD_4800_ID, 
    eBAUD_9600_ID, 
    eBAUD_19200_ID,
    eBAUD_38400_ID,
    eBAUD_57600_ID,
    eBAUD_115200_ID,
}eUSART_BAUD_ID_TYPE;

typedef enum
{
    eBAUD_1200 = 1200,
    eBAUD_2400 = 2400,
    eBAUD_4800 = 4800,
    eBAUD_9600 = 9600,
    eBAUD_19200 = 19200,
    eBAUD_38400 = 38400,
    eBAUD_57600 = 57600,
    eBAUD_115200 = 115200,
}eUSART_BAUD_TYPE;

typedef enum
{
    eSTOP_1 = 0,
    eSTOP_2 = 1,
}eUSART_STOP_TYPE;

typedef enum
{
    ePARITY_NONE = 0,
    ePARITY_EVEN ,
    ePARITY_ODD ,
}eUSART_PARITY_TYPE;

typedef enum
{
    eMODBUS_OK = 0,
    eMODBUS_OK_NO_REPLY_ENOCEAN = 1,

    eMODBUS_CMD_ERR,    
    eMODBUS_READ_REG_NUMS_ERR = 17,
    eMODBUS_READ_INPUT_REG_ID_ERR = 18,
    eMODBUS_READ_HOLD_REG_ID_ERR = 19,
    eMODBUS_WRITE_ONE_HOLD_ID_ERR = 20,
    eMODBUS_WRITE_ONE_HOLD_VALUE_ERR = 21,
}eMODBUS_ERROR_TYPE;
/*********************************************************************************/
typedef enum
{
    eDEAD_TIME_5S = 5,
    eDEAD_TIME_10S = 10,
    eDEAD_TIME_20S = 20,
    eDEAD_TIME_30S = 30,
    eDEAD_TIME_40S = 40,
    eDEAD_TIME_50S = 50,
    eDEAD_TIME_60S = 60,
    eDEAD_TIME_90S = 90,
    eDEAD_TIME_120S = 120,
    eDEAD_TIME_150S = 150,
    eDEAD_TIME_180S = 180,
    eDEAD_TIME_240S = 240,
    eDEAD_TIME_300S = 300,
    eDEAD_TIME_360S = 360,
    eDEAD_TIME_600S = 600,
}eDEAD_TIME_TYPE;

typedef enum
{
    eSTATE_OFF = 0,
    eSTATE_ON,
}eON_OFF_STATE_TYPE;

typedef enum
{
    eFUNCTION_DISABLE = 0,
    eFUNCTION_ENABLE,
}eFUNCTION_TYPE;

typedef enum
{
    eAIR_CONDITION_MODE_AUTO = 0,
    eAIR_CONDITION_MODE_COOL ,
    eAIR_CONDITION_MODE_HEAT ,
    eAIR_CONDITION_MODE_FAN ,
    eAIR_CONDITION_MODE_DEHUMI,
    eAIR_CONDITION_MODE_FLOOR_HEAT,
    //eAIR_CONDITION_MODE_ALL_HEAT,

}eAIR_CONDITION_MODE_TYPE;

typedef enum
{
    eFAN_SET_AUTO = 0,
    eFAN_SET_LOW ,
    eFAN_SET_MEDIUM ,
    eFAN_SET_HIGH ,

}eFAN_SET_TYPE;

typedef enum
{
    eFAN_SPEED_OFF = 0,
    eFAN_SPEED_LOW ,
    eFAN_SPEED_MEDIUM ,
    eFAN_SPEED_HIGH ,
}eFAN_SPEED_TYPE;

typedef enum
{
    eAC_COOL_HEAT_FAN_MODE = 0,
    eAC_COOL_FAN_MODE ,
    eAC_COOL_HEAT_MODE ,  
    eAC_COOL_HEAT_FAN_FLOORHEAT_MODE,
    eAC_COOL_HEAT_NO_FAN_MODE,
    eAC_COOL_HEAT_FAN_DEHUMI_MODE,
    eAC_COOL_HEAT_FAN_DEHUMI_AUTO_MODE,
    
}eAC_MODE_TYPE;

typedef enum
{
    eFAN_AUTO_SPEED_TEMP_OFFSET_2_0 = 20,
    eFAN_AUTO_SPEED_TEMP_OFFSET_1_0 = 10,
}eFAN_AUTO_OFFSET_TYPE;

typedef enum
{
    eLOCK_LEVEL_NO = 0,
    eLOCK_LEVEL_1,
    eLOCK_LEVEL_2,
}eLOCK_LEVEL_TYPE;
/*
typedef enum
{
    eHEATING_OPTION_FH_DISABLE = 0,    
    eHEATING_OPTION_FH_ENABLE,
    

}eHEATING_OPTION_TYPE;
*/
typedef enum
{
    ePOWER_ON_STATE_NVM = 0,
    ePOWER_ON_OFF,
    ePOWER_ON_ON,    

}ePOWER_ON_TYPE;

typedef enum
{
    /* fan speed type: auto ,high ,medium, low */
    eAC_A_H_M_L_FAN = 0,
    /* fan speed type: auto ,high , low */
    eAC_A_H_L_FAN,
    /* fan speed type: ,high ,medium, low */
    eAC_H_M_L_FAN,
    /* fan speed type: high , low */
    eAC_H_L_FAN,
    /* fan speed type: high  */
    eAC_H_FAN,
}eFAN_SPEED_SELECT_TYPE;



#endif
