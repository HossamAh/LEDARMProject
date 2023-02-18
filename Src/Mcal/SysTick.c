/*---------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
---------------------------------------------------------------------------------------------------------------------*/
/**        \file  SysTick.c
 *        \brief  SysTick Driver
 *
 *      \details  Configure SysTick according to user Configurations
---------------------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/
#include "SysTick.h"
#include "SystemClock.h"

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA TYPES AND STRUCTURES
---------------------------------------------------------------------------------------------------------------------*/
typedef struct 
{
    uint32 ENABLE   :1;
    uint32 INTEN    :1;
    uint32 CLK_SRC  :1;
    uint32          :13;
    uint32 COUNT    :1;
    uint32          :15;
}STCTRL_BITFIELD;

typedef union 
{
    uint32 Reg;
    STCTRL_BITFIELD B;
}STCTRL_TAG;



/*---------------------------------------------------------------------------------------------------------------------
 *  LOCAL MACROS CONSTANT\FUNCTION
---------------------------------------------------------------------------------------------------------------------*/
#define NULL ((void *)0)
#define PIOSC4_SECONDTICKS (4000000u) //ticks to 1 second
#define MAXTICKS (0x02FFFFFF)

#define STRELOAD (*(volatile uint32*)0xE000E014)
#define STCTRL (*(volatile STCTRL_TAG*)0xE000E010)
#define STCURRENT (*(volatile uint32*)0xE000E018)


/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA
---------------------------------------------------------------------------------------------------------------------*/
CallBack_type callBack_Ptr = NULL;
extern const SysTick_ConfigurationType SysTick_Config;

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL FUNCTION
---------------------------------------------------------------------------------------------------------------------*/
/******************************************************************************
* \Syntax          : void Register_CallBack(CallBack_type CB_ptr)                                    
* \Description     : Initialize the SysTick ISR callback function with  CB_ptr                                                                            
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : CALLBACK_type CB_ptr  pointer to the callback function to be called from ISR                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void Register_CallBack(CallBack_type CB_ptr)
{
    if(CB_ptr != NULL)
    {
        callBack_Ptr = CB_ptr;
    }

}
/******************************************************************************
* \Syntax          : void SysTick_Handler(void)                                   
* \Description     : Handler function of SysTick interrupt.                                                                            
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void SysTick_Handler(void)
{
    if(callBack_Ptr !=NULL )
    {
        callBack_Ptr();
			  STCTRL.B.COUNT=0;/*clear interrupt flag*/
    }
		
}
/******************************************************************************
* \Syntax          : void SysTick_init(void)                                   
* \Description     : Initialize the SysTick with the global configurations by change configuration 
*                   registers. timeout after number of seconds in configuration struct.                                                                         
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void SysTick_init(void)
{
    uint32 numberOfTicks;
    if(SysTick_Config.CLKSRC == PIOSC4_Clock)
    {
        /*frequency of PIOSC/4 = 4MHZ*/
        numberOfTicks = PIOSC4_SECONDTICKS*SysTick_Config.NumberOfSeconds;
    }
    else
    {
        numberOfTicks = SysTick_Config.NumberOfSeconds*(SysTick_Config.Frequency*1000000);
        //SystemClock_Init();
    }
    numberOfTicks %= MAXTICKS;//guard
    /*Load the preload value*/
    STRELOAD = numberOfTicks - 1;
    /*clear current and clear COUNT flag*/
    STCURRENT = 0;
    STCTRL.B.COUNT = 0;

    /*Config the control register */
    STCTRL.B.CLK_SRC = SysTick_Config.CLKSRC;
    STCTRL.B.INTEN = 1;
    STCTRL.B.ENABLE = 1;
}

/******************************************************************************
* \Syntax          : void SysTick_init_tick(uint32 ticks)                                   
* \Description     : Initialize the SysTick with the global configurations by change configuration 
*                   registers and with spcific ticks less than 2pow 24.timesout after the ticks in argument                                                          
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : uint32 ticks  number of ticks to time out after.                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void SysTick_init_tick(uint32 ticks)
{
    if(SysTick_Config.CLKSRC == System_Clock)
    {
        SystemClock_Init();
    }
    /*Load the preload value*/
    STRELOAD = ticks - 1;
    /*clear current and clear COUNT flag*/
    STCURRENT = 0;
    STCTRL.B.COUNT = 0;

    /*Config the control register */
    STCTRL.B.CLK_SRC = SysTick_Config.CLKSRC;
    STCTRL.B.INTEN = 1;
    STCTRL.B.ENABLE = 1;
}
/******************************************************************************
* \Syntax          : void SysTick_Stop(void)                                    
* \Description     : Stop the SysTick Timer and disable its interrupt and reset all its registers.                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void SysTick_Stop(void)
{
    STCTRL.B.ENABLE=0;
    STCTRL.B.INTEN=0;
    STCTRL.B.COUNT=0;
}
