/*---------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
---------------------------------------------------------------------------------------------------------------------*/
/**        \file  DIO.c
 *        \brief  Digital Input Output Driver
 *      \details  Digital Input Output Driver source file
---------------------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/
#include "DIO.h"

/*---------------------------------------------------------------------------------------------------------------------
*  LOCAL MACROS CONSTANT\FUNCTION
---------------------------------------------------------------------------------------------------------------------*/
#define PIN_MAX_SIZE 8u
#define PORTE_SIZE 6u
#define PORTF_SIZE 5u
#define ALL_PORT_OFFSET 0x3FC

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL FUNCTIONS
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
DIO_LevelType DIO_ReadChannel(DIO_ChannelType ChannelId)
{
    volatile uint32 * GPIOX_DATA;
    uint8 PortId = ChannelId<PinE0?ChannelId/PIN_MAX_SIZE:(ChannelId>=PinF0?PORTF:PORTE);
    ChannelId = ChannelId<PinE0?ChannelId%PIN_MAX_SIZE:(ChannelId>=PinF0?ChannelId-PinF0:ChannelId-PinE0);
    GPIOX_DATA = (volatile uint32*)(GPIO_ADDRESS(PortId)+((1<<ChannelId)<<2));
    //return  (*GPIOX_DATA)>>ChannelId?(DIO_LevelType)(HIGH):(DIO_LevelType)(LOW);
	return  ((*GPIOX_DATA)>>ChannelId)&0x1;
	
}
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
void DIO_WriteChannel(DIO_ChannelType ChannelId,DIO_LevelType Level)
{
    volatile uint32 * GPIOX_DATA;
    uint8 PortId = ChannelId<PinE0?ChannelId/PIN_MAX_SIZE:(ChannelId>=PinF0?PORTF:PORTE);
    ChannelId = ChannelId<PinE0?ChannelId%PIN_MAX_SIZE:(ChannelId>=PinF0?ChannelId-PinF0:ChannelId-PinE0);
    GPIOX_DATA = (volatile uint32*)(GPIO_ADDRESS(PortId)+((1<<ChannelId)<<2));
    *GPIOX_DATA = Level==HIGH?0xFF:0x0;
}
/******************************************************************************
* \Syntax          : DIO_PortLevelType DIO_ReadPort(DIO_PortType PortId)                                      
* \Description     : Read DIO port value which is value from 0 to 255                                                                                                           
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : PortId                      
* \Parameters (out): None                                                      
* \Return value:   : port level
*******************************************************************************/
DIO_PortLevelType DIO_ReadPort(DIO_PortType PortId)
{
    volatile uint32 * GPIOX_DATA;
    GPIOX_DATA = (volatile uint32*)(GPIO_ADDRESS(PortId)+ALL_PORT_OFFSET);
    if(*GPIOX_DATA != ALL_OFF && *GPIOX_DATA != ALL_ON && *GPIOX_DATA != LOWER_ON && *GPIOX_DATA != HIGHER_ON)
        return DIFFERENT_COMBINATION;
    return (*GPIOX_DATA);
}
/******************************************************************************
* \Syntax          : void DIO_WritePort(DIO_PortType PortId,DIO_PortLevelType Level)                                      
* \Description     : write port value using bit masking method.               
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : portId , port level                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void DIO_WritePort(DIO_PortType PortId,DIO_PortLevelType Level)
{
    volatile uint32 * GPIOX_DATA;
    GPIOX_DATA = (volatile uint32*)(GPIO_ADDRESS(PortId)+ALL_PORT_OFFSET);
    (*GPIOX_DATA) = Level;
}
/******************************************************************************
* \Syntax          : DIO_LevelType DIO_FlipChannel(DIO_ChannelType channelId)                                      
* \Description     : toggle channel level                                     
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : channelId                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
DIO_LevelType DIO_FlipChannel(DIO_ChannelType ChannelId)
{
    volatile uint32 * GPIOX_DATA;
    uint8 PortId = ChannelId<PinE0?ChannelId/PIN_MAX_SIZE:(ChannelId>=PinF0?PORTF:PORTE);
    ChannelId = ChannelId<PinE0?ChannelId%PIN_MAX_SIZE:(ChannelId>=PinF0?ChannelId-PinF0:ChannelId-PinE0);
    GPIOX_DATA = (volatile uint32*)(GPIO_ADDRESS(PortId)+((1<<ChannelId)<<2));
    (*GPIOX_DATA) ^= ALL_ON; 
}