/*---------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
---------------------------------------------------------------------------------------------------------------------*/
/**        \file  port_Lcfg.c
 *        \brief  GPIO PORT Driver Configurations
 *
 *      \details  Contain configurations of the GPIO PORT Driver.
---------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/
#include "Std_Types.h"
#include "port.h"

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA
---------------------------------------------------------------------------------------------------------------------*/
 const Port_Cfg_Type Port_CONFIGURATIONS[MAX_PIN_NUMBER] = 
{
/*   portMode   ,  startLevel ,  Direction,      inputAttachment    , outputCurrent     , PORT      ,   Pin     ,     int_enable ,     PULSE Type , Level Type*/
    {DIGITAL    ,  PIN_HIGH   ,   OUTPUT  ,         NONE            , PAD_8_MA          , F         ,   Pin3    ,        DISABLE ,     NONE,       NONE   },
    {DIGITAL    ,  PIN_HIGH   ,   OUTPUT  ,         NONE            , PAD_8_MA          , F         ,   Pin1    ,        DISABLE ,     NONE,       NONE   },
		{DIGITAL    ,  PIN_HIGH   ,   OUTPUT  ,         NONE            , PAD_8_MA          , F         ,   Pin2    ,        DISABLE ,     NONE,       NONE   },
    {DIGITAL    ,  PIN_LOW   ,   INPUT  ,         	PULLUP            , PAD_8_MA          , F           ,   Pin4 ,        ENABLE ,     FALLING,       NONE   },
    {DIGITAL    ,  PIN_LOW   ,   INPUT  ,         	PULLUP            , PAD_8_MA          , F           ,   Pin0 ,        ENABLE ,     FALLING,       NONE   }			
};
