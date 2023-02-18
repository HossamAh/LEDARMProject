/*---------------------------------------------------------------------------------------------------------------------
 *  *  FILE DESCRIPTION
 *  --------------------
 *         File:  port.h
 *       Module:  PORT Driver
 *  Description:  header file for PORT Module            
---------------------------------------------------------------------------------------------------------------------*/
#ifndef PORT_H
#define PORT_H

/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/
#include "port_Types.h"
#include "port_Cfg.h"


/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA TYPES AND STRUCTURES
---------------------------------------------------------------------------------------------------------------------*/
typedef struct 
{
    Port_PinModeType PinMode;
    Port_PinLevel PinLevel;
    Port_PinDirectionType PinDir;
    Port_PinInternalAttachType InternalAttach;
    Port_PinOutputCurrentType CurrentValue;
    Port_Num Port;
    Port_PinNum Pin;
    Port_Enable_Interrupt Enable_INT;
    Port_Trigger_Pulse_Type   Trigger_Pulse_Type;
    Port_Trigger_Level_Type   Trigger_Level_type;
}Port_Cfg_Type;



/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA PROTOTYPES
---------------------------------------------------------------------------------------------------------------------*/
extern const Port_Cfg_Type Port_CONFIGURATIONS[MAX_PIN_NUMBER];
 
/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL FUNCTION PROTOTYPES
---------------------------------------------------------------------------------------------------------------------*/ 
/******************************************************************************
* \Syntax          : void Port_Init(const Port_Cfg_Type* ConfigPtr)                                      
* \Description     : initialize Port using configuration struct bu parsing all 
*       its configurations to the port registers                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : ConfigPtr  pointer to port initalization configurations.                   
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void Port_Init(const Port_Cfg_Type* ConfigPtr);
 
/******************************************************************************
* \Syntax          : void PortEnable_Notificaion(Port_PinNum num,Port_INT_callBack ptr)                                     
* \Description     : Assign callback function to PORT interrupt                                       
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : num the port which generate the interrupt , ptr pointer to function that will be called from ISR.                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/

void PortEnable_Notificaion(Port_Num num,Port_INT_callBack ptr);//ptr is writen in app layer

#endif