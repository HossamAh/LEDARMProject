/*---------------------------------------------------------------------------------------------------------------------
 *  *  FILE DESCRIPTION
 *  --------------------
 *         File:  GPT_Types.h
 *  Description:  GPT new types header file 
---------------------------------------------------------------------------------------------------------------------*/
#ifndef GPT_TYPES_H
#define GPT_TYPES_H

/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/
#include "Std_Types.h"
#include "GPT_Cfg.h"
/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA TYPES AND STRUCTURES
---------------------------------------------------------------------------------------------------------------------*/
typedef enum
{
    CH0,
    CH1,
    CH2,
    CH3,/*timers from ch0 to ch5 are 16/32-bits timers*/
    CH4,
    CH5,
    CH6,
    CH7,
    CH8,/*timers from ch6 to ch11 are 32/64-bits timers*/
    CH9,
    CH10,
    CH11
}GPT_ChannelType;

typedef enum
{
GPT_ONESHOT,
GPT_PERIODIC,
GPT_RTC,
GPT_EDGECOUNT,
GPT_EDGETIME,
GPT_PWM
}GPT_ModeType;

#ifdef  TIMER_16_BIT_VALUE_TYPE
typedef   uint16      GPT_ValueType;  
#endif
#ifdef  TIMER_32_BIT_VALUE_TYPE
typedef   uint32      GPT_ValueType;   
#endif
#ifdef  TIMER_64_BIT_VALUE_TYPE
typedef   uint64      GPT_ValueType;
#endif


typedef enum
{
    GPT_FREQ16MHZ = 16000000ul,
    GPT_FREQ_125KHZ = 125000ul,
    GPT_FREQ_50KHZ = 50000ul
}GPT_TickFrequencyType;

typedef enum
{
    NOT_OK,
    OK
}Std_ReturnType;

typedef enum
{
    GPT_PREDEF_100US_32BIT,
    GPT_PREDEF_1US_32BIT,
    GPT_PREDEF_1US_24BIT,
    GPT_PREDEF_1US_16BIT,
}GPT_PredefTimerValue;

typedef enum
{
    TimerA,
    TimerB
}GPT_ChannelTimerType;
typedef  void (*GPT_PtrToCBFunc)(void);

#endif