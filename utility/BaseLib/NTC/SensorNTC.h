

#ifndef _SENSOR_NTC_H_
#define _SENSOR_NTC_H_


#include "..\..\MCU_platform\platform.h"

#define NTC_SAMPLE_PERIOD              (5)

typedef enum
{
    eNTC_OK = 0,
    eNTC_SHORT_CIRCUIT,
    eNTC_OPEN_CIRCUIT,
}eNTC_STATE_TYPE;



/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
typedef struct
{ 
    uint16_t temprature;                /* 温度 */
    uint16_t adValueSum;               /* 采样值 */
    //uint8_t errorTimes;
    //uint8_t errorFlag :1;              /* 错误位 */
    //uint8_t totalConvTimes :7;         /* 采集次数计数*/
    uint8_t u8SamplePeriod;    
    eNTC_STATE_TYPE eError;
}Ntc_Typedef;
/*============================ GLOBAL VARIABLES ==============================*/
extern Ntc_Typedef NTC_3380;
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/


/*! \note initialize hardware abstract layer
 *  \param none
 *  \retval true hal initialization succeeded.
 *  \retval false hal initialization failed
 */  
extern void NTC_StartAndMeasureTemprature(Ntc_Typedef *me);
/**
   * @brief
   * @param
   * @retval
   */
void NTC_TimeTick_1000ms(Ntc_Typedef *pNTC);



#endif

/* End of file */
