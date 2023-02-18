/*---------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
---------------------------------------------------------------------------------------------------------------------*/
/**        \file  port.c
 *        \brief  GPIO PORT Driver
 *
 *      \details  Configure ALL GPIO PORTS according to user Configurations
---------------------------------------------------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/
#include "Std_Types.h"
#include "port.h"
#include "Mcu_Hw.h"


/*---------------------------------------------------------------------------------------------------------------------
 *  LOCAL MACROS CONSTANT\FUNCTION
---------------------------------------------------------------------------------------------------------------------*/
#define NULL                    ((void*)0)
#define UNLOCKVALUE             (0x4C4F434B)
#define RCGCGPIO                (*((volatile uint32 *)0x400FE608))

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA
---------------------------------------------------------------------------------------------------------------------*/
Port_INT_callBack callBack_PtrA = NULL;
Port_INT_callBack callBack_PtrB = NULL;
Port_INT_callBack callBack_PtrC = NULL;
Port_INT_callBack callBack_PtrD = NULL;
Port_INT_callBack callBack_PtrE = NULL;
Port_INT_callBack callBack_PtrF = NULL;
/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL FUNCTIONS
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
void Port_Init(const Port_Cfg_Type *ConfigPtr)
{
    unsigned long volatile delay;
    uint8 pinsItr = 0;
    /* configuration structure content variables defination*/
    Port_PinModeType PinMode;
    Port_PinDirectionType Direction;
    Port_PinInternalAttachType InternalAttach;
    Port_PinOutputCurrentType OutputCurrent;
    Port_PinNum Pin ;
    Port_PinLevel Level;
    Port_Num Port;
    Port_Enable_Interrupt EnabelINT;
    Port_Trigger_Pulse_Type  INTPulseType;
    Port_Trigger_Level_Type INTLevelType;

    for (pinsItr = 0; pinsItr < MAX_PIN_NUMBER; pinsItr++)
    {
        PinMode = ConfigPtr[pinsItr].PinMode;
        Direction = ConfigPtr[pinsItr].PinDir;
        InternalAttach = ConfigPtr[pinsItr].InternalAttach;
        OutputCurrent = ConfigPtr[pinsItr].CurrentValue;
        Pin = ConfigPtr[pinsItr].Pin;
        Level = ConfigPtr[pinsItr].PinLevel;
        Port = ConfigPtr[pinsItr].Port;
        EnabelINT = ConfigPtr[pinsItr].Enable_INT;
        INTPulseType = ConfigPtr[pinsItr].Trigger_Pulse_Type;
        INTLevelType = ConfigPtr[pinsItr].Trigger_Level_type;
        /* Enable clock for GPIO port*/
        RCGCGPIO |= (1 << Port);
				delay = RCGCGPIO; // wait 3-5 bus cycles.
        /*unlock pin at first and allow commit at it.*/
        GPIOLOCK(Port) = UNLOCKVALUE;
        GPIOCR(Port) |= (1<<Pin); 
        /*set Direction*/
        if (Direction == INPUT)
            GPIODIR(Port) &= ~(1 << Pin);
        else
            GPIODIR(Port) |= (1 << Pin);
        
        /*set alternatives Configuration*/
        if (PinMode == ALTERNATIVE)
        {
            // TODO: replace alternative with different functions supported and configure according to.
        }
        else if (PinMode == DIGITAL)
        {
            /*clear the pin bit to work as GPIO , set for alternative function*/
            GPIOAFSEL(Port) &= ~(1 << Pin);
            /*clear the pin bit to work as GPIO , set for ADC*/
            GPIOAMSEL(Port) &= ~(1 << Pin);
            /*Enable Digital in case of digital mode*/
            GPIODEN(Port) |= (1 << Pin);
						
        }
        else if (PinMode == ANALOG)
        {
            /*TODO: configure pin for analog mode*/
        }
        else
        {
        }
        /*set drive strength*/
        switch (OutputCurrent)
        {
        case PAD_2_MA:
            GPIOR2R(Port) |= (1 << Pin);
            break;
        case PAD_4_MA:
            GPIOR4R(Port) |= (1 << Pin);
            break;
        case PAD_8_MA:
            GPIOR8R(Port) |= (1 << Pin);
            break;
        default:
            break;
        }
        /*set internal attachment for input pins*/

        switch (InternalAttach)
        {
        case PULLUP:
            GPIOPUR(Port) |= (1 << Pin);
            break;
        case PULLDOWN:
            GPIOPDR(Port) |= (1 << Pin);
            break;
        case OPENDRAIN:
            GPIOODR(Port) |= (1 << Pin);
            break;
        case NONE:
        default:
            break;
        }
    /*TODO: Adding interrupts to GPIO -> add to configuration struct, do its configurations. enable GPIO port in NVIC first at INTCTRL config struct. */
        if(PinMode == DIGITAL)
        {
            if(EnabelINT ==  ENABLE)
            {
                //enable pins interrupt to be sent to NVIC.
                GPIOIM(Port) |= (1<<Pin);
                switch (INTPulseType)
                {
                case RISING:
                    GPIOIS(Port) &= ~(1<<Pin);//edge
                    GPIOIEV(Port) |=(1<<Pin);//rising 
                    break;

                case FALLING:
                    GPIOIS(Port) &= ~(1<<Pin);//edge
                    GPIOIEV(Port) &= ~(1<<Pin);//rising 
                    break;
                
                default:
                    break;
                }

                switch (INTLevelType)
                {
                case LEVEL_HIGH:
                    GPIOIS(Port) = (1<<Pin);//level
                    GPIOIEV(Port) |=(1<<Pin);//high 
                    break;

                case LEVEL_LOW:
                    GPIOIS(Port) = (1<<Pin);//level
                    GPIOIEV(Port) &= ~(1<<Pin);//low 
                    break;
                
                default:
                    break;
                }
            }
        }
    }

}



void GPIOA_Handler(void)
{
    if(callBack_PtrA !=NULL)
        {
            callBack_PtrA();
        }
}
void GPIOB_Handler(void)
{
        if(callBack_PtrB !=NULL)
        {
            callBack_PtrB();
        }
}
void GPIOC_Handler(void)
{
        if(callBack_PtrC !=NULL)
        {
            callBack_PtrC();
        }
}
void GPIOD_Handler(void)
{
    if(callBack_PtrD !=NULL)
    {
        callBack_PtrD();
    }   
}
void GPIOE_Handler(void)
{
        if(callBack_PtrE !=NULL)
        {
            callBack_PtrE();
        }
}
void GPIOF_Handler(void)
{
        if(callBack_PtrF !=NULL)
        {
            callBack_PtrF();
        }
}
/******************************************************************************
* \Syntax          : void PortEnable_Notificaion(Port_PinNum num,Port_INT_callBack ptr)                                     
* \Description     : Assign callback function to PORT interrupt                                       
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : num the port which generate the interrupt , ptr pointer to function that will be called from ISR.                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void PortEnable_Notificaion(Port_Num num,Port_INT_callBack ptr)//ptr is writen in app layer
{
    switch (num)
    {
    case A:
        callBack_PtrA = ptr;
        break;
    case B:
        callBack_PtrB = ptr;
        break;
    case C:
        callBack_PtrC = ptr;
        break;
    case D:
        callBack_PtrD = ptr;
        break;
    case E:
        callBack_PtrE = ptr;
        break;
    case F:
        callBack_PtrF = ptr;
        break;
    
    default:
        break;
    }
}

