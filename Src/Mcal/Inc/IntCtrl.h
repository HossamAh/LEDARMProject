/*---------------------------------------------------------------------------------------------------------------------
 *  *  FILE DESCRIPTION
 *  --------------------
 *         File:  IntCrtl.h
 *       Module:  IntCrtl
 *  Description:  header file for IntCrtl Module       
---------------------------------------------------------------------------------------------------------------------*/
#ifndef IntCrtl_H
#define IntCrtl_H

/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/
#include "Std_Types.h"
#include "IntCtrl_Cfg.h"

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA TYPES AND STRUCTURES
---------------------------------------------------------------------------------------------------------------------*/
typedef struct 
{
    uint8 enableExceptions_Numbers[INTCTRL_EXCEPTION_ENABLE_SIZE];//Contain the index of exceptions to be enabled.
    uint8 disableExceptions_Numbers[INTCTRL_EXCEPTION_DISABLE_SIZE];//Contain the index of exceptions to be disabled. 
    uint8 priorityGroup_Exceptions[INTCTRL_EXCEPTION_ENABLE_SIZE];//Contain the priority group of the exceptions sorted raltive to enableExceptions_numbers . 
    uint8 prioritySubGroup_Exceptions[INTCTRL_EXCEPTION_ENABLE_SIZE];//Contain the priority sub-group of the exceptions sorted raltive to enableExceptions_numbers. 
}IntCtrl_Cfg_Type;


/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA PROTOTYPES
---------------------------------------------------------------------------------------------------------------------*/
extern IntCtrl_Cfg_Type IntCTRL_CONFIGURATIONS;
 
/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL FUNCTIONS
---------------------------------------------------------------------------------------------------------------------*/ 
/******************************************************************************
* \Syntax          : void IntCrtl_Init(void)                                      
* \Description     : initialize Nvic\SCB Module by parsing the Configuration 
*                    into Nvic\SCB registers                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void IntCrtl_Init(void);
/******************************************************************************
* \Syntax          : void IntCrtl_DeInit(void)                                      
* \Description     : Deinitialize Nvic\SCB Module by parsing the Configuration 
*                    into Nvic\SCB registers                                                                                           
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void IntCrtl_DeInit(void);
 
#endif