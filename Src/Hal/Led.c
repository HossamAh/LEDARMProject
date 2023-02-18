/*---------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
---------------------------------------------------------------------------------------------------------------------*/
/**        \file  Led.c
 *        \brief  Led Driver
 *
 *      \details  Led initialization and functionality
---------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/
#include "Led.h"

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL FUNCTIONS
---------------------------------------------------------------------------------------------------------------------*/
/******************************************************************************
* \Syntax          : void Led_On(void)                                      
* \Description     : Turn the led on                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void Led_On(void)
{
    DIO_WriteChannel(LED_pin,HIGH);
}
/******************************************************************************
* \Syntax          : void Led_Off(void)                                      
* \Description     : Turn the led off                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void Led_Off(void)
{
    DIO_WriteChannel(LED_pin,LOW);
}

/******************************************************************************
* \Syntax          : void Led_Toggle(void)                                      
* \Description     : Toggle the led                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void Led_Toggle(void)
{
    DIO_FlipChannel(LED_pin);
}
