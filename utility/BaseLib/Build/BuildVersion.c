/*******************************************************************
    printf("NETCtrl_SelfTest(void=)\n", void);
*
*    DESCRIPTION:
*
*    AUTHOR:
*
*    HISTORY:
*
*    DATE:
*
*******************************************************************/


#include "..\BaselibInclude.h"




const char BuildInfoDate[] = __DATE__;                                                                     
const char BuildInfoTime[] = __TIME__;
const uint8_t u8MonthStr[][3] = 
{
    "Jan",
    "Feb",
    "Mar",
    "Apr",
    "May",
    "Jun",
    "Jul",
    "Aug",
    "Sep",
    "Oct",
    "Nov",
    "Dec",    
};


/* Private functions ---------------------------------------------------------*/


/* Private functions ---------------------------------------------------------*/
/**
  * @brief
  * @param
  * @retval None
  */
uint8_t BuildComplierDateTime(uint32_t *pu32BuildDate,uint32_t *pu32BuildTime)
{
    uint8_t  u8Temp;
    uint16_t  u16Temp;

    *pu32BuildDate = 0x00;
    /* Month */
    if ( ( BuildInfoDate[0] == 'J' )&&( BuildInfoDate[1] == 'a' )&&( BuildInfoDate[2] == 'n' ) )
    {
        *pu32BuildDate |= 0x00000100;
    }
    else if ( ( BuildInfoDate[0] == 'F' )&&( BuildInfoDate[1] == 'e' )&&( BuildInfoDate[2] == 'b' ) )
    {
        *pu32BuildDate |= 0x00000200;
    }
    else if ( ( BuildInfoDate[0] == 'M' )&&( BuildInfoDate[1] == 'a' )&&( BuildInfoDate[2] == 'r' ) )
    {
        *pu32BuildDate |= 0x00000300;
    }
    else if ( ( BuildInfoDate[0] == 'A' )&&( BuildInfoDate[1] == 'p' )&&( BuildInfoDate[2] == 'r' ) )
    {
        *pu32BuildDate |= 0x00000400;
    }
    else if ( ( BuildInfoDate[0] == 'M' )&&( BuildInfoDate[1] == 'a' )&&( BuildInfoDate[2] == 'y' ) )
    {
        *pu32BuildDate |= 0x00000500;
    }
    else if ( ( BuildInfoDate[0] == 'J' )&&( BuildInfoDate[1] == 'u' )&&( BuildInfoDate[2] == 'n' ) )
    {
        *pu32BuildDate |= 0x00000600;
    }
    else if ( ( BuildInfoDate[0] == 'J' )&&( BuildInfoDate[1] == 'u' )&&( BuildInfoDate[2] == 'l' ) )
    {
        *pu32BuildDate |= 0x00000700;
    }
    else if ( ( BuildInfoDate[0] == 'A' )&&( BuildInfoDate[1] == 'u' )&&( BuildInfoDate[2] == 'g' ) )
    {
        *pu32BuildDate |= 0x00000800;
    }
    else if ( ( BuildInfoDate[0] == 'S' )&&( BuildInfoDate[1] == 'e' )&&( BuildInfoDate[2] == 'p' ) )
    {
        *pu32BuildDate |= 0x00000900;
    }
    else if ( ( BuildInfoDate[0] == 'O' )&&( BuildInfoDate[1] == 'c' )&&( BuildInfoDate[2] == 't' ) )
    {
        *pu32BuildDate |= 0x00001000;
    }
    else if ( ( BuildInfoDate[0] == 'N' )&&( BuildInfoDate[1] == 'o' )&&( BuildInfoDate[2] == 'v' ) )
    {
        *pu32BuildDate |= 0x00001100;
    }
    else if ( ( BuildInfoDate[0] == 'D' )&&( BuildInfoDate[1] == 'e' )&&( BuildInfoDate[2] == 'c' ) )
    {
        *pu32BuildDate |= 0x00001200;
    }

    
    /* Day */
    u8Temp   = BuildInfoDate[4]-'0';
    u16Temp  = (uint16_t)u8Temp<<4;
    u16Temp &= 0xF0;
    u8Temp   = BuildInfoDate[5]-'0';
    u16Temp |= (uint16_t)u8Temp;
    *pu32BuildDate |= u16Temp;

    /* Year */
    u8Temp   = BuildInfoDate[7]-'0';
    u16Temp  = (uint16_t)u8Temp<<4;
    u8Temp   = BuildInfoDate[8]-'0';
    u16Temp += (uint16_t)u8Temp;
    *pu32BuildDate |= (uint32_t)u16Temp<<24;
    u8Temp   = BuildInfoDate[9]-'0';
    u16Temp  = (uint16_t)u8Temp<<4;
    u8Temp   = BuildInfoDate[10]-'0';
    u16Temp += (uint16_t)u8Temp;
    *pu32BuildDate |= (uint32_t)u16Temp<<16;

    *pu32BuildTime = 0x00;
    u8Temp   = BuildInfoTime[0]-'0';
    u16Temp  = u8Temp*16;
    u8Temp   = BuildInfoTime[1]-'0';
    u16Temp += u8Temp;
    *pu32BuildTime |= (uint32_t)u16Temp<<16;

    u8Temp   = BuildInfoTime[3]-'0';
    u16Temp  = u8Temp*16;
    u8Temp   = BuildInfoTime[4]-'0';
    u16Temp += u8Temp;
    *pu32BuildTime |= u16Temp<<8;

    u8Temp   = BuildInfoTime[6]-'0';
    u16Temp  = u8Temp*16;
    u8Temp   = BuildInfoTime[7]-'0';
    u16Temp += u8Temp;
    *pu32BuildTime |= u16Temp;
    
    
    
    return 0;
}
/* End of file */
