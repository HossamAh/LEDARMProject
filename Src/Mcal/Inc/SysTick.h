/*---------------------------------------------------------------------------------------------------------------------
 *  *  FILE DESCRIPTION
 *  --------------------
 *         File:  SysTick.h
 *       Module:  SysTick timer Driver
 *  Description:  header file for SysTick timer Module            
---------------------------------------------------------------------------------------------------------------------*/
#ifndef SYSTICK_H
#define SYSTICK_H
/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/
#include"SysTick_Types.h"
#include"Std_Types.h"

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA TYPES AND STRUCTURES
---------------------------------------------------------------------------------------------------------------------*/
typedef void (*CallBack_type)(void);

typedef struct 
{
    SysTick_ClockSource CLKSRC;
    uint8 Frequency;//predefined the frequency of the drived clock. 
    uint32 NumberOfSeconds;//predefined number of seconds to interrupt after them.
}SysTick_ConfigurationType;


/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL FUNCTION PROTOTYPES
---------------------------------------------------------------------------------------------------------------------*/
/******************************************************************************
* \Syntax          : void Register_CallBack(CallBack_type CB_ptr)                                    
* \Description     : Initialize the SysTick ISR callback function with  CB_ptr                                                                            
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : CALLBACK_type CB_ptr  pointer to the callback function to be called from ISR                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void Register_CallBack(CallBack_type CB_ptr);
/******************************************************************************
* \Syntax          : void SysTick_init(void)                                   
* \Description     : Initialize the SysTick with the global configurations by change configuration 
*                   registers.                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void SysTick_init(void);

/******************************************************************************
* \Syntax          : void SysTick_init_tick(uint32 ticks)                                   
* \Description     : Initialize the SysTick with the global configurations by change configuration 
*                   registers and with spcific ticks less than 2pow 24                                                                
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void SysTick_init_tick(uint32 ticks);
/******************************************************************************
* \Syntax          : void SysTick_Stop(void)                                    
* \Description     : Stop the SysTick Timer and disable its interrupt and reset all its registers.                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void SysTick_Stop(void);

#endif