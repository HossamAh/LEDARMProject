/*---------------------------------------------------------------------------------------------------------------------
 *  *  FILE DESCRIPTION
 *  --------------------
 *         File:  buttons.h
 *       Module:  buttons Driver
 *  Description:  buttons Driver header file        
---------------------------------------------------------------------------------------------------------------------*/
#ifndef BUTTONS_H
#define BUTTONS_H

/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/
#include "DIO.h"

/*---------------------------------------------------------------------------------------------------------------------
 *  LOCAL MACROS
---------------------------------------------------------------------------------------------------------------------*/
#define ConfirmButton PinF0
#define IncButton PinF4

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL FUNCTION PROTOTYPES
---------------------------------------------------------------------------------------------------------------------*/
/******************************************************************************
* \Syntax          : DIO_LevelType Confirm_Read(void)                                      
* \Description     : Read the value at confirm button pin                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None
* \Parameters (out): None                                                      
* \Return value:   : DIO_LevelType the value at the button pin
*******************************************************************************/
DIO_LevelType Confirm_Read(void);
/******************************************************************************
* \Syntax          : DIO_LevelType Inc_Read(void)                                      
* \Description     : Read the value at Inc button pin                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None
* \Parameters (out): None                                                      
* \Return value:   : DIO_LevelType the value at the button pin
*******************************************************************************/
DIO_LevelType Inc_Read(void);

#endif