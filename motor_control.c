/* File Comment
 * ---------------------------------------------------------------------------------------------------
 * [FILE NAME]: <motor_control.c>
 *
 * [AUTHOR]: Abdallah Hossam-Eldin Hosni
 *
 * [DATE CREATED]: <7 - 8 - 2022>
 *
 * [DESCRIPTION]: This source file is used to control the motor of the vacuum cleaner
 * ---------------------------------------------------------------------------------------------------
 */


#include "motor_control.h"


static uint8 g_currentStart = 180;          // global variable to include the current triac angle


/* Function Comment
 * ---------------------------------------------------------------------------------------------------
 * [FUNCTION NAME]: motorControl_init
 *
 * [DESCRIPTION]:   Function to initialize the pin connected to the triac
 *
 * [Args]:          None
 *
 * [IN]:
 *
 * [OUT]:
 *
 * [IN / OUT]:
 *
 * [RETURNS]:       Void
 * ---------------------------------------------------------------------------------------------------
 */
void motorControl_init(void){

    IfxPort_setPinModeOutput(MOTOR_CONTROL, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinState(MOTOR_CONTROL, IfxPort_State_low);

}



/* Function Comment
 * ---------------------------------------------------------------------------------------------------
 * [FUNCTION NAME]:     motorControl_update
 *
 * [DESCRIPTION]:       function to uodate the angle
 *
 * [Args]:              None
 *
 * [IN]:
 *
 * [OUT]:
 *
 * [IN / OUT]:
 *
 * [RETURNS]:           void
 * ---------------------------------------------------------------------------------------------------
 */
void motorControl_update(void){
    static uint8 counter = 0;
    SpeedState_t currentSpeed = speedSwitches_getCurrentSpeed();
    const uint8 requiredSpeed[4] = {0, 140, 90, 10};
    if((g_currentStart != requiredSpeed[currentSpeed]) && !(counter % 8)){
        if(requiredSpeed[currentSpeed] > g_currentStart){
            g_currentStart += 10;
        }
        else{
            g_currentStart -= 10;
        }
    }
    else{

    }

    if(currentSpeed != SpeedState_OFF){
        uint16 appliedCounterValue = calculateEdge(motorControl_getCurrentAppliedStart());
        IfxGpt12_T3_setTimerValue(&MODULE_GPT120, appliedCounterValue);
        IfxGpt12_T2_setTimerValue(&MODULE_GPT120, appliedCounterValue);
        IfxGpt12_T3_run(&MODULE_GPT120, IfxGpt12_TimerRun_start);
    }
    else{
        g_currentStart = 180;
    }
}


/* Function Comment
 * ---------------------------------------------------------------------------------------------------
 * [FUNCTION NAME]: calculateEdge
 *
 * [DESCRIPTION]:   function to calculate the current edge for the timer
 *
 * [Args]:          (uint8) appliedStart
 *
 * [IN]:            appliedStart : varibale contains the applied angle for the triac
 *
 * [OUT]:
 *
 * [IN / OUT]:
 *
 * [RETURNS]:       void
 * ---------------------------------------------------------------------------------------------------
 */
static uint16 calculateEdge(uint8 appliedStart){
    return (uint16) appliedStart* 5.4;
}

/* Function Comment
 * ---------------------------------------------------------------------------------------------------
 * [FUNCTION NAME]: motorControl_getCurrentStart
 *
 * [DESCRIPTION]:   function to get the current angle
 *
 * [Args]:          None
 *
 * [IN]:
 *
 * [OUT]:
 *
 * [IN / OUT]:
 *
 * [RETURNS]:   return the current triac angle
 * ---------------------------------------------------------------------------------------------------
 */
uint8 motorControl_getCurrentStart(void){
    return g_currentStart;
}


/* Function Comment
 * ---------------------------------------------------------------------------------------------------
 * [FUNCTION NAME]: motorControl_getCurrentAppliedStart
 *
 * [DESCRIPTION]:   function to get the applied after add or substract 5
 *
 * [Args]:          None
 *
 * [IN]:
 *
 * [OUT]:
 *
 * [IN / OUT]:
 *
 * [RETURNS]:       return the current applied triac angle
 * ---------------------------------------------------------------------------------------------------
 */
uint8 motorControl_getCurrentAppliedStart(void){
    static uint8 counter = 0;
    if(counter++ % 2){
        return motorControl_getCurrentStart() + 5;
    }
    else{
        return motorControl_getCurrentStart() - 5;
    }

}



