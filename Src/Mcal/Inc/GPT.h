/*---------------------------------------------------------------------------------------------------------------------
 *  *  FILE DESCRIPTION
 *  --------------------
 *         File:  GPT.h
 *       Module:  GPT Driver
 *  Description:  GPT Driver header file        
---------------------------------------------------------------------------------------------------------------------*/
#ifndef GPT_H
#define GPT_H
/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/
#include "GPT_Types.h"
#include "Std_Types.h"
#include "Bit_Math.h"


/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA TYPES AND STRUCTURES
---------------------------------------------------------------------------------------------------------------------*/
typedef struct 
{
    GPT_ChannelType ChannelId;
    GPT_ModeType    ChannelMode;
    GPT_TickFrequencyType  FreqValue;//predefined values to select from.
    GPT_ValueType           MAXTickValue;//Value type 16 or 32 or 64 , defined in cfg.h                             
    GPT_PtrToCBFunc         notificaionPtr;
}GPT_ConfigurationType;

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA PROTOTYPES
---------------------------------------------------------------------------------------------------------------------*/
extern const GPT_ConfigurationType GPT_CONFIGURATIONS[MAX_GPT_CONFIG_SIZE];
extern const GPT_PredefTimerValue Predef;
extern const uint16     SystemClockProvided;//in MHZ
extern GPT_PtrToCBFunc  Predef_100US_32_handle;
extern GPT_PtrToCBFunc  Predef_1US_32_handle;
extern GPT_PtrToCBFunc  Predef_1US_16_handle;
extern GPT_PtrToCBFunc  Predef_1US_24_handle;

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL FUNCTION PROTOTYPES
---------------------------------------------------------------------------------------------------------------------*/ 
/******************************************************************************
* \Syntax          : void GPT_Init(const GPT_ConfigurationType* ConfigPtr)                                      
* \Description     : initialize GPT using configuration struct bu parsing all 
*       its configurations to the GPT registers                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : ConfigPtr  pointer to GPT initalization configurations.                   
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void GPT_Init(const GPT_ConfigurationType* ConfigPtr);

/******************************************************************************
* \Syntax          : void GPT_DisableNotification(GPT_ChannelType ChannelId)                                      
* \Description     : Disable interrupt for timer channel 
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : ChannelId  channel number to disable its interrupt                  
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void GPT_DisableNotification(GPT_ChannelType ChannelId);

/******************************************************************************
* \Syntax          : void GPT_EnableNotification(GPT_ChannelType ChannelId)                                      
* \Description     : Enable interrupt for timer channel 
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : ChannelId  channel number to enable its interrupt                  
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void GPT_EnableNotification(GPT_ChannelType ChannelId);

/******************************************************************************
* \Syntax          : GPT_ValueType GPT_GetTimeElapsed(GPT_ChannelType ChannelId)                                      
* \Description     : Return the time elpased at channelId timer                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : ChannelId  the channel number to get its elapsed time.                   
* \Parameters (out): None                                                      
* \Return value:   : GPT_ValueType the value of time
*******************************************************************************/
GPT_ValueType GPT_GetTimeElapsed(GPT_ChannelType ChannelId);

/******************************************************************************
* \Syntax          : GPT_ValueType GPT_GetTimeRemaining(GPT_ChannelType ChannelId)                                      
* \Description     : Return the time remaining at channelId timer                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : ChannelId  the channel number to get its remaining time.                   
* \Parameters (out): None                                                      
* \Return value:   : GPT_ValueType the value of time
*******************************************************************************/
GPT_ValueType GPT_GetTimeRemaining(GPT_ChannelType ChannelId);


/******************************************************************************
* \Syntax          : void GPT_StartTimer(GPT_ChannelType ChannelId,GPT_ValueType TargetTime)                                      
* \Description     : Start the timer at channel with target value ticks to times out after                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : GPT_ChannelType ChannelId channel to start timer at.,GPT_ValueType TargetTime number of ticks to time out after.                   
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void GPT_StartTimer(GPT_ChannelType ChannelId,GPT_ValueType TargetTime);


/******************************************************************************
* \Syntax          : void GPT_StopTimer(GPT_ChannelType ChannelId)                                      
* \Description     : Start the timer at channel with target time ticks to times out after                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : GPT_ChannelType ChannelId channel to start timer at                   
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void GPT_StopTimer(GPT_ChannelType ChannelId,GPT_ValueType TargetTime);


/******************************************************************************
* \Syntax          : void GPT_NotificationChannel(GPT_ChannelType ChannelId,GPT_PtrToCBFunc CB_ptr)                                      
* \Description     : Regsiter the channelId timer ISR with CB_ptr call back function to call 
                    handler function in app layer from the Mcal layer                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : GPT_ChannelType ChannelId channel to register CB_ptr at. CB_ptr to the function in APP layer.                   
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void GPT_NotificationChannelRegister(GPT_ChannelType ChannelId,GPT_PtrToCBFunc CB_ptr);




/******************************************************************************
* \Syntax          : Std_ReturnType GPT_GetPredefTimerValue(GPT_PredefTimerValue predefTimer,GPT_ValueType* timeValuePtr)                                      
* \Description     : get the current timer value of the predefined timer passed 
                    and return ok or not according to whether the predef timer is enabled or not                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : predefTimer the timer to enable                    
* \Parameters (out): ptr passed by reference to return the timer value.                                                      
* \Return value:   : Std_ReturnType Ok if config is enabled and NOT_OK otherwise.
*******************************************************************************/
Std_ReturnType GPT_GetPredefTimerValue(GPT_PredefTimerValue predefTimer,GPT_ValueType* timeValuePtr);


#endif