/*---------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
---------------------------------------------------------------------------------------------------------------------*/
/**        \file  SystemClock.c
 *        \brief  System Clock Driver
 *
 *      \details  Configure System Clock according to user Configurations
---------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/
#include "SystemClock.h"
#include "Bit_Math.h"

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA TYPES AND STRUCTURES
---------------------------------------------------------------------------------------------------------------------*/
typedef struct
{
    uint32 MOSCDIS  :1;
    uint32          :3;
    uint32 OSCSRC   :2;
    uint32 XTAL     :5;
    uint32 BYPASS   :1;
    uint32          :1;
    uint32 PWRDN    :1;
    uint32          :2;
    uint32 PWMDIV   :3;
    uint32 USEPWMDIV:1;
    uint32          :1;
    uint32 USESYSDIV:1;
    uint32 SYSDIV   :4;
    uint32 ACG      :1;
    uint32          :4;
}RCC_BITFIELD;

typedef union 
{
    uint32 Reg;
    RCC_BITFIELD B;
}RCC_TAG;

/*---------------------------------------------------------------------------------------------------------------------
 *  LOCAL MACROS CONSTANT\FUNCTION
---------------------------------------------------------------------------------------------------------------------*/
#define PLLLRIS (6)
#define RIS (*(volatile uint32*)0x400FE050)
#define RCC (*(volatile RCC_TAG*)0x400FE060)
#define RCC_REG (*(volatile uint32*)0x400FE060)
/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA 
---------------------------------------------------------------------------------------------------------------------*/
extern const SystemClock_ConfigurationType ClockConfig;

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL FUNCTIONS
---------------------------------------------------------------------------------------------------------------------*/
/******************************************************************************
* \Syntax          : void SystemClock_Init(void)                                    
* \Description     : Initialize the system clock with the global configurations by change configuration 
*                   registers.                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void SystemClock_Init(void)
{
    if(ClockConfig.ClockSoruce== MOSC_Clock)
		{
        RCC.B.MOSCDIS = 1; //enable MOSC.
    }
		if(ClockConfig.PLLState == PLL)//required
    {
        /*setting bypass bit and clear usesys bit*/
        RCC.B.BYPASS = 1;
        //RCC.B.USESYSDIV = 0;
				
				CLEAR_BIT(RCC_REG,22);
				
        /*select XTAL value , select oscillating source and clear PWRDN bit*/
        RCC.B.XTAL = ClockConfig.XTALValue;
        RCC.B.OSCSRC = ClockConfig.ClockSoruce;
        RCC.B.PWRDN = 0;

        /*select the disred divition factor then set usesysdiv bit*/
        RCC.B.SYSDIV = ClockConfig.DivFactor;
				//RCC_REG |= (0x07800000&(ClockConfig.DivFactor<<23));
				SET_BIT(RCC_REG,22);
				//RCC.B.USESYSDIV=1;
        while(((RIS>>PLLLRIS)&0x1)==0);/*wait untill PLL is locked*/
        /*enable bypass to use PLL*/
        RCC.B.BYPASS =0;
    }
    else
    {
        /* select the clock source and set BYPASS to disable pll*/
        RCC.B.BYPASS = 1;
        RCC.B.OSCSRC = ClockConfig.ClockSoruce;
				
				//RCC_REG |= (0x07800000&(ClockConfig.DivFactor<<23));
				RCC.B.SYSDIV = ClockConfig.DivFactor;
				RCC.B.USESYSDIV = 1;
		
    }
}