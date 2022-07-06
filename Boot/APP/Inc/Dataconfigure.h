

#ifndef _DATA_CONFIGURE_H_
#define _DATA_CONFIGURE_H_

#include "platform.h"
#include "BaselibInclude.h"
#include "EnOceanlibInclude.h"



/**********************************************************************************************************************/
#define RPL4M_HW_VERSION                                                (0x0010)
#define RPL4M_FW_VERSION                                                (0x001A)
//V12 dimming dali and triac control color bug

#define RPL4R_HW_VERSION                                                (0x0010)
#define RPL4R_FW_VERSION                                                (0x0016)
#define RPL4X_CASCADE_VERSION                                           (0x0010)
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
#define NVM_DEV_CFG_ADDRESS                                             (0x0000)
#define NVM_DEV_CFG_OFFSET_BASE                                         (0x0080)

#define NVM_HARDWARE_INFO_ADDRESS                                       (0x0100)
#define NVM_HARDWARE_INFO_OFFSET_BASE                                   (0x0180)

#define NVM_DEV_EXPAND_CFG_ADDRESS                                      (0x0200)
#define NVM_DEV_EXPAND_CFG_OFFSET_BASE                                  (0x0300)
/* 0x400 -- 0xFFF for resever */

#define NVM_IO_PROFILE_BASE                                             (0x1000)//64 * 64 = 4096
#define NVM_IO_PROFILE_SIZE                                             (64)//64 * 64 = 4096
#define NVM_IO_PROFILE_OFFSET_BASE                                      (0x2000)//64 * 64 = 4096

#define NVM_IO_STATUS_BASE                                              (0x3000)
#define NVM_IO_STATUS_SIZE                                              (64)
#define NVM_IO_STATUS_OFFSET_BASE                                       (0x4000)

#define NVM_LRN_TAB_ADDRESS                                             (0x5000)//
#define NVM_LRN_TAB_ADDRESS_OFFSET                                      (0x1000)//

/**********************************************************************************************************************/
/**********************************************************************************************************************/
#ifdef CASCADE_MASTER
    #define TRIAC_OUT_NUMS                                              (8)
    #define DALI_OUT_NUMS                                               (16)
    #define RELAY_OUT_NUMS                                              (4)
    #define V0_10V_OUT_NUMS                                             (0) 

    #define LIGHT_DIMMING_CHL_BUFF_START                                    (4)
    #define LIGHT_DIMMING_CHL_BUFF_END                                      (27)

    #define LIGHT_DALI_CHL_BUFF_START                                       (4)
    #define LIGHT_DALI_CHL_BUFF_END                                         (19)

    #define LIGHT_TRIAC_CHL_BUFF_START                                      (20)
    #define LIGHT_TRIAC_CHL_BUFF_END                                        (27)
    
#else
    #define TRIAC_OUT_NUMS                                              (0)
    #define DALI_OUT_NUMS                                               (0)
    #define RELAY_OUT_NUMS                                              (4)
    #define V0_10V_OUT_NUMS                                             (0)   
#endif

#define LIGHT_SELF_RELAY_CHL_START                                      (0)
#define LIGHT_SELF_RELAY_CHL_END                                        (3)
#define LIGHT_CASCADE_RELAY_CHL_START                                   (4)
#define LIGHT_CASCADE_RELAY_CHL_END                                     (39)
#define LIGHT_DIMMING_CHL_START                                         (40)
#define LIGHT_DIMMING_CHL_END                                           (63)



#define LIGHT_CHANNEL_NUMS                                              (RELAY_OUT_NUMS + DALI_OUT_NUMS + TRIAC_OUT_NUMS + V0_10V_OUT_NUMS)
#define DIMMING_CHANNEL_NUMS                                            (DALI_OUT_NUMS + TRIAC_OUT_NUMS + V0_10V_OUT_NUMS)
#define LIGHT_CASCADE_NUMS_MAX                                          (10)
#define CASCADE_DEV_ADD_MAX                                             (LIGHT_CASCADE_NUMS_MAX-1)


#define EXPAND_PANEL_NUMS_MAX                                           (16)
#define EXPAND_PANEL_BUTTON_MAX_NUMS                                    (6)
#define SLAVE_RELAY_NUMS                                                (4*LIGHT_CASCADE_NUMS_MAX)
#define SLAVE_DI_MAX                                                    (4)


#define EEP_CASCADE_BASEID_START                                        (0x00)
#define EEP_CASCADE_BASEID_END                                          (0x09)
#define EEP_DIMMING_BASEID_START                                        (0x10)
#define EEP_DIMMING_BASEID_END                                          (0x1B)

#define EEP_DALI_BASEID_START                                           (0x10)
#define EEP_DALI_BASEID_END                                             (0x17)

#define EEP_TRIAC_BASEID_START                                          (0x18)
#define EEP_TRIAC_BASEID_END                                            (0x1B)

#define EEP_DI_BASEID_START                                             (0x1C)
#define EEP_DI_BASEID_END                                               (0x3F)
#define EEP_EXPAND_PANEL_BASEID_START                                   (0x40)
#define EEP_EXPAND_PANEL_BASEID_END                                     (0x7F)
/* !!!! Must attention !!!!*/
/* Relay Coil time */
/* Can't modify it */
#define HF3FL_COIL_ON_DELAY_DEFAULT                                     (5) 
#define HF3FL_COIL_OFF_DELAY_DEFAULT                                    (3)
/**********************************************************************************************************************/
/**********************************************************************************************************************/
#define LIGHT_RAND_SEND_BASE_TIME                                       (600000)
#define LIGHT_RAND_SEND_VAR_TIME                                        (300000)
/**********************************************************************************************************************/
/**********************************************************************************************************************/
#define RELAY_OFF_TO_ON_PROTECT_TIME_DEFAULT                            (5)// On delay 0.5S

/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/* Modbus register and enocean msc regisiter segment */
/* Use Chip ID */
/* EEP: D201XX channel is from 0 to 30 */
/* Use Chip ID */
/* Modbus register and enocean msc regisiter segment */
/* Use Chip ID */
/*******************************************************************************************/
/* Channel range description */
/*
1. 0 is the dev channel
2. 1--4 is the relay channel of controller with 4channel
3. 5 -- 30, and 0x70 -- 0x79 is the cascade slaver relay channel
4. 0x7A -- 0x8D is the dimming channel triac or dali
*/
#define DEV_CHANNEL                                                 (0x00)
#define LIGHT_CHANNEL_RELAY_START                                   (0x01)// light channel 1
#define LIGHT_CHANNEL_RELAY_END                                     (0x04)// light channel 4

#define LIGHT_CHANNEL_CASCADE_START                                 (0x05)// light channel 5
#define LIGHT_CHANNEL_CASCADE_END                                   (0x28)// light channel 40

#define LIGHT_CHANNEL_DIMMING_START                                 (0x29)// light channel 41
#define LIGHT_CHANNEL_DIMMING_END                                   (0x40)// light channel 63

/* Every the DALI's devices have the 64Bytes data for light infomation */
#define LIGHT_DALI_CONFIG_START                                     (0x90)// DALI short address 0 -- 63
#define LIGHT_DALI_CONFIG_END                                       (0x9F)// 

#define EXPANDE_PANEL_CONFIG_START                                  (0xA0)
#define EXPANDE_PANEL_CONFIG_END                                    (0xAF)

#define SLAVER_DEV_INFO_START                                       (0xF1)
#define SLAVER_DEV_INFO_END                                         (0xFF)

/* EEP: D201XX channel is from 0 to 30 */
/* Use Chip ID */
/* 30 Channels like the EEP */                                                                            
#define MODBUS_LIGHT_RELAY_START                                    (0x0100)// 0x01 00 -- 0x00 FF
#define MODBUS_LIGHT_RELAY_END                                      (0x04FF)// 0x1D 00 -- 0x00 FF

#define MODBUS_LIGHT_CASCADE_START                                  (0x0500)// 0x01 00 -- 0x00 FF
#define MODBUS_LIGHT_CASCADE_END                                    (0x28FF)// 0x29 00 -- 0x00 FF

#define MODBUS_LIGHT_DIMMING_START                                  (0x2900)// 0x7A 00 -- 0x00 FF
#define MODBUS_LIGHT_DIMMING_END                                    (0x40FF)// 0x8D 00 -- 0x00 FF

#define MODBUS_LIGHT_DALI_CONFIG_START                              (0x9000)// DALI short address 0 -- 63
#define MODBUS_LIGHT_DALI_CONFIG_END                                (0x9FFF)// 

#define MODBUS_EXPANDE_PANEL_CONFIG_START                           (0xA000)
#define MODBUS_EXPANDE_PANEL_CONFIG_END                             (0xAFFF)
/* resever segment */
#define MODBUS_MASTER_DEV_INFO_START                                (0xF000)
#define MODBUS_MASTER_DEV_INFO_END                                  (0xF0FF)

#define MODBUS_SLAVER_DEV_INFO_START                                (0xF100)
#define MODBUS_SLAVER_DEV_INFO_END                                  (0xFFFF)
/* Use base ID resever 0x20 -- 0x6F for HVAC and Rock */
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/**********************************************************************************************************************/
#define MODBUS_MAX_REG_NUMS                                         (255)


/* Use modbus reg resever 0x2000 -- 0x6FFF for HVAC and Rock */
#if 0
/**********************************************************************************************************************/
/********************* Data reg permission mask *******************************************/
/**********************************************************************************************************************/
#define REG_PERMISSION_N                                            (0x00)
#define REG_PERMISSION_X                                            (0x04)
#define REG_PERMISSION_R                                            (0x02)
#define REG_PERMISSION_W                                            (0x01)
#define REG_VALUE_RANGE_ENABLE                                      (1)
#define REG_VALUE_RANGE_DISABLE                                     (0)
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/* 0 -- 255 dev have max 256 parameter */

//#define MB_INPUT_BASE                                               (0x00)
#define MB_HOLD_BASE                                                (0x00)

/* dev read */
/* dev run can only read */
#define MB_INPUT_HW_VERSION                                         (0x00)

#define MB_INPUT_FW_VERSION                                         (0x01)
#define MB_INPUT_FW_DATE                                            (0x02)
#define MB_INPUT_FW_DATE_H                                          (0x02)
#define MB_INPUT_FW_DATE_L                                          (0x03)
#define MB_INPUT_FW_TIME                                            (0x04)
#define MB_INPUT_FW_TIME_H                                          (0x04)
#define MB_INPUT_FW_TIME_L                                          (0x05)

#ifdef CASCADE_MASTER
    #define MB_INPUT_SUPPORT_MASK                                       (0x0C)
    #define HW_SUPPORT_DALI_GATEWAY_MASK                                (0x0001)  
    #define HW_SUPPORT_DALI_INTERFACE_MASK                              (0x0002)  
    #define HW_SUPPORT_DALI_TRIAC_MASK                                  (0x0004)
    #define HW_SUPPORT_0_10V_MASK                                       (0x0008)
    #define HW_SUPPORT_ENABLE_MASK                                      (HW_SUPPORT_DALI_GATEWAY_MASK|HW_SUPPORT_DALI_TRIAC_MASK)

    #define MB_INPUT_ENOCEAN_CHIPID_H                                   (0x0D)
    #define MB_INPUT_ENOCEAN_CHIPID_L                                   (0x0E)

    #define MB_INPUT_ERROR                                              (0x10)
    #define MB_INPUT_ERROR_H                                            (0x10)
    #define MB_INPUT_ERROR_L                                            (0x11)
    #define MB_INPUT_RUN_TIME                                           (0x12)
    #define MB_INPUT_RUN_TIME_H                                         (0x12)
    #define MB_INPUT_RUN_TIME_L                                         (0x13)
    #define MB_INPUT_ENOCEAN_RSSI                                       (0x14)
    #define MB_INPUT_POWER_ON_CNT                                       (0x15)
    
    #define MB_INPUT_FAULT_CNT                                          (0x17)
    #define MB_INPUT_ENOCEAN_BASEID                                     (0x18)
    #define MB_INPUT_ENOCEAN_BASEID_H                                   (0x18)
    #define MB_INPUT_ENOCEAN_BASEID_L                                   (0x19)
    #define MB_INPUT_CASCADE_ONLINE_MASK                                (0x1A)
    #define MB_INPUT_EXPAND_PANEL_MASK                                  (0x1B)
    #define MB_INPUT_TRIAC_ONLINE_MASK                                  (0x1C)
        #define MB_INPUT_DALI_TRIAC_ID0_ONLINE_MASK                         (0x01)
        #define MB_INPUT_DALI_TRIAC_ID1_ONLINE_MASK                         (0x02)
        #define MB_INPUT_DALI_TRIAC_ID2_ONLINE_MASK                         (0x04)
        #define MB_INPUT_DALI_TRIAC_ID3_ONLINE_MASK                         (0x08)
        #define MB_INPUT_DALI_GATEWAY_ONLINE_MASK                           (0x40)
    /* DALI input running */ 
    
    #define MB_INPUT_DALI_BUS_SEARCH_LAST_H                             (0x30)
    #define MB_INPUT_DALI_BUS_SEARCH_LAST_L                             (0x31)
    #define MB_INPUT_DALI_BUS_SEARCH_NOW_H                              (0x32)
    #define MB_INPUT_DALI_BUS_SEARCH_NOW_L                              (0x33)
    #define MB_INPUT_DALI_BUS_SEARCH_SHORT_ID                           (0x34)
    #define MB_INPUT_DALI_BUS_SEARCH_SUCCESS_L                          (0x35)
    #define MB_INPUT_DALI_BUS_SEARCH_ADJUST_STATE                       (0x36)
    #define MB_INPUT_DALI_BUS_SEARCH_ADJUST_STATE1                      (0x37)
    #define MB_INPUT_DALI_BUS_SEARCH_CONFLICT_CNT                       (0x38)
    #define MB_INPUT_DALI_BUS_SEARCH_CALCULATE_CNT                      (0x39)
    #define MB_INPUT_DALI_BUS_SEARCH_REMAIN_TIME_H                      (0x3A)
    #define MB_INPUT_DALI_BUS_SEARCH_REMAIN_TIME_L                      (0x3B)            
    #define MB_INPUT_DALI_GEAR_UPDATE_0_15_MASK                         (0x3C)
    #define MB_INPUT_DALI_GEAR_UPDATE_16_31_MASK                        (0x3D)
    #define MB_INPUT_DALI_GEAR_UPDATE_32_47_MASK                        (0x3E)
    #define MB_INPUT_DALI_GEAR_UPDATE_48_63_MASK                        (0x3F)
#else
    #define MB_INPUT_SUPPORT_MASK                                       (0x0C)
    #define HW_SUPPORT_DALI_GATEWAY_MASK                                (0x0001)  
    #define HW_SUPPORT_DALI_INTERFACE_MASK                              (0x0002)  
    #define HW_SUPPORT_DALI_TRIAC_MASK                                  (0x0004)
    #define HW_SUPPORT_0_10V_MASK                                       (0x0008)
    #define HW_SUPPORT_ENABLE_MASK                                      (0x0000)

    #define MB_INPUT_ENOCEAN_CHIPID_H                                   (0x0D)
    #define MB_INPUT_ENOCEAN_CHIPID_L                                   (0x0E)

    #define MB_INPUT_ERROR                                              (0x10)
    #define MB_INPUT_ERROR_H                                            (0x10)
    #define MB_INPUT_ERROR_L                                            (0x11)

    #define MB_INPUT_RUN_TIME                                           (0x12)
    #define MB_INPUT_RUN_TIME_H                                         (0x12)
    #define MB_INPUT_RUN_TIME_L                                         (0x13)

    
    #define MB_INPUT_POWER_ON_CNT                                       (0x15)
    
    #define MB_INPUT_FAULT_CNT                                          (0x17)
    #define MB_INPUT_ENOCEAN_BASEID                                     (0x18)
    #define MB_INPUT_ENOCEAN_BASEID_H                                   (0x18)
    #define MB_INPUT_ENOCEAN_BASEID_L                                   (0x19)
    #define MB_INPUT_CASCADE_ONLINE_MASK                                (0x1A)
    
#endif


/*********************************************************************************************************/
/*********************************************************************************************************/
/*********************************************************************************************************/
/*********************************************************************************************************/
#define MB_INPUT_EXPAND_PANEL_BUTTON_NUMS                          (0x00)
#define MB_INPUT_EXPAND_PANEL_RELATE_MASK                          (0x01)
#define MB_INPUT_EXPAND_PANEL_OFFSET_ID                            (0x02)
#define MB_INPUT_EXPAND_PANEL_1_SENSOR_TYPE                        (0x03)//3--10
#define MB_INPUT_EXPAND_PANEL_1_MODE                               (0x04)
#define MB_INPUT_EXPAND_PANEL_1_VALUE                              (0x05)
#define MB_INPUT_EXPAND_PANEL_1_STATE                              (0x06)
#define MB_INPUT_EXPAND_PANEL_2_SENSOR_TYPE                        (0x0B)//11--18
#define MB_INPUT_EXPAND_PANEL_2_MODE                               (0x0C)
#define MB_INPUT_EXPAND_PANEL_2_VALUE                              (0x0D)
#define MB_INPUT_EXPAND_PANEL_2_STATE                              (0x0E)
#define MB_INPUT_EXPAND_PANEL_3_SENSOR_TYPE                        (0x13)//19--26
#define MB_INPUT_EXPAND_PANEL_3_MODE                               (0x14)
#define MB_INPUT_EXPAND_PANEL_3_VALUE                              (0x15)
#define MB_INPUT_EXPAND_PANEL_3_STATE                              (0x16)
#define MB_INPUT_EXPAND_PANEL_4_SENSOR_TYPE                        (0x1B)//27--34
#define MB_INPUT_EXPAND_PANEL_4_MODE                               (0x1C)
#define MB_INPUT_EXPAND_PANEL_4_VALUE                              (0x1D)
#define MB_INPUT_EXPAND_PANEL_4_STATE                              (0x1E)
#define MB_INPUT_EXPAND_PANEL_5_SENSOR_TYPE                        (0x23)//35--42
#define MB_INPUT_EXPAND_PANEL_5_MODE                               (0x24)
#define MB_INPUT_EXPAND_PANEL_5_VALUE                              (0x25)
#define MB_INPUT_EXPAND_PANEL_5_STATE                              (0x26)
#define MB_INPUT_EXPAND_PANEL_6_SENSOR_TYPE                        (0x2B)//43--50
#define MB_INPUT_EXPAND_PANEL_6_MODE                               (0x2C)
#define MB_INPUT_EXPAND_PANEL_6_VALUE                              (0x2D)
#define MB_INPUT_EXPAND_PANEL_6_STATE                              (0x2E)
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/*******************************************************************************************************************/
/* Master hold */
/*******************************************************************************************************************/
/* dev write */

/* dev set */
#define MB_HOLD_LIGHT_NUMS                                          (MB_HOLD_BASE + 0x64)
#define MB_HOLD_LOCK_ENABLE                                         (MB_HOLD_BASE + 0x65)

#define MB_HOLD_RESET_DEFAULT_CMD                                   (MB_HOLD_BASE + 0x66)
#define MB_HOLD_RESET_DEFAULT_PASSWORD                              (MB_HOLD_BASE + 0x67)   
#define MB_HOLD_RESET_DEFAULT_PASSWORD_H                            (MB_HOLD_BASE + 0x67)
#define MB_HOLD_RESET_DEFAULT_PASSWORD_L                            (MB_HOLD_BASE + 0x68)

#define MB_HOLD_RS485MB_ADDRESS                                     (MB_HOLD_BASE + 0x69)
#define MB_HOLD_RS485MB_BAUD                                        (MB_HOLD_BASE + 0x6A)
#define MB_HOLD_RS485MB_STOPS                                       (MB_HOLD_BASE + 0x6B)
#define MB_HOLD_RS485MB_PARITY                                      (MB_HOLD_BASE + 0x6C)
#define MB_HOLD_ENOCEAN_REAPER                                      (MB_HOLD_BASE + 0x6D)
#define MB_HOLD_ENOCEAN_REMANCODE                                   (MB_HOLD_BASE + 0x6E)
#define MB_HOLD_ENOCEAN_REMANCODE_H                                 (MB_HOLD_BASE + 0x6E)
#define MB_HOLD_ENOCEAN_REMANCODE_L                                 (MB_HOLD_BASE + 0x6F)
/* Enocean send period */                                            
#define MB_HOLD_ENOCEAN_SEND_PERIOD                                 (MB_HOLD_BASE + 0x70)
#define MB_HOLD_ENOCEAN_VLD_SUPPORT                                 (MB_HOLD_BASE + 0x71) 
#define MB_HOLD_LIGHT_PROTECT_ON_DELAY                              (MB_HOLD_BASE + 0x72)
#define MB_HOLD_DALI_CHANNEL_NUMS                                   (MB_HOLD_BASE + 0x73)
#define MB_HOLD_TRIAC_CHANNEL_NUMS                                  (MB_HOLD_BASE + 0x74)


#define MB_HOLD_EXPAND_ID0_TYPE                                     (MB_HOLD_BASE + 0x8C)
#define MB_HOLD_EXPAND_ID1_TYPE                                     (MB_HOLD_BASE + 0x8D)
#define MB_HOLD_EXPAND_ID2_TYPE                                     (MB_HOLD_BASE + 0x8E)
#define MB_HOLD_EXPAND_ID3_TYPE                                     (MB_HOLD_BASE + 0x8F)
#define MB_HOLD_EXPAND_PANEL_NUMS                                   (MB_HOLD_BASE + 0x90)
#define MB_HOLD_EXPAND_PANEL_FACTORY                                (MB_HOLD_BASE + 0x91)
#define MB_HOLD_EXPAND_PANEL_BUTTON_NUMS                            (MB_HOLD_BASE + 0x92)
#define MB_HOLD_EXPAND_PANEL_RELATE_MASK                            (MB_HOLD_BASE + 0x93)
#define MB_HOLD_EXPAND_PANEL_SENSOR_TYPE                            (MB_HOLD_BASE + 0x94)
#define MB_HOLD_EXPAND_PANEL_MODE                                   (MB_HOLD_BASE + 0x95)
/* 
0xFFFF: Search all
0xFFFE: Search New
Others: forward the data from master command
*/
#define MB_HOLD_DALI_BUS_STATE                                      (MB_HOLD_BASE + 0xB0)
#define MB_HOLD_DALI_BUS_CMD_WR_ALL                                 (MB_HOLD_BASE + 0xB1)
#define MB_HOLD_DALI_BUS_CMD_ADDRESS                                (MB_HOLD_BASE + 0xB2)
#define MB_HOLD_DALI_BUS_ONLINE_MASK_0_16                           (MB_HOLD_BASE + 0xB3)
#define MB_HOLD_DALI_BUS_ONLINE_MASK_17_31                          (MB_HOLD_BASE + 0xB4)
#define MB_HOLD_DALI_BUS_ONLINE_MASK_32_47                          (MB_HOLD_BASE + 0xB5)
#define MB_HOLD_DALI_BUS_ONLINE_MASK_48_63                          (MB_HOLD_BASE + 0xB6)
#define MB_HOLD_DALI_BUS_SEARCH_NUMS                                (MB_HOLD_BASE + 0xB7)

/*******************************************************************************************************************/
/* Slaver hold Offset ,the base add is 0xFN00 */
/*******************************************************************************************************************/
#define MB_HOLD_DI_NUMS                                             (MB_HOLD_BASE + 0x8E)
#define MB_HOLD_DI_RELATE_MASK                                      (MB_HOLD_BASE + 0x8F)

#define MB_HOLD_DI_1_SENSOR_TYPE                                    (MB_HOLD_BASE + 0x90)
#define MB_HOLD_DI_1_MODE                                           (MB_HOLD_BASE + 0x91)
#define MB_HOLD_DI_1_VALUE                                          (MB_HOLD_BASE + 0x92)
#define MB_HOLD_DI_1_STATE                                          (MB_HOLD_BASE + 0x93)
#define MB_HOLD_DI_1_AUTO_SEND_TIME                                 (MB_HOLD_BASE + 0x94)

#define MB_HOLD_DI_2_SENSOR_TYPE                                    (MB_HOLD_BASE + 0x98)
#define MB_HOLD_DI_2_MODE                                           (MB_HOLD_BASE + 0x99)
#define MB_HOLD_DI_2_VALUE                                          (MB_HOLD_BASE + 0x9A)
#define MB_HOLD_DI_2_STATE                                          (MB_HOLD_BASE + 0x9B)
#define MB_HOLD_DI_2_AUTO_SEND_TIME                                 (MB_HOLD_BASE + 0x9C)

#define MB_HOLD_DI_3_SENSOR_TYPE                                    (MB_HOLD_BASE + 0xA0)
#define MB_HOLD_DI_3_MODE                                           (MB_HOLD_BASE + 0xA1)
#define MB_HOLD_DI_3_VALUE                                          (MB_HOLD_BASE + 0xA2)
#define MB_HOLD_DI_3_STATE                                          (MB_HOLD_BASE + 0xA3)
#define MB_HOLD_DI_3_AUTO_SEND_TIME                                 (MB_HOLD_BASE + 0xA4)

#define MB_HOLD_DI_4_SENSOR_TYPE                                    (MB_HOLD_BASE + 0xA8)
#define MB_HOLD_DI_4_MODE                                           (MB_HOLD_BASE + 0xA9)
#define MB_HOLD_DI_4_VALUE                                          (MB_HOLD_BASE + 0xAA)
#define MB_HOLD_DI_4_STATE                                          (MB_HOLD_BASE + 0xAB)
#define MB_HOLD_DI_4_AUTO_SEND_TIME                                 (MB_HOLD_BASE + 0xAC)
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/* Detect the EnOcean send count for MSC*/
/* Detect EnOcean receive the register for MSC */
#if 0
#define MB_HOLD_ENOCEAN_RX_COUNT                                    (MB_HOLD_BASE + 0xE0)
#define MB_HOLD_ENOCEAN_RX_ID                                       (MB_HOLD_BASE + 0xE2)
#define MB_HOLD_ENOCEAN_RPS_COUNT                                   (MB_HOLD_BASE + 0xE4)
#define MB_HOLD_ENOCEAN_RPS_ID                                      (MB_HOLD_BASE + 0xE6)
#define MB_HOLD_ENOCEAN_4BS_COUNT                                   (MB_HOLD_BASE + 0xE8)
#define MB_HOLD_ENOCEAN_4BS_ID                                      (MB_HOLD_BASE + 0xEA)
#define MB_HOLD_ENOCEAN_1BS_COUNT                                   (MB_HOLD_BASE + 0xEC)
#define MB_HOLD_ENOCEAN_1BS_ID                                      (MB_HOLD_BASE + 0xEE)
#define MB_HOLD_ENOCEAN_VLD_COUNT                                   (MB_HOLD_BASE + 0xF0)
#define MB_HOLD_ENOCEAN_VLD_ID                                      (MB_HOLD_BASE + 0xF2)
#define MB_HOLD_ENOCEAN_MSC_COUNT                                   (MB_HOLD_BASE + 0xF4)
#define MB_HOLD_ENOCEAN_MSC_ID                                      (MB_HOLD_BASE + 0xF6)

/* Detect EnOcean receive the register for RS485 */


#define MB_HOLD_ENOCEAN_RX_COUNT_H                                   (MB_HOLD_BASE + 0xE0)
#define MB_HOLD_ENOCEAN_RX_COUNT_L                                   (MB_HOLD_BASE + 0xE1)
#define MB_HOLD_ENOCEAN_RX_ID_H                                      (MB_HOLD_BASE + 0xE2)
#define MB_HOLD_ENOCEAN_RX_ID_L                                      (MB_HOLD_BASE + 0xE3)

#define MB_HOLD_ENOCEAN_RPS_COUNT_H                                  (MB_HOLD_BASE + 0xE4)
#define MB_HOLD_ENOCEAN_RPS_COUNT_L                                  (MB_HOLD_BASE + 0xE5)

#define MB_HOLD_ENOCEAN_RPS_ID_H                                     (MB_HOLD_BASE + 0xE6)
#define MB_HOLD_ENOCEAN_RPS_ID_L                                     (MB_HOLD_BASE + 0xE7)

#define MB_HOLD_ENOCEAN_4BS_COUNT_H                                  (MB_HOLD_BASE + 0xE8)
#define MB_HOLD_ENOCEAN_4BS_COUNT_L                                  (MB_HOLD_BASE + 0xE9)

#define MB_HOLD_ENOCEAN_4BS_ID_H                                     (MB_HOLD_BASE + 0xEA)
#define MB_HOLD_ENOCEAN_4BS_ID_L                                     (MB_HOLD_BASE + 0xEB)

#define MB_HOLD_ENOCEAN_1BS_COUNT_H                                  (MB_HOLD_BASE + 0xEC)
#define MB_HOLD_ENOCEAN_1BS_COUNT_L                                  (MB_HOLD_BASE + 0xED)

#define MB_HOLD_ENOCEAN_1BS_ID_H                                     (MB_HOLD_BASE + 0xEE)
#define MB_HOLD_ENOCEAN_1BS_ID_L                                     (MB_HOLD_BASE + 0xEF)

#define MB_HOLD_ENOCEAN_VLD_COUNT_H                                  (MB_HOLD_BASE + 0xF0)
#define MB_HOLD_ENOCEAN_VLD_COUNT_L                                  (MB_HOLD_BASE + 0xF1)

#define MB_HOLD_ENOCEAN_VLD_ID_H                                     (MB_HOLD_BASE + 0xF2)
#define MB_HOLD_ENOCEAN_VLD_ID_L                                     (MB_HOLD_BASE + 0xF3)

#define MB_HOLD_ENOCEAN_MSC_COUNT_H                                  (MB_HOLD_BASE + 0xF4)
#define MB_HOLD_ENOCEAN_MSC_COUNT_L                                  (MB_HOLD_BASE + 0xF5)

#define MB_HOLD_ENOCEAN_MSC_ID_H                                     (MB_HOLD_BASE + 0xF6)
#define MB_HOLD_ENOCEAN_MSC_ID_L                                     (MB_HOLD_BASE + 0xF7)
#endif

/**********************************************************************************************************************/

/**********************************************************************************************************************/
/********************** switch page start *****************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/


/**********************************************************************************************************************/
/**********************************************************************************************************************/
//#pragma pack(1)



//#pragma pack(4)
typedef union 
{
    struct
    {
        uint32_t                 u32ResetPassword;                                               
        uint8_t                  u8LightProtectDelayOn;       
        uint32_t                 u32EnOceanChipID;
        uint32_t                 u32EnOceanBaseID;

    #ifdef CASCADE_MASTER
        uint8_t                  u8RadioInterval;
        uint8_t                  u8Repeater;        
        uint8_t                  u8EnOceanBaseEnable;
        eUSART_PARITY_TYPE       eParity;
        eUSART_STOP_TYPE         eStops;           
        eUSART_BAUD_ID_TYPE      eBaudRateID;            

        uint8_t                  u8DALIChannelNums;
        uint32_t                 u32RemanCode;                     
        uint32_t                 u32DALIHOnlineMask;
        uint32_t                 u32DALILOnlineMask;      
    #else 
        uint8_t                  u8DIRelateMask;    
        uint8_t                  u8DISensorType[SLAVE_DI_MAX];
        uint8_t                  u8DIMode[SLAVE_DI_MAX];
        uint16_t                 u16AutoSendTime[SLAVE_DI_MAX];
    #endif
        
    };
    

    uint8_t  u8Bytes[60];

}HWCfg_Typedef;



typedef union 
{
    struct
    {                            
        uint32_t            u32RunTime;
        uint16_t            u16ResetCount;
        uint16_t            u16SoftFaultCount;    
    };

    uint32_t u32Words[8];
    uint8_t  u8Bytes[32];

}HWLogInfo_Typedef;
//#pragma pack()

typedef struct
{
    uint32_t            u32BuildYYMMDD;
    uint32_t            u32BuildHHMMSS;
    uint16_t            u16HWVersion;
    uint16_t            u16FWVersion;
    
    uint8_t             u8ModbusPhyAdd;
    uint8_t             u8CascadePhyAdd;

    uint8_t             u8DINums;
    uint8_t             u8CascadeNums;
    uint16_t            u16CascadeOnlineMask;

    uint16_t            u16TriacReadAddPeriod;
    uint8_t             u8TriacAndDALIOnlineMask;
    uint16_t            u16ExpandPanelOnlineMask;

    uint16_t            u16ReadDALIGatewayPeriod;
    uint16_t            u16SetDALIGaterwayPeriod;

    uint8_t             u8DALIConvertAddress;
    uint8_t             u8DALIPowerSettings;
    uint8_t             u8DALIResponseStatus;
    uint32_t            u32DALIHUpdateMask;
    uint32_t            u32DALILUpdateMask;

    uint16_t            u16ExpandPanelReadPeriod;
    uint8_t             u8DimmingTestValue;

    uint32_t            u32Error; 
    uint16_t            u16ErrorSendTime;
    
    uint8_t             u8TraicErrCnt[4];
    uint32_t            u32TraicErrTime[4];
    uint8_t             u8DALIErrCnt;
    uint32_t            u32DALIErrTime;

    uint8_t             u8LrnSet;
    uint8_t             u8CfgUpdate;   
    uint8_t             u8LogUpdate;
    uint8_t             u8ExpandUpdate;
    uint8_t             u8NVMSaveState;
}DevRun_Typedef;

#ifdef HW_DEBUG    
    typedef struct 
    {

        uint32_t            u32EnOceanRxID;
        uint32_t            u32EnOceanRxCount;    
        uint32_t            u32EnOceanRPSID;
        uint32_t            u32EnOceanRPSRxCount;
        uint32_t            u32EnOcean4BSID;
        uint32_t            u32EnOcean4BSRxCount;
        uint32_t            u32EnOcean1BSID;
        uint32_t            u32EnOcean1BSRxCount;
        uint32_t            u32EnOceanVLDID;
        uint32_t            u32EnOceanVLDRxCount;
        uint32_t            u32EnOceanMSCID;
        uint32_t            u32EnOceanMSCRxCount;

    }DevDebug_Typedef;
#endif

typedef struct
{
    uint8_t             u8ManualState;
    uint8_t             u8LearnState;
    uint8_t             u8LearnChannel;
    uint8_t             u8LearnMode;
    uint8_t             u8LearnSuccessTime;
    uint8_t             u8LearnAutoSendEEPTime;
	uint8_t             u8LearnSendEvent;
}DevManual_Typedef;


typedef struct
{
    HWCfg_Typedef       Cfg;
    HWLogInfo_Typedef   Log;
    DevRun_Typedef         ;

#ifdef HW_DEBUG
    DevDebug_Typedef       ;    
#endif

    DevManual_Typedef;

}Dev_Typedef;

//#pragma pack(1)
typedef union 
{
    struct
    {
        uint8_t                  u8TriacChannelNums;
        uint8_t                  u8ExpandPanelNums;
            
        uint8_t                  u8ButtonNums[EXPAND_PANEL_NUMS_MAX];
        uint8_t                  u8RelateMask[EXPAND_PANEL_NUMS_MAX];
        uint8_t                  u8Mode[EXPAND_PANEL_NUMS_MAX][6];
        uint8_t                  u8SensorType[EXPAND_PANEL_NUMS_MAX][6];

        uint8_t                  u8TraicType[4];
    };
    
    uint8_t  u8Bytes[240];
}MasterExpandDevCfg_typedef;

typedef struct 
{
    uint8_t u8SensorType;
    uint8_t u8Mode;
    uint8_t u8Event;
    uint8_t u8DownState;
    uint8_t u8DownStatePre;
    uint8_t u4Value;
    uint8_t u8AutoSendState;
    uint16_t u16AutoSend;
}DI_Typedef;

typedef struct 
{    
    uint8_t u8DINums;
    uint8_t u8RelateMask;

    uint8_t u8LrnSet;
    uint8_t u8EventMask;
    uint8_t u8Mask;
    uint8_t u8OffsetID;
    
    DI_Typedef DI[SLAVE_DI_MAX];

}SlaverDI_Typedef;

typedef struct 
{    
    uint8_t u8ButtonNums;
    uint8_t u8RelateMask;

    uint8_t u8OffsetID;    
    uint8_t u8LedMask;

    DI_Typedef DI[6];
    
}ExpandPanel_Typedef;

//#pragma pack()
/*******************************************************************************/
/*******************************************************************************/


/*******************************************************************************/
/*******************************************************************************/
extern Dev_Typedef               Dev;
extern SlaverDI_Typedef          SlaverDI[LIGHT_CASCADE_NUMS_MAX];
extern ExpandPanel_Typedef       ExpandPanel[EXPAND_PANEL_NUMS_MAX];
extern Radio_Typedef             ExpandRadio;


#ifdef CASCADE_MASTER
    
    
#endif






/**
  * @brief
  * @param
  * @retval None
  */
void NVM_DevRunSave(void);
/**
   * @brief
   * @param
   * @retval
   */
void NVM_ChannelUpdate(uint8_t u8Channel);
/**
  * @brief
  * @param
  * @retval None
  */
void HardWareLoadDefaultSettings(void);
/**
  * @brief
  * @param
  * @retval None
  */
void DevLoadDefaultSettings(void);
/**
  * @brief
  * @param
  * @retval None
  */
void IOProfileLoadDefault(uint8_t u8Channel);
/**
  * @brief
  * @param
  * @retval None
  */
void NVM_GetLightPowerOn(void);
/**
  * @brief
  * @param
  * @retval None
  */
void ResetDefaultData(void);
/**
  * @brief
  * @param
  * @retval None
  */
void ResetDefaultEnable(void);
/**
  * @brief
  * @param
  * @retval None
  */
void NVM_LoadSettings(void);
/**
  * @brief
  * @param
  * @retval None
  */
void NVM_WriteSettings(void);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t NVM_DevWriteSetting(void);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t NVM_ExpandDevWriteSetting(void);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t NVM_IOProfileWriteSetting(void);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t NVM_IOStateWriteSetting(void);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t NVM_DevRunInfo(void);
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t NVM_LearnInfoTabWriteSetting(void);


#endif




extern uint32_t u32EnOceanChipID;
extern uint32_t u32EnOceanBaseID;
extern uint8_t u8EnOceanRepeater;
extern uint32_t u32EnOceanRemanCode;





#endif

