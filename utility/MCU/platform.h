#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#include "Common.h"
#include ".\BSP\BSP_Include.h"
//#include "..\BaseLib\CRC\CRC_8_16_32.h"

#define ENTER_CRITICAL_SECTION( )   disableInterrupts()
#define EXIT_CRITICAL_SECTION( )    enableInterrupts()



#endif




