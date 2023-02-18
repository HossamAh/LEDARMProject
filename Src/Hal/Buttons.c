/*---------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
---------------------------------------------------------------------------------------------------------------------*/
/**        \file  Buttons.c
 *        \brief  Buttons Driver
 *
 *      \details  Buttons functionality
---------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/
#include "Buttons.h"

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL FUNCTIONS
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
DIO_LevelType Confirm_Read(void)
{
    return DIO_ReadChannel(ConfirmButton);
}
/******************************************************************************
* \Syntax          : DIO_LevelType Inc_Read(void)                                      
* \Description     : Read the value at Inc button pin                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None
* \Parameters (out): None                                                      
* \Return value:   : DIO_LevelType the value at the button pin
*******************************************************************************/
DIO_LevelType Inc_Read(void)
{
    return DIO_ReadChannel(IncButton);
}
