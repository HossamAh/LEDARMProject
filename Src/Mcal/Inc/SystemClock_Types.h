/*---------------------------------------------------------------------------------------------------------------------
 *  *  FILE DESCRIPTION
 *  --------------------
 *         File:  SystemClock_Types.h
 *  Description:  System Clock new types header file 
---------------------------------------------------------------------------------------------------------------------*/
#ifndef SYSTEMCLOCK_TYPES_H
#define SYSTEMCLOCK_TYPES_H
/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/
#include "Std_Types.h"

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA TYPES AND STRUCTURES
---------------------------------------------------------------------------------------------------------------------*/
typedef enum
{
    
Crystal_5MHz = 0x09,
Crystal5_12MHz =0x0A,
Crystal6MHz =0x0B,
Crystal6_144MHz =0x0C,
Crystal7_3728MHz =0x0D,
Crystal8MHz =0x0E,
Crystal12MHz =0x11,
Crystal16MHz =0x15,
Crystal25MHz =0x1A,
}SystemClock_XTAL_Values;// value of crystal oscilattor atached to MOSC.

typedef enum
{
    MOSC_Clock,
    PIOSC_Clock,
    PIOSC_4_Clock,
    LFIOS_Clock
}SystemClock_ClockSRC;

typedef enum
{
    NO_PLL,
    PLL
}SystemClock_PLL;

typedef enum
{
    SYSCTL_SYSDIV_1,
    SYSCTL_SYSDIV_2,
    SYSCTL_SYSDIV_3,
    SYSCTL_SYSDIV_4,//50MHZ in PLL
    SYSCTL_SYSDIV_5,
    SYSCTL_SYSDIV_6,
    SYSCTL_SYSDIV_7,
    SYSCTL_SYSDIV_8,
    SYSCTL_SYSDIV_9,
    SYSCTL_SYSDIV_10,
    SYSCTL_SYSDIV_11,
    SYSCTL_SYSDIV_12,
    SYSCTL_SYSDIV_13,
    SYSCTL_SYSDIV_14,
    SYSCTL_SYSDIV_15,
    SYSCTL_SYSDIV_16
}SystemClock_ClockDiv;
#endif