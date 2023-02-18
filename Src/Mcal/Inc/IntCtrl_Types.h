/*---------------------------------------------------------------------------------------------------------------------
 *  *  FILE DESCRIPTION
 *  --------------------
 *         File:  IntCtrl_Types.h
 *  Description:  INTCTRL new types header file 
---------------------------------------------------------------------------------------------------------------------*/
#ifndef INTCTRL_TYPES_H
#define INTCTRL_TYPES_H

/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/
#include "Std_Types.h"


/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA TYPES AND STRUCTURES
---------------------------------------------------------------------------------------------------------------------*/
typedef enum
{
    INTCTRL_MEMORY_MANAGMENT = 4,
    INTCTRL_BUS_FAULT,
    INTCTRL_USAGE_FAULT,
    INTCTRL_SVCALL = 11,
    INTCTRL_DEBUG_MONITOR,
    INTCTRL_PENDSV = 14,
    INTCTRL_SYSTICK,
    INTCTRL_GPIOA,
    INTCTRL_GPIOB,
    INTCTRL_GPIOC,
    INTCTRL_GPIOD,
    INTCTRL_GPIOE,
    INTCTRL_UART0,
    INTCTRL_UART1,
    INTCTRL_SSI0,
    INTCTRL_I2C0,
    INTCTRL_PWM0_FAULT,
    INTCTRL_PWM0_GENRATOR0,
    INTCTRL_PWM0_GENRATOR1,
    INTCTRL_PWM0_GENRATOR2,
    INTCTRL_QEI0,
    INTCTRL_ADC0_SEQUENCE0,
    INTCTRL_ADC0_SEQUENCE1,
    INTCTRL_ADC0_SEQUENCE2,
    INTCTRL_ADC0_SEQUENCE3,
    INTCTRL_WATCHDOG_TIMER01,
    INTCTRL_TIMER_0A,
    INTCTRL_TIMER_0B,
    INTCTRL_TIMER_1A,
    INTCTRL_TIMER_1B,
    INTCTRL_TIMER_2A,
    INTCTRL_TIMER_2B,
    INTCTRL_ANALOG_COMPARTOR_0,
    INTCTRL_ANALOG_COMPARTOR_1,
    INTCTRL_SYSTEM_CONTROL = 44,
    INTCTRL_FLASH_MEMORY_CONTROL_EEPROM_CONTROL,
    INTCTRL_GPIOF,
    INTCTRL_UART2 = 49,
    INTCTRL_SSI1,
    INTCTRL_TIMER_3A,
    INTCTRL_TIMER_3B,
    INTCTRL_I2C1,
    INTCTRL_QEI1,
    INTCTRL_CAN0,
    INTCTRL_CAN1,
    INTCTRL_HIBERNATION_MODULE = 59,
    INTCTRL_USB,
    INTCTRL_PWM0_GENRATOR3,
    INTCTRL_DMA_SOFTWARE,
    INTCTRL_DMA_ERROR,
    INTCTRL_ADC1_SEQUENCE0,
    INTCTRL_ADC1_SEQUENCE1,
    INTCTRL_ADC1_SEQUENCE2,
    INTCTRL_ADC1_SEQUENCE3,
    INTCTRL_SSI2 = 73,
    INTCTRL_SSI3,
    INTCTRL_UART3,
    INTCTRL_UART4,
    INTCTRL_UART5,
    INTCTRL_UART6,
    INTCTRL_UART7,
    INTCTRL_I2C2 = 84,
    INTCTRL_I2C3,
    INTCTRL_TIMER_4A,
    INTCTRL_TIMER_4B,
    INTCTRL_TIMER_5A = 108,
    INTCTRL_TIMER_5B,
    INTCTRL_TIMER32_64_0A,
    INTCTRL_TIMER32_64_0B,
    INTCTRL_TIMER32_64_1A,
    INTCTRL_TIMER32_64_1B,
    INTCTRL_TIMER32_64_2A,
    INTCTRL_TIMER32_64_2B,
    INTCTRL_TIMER32_64_3A,
    INTCTRL_TIMER32_64_3B,
    INTCTRL_TIMER32_64_4A,
    INTCTRL_TIMER32_64_4B,
    INTCTRL_TIMER32_64_5A,
    INTCTRL_TIMER32_64_5B,
    INTCTRL_SYSTEM_EXCEPION_IMPRECISE,
    INTCTRL_PWM1_GENRATOR0 = 150,
    INTCTRL_PWM1_GENRATOR1,
    INTCTRL_PWM1_GENRATOR2,
    INTCTRL_PWM1_GENRATOR3,
    INTCTRL_PWM1_FAULT,
    
}IntCtrl_InterruptType;

 
#endif