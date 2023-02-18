/*---------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  ----------------
 *         File:  IntCtrl_Cfg.h
 *       Module:  NVIC
 *  Description:  Configuration header file for NVIC     
---------------------------------------------------------------------------------------------------------------------*/
#ifndef INTCTRL_CFG_H
#define INTCTRL_CFG_H

/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/
#include "Std_types.h"
#include "IntCtrl_Types.h"
/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL CONSTANT MACROS
---------------------------------------------------------------------------------------------------------------------*/
#define INTCTRL_PRIORITY_XXX 	4
#define INTCTRL_PRIORITY_XXY 	5
#define INTCTRL_PRIORITY_XYY 	6
#define INTCTRL_PRIORITY_YYY 	7


#define INTCTRL_PRIORITY_CONFIGURAION_TYPE  INTCTRL_PRIORITY_XXY
#define INTCTRL_EXCEPTION_ENABLE_SIZE  1 //number of exceptions to be enabled
#define INTCTRL_EXCEPTION_DISABLE_SIZE  0 //number of exceptions to be disabled

#endif