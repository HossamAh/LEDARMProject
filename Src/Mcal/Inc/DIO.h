/*---------------------------------------------------------------------------------------------------------------------
 *  *  FILE DESCRIPTION
 *  --------------------
 *         File:  DIO.h
 *       Module:  DIO Driver
 *  Description:  DIO Driver header file        
---------------------------------------------------------------------------------------------------------------------*/
#ifndef DIO_H
#define DIO_H

/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/
#include "DIO_Types.h"
#include "Std_Types.h"
#include "Mcu_Hw.h"

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL FUNCTION PROTOTYPES
---------------------------------------------------------------------------------------------------------------------*/
/******************************************************************************
* \Syntax          : DIO_LevelType DIO_ReadChannel(DIO_ChannelType ChannelId)                                    
* \Description     : Read DIO pin (channel) by reading its GPIODATA register value
*                    using bit masking method.                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : channelId                     
* \Parameters (out): None                                                      
* \Return value:   : DIO_LevelType (High or Low)
*******************************************************************************/
DIO_LevelType DIO_ReadChannel(DIO_ChannelType ChannelId);
/******************************************************************************
* \Syntax          : void DIO_WriteChannel(DIO_ChannelType ChannelId,DIO_LevelType Level)                                      
* \Description     : Write the output value to channel by writing its level value
*                    to GPIODATA register using bit masking method.
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : channelId , level                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void DIO_WriteChannel(DIO_ChannelType ChannelId,DIO_LevelType Level);
/******************************************************************************
* \Syntax          : DIO_PortLevelType DIO_ReadPort(DIO_PortType PortId)                                      
* \Description     : Read DIO port value which is value from 0 to 255                                                                                                           
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : PortId                      
* \Parameters (out): None                                                      
* \Return value:   : port level
*******************************************************************************/
DIO_PortLevelType DIO_ReadPort(DIO_PortType PortId);
/******************************************************************************
* \Syntax          : void DIO_WritePort(DIO_PortType PortId,DIO_PortLevelType Level)                                      
* \Description     : write port value using bit masking method.               
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : portId , port level                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void DIO_WritePort(DIO_PortType PortId,DIO_PortLevelType Level);
/******************************************************************************
* \Syntax          : DIO_LevelType DIO_FlipChannel(DIO_ChannelType channelId)                                      
* \Description     : toggle channel level                                     
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : channelId                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
DIO_LevelType DIO_FlipChannel(DIO_ChannelType ChannelId);
 
#endif  /* DIO_H */

/**********************************************************************************************************************
 *  END OF FILE: DIO.h
 *********************************************************************************************************************/
