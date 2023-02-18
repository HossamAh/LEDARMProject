/*---------------------------------------------------------------------------------------------------------------------
 *  *  FILE DESCRIPTION
 *  --------------------
 *         File:  port_Types.h
 *       Module:  PORT Driver
 *  Description:  PORT Driver types header file 
---------------------------------------------------------------------------------------------------------------------*/
#ifndef PORT_TYPES_H
#define PORT_TYPES_H

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA TYPES AND STRUCTURES
---------------------------------------------------------------------------------------------------------------------*/
typedef enum
{
    DIGITAL,
    ANALOG,
    ALTERNATIVE,
    //TODO: add alternative functions
}Port_PinModeType;

typedef enum
{
    PIN_HIGH = 1u,
    PIN_LOW  = 0u
}Port_PinLevel;

typedef enum
{
    INPUT,
    OUTPUT
}Port_PinDirectionType;

typedef enum
{
    PULLUP,
    PULLDOWN,
    OPENDRAIN,
    NONE /*incase of output*/ 
}Port_PinInternalAttachType;

typedef enum
{
    PAD_2_MA,
    PAD_4_MA,
    PAD_8_MA
}Port_PinOutputCurrentType;

typedef enum
{
    A,B,C,D,E,F
}Port_Num;

typedef enum
{
    Pin0,
    Pin1,
    Pin2,
    Pin3,
    Pin4,
    Pin5,
    Pin6,
    Pin7
}Port_PinNum;


typedef enum
{
    ENABLE,
    DISABLE
}Port_Enable_Interrupt;

typedef enum
{
    RISING,
    FALLING,
    NOT_PULSE//not pulse
}Port_Trigger_Pulse_Type;
typedef enum
{
    LEVEL_LOW,
    LEVEL_HIGH,
    NOT_LEVEL//not level
}Port_Trigger_Level_Type;

typedef void(*Port_INT_callBack)(void);


#endif  