#ifndef __HW_TEST_H__
#define __HW_TEST_H__


/* USER CODE BEGIN Includes */
#include "platform.h"
#include "BaselibInclude.h"
#include "Dataconfigure.h"
#include "Led.h"

typedef enum
{
    eHWTESTLED_STANDBY = 0, // 待机状态
    //硬件自检模式
    eHWTESTLED_SELFTESTREADY,     //自检测试准备
    eHWTESTLED_SELFTESTING,       //展示自动测试中的效果（四种颜色的LED此起彼伏的亮，表示正在测试）
    eHWTESTLED_SELFTESTSHOWSTART, //测试结束,开始展示测试结果
    eHWTESTLED_SELFTESTSHOWING,   //自检展示中

    //PMS测试
    eHWTESTLED_PMSTEST_CMDSTART, //PMS测试命令开始
    eHWTESTLED_PMSTEST_WAITEND,  //等待PMS测试命令结束

}HWTestLed_t;

typedef struct
{
    eLed_t eLedID;           // ID
    HWTestLed_t HWTestLed;

    uint8_t u8MarqueeFlag;
    uint8_t u8SelfTestState;  //自检进入标记
    uint16_t u16HWTestLedTimer;  //自检LED定时器
    uint32_t u32HWTestCount;     //自检定时计数

    uint32_t u32HWTestEnoceanSendCout;   //Enocean发送计数

} HWTest_Typedef;

extern HWTest_Typedef HWTest;

/*! \note  
*  \param  
*  \retval  
*  \retval  
*/
void HardwareSelfTest_Tick1ms(HWTest_Typedef *pHWTest);
/*! \note  
*  \param  
*  \retval  
*  \retval  
*/
void HardwareSelfTestLed(HWTest_Typedef *pHWTest);


/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */
void HardwareSelfTest(HWTest_Typedef *pHWTest);

#endif

