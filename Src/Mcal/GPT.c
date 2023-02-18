/*---------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
---------------------------------------------------------------------------------------------------------------------*/
/**        \file  GPT.c
 *        \brief  GPT Driver
 *
 *      \details  Configure GPT according to user Configurations
---------------------------------------------------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/
#include "GPT.h"

/*---------------------------------------------------------------------------------------------------------------------
 *  LOCAL MACROS CONSTANT\FUNCTION
---------------------------------------------------------------------------------------------------------------------*/
#define RCGCTIMER                   (*(volatile uint32*)0x400FE604)/*ch0 to ch5 clock gate enable*/
#define RCGCWTIMER                  (*(volatile uint32*)0x400FE65C)/*ch6 to ch11 clock gate enable*/

#define CAllBACKFUNCTIONSSIZE       24u
#define TIMERBASEADDRESS            (0x40030000)
/*Timer registers Function like macros*/
#define GPTMCFG(ChannelId)          (*(volatile uint32*)((TIMERBASEADDRESS+(ChannelId*0x1000))))
#define GPTMTAMR(ChannelId)         (*(volatile uint32*)((TIMERBASEADDRESS+(ChannelId*0x1000)+0x004)))
#define GPTMTBMR(ChannelId)         (*(volatile uint32*)((TIMERBASEADDRESS+(ChannelId*0x1000)+0x008)))
#define GPTMCTL(ChannelId)          (*(volatile uint32*)((TIMERBASEADDRESS+(ChannelId*0x1000)+0x00C)))
#define GPTMSYNC(ChannelId)         (*(volatile uint32*)((TIMERBASEADDRESS+(ChannelId*0x1000)+0x010)))
#define GPTMIMR(ChannelId)          (*(volatile uint32*)((TIMERBASEADDRESS+(ChannelId*0x1000)+0x018)))
#define GPTMRIS(ChannelId)          (*(volatile uint32*)((TIMERBASEADDRESS+(ChannelId*0x1000)+0x01C)))
#define GPTMMIS(ChannelId)          (*(volatile uint32*)((TIMERBASEADDRESS+(ChannelId*0x1000)+0x020)))
#define GPTMICR(ChannelId)          (*(volatile uint32*)((TIMERBASEADDRESS+(ChannelId*0x1000)+0x024)))
#define GPTMTAILR(ChannelId)        (*(volatile uint32*)((TIMERBASEADDRESS+(ChannelId*0x1000)+0x028)))
#define GPTMTBILR(ChannelId)        (*(volatile uint32*)((TIMERBASEADDRESS+(ChannelId*0x1000)+0x02C)))
#define GPTMTAMATCHR(ChannelId)     (*(volatile uint32*)((TIMERBASEADDRESS+(ChannelId*0x1000)+0x030)))
#define GPTMTBMATCHR(ChannelId)     (*(volatile uint32*)((TIMERBASEADDRESS+(ChannelId*0x1000)+0x034)))
#define GPTMTAPR(ChannelId)         (*(volatile uint32*)((TIMERBASEADDRESS+(ChannelId*0x1000)+0x038)))
#define GPTMTBPR(ChannelId)         (*(volatile uint32*)((TIMERBASEADDRESS+(ChannelId*0x1000)+0x03C)))
#define GPTMTAV(ChannelId)          (*(volatile uint32*)((TIMERBASEADDRESS+(ChannelId*0x1000)+0x050)))
#define GPTMTBV(ChannelId)          (*(volatile uint32*)((TIMERBASEADDRESS+(ChannelId*0x1000)+0x054)))
#define GPTMRTCPD(ChannelId)        (*(volatile uint32*)((TIMERBASEADDRESS+(ChannelId*0x1000)+0x058)))
#define GPTMTAPS(ChannelId)        (*(volatile uint32*)((TIMERBASEADDRESS+(ChannelId*0x1000)+0x05C)))
#define GPTMTBPS(ChannelId)        (*(volatile uint32*)((TIMERBASEADDRESS+(ChannelId*0x1000)+0x060)))
#define GPTMTAPV(ChannelId)        (*(volatile uint32*)((TIMERBASEADDRESS+(ChannelId*0x1000)+0x064)))
#define GPTMTBPV(ChannelId)        (*(volatile uint32*)((TIMERBASEADDRESS+(ChannelId*0x1000)+0x068)))
#define GPTMPP(ChannelId)        (*(volatile uint32*)((TIMERBASEADDRESS+(ChannelId*0x1000)+0xFC0)))

/*pins macros*/
#define TAEN                0
#define TnMR0               0
#define TnMR1               1
#define TACDIR              4
#define TASNAPS             7
#define TATOIM              0
#define GPTMCFG0            0
#define GPTMCFG1            1
#define GPTMCFG2            2






/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA
---------------------------------------------------------------------------------------------------------------------*/
GPT_PtrToCBFunc callBack_ChannelsArray[CAllBACKFUNCTIONSSIZE]=
{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
,NULL,NULL,NULL,NULL};
/*call back pointers for the predef timers*/
GPT_PtrToCBFunc callBack_100us_32 = NULL;
GPT_PtrToCBFunc callBack_1us_16 = NULL;
GPT_PtrToCBFunc callBack_1us_24 = NULL;
GPT_PtrToCBFunc callBack_1us_32 = NULL;
// GPT_PtrToCBFunc callBack_CH_1B = NULL;
// GPT_PtrToCBFunc callBack_CH_2A = NULL;
// GPT_PtrToCBFunc callBack_CH_2B = NULL;
// GPT_PtrToCBFunc callBack_CH_3A = NULL;
// GPT_PtrToCBFunc callBack_CH_3B = NULL;
// GPT_PtrToCBFunc callBack_CH_4A = NULL;
// GPT_PtrToCBFunc callBack_CH_4B = NULL;
// GPT_PtrToCBFunc callBack_CH_5A = NULL;
// GPT_PtrToCBFunc callBack_CH_5B = NULL;
// GPT_PtrToCBFunc callBack_CH_6A = NULL;
// GPT_PtrToCBFunc callBack_CH_6B = NULL;
// GPT_PtrToCBFunc callBack_CH_7A = NULL;
// GPT_PtrToCBFunc callBack_CH_7B = NULL;
// GPT_PtrToCBFunc callBack_CH_8A = NULL;
// GPT_PtrToCBFunc callBack_CH_8B = NULL;
// GPT_PtrToCBFunc callBack_CH_9A = NULL;
// GPT_PtrToCBFunc callBack_CH_9B = NULL;
// GPT_PtrToCBFunc callBack_CH_10A = NULL;
// GPT_PtrToCBFunc callBack_CH_10B = NULL;
// GPT_PtrToCBFunc callBack_CH_11A = NULL;
// GPT_PtrToCBFunc callBack_CH_11B = NULL;

#define GPTMCFG_R 		(*(volatile uint32*)0x40030000)
#define GPTMTAMR_R 		(*(volatile uint32*)0x40030004)
	

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL FUNCTIONS
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
void GPT_Init(const GPT_ConfigurationType* ConfigPtr)
{
    GPT_ChannelType ChannelId;
    GPT_ModeType    ChannelMode;
    GPT_TickFrequencyType  FreqValue;//predefined values to select from.
    GPT_ValueType           MAXTickValue;//Value type 16 or 32 or 64 , defined in cfg.h                             
    GPT_PtrToCBFunc         notificaionPtr;
    uint8                  prescaler_8;
    uint16                  prescaler_16;
    uint8 ConfigItr ;
		unsigned long volatile delay;
    for(ConfigItr = 0;ConfigItr<MAX_GPT_CONFIG_SIZE;ConfigItr++)
    {
        /*Parse the structure content*/
        ChannelId = ConfigPtr[ConfigItr].ChannelId;
        ChannelMode = ConfigPtr[ConfigItr].ChannelMode;
        FreqValue = ConfigPtr[ConfigItr].FreqValue;
        MAXTickValue = ConfigPtr[ConfigItr].MAXTickValue;
        notificaionPtr = ConfigPtr[ConfigItr].notificaionPtr;
        
        /*Configuration of System Clock is done in app layer according to user configuration
        so the frequency in timer is based on this configuration*/
        
        /*Enable clock gate*/
        /*calculate the prescaler value*/
        if(ChannelId<=CH5)
        {
            SET_BIT(RCGCTIMER,ChannelId);
						delay = RCGCTIMER;
            prescaler_8 = (SystemClockProvided*1000000 / FreqValue)-1; 
        }
        else 
        {
						
            SET_BIT(RCGCWTIMER,ChannelId-CH6);	
						delay = RCGCWTIMER;					
            prescaler_16 = (SystemClockProvided*1000000 / FreqValue)-1;
        }
        
        switch (ChannelMode)
        {
        case GPT_PERIODIC:
        case GPT_ONESHOT:
            /*Disable timer*/
            CLEAR_BIT(GPTMCTL(ChannelId),TAEN);
            /*clear timer configuration register*/
            GPTMCFG(ChannelId) = 0;
            /* set don't concatinate A,B timers*/
            
						SET_BIT(GPTMCFG(ChannelId),GPTMCFG2);
            CLEAR_BIT(GPTMCFG(ChannelId),GPTMCFG0);
            CLEAR_BIT(GPTMCFG(ChannelId),GPTMCFG1);
            
            /*Timer A*/
            if(ChannelMode==GPT_PERIODIC)
            {
                CLEAR_BIT(GPTMTAMR(ChannelId),TnMR0);
                SET_BIT(GPTMTAMR(ChannelId),TnMR1);
            }
            else/*one-shot*/
            {
							
                SET_BIT(GPTMTAMR(ChannelId),TnMR0);
                CLEAR_BIT(GPTMTAMR(ChannelId),TnMR1);
							
							//GPTMTAMR_R |=	0x1; 
            }
            /*select count direction*/
            CLEAR_BIT(GPTMTAMR(ChannelId),TACDIR);//Count down.
            
            /*set prescaler value */
            if(ChannelId<=CH5)
            {
                GPTMTAPR(ChannelId) = prescaler_8;
            }
            else
            {
                GPTMTAPR(ChannelId) = prescaler_16;
            }
            /*Enable snapshot to use it later to get the remaining and elapsed time*/
            SET_BIT(GPTMTAMR(ChannelId),TASNAPS);


            /*enable time out interrupt on timer A*/
            SET_BIT(GPTMIMR(ChannelId),TATOIM);

            /*register the interrupt callback function*/
            callBack_ChannelsArray[ChannelId*2] = notificaionPtr;


            break;

        default:
            break;
        }

    }
    /* Predeifned timers configuration will be on Timer A
    *  16 bit is on Channel 5
    *  24 , 32 is on Channel 11
    */
    switch (Predef)
    {
    case GPT_PREDEF_100US_32BIT:
        ChannelId = CH11;
				SET_BIT(RCGCWTIMER,ChannelId-CH6);	
				delay = RCGCWTIMER;
        CLEAR_BIT(GPTMCTL(ChannelId),TAEN);
        /*clear timer configuration register*/
        GPTMCFG(ChannelId) = 0;
        /* set don't concatinate A,B timers*/
        SET_BIT(GPTMCFG(ChannelId),GPTMCFG2);
        CLEAR_BIT(GPTMCFG(ChannelId),GPTMCFG0);
        CLEAR_BIT(GPTMCFG(ChannelId),GPTMCFG1);
        /*periodic*/
        CLEAR_BIT(GPTMTAMR(ChannelId),TnMR0);
        SET_BIT(GPTMTAMR(ChannelId),TnMR1);        
        CLEAR_BIT(GPTMTAMR(ChannelId),TACDIR);//Count down.
        
        /*with frequency 16 MHZ as system clock and prescaler value of 3 -> /4 
        then to count 100 us we need 400 tick */
        prescaler_16 = 3;
        GPTMTAPR(ChannelId) = prescaler_16;

        /*Enable snapshot to use it later to get the remaining and elapsed time*/
        SET_BIT(GPTMTAMR(ChannelId),TASNAPS);


        /*enable time out interrupt on timer A*/
        SET_BIT(GPTMIMR(ChannelId),TATOIM);

        /*register the interrupt callback function*/
        callBack_100us_32 = Predef_100US_32_handle;

        /*Load Start Value of timer in GPTMTnILR.*/
        GPTMTAILR(ChannelId) = 400u;
        /*Enable timer A to start count*/
        SET_BIT(GPTMCTL(ChannelId),TAEN);
        break;

    case GPT_PREDEF_1US_32BIT:
    case GPT_PREDEF_1US_24BIT:
        ChannelId = CH11;
        SET_BIT(RCGCWTIMER,ChannelId-CH6);	
				delay = RCGCWTIMER;
				CLEAR_BIT(GPTMCTL(ChannelId),TAEN);
        /*clear timer configuration register*/
        GPTMCFG(ChannelId) = 0;
        /* set don't concatinate A,B timers*/
        SET_BIT(GPTMCFG(ChannelId),GPTMCFG2);
        CLEAR_BIT(GPTMCFG(ChannelId),GPTMCFG0);
        CLEAR_BIT(GPTMCFG(ChannelId),GPTMCFG1);
        /*periodic*/
        CLEAR_BIT(GPTMTAMR(ChannelId),TnMR0);
        SET_BIT(GPTMTAMR(ChannelId),TnMR1);        
        CLEAR_BIT(GPTMTAMR(ChannelId),TACDIR);//Count down.
        
        
        /*Enable snapshot to use it later to get the remaining and elapsed time*/
        SET_BIT(GPTMTAMR(ChannelId),TASNAPS);


        /*enable time out interrupt on timer A*/
        SET_BIT(GPTMIMR(ChannelId),TATOIM);
        
        if(Predef == GPT_PREDEF_1US_32BIT)    
            /*register the interrupt callback function*/
            callBack_1us_32 = Predef_1US_32_handle;
        else if(Predef == GPT_PREDEF_1US_24BIT)
            /*register the interrupt callback function*/
            callBack_1us_24 = Predef_1US_24_handle;

        /*with frequency 16 MHZ as system clock then to count 1us we need 16 tick */
        /*Load Start Value of timer in GPTMTnILR.*/
        GPTMTAILR(ChannelId) = 16u;
        /*Enable timer A to start count*/
        SET_BIT(GPTMCTL(ChannelId),TAEN);
        
        break;
    case GPT_PREDEF_1US_16BIT:
        ChannelId = CH5;
        SET_BIT(RCGCTIMER,ChannelId);	
				delay = RCGCTIMER;
				CLEAR_BIT(GPTMCTL(ChannelId),TAEN);
        /*clear timer configuration register*/
        GPTMCFG(ChannelId) = 0;
        /* set don't concatinate A,B timers*/
        SET_BIT(GPTMCFG(ChannelId),GPTMCFG2);
        CLEAR_BIT(GPTMCFG(ChannelId),GPTMCFG0);
        CLEAR_BIT(GPTMCFG(ChannelId),GPTMCFG1);
        /*periodic*/
        CLEAR_BIT(GPTMTAMR(ChannelId),TnMR0);
        SET_BIT(GPTMTAMR(ChannelId),TnMR1);        
        CLEAR_BIT(GPTMTAMR(ChannelId),TACDIR);//Count down.
        
        
        /*Enable snapshot to use it later to get the remaining and elapsed time*/
        SET_BIT(GPTMTAMR(ChannelId),TASNAPS);


        /*enable time out interrupt on timer A*/
        SET_BIT(GPTMIMR(ChannelId),TATOIM);

        /*register the interrupt callback function*/
        callBack_1us_16 = Predef_1US_16_handle;

        /*with frequency 16 MHZ as system clock then to count 1us we need 16 tick */
        /*Load Start Value of timer in GPTMTnILR.*/
        GPTMTAILR(ChannelId) = 16u;
        /*Enable timer A to start count*/
        SET_BIT(GPTMCTL(ChannelId),TAEN);
        break;
    default:
        break;
    }
}

/******************************************************************************
* \Syntax          : void GPT_DisableNotification(GPT_ChannelType ChannelId)                                      
* \Description     : Disable interrupt for timer channel 
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : ChannelId  channel number to disable its interrupt                  
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void GPT_DisableNotification(GPT_ChannelType ChannelId)
{
    /*disable time out interrupt on timer A*/
    CLEAR_BIT(GPTMIMR(ChannelId),TATOIM);

}
/******************************************************************************
* \Syntax          : void GPT_EnableNotification(GPT_ChannelType ChannelId)                                      
* \Description     : Enable interrupt for timer channel 
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : ChannelId  channel number to enable its interrupt                  
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void GPT_EnableNotification(GPT_ChannelType ChannelId)
{
    /*enable time out interrupt on timer A*/
    SET_BIT(GPTMIMR(ChannelId),TATOIM);

}
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
void GPT_StartTimer(GPT_ChannelType ChannelId,GPT_ValueType TargetTime)
{
    /*Load Start Value of timer in GPTMTnILR.*/
    GPTMTAILR(ChannelId) = TargetTime;
    /*Enable timer A to start count*/
    SET_BIT(GPTMCTL(ChannelId),TAEN);
}

/******************************************************************************
* \Syntax          : void GPT_StopTimer(GPT_ChannelType ChannelId)                                      
* \Description     : Start the timer at channel with target time ticks to times out after                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : GPT_ChannelType ChannelId channel to start timer at                   
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void GPT_StopTimer(GPT_ChannelType ChannelId,GPT_ValueType TargetTime)
{
    /*Disable timer*/
    CLEAR_BIT(GPTMCTL(ChannelId),TAEN);
    /*disable time out interrupt on timer A*/
    CLEAR_BIT(GPTMIMR(ChannelId),TATOIM);

}

/******************************************************************************
* \Syntax          : void GPT_NotificationChannel(GPT_ChannelType ChannelId,GPT_PtrToCBFunc CB_ptr)                                      
* \Description     : Regsiter the channelId timer ISR with CB_ptr call back function to call 
                    handler function in app layer from the Mcal layer                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : GPT_ChannelType ChannelId channel to register CB_ptr at. CB_ptr to the function in APP layer.      
                    TimerType whether timerA or TimerB             
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
//void GPT_NotificationChannelRegister(GPT_ChannelType ChannelId,GPT_ChannelTimerType TimerType,GPT_PtrToCBFunc CB_ptr);



/*---------------------------------------------------------------------------------------------------------------------
 *  GPT channel ISRs
---------------------------------------------------------------------------------------------------------------------*/
void TIMER0A_Handler(void)
{
    if(callBack_ChannelsArray[0] != NULL)
    {
        callBack_ChannelsArray[0]();
    }
}
void TIMER1A_Handler(void)
{
    if(callBack_ChannelsArray[1] != NULL)
    {
        callBack_ChannelsArray[1]();
    }
}
void TIMER2A_Handler(void)
{
    if(callBack_ChannelsArray[2] != NULL)
    {
        callBack_ChannelsArray[2]();
    }
}
void TIMER3A_Handler(void)
{
    if(callBack_ChannelsArray[3] != NULL)
    {
        callBack_ChannelsArray[3]();
    }
}
void TIMER4A_Handler(void)
{
    if(callBack_ChannelsArray[4] != NULL)
    {
        callBack_ChannelsArray[4]();
    }
}
void TIMER5A_Handler(void)
{
    if(callBack_ChannelsArray[5] != NULL)
    {
        callBack_ChannelsArray[5]();
    }
    else if(callBack_1us_16 !=NULL)
    {
        callBack_1us_16();
    }
    else{}
}
void TIMER0B_Handler(void);
void TIMER1B_Handler(void);
void TIMER2B_Handler(void);
void TIMER3B_Handler(void);
void TIMER4B_Handler(void);
void TIMER5B_Handler(void);
void WTIMER0A_Handler(void)
{
    if(callBack_ChannelsArray[6] != NULL)
    {
        callBack_ChannelsArray[6]();
    }
}
void WTIMER1A_Handler(void)
{
    if(callBack_ChannelsArray[7] != NULL)
    {
        callBack_ChannelsArray[7]();
    }
}
void WTIMER2A_Handler(void)
{
    if(callBack_ChannelsArray[8] != NULL)
    {
        callBack_ChannelsArray[8]();
    }
}
void WTIMER3A_Handler(void)
{
    if(callBack_ChannelsArray[9] != NULL)
    {
        callBack_ChannelsArray[9]();
    }
}
void WTIMER4A_Handler(void)
{
    if(callBack_ChannelsArray[10] != NULL)
    {
        callBack_ChannelsArray[10]();
    }
}
void WTIMER5A_Handler(void)
{
    if(callBack_ChannelsArray[11] != NULL)
    {
        callBack_ChannelsArray[11]();
    }
    else if(callBack_100us_32 !=NULL)
    {
        callBack_100us_32();
    }
    else if(callBack_1us_24 !=NULL)
    {
        callBack_1us_24();
    }
    else if(callBack_1us_32 !=NULL)
    {
        callBack_1us_32();
    }
    else{}
}
void WTIMER0B_Handler(void);
void WTIMER1B_Handler(void);
void WTIMER2B_Handler(void);
void WTIMER3B_Handler(void);
void WTIMER4B_Handler(void);
void WTIMER5B_Handler(void);