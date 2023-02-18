/*---------------------------------------------------------------------------------------------------------------------
 *  *  FILE DESCRIPTION
 *  --------------------
 *         File:  DIO_Types.h
 *       Module:  DIO Driver
 *
 *  Description:  DIO Driver types header file     
---------------------------------------------------------------------------------------------------------------------*/
#ifndef DIO_TYPES_H
#define DIO_TYPES_H
/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA TYPES AND STRUCTURES
---------------------------------------------------------------------------------------------------------------------*/
typedef enum
{
    PinA0,
    PinA1,
    PinA2,
    PinA3,
    PinA4,
    PinA5,
    PinA6,
    PinA7,

    PinB0,
    PinB1,
    PinB2,
    PinB3,
    PinB4,
    PinB5,
    PinB6,
    PinB7,

    PinC0,
    PinC1,
    PinC2,
    PinC3,
    PinC4,
    PinC5,
    PinC6,
    PinC7,

    PinD0,
    PinD1,
    PinD2,
    PinD3,
    PinD4,
    PinD5,
    PinD6,
    PinD7,

    PinE0,
    PinE1,
    PinE2,
    PinE3,
    PinE4,
    PinE5,

    PinF0,
    PinF1,
    PinF2,
    PinF3,
    PinF4


}DIO_ChannelType;

typedef enum
{
    PORTA,
    PORTB,
    PORTC,
    PORTD,
    PORTE,
    PORTF
}DIO_PortType;

typedef enum
{
    HIGH=1u,LOW=0u
}DIO_LevelType;

typedef enum
{
    ALL_OFF = 0x00,
    ALL_ON  = 0xFF,
    LOWER_ON = 0x0F,
    HIGHER_ON = 0xF0,
    DIFFERENT_COMBINATION=0x01,
}DIO_PortLevelType;

#endif