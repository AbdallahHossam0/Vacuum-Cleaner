/* File Comment
 * ---------------------------------------------------------------------------------------------------
 * [FILE NAME]: <speed_inicator.c>
 *
 * [AUTHOR]: Abdallah Hossam-Eldin Hosny
 *
 * [DATE CREATED]: <5 - 8 - 2022>
 *
 * [DESCRIPTION]: <The header file for the Speed LEDs on the 7 Segment>
 * ---------------------------------------------------------------------------------------------------
 */

#ifndef SPEED_INDICATOR_H_
#define SPEED_INDICATOR_H_

/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "IfxPort.h"
#include "Bsp.h"
#include "speed_switches.h"

/*********************************************************************************************************************/
/*------------------------------------------------Function Prototypes------------------------------------------------*/
/*********************************************************************************************************************/

void speedLEDs_init(void);
void speedLEDs_update(void);

#endif /* SPEED_INDICATOR_H_ */
