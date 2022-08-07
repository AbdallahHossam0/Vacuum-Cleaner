/* File Comment
 * ---------------------------------------------------------------------------------------------------
 * [FILE NAME]: <motor_control.h>
 *
 * [AUTHOR]: Abdallah Hossam-Eldin Hosny
 *
 * [DATE CREATED]: <7 - 8 - 2022>
 *
 * [DESCRIPTION]: This header file is used to control the motor of the vacuum cleaner
 * ---------------------------------------------------------------------------------------------------
 */

#ifndef MOTOR_CONTROL_H_
#define MOTOR_CONTROL_H_

/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "IfxPort.h"
#include "Bsp.h"
#include "speed_switches.h"
#include "GPT12_Timer_Interrupt.h"
#include "Ifx_Types.h"
#include "IfxGpt12.h"
#include "IfxPort.h"

#define MOTOR_CONTROL     &MODULE_P15,0


/*********************************************************************************************************************/
/*------------------------------------------------Function Prototypes------------------------------------------------*/
/*********************************************************************************************************************/
void motorControl_init(void);
void motorControl_update(void);
uint8 motorControl_getCurrentStart(void);
uint8 motorControl_getCurrentAppliedStart(void);
static uint16 calculateEdge(uint8 appliedStart);



#endif /* MOTOR_CONTROL_H_ */
