/*---------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
---------------------------------------------------------------------------------------------------------------------*/
/**        \file  IntCrtl.c
 *        \brief  Nested Vector Interrupt Controller Driver
 *      \details  Configure ALL MCU Exceptions according to user Configurations
---------------------------------------------------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/
#include "Std_Types.h"
#include "IntCtrl.h"
#include "Mcu_Hw.h"


/*---------------------------------------------------------------------------------------------------------------------
*  LOCAL MACROS CONSTANT\FUNCTION
---------------------------------------------------------------------------------------------------------------------*/
#define APINT_KEY           0x05FA0000
#define LOWER_ON            0x0000FFFF
#define INTERUPT_START_INDEX    16u
#define PRI_FIRST_SECTION_START   5u
#define PRI_SECOND_SECTION_START   13u
#define PRI_THIRD_SECTION_START   21u
#define PRI_FOURTH_SECTION_START   29u

#define INTCTRL_MEMORY_MANAGMENT_EN_BIT     16u
#define INTCTRL_BUS_FAULT_EN_BIT            17u
#define INTCTRL_USAGE_FAULT_EN_BIT          18u
#define INTCTRL_APINT_CONFIG_START					0x8u

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL FUNCTIONS
---------------------------------------------------------------------------------------------------------------------*/
/******************************************************************************
* \Syntax          : void IntCrtl_Init(void)                                      
* \Description     : initialize Nvic\SCB Module by parsing the Configuration 
*                    into Nvic\SCB registers                                    
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void IntCrtl_Init(void)
{
	unsigned int currentINT;
	uint8 priority;
	uint8 intCounter = 0 ;
	uint8 groupValue,subGroupValue;
        
	/*TODO Configure Grouping\SubGrouping System in APINT register in SCB*/
    APINT = APINT_KEY |(INTCTRL_PRIORITY_CONFIGURAION_TYPE<<INTCTRL_APINT_CONFIG_START);
    
    /*TODO : Assign Group\Subgroup priority in NVIC_PRIx Nvic and SCB_SYSPRIx Registers*/  
    
    while(intCounter<INTCTRL_EXCEPTION_ENABLE_SIZE)
    {
			
        currentINT = IntCTRL_CONFIGURATIONS.enableExceptions_Numbers[intCounter];
        groupValue = IntCTRL_CONFIGURATIONS.priorityGroup_Exceptions[intCounter];
        subGroupValue = IntCTRL_CONFIGURATIONS.prioritySubGroup_Exceptions[intCounter];

        
        /*Priority guard to allow priority values accroding to configurations*/
        #if (INTCTRL_PRIORITY_CONFIGURAION_TYPE == INTCTRL_PRIORITY_XXX)
                groupValue &= 0x7;
        #elif (INTCTRL_PRIORITY_CONFIGURAION_TYPE == INTCTRL_PRIORITY_XXY)
                groupValue = (groupValue<<1)&0x6;
                subGroupValue &= 0x1;
        #elif (INTCTRL_PRIORITY_CONFIGURAION_TYPE == INTCTRL_PRIORITY_XYY)
                groupValue =(groupValue<<2)&0x1;
                subGroupValue &= 0x3; 
        #elif (INTCTRL_PRIORITY_CONFIGURAION_TYPE == INTCTRL_PRIORITY_YYY)        
                groupValue &= 0;
                subGroupValue &= 0x7;
        #else
            #error INVALID PRIORITY CONFIGURATION SELECTION

        #endif
        priority = groupValue|subGroupValue;   

        if(currentINT >=INTERUPT_START_INDEX)
        {
            //interrupts prioriy configurations  
						uint8 intIndex = currentINT - INTERUPT_START_INDEX;
            uint8 priIndex = intIndex/4;
            uint8 priSection = intIndex%4; //0 from 5-7 ,1 from 13-15 , 2 from 21-23 , 3 from 29-31
            uint32 *PRIn  = (volatile uint32*)(NVIC_PRI_BASE+(priIndex*4));
            uint8 enIndex = intIndex/32;
            uint32 *ENn  = (volatile uint32*)(NVIC_EN_BASE+(enIndex*4));
            
            switch (priSection)
            {
            case 0:
                *PRIn |= (priority<<PRI_FIRST_SECTION_START);
                break;
            case 1:
                *PRIn |= (priority<<PRI_SECOND_SECTION_START);
                break;
            case 2:
                *PRIn |= (priority<<PRI_THIRD_SECTION_START);
                break;
            case 3:
                *PRIn |= (priority<<PRI_FOURTH_SECTION_START);
                break;
            default:
                break;
            }
            
            *ENn |= (1<<(intIndex%32u));
        }
        else
        {
            
            switch (currentINT)
            {
            case INTCTRL_MEMORY_MANAGMENT:
                SYSPRI1 |= (priority<<PRI_FIRST_SECTION_START);
                SCB_SYSHNDCTRL |= (1<<INTCTRL_MEMORY_MANAGMENT_EN_BIT); 
                break;
            case INTCTRL_BUS_FAULT:
                SYSPRI1 |= (priority<<PRI_SECOND_SECTION_START);
                SCB_SYSHNDCTRL |= (1<<INTCTRL_BUS_FAULT_EN_BIT);
                break;
            case INTCTRL_USAGE_FAULT:
                SYSPRI1 |= (priority<<PRI_THIRD_SECTION_START);
                SCB_SYSHNDCTRL |= (1<<INTCTRL_USAGE_FAULT_EN_BIT);
                break;
            case INTCTRL_SVCALL:
                SYSPRI2 |= (priority<<PRI_FOURTH_SECTION_START);
                break;
            case INTCTRL_DEBUG_MONITOR:
                SYSPRI3 |= (priority<<PRI_FIRST_SECTION_START);
                break;
            case INTCTRL_PENDSV:
                SYSPRI3 |= (priority<<PRI_THIRD_SECTION_START);
                break;
            case INTCTRL_SYSTICK:
                SYSPRI3 |= (priority<<PRI_FOURTH_SECTION_START);
                break;
            default:
                break;
            }
        }
				intCounter++;    
    }

}

/******************************************************************************
* \Syntax          : void IntCrtl_DeInit(void)                                      
* \Description     : Deinitialize Nvic\SCB Module by parsing the Configuration 
*                    into Nvic\SCB registers                                                                                           
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void IntCrtl_DeInit(void)
{
    uint8 intCounter = 0 ;
    uint8 currentINT, intIndex,disIndex;
    while(intCounter<INTCTRL_EXCEPTION_DISABLE_SIZE)
    {
        currentINT = IntCTRL_CONFIGURATIONS.disableExceptions_Numbers[intCounter];
        
        if(currentINT >=INTERUPT_START_INDEX)
        {
            intIndex = currentINT - INTERUPT_START_INDEX;
            disIndex = intIndex/32u;
            uint32 *DISn = (volatile uint32*)(NVIC_DIS_BASE+(disIndex*4));
            *DISn |= (1<<(intIndex%32u));
        }
        else
        {
            switch (currentINT)
            {
            case INTCTRL_MEMORY_MANAGMENT:
                SCB_SYSHNDCTRL &= ~(1<<INTCTRL_MEMORY_MANAGMENT_EN_BIT); 
                break;
            case INTCTRL_BUS_FAULT:
                SCB_SYSHNDCTRL &= ~(1<<INTCTRL_BUS_FAULT_EN_BIT);
                break;
            case INTCTRL_USAGE_FAULT:
                SCB_SYSHNDCTRL &= ~(1<<INTCTRL_USAGE_FAULT_EN_BIT);
                break;

            //Find a way to disable them.
            case INTCTRL_SVCALL:
                break;
            case INTCTRL_DEBUG_MONITOR:

                break;
            case INTCTRL_PENDSV:
                break;
            case INTCTRL_SYSTICK:
                break;
            default:
                break;
            }
        }
        intCounter++;
    }
}