/*---------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
---------------------------------------------------------------------------------------------------------------------*/
/**        \file  SystemClock_Lcfg.c
 *        \brief  System Clock Driver Configurations
 *
 *      \details  Contain configurations of the System Clock Driver.
---------------------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/
#include "SystemClock.h"

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA
---------------------------------------------------------------------------------------------------------------------*/
const uint16     SystemClockProvided = 16;//in MHZ
const SystemClock_ConfigurationType ClockConfig=
{
    /*ClockSoruce           PLLState            XTALValue           DivFactor*/
    MOSC_Clock,             NO_PLL,                Crystal16MHz,    SYSCTL_SYSDIV_1};