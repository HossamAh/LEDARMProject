/*---------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
---------------------------------------------------------------------------------------------------------------------*/
/**        \file  main.c
 *        \brief  Main file for Led Flash with PWM mode
 *      \details  main file for led flash with PWM mode from user input by 2 buttons
---------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/
#include "IntCtrl.h"
#include "port.h"
#include "SysTick.h"
#include "Led.h"
#include "Buttons.h"
#include "SystemClock.h"
#include "GPT.h"

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA TYPES AND STRUCTURES
---------------------------------------------------------------------------------------------------------------------*/
typedef enum
{
	Ideal_State,
	Config_onTime_State,
	Config_offTime_State,
	OnTime_State,
	OffTime_State
}System_States;

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL FUNCTION PROTOTYPES
---------------------------------------------------------------------------------------------------------------------*/
void handle_SysTick_ISR(void);
void handle_Buttons_ISR(void);
void Timer0A_HandleFucntion(void);
void Predef_HandleFunction(void);
/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA 
---------------------------------------------------------------------------------------------------------------------*/
extern const Port_Cfg_Type Port_CONFIGURATIONS[MAX_PIN_NUMBER];
uint32 onTime,offTime,currentTargetTime;
uint8 currentState = Ideal_State;
extern const GPT_ConfigurationType GPT_CONFIGURATIONS[MAX_GPT_CONFIG_SIZE];	

int main(void)
{
	IntCrtl_Init();
	Port_Init(Port_CONFIGURATIONS);
	PortEnable_Notificaion(PORTF,handle_Buttons_ISR);
	Register_CallBack(handle_SysTick_ISR);
	SystemClock_Init();
	/* 0x40000000, 0x400FFFFF  memory map before debug*/
	GPT_Init(GPT_CONFIGURATIONS);
	while(1)
{
	switch (currentState)
	{
	case OnTime_State:/*change configuration can be triggered from this state*/
		Led_On();
		break;
	case OffTime_State:/*change configuration can be triggered from this state*/
		Led_Off();
		break;
	default:
		break;
	}

}
return 0;
}
/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL FUNCTION 
---------------------------------------------------------------------------------------------------------------------*/
/******************************************************************************
* \Syntax          : void handle_SysTick_ISR(void)                                      
* \Description     : function that is called from SysTick ISR to handle timer interrupt
					to start off period when on period is over and start on time agian after on time is over
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void handle_SysTick_ISR(void)
{
	static uint32 numOfseconds = 0;
	numOfseconds++;
	if(numOfseconds == currentTargetTime)
	{	
		numOfseconds=0;
		SysTick_Stop();
		switch (currentState)
		{
		case OnTime_State:
			currentTargetTime=offTime;
			currentState = OffTime_State;
			SysTick_init();
			break;
		case OffTime_State:
			/*start again with the same configuration */
			currentTargetTime = onTime;
			currentState = OnTime_State;
			SysTick_init();
			break;
		default:
			break;
		}
	}
}
/******************************************************************************
* \Syntax          : void handle_Buttons_ISR(void)                                      
* \Description     : called from Buttons Port ISR to change the state of system according to user inputs.                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void handle_Buttons_ISR(void)
{
	if(GPIOMIS(PORTF)&(1<<0))
	{
		/*confirm button */
		switch (currentState)
		{
		case Ideal_State:
			onTime =0;
			offTime =0;
			currentTargetTime = 0;
			Led_Off();
			SysTick_Stop();
			currentState = Config_onTime_State;
			break;
		case Config_onTime_State:
			currentState = Config_offTime_State;
			break;
		case Config_offTime_State:
			currentTargetTime = onTime;
			SysTick_init();
			currentState = OnTime_State;
			break;
		case OnTime_State:
		case OffTime_State:
			/*start new configuration cycle*/
			Led_Off();
			SysTick_Stop();
			currentTargetTime=0;
			onTime=0;
			offTime=0;
			currentState = Config_onTime_State;
			break;
		
		default:
			break;
		}
		GPIOICR(PORTF) |=(1<<0); 
	}
	else if(GPIOMIS(PORTF)&(1<<4))
	{
		/*Inc button */
		/*as an indication of configuration mode the led will toggles with each inc button click*/
		switch (currentState)
		{
		case Config_onTime_State:
			Led_Toggle();
			onTime++;
			break;
		case Config_offTime_State:
			Led_Toggle();
			offTime++;
			break;
		default:
			break;
		}
		GPIOICR(PORTF) |=(1<<4); 
	}
}

void Timer0A_HandleFucntion(void){}
void Predef_HandleFunction(void){}



