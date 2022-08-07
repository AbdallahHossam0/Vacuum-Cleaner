/* File Comment
 * ---------------------------------------------------------------------------------------------------
 * [FILE NAME]: <speed_switches.h>
 *
 * [AUTHOR]: Abdallah Hossam-Eldin Hosny
 *
 * [DATE CREATED]: <2 - 8 - 2022>
 *
 * [DESCRIPTION]: <The header file to make the user able to change the speed of the vacuum cleaner>
 * ---------------------------------------------------------------------------------------------------
 */

#ifndef SPEED_SWITCHES_H_
#define SPEED_SWITCHES_H_


/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "IfxPort.h"
#include "Bsp.h"
#include "switch_dust.h"

#define INCREASE_SPEED_SWITCH       &MODULE_P02,5
#define DECREASE_SPEED_SWITCH       &MODULE_P02,4

/******************************************************************************/
/*--------------------------------Enumerations--------------------------------*/
/******************************************************************************/

typedef enum
{
    SpeedState_OFF = 0,
    SpeedState_LOW = 1,
    SpeedState_MEDIUM = 2,
    SpeedState_HIGH = 3
} SpeedState_t;

typedef enum
{
    Speed_Switch_State_NOT_PRESSED = 0,
    Speed_Switch_State_PRE_PRESSED = 1,
    Speed_Switch_State_PRESSED = 2
} SpeedSwitchState_t;

/*********************************************************************************************************************/
/*------------------------------------------------Function Prototypes------------------------------------------------*/
/*********************************************************************************************************************/
static void decreaseSwitchInit(void);
static void increaseSwitchInit(void);
static void decreaseSwitchUpdate(void);
static void increaseSwitchUpdate(void);
void speedSwitches_init(void);
void speedSwitches_update(void);
void speedSwitches_setSpeed(SpeedState_t currentSpeed);
SpeedState_t speedSwitches_getCurrentSpeed(void);
static void insertCurrentState(SpeedSwitchState_t* arr, SpeedSwitchState_t currentElement);


#endif /* SPEED_SWITCHES_H_ */
