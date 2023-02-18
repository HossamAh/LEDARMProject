/*---------------------------------------------------------------------------------------------------------------------
 *  *  FILE DESCRIPTION
 *  --------------------
 *         File:  SystemClock.h
 *       Module:  System Clock Driver
 *  Description:  header file for System Clock Module            
---------------------------------------------------------------------------------------------------------------------*/
#ifndef SYSTEMCLOCK_H
#define SYSTEMCLOCK_H

/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/
#include "SystemClock_Types.h"

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA TYPES AND STRUCTURES
---------------------------------------------------------------------------------------------------------------------*/
typedef struct 
{
    SystemClock_ClockSRC ClockSoruce;
    SystemClock_PLL  PLLState;
    SystemClock_XTAL_Values XTALValue;//divisors with PLL and without P223 table 5-4
    SystemClock_ClockDiv DivFactor;
}SystemClock_ConfigurationType;


/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL FUNCTION PROTOTYPES
---------------------------------------------------------------------------------------------------------------------*/
/******************************************************************************
* \Syntax          : void SystemClock_Init(void)                                    
* \Description     : Initialize the system clock with the global configurations by change configuration 
*                   registers.                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void SystemClock_Init(void);
#endif