

/*============================ INCLUDES ======================================*/
#include "SensorNTC.h"

/*============================ MACROS ========================================*/
#define NTC_AVERAGE_TIMES_16

#if defined NTC_AVERAGE_TIMES_1
    #define NTC_AVERAGE_TIMES  1
    #define NTC_AVERAGE_OFFSET 0
#elif defined NTC_AVERAGE_TIMES_2   
    #define NTC_AVERAGE_TIMES  2
    #define NTC_AVERAGE_OFFSET 1
#elif defined NTC_AVERAGE_TIMES_4
    #define NTC_AVERAGE_TIMES  4
    #define NTC_AVERAGE_OFFSET 2
#elif defined NTC_AVERAGE_TIMES_8
    #define NTC_AVERAGE_TIMES  8
    #define NTC_AVERAGE_OFFSET 3
#elif defined NTC_AVERAGE_TIMES_16
    #define NTC_AVERAGE_TIMES  16
    #define NTC_AVERAGE_OFFSET 4
#elif defined NTC_AVERAGE_TIMES_32
    #define NTC_AVERAGE_TIMES  32
    #define NTC_AVERAGE_OFFSET 5
#else 
    #define NTC_AVERAGE_TIMES  32
    #define NTC_AVERAGE_OFFSET 5
#endif

/*
*/
#define NTC_MAX_AD_VALUE     900
#define NTC_MIN_AD_VALUE     90
/*
*/
#define MAX_ERROR_TIMES     0X03
#define ERROR_LIMIT_TIMES 0X05
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
const uint16_t NTC_10K3380_Tab[] =
{

903	,//	-20
897	,//	-19
891	,//	-18
885	,//	-17
879	,//	-16
872	,//	-15
866	,//	-14
859	,//	-13
852	,//	-12
845	,//	-11
838	,//	-10
830	,//	-9
822	,//	-8
815	,//	-7
807	,//	-6
798	,//	-5
790	,//	-4
782	,//	-3
773	,//	-2
764	,//	-1
755	,//	0
746	,//	1
737	,//	2
728	,//	3
719	,//	4
709	,//	5
700	,//	6
690	,//	7
680	,//	8
670	,//	9
661	,//	10
651	,//	11
641	,//	12
631	,//	13
621	,//	14
611	,//	15
601	,//	16
591	,//	17
581	,//	18
571	,//	19
561	,//	20
551	,//	21
541	,//	22
531	,//	23
521	,//	24
512	,//	25
502	,//	26
492	,//	27
483	,//	28
473	,//	29
464	,//	30
455	,//	31
445	,//	32
436	,//	33
427	,//	34
418	,//	35
410	,//	36
401	,//	37
393	,//	38
384	,//	39
376	,//	40
368	,//	41
360	,//	42
352	,//	43
344	,//	44
337	,//	45
329	,//	46
322	,//	47
315	,//	48
307	,//	49
301	,//	50
294	,//	51
287	,//	52
281	,//	53
274	,//	54
268	,//	55
262	,//	56
256	,//	57
250	,//	58
244	,//	59
238	,//	60
233	,//	61
228	,//	62
222	,//	63
217	,//	64
212	,//	65
207	,//	66
202	,//	67
198	,//	68
193	,//	69
189	,//	70
184	,//	71
180	,//	72
176	,//	73
172	,//	74
168	,//	75
164	,//	76
160	,//	77
157	,//	78
153	,//	79
149	,//	80
146	,//	81
143	,//	82
139	,//	83
136	,//	84
133	,//	85
130	,//	86
127	,//	87
124	,//	88
122	,//	89
119	,//	90
116	,//	91
114	,//	92
111	,//	93
109	,//	94
106	,//	95
104	,//	96
102	,//	97
99	,//	98
97	,//	99
                                
};
#define NTC_TAB_LENGTH                      ( sizeof(NTC_10K3380_Tab)/sizeof(uint16_t) )
#define NTC_TAB_INDEX_MAX                   (NTC_TAB_LENGTH - 1)
/******************************************************************************/
/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/

Ntc_Typedef NTC_3380;
/**
   * @brief
   * @param
   * @retval
   */
static int16_t SeachTempTable( uint16_t adValue,const uint16_t *tempTable)
{
    uint16_t  table_high=0;
    uint16_t  table_low=0;
    int16_t  temprature=0;            //返回温度
    int16_t  remain=0;
    const  uint16_t  *pt ;              //小数部分    
    
    pt = &NTC_10K3380_Tab[0];    
        
    if(adValue > *pt)          //查表
    {
        adValue = *pt;
    }     

    if(adValue < *(pt + NTC_TAB_INDEX_MAX))
    {
        adValue = *(pt + NTC_TAB_INDEX_MAX);
    }

    while(temprature < NTC_TAB_INDEX_MAX)       
    {
        if(adValue >= *pt)
        {
            break;
        }
        else
        {
            temprature++;
            pt++;
        }
    }

    if(temprature==0)
    {
        remain=0;
    }
    else
    {    
        table_high=*(pt-1);
        table_low=*pt;         
        remain=(adValue-table_low)*10/(table_high-table_low);       
    }   
    if(remain>=5)
    {
        remain=5;
    }
    else
    {
        remain=0;
    }
    temprature = temprature*10;
    //temprature-=remain;          //小数部分       
    return(temprature);
}
/**
   * @brief
   * @param
   * @retval
   */
static void CurrentTempratureAverageMeasure(Ntc_Typedef *me)
{
    uint16_t tempAdvalue = 0;
    
    tempAdvalue = (me->adValueSum>>=NTC_AVERAGE_OFFSET);
    
    /* ADC open circuit */
    if (tempAdvalue > NTC_MAX_AD_VALUE)
    {
        /* */
        /*
        if (me->errorTimes < 0xFF)
        {
            me->errorTimes++;        
        }
        if ( me->errorTimes > 3 )
        {
            me->eError     = eNTC_OPEN_CIRCUIT;
        }
        */
        me->eError     = eNTC_OPEN_CIRCUIT;
        me->temprature = 0;
    }
    /* ADC Short circuit */
    else if (tempAdvalue < NTC_MIN_AD_VALUE)
    {
        /*
        if (me->errorTimes < 0xFF)
        {
            me->errorTimes++;        
        }
        if ( me->errorTimes > 3 )
        {
            me->eError     = eNTC_SHORT_CIRCUIT;
        }
        */
        me->eError     = eNTC_SHORT_CIRCUIT;
        me->temprature = 0;
    }
    else
    {
        me->eError     = eNTC_OK;
        me->temprature = SeachTempTable(tempAdvalue, NTC_10K3380_Tab);
    } 
     
}
/**
   * @brief
   * @param
   * @retval
   */
void NTC_StartAndMeasureTemprature(Ntc_Typedef *me)
{    
    uint16_t tempAdvalue = 0;
    static uint8_t SampleCount = 0;   
 
    /* If sample period is not clear, return back */
    if ( NTC_3380.u8SamplePeriod )
    {
        return;
    }
    
    if ( SampleCount < NTC_AVERAGE_TIMES )
    {
        if(SET == (ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)))
        {
            ADC_ClearFlag(ADC1,ADC_FLAG_EOC);
            tempAdvalue         = ADC_GetConversionValue(ADC1);
            me->adValueSum     += tempAdvalue;
            SampleCount++;
            ADC_SoftwareStartConv(ADC1);
        }
    }
    else
    {        
        CurrentTempratureAverageMeasure(me);
        SampleCount    = 0; 
        me->adValueSum = 0;        
        me->u8SamplePeriod = NTC_SAMPLE_PERIOD;
    }
}
/**
   * @brief
   * @param
   * @retval
   */
void NTC_TimeTick_1000ms(Ntc_Typedef *pNTC)
{
    if ( pNTC->u8SamplePeriod )
    {
        pNTC->u8SamplePeriod --;
    }
}
/* End of file */
