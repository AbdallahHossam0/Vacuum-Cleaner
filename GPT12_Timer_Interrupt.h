/* File Comment
 * ---------------------------------------------------------------------------------------------------
 * [FILE NAME]: <GPT12_timer_interrupt.h>
 *
 * [AUTHOR]: Abdallah Hossam-Eldin Hosni
 *
 * [DATE CREATED]: <6 - 8 - 2022>
 *
 * [DESCRIPTION]: This header file is the timer driver used to bypass the electricity to the motor at the required position
 * ---------------------------------------------------------------------------------------------------
 */

#ifndef GPT12_TIMER_INTERRUPT_H_
#define GPT12_TIMER_INTERRUPT_H_

/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/

#include "Ifx_Types.h"
#include "IfxGpt12.h"
#include "IfxPort.h"


/*********************************************************************************************************************/
/*-----------------------------------------------Function Prototypes-------------------------------------------------*/
/*********************************************************************************************************************/
void initGpt12Timer(void);                          /* Function to initialize the GPT12 Module and start the timer  */
void interruptGpt12(void);                          /* Interrupt Service Routine of the GPT12                       */
void GPT12_Timer_setCallBack(void(*a_ptr)(void));


#endif /* GPT12_TIMER_INTERRUPT_H_ */
