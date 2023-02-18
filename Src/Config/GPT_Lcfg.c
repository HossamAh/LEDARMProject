/*---------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
---------------------------------------------------------------------------------------------------------------------*/
/**        \file  GPT_Lcfg.c
 *        \brief  GPTT Driver Configurations
 *
 *      \details  Contain configurations of the GPT Driver.
---------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/
#include "GPT.h"


/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA
---------------------------------------------------------------------------------------------------------------------*/
const GPT_PredefTimerValue Predef = GPT_PREDEF_100US_32BIT ;

extern void Timer0A_HandleFucntion(void);  

extern void Predef_HandleFunction(void);

GPT_PtrToCBFunc  Predef_100US_32_handle = Predef_HandleFunction;
GPT_PtrToCBFunc  Predef_1US_32_handle = NULL;
GPT_PtrToCBFunc  Predef_1US_16_handle = NULL;
GPT_PtrToCBFunc  Predef_1US_24_handle =NULL;

const GPT_ConfigurationType GPT_CONFIGURATIONS[MAX_GPT_CONFIG_SIZE]=
{
    /*ChannelId             ChannelMode         FreqValue       MAXtickValue        notification ptr*/
    {CH6,                    GPT_PERIODIC,       GPT_FREQ16MHZ,      0,                  Timer0A_HandleFucntion}
};