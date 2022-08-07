/* File Comment
 * ---------------------------------------------------------------------------------------------------
 * [FILE NAME]: <speed_inicator.c>
 *
 * [AUTHOR]: Abdallah Hossam-Eldin Hosny
 *
 * [DATE CREATED]: <5 - 8 - 2022>
 *
 * [DESCRIPTION]: <The source file for the Speed LEDs on the 7 Segment>
 * ---------------------------------------------------------------------------------------------------
 */

#include "speed_indicator.h"


#define LOW_LED         &MODULE_P00,0
#define MED_LED         &MODULE_P00,1
#define HIGH_LED        &MODULE_P00,2


/* Function Comment
 * ---------------------------------------------------------------------------------------------------
 * [FUNCTION NAME]: speedLeds_init
 *
 * [DESCRIPTION]:   This function is used to initialize the LEDs used to indicate the user about the speed.
 *
 * [Args]:          None
 *
 * [IN]:
 *
 * [OUT]:
 *
 * [IN / OUT]:
 *
 * [RETURNS]:       void.
 * ---------------------------------------------------------------------------------------------------
 */
void speedLEDs_init(void){
    IfxPort_setPinModeOutput(LOW_LED, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinState(LOW_LED, IfxPort_State_low);

    IfxPort_setPinModeOutput(MED_LED, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinState(MED_LED, IfxPort_State_low);

    IfxPort_setPinModeOutput(HIGH_LED, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinState(HIGH_LED, IfxPort_State_low);
}


/* Function Comment
 * ---------------------------------------------------------------------------------------------------
 * [FUNCTION NAME]: speedLEDs_update
 *
 * [DESCRIPTION]:   This function is used to update the LEDs used to indicate the user about the current speed.
 *
 * [Args]:          None
 *
 * [IN]:
 *
 * [OUT]:
 *
 * [IN / OUT]:
 *
 * [RETURNS]:   void.
 * ---------------------------------------------------------------------------------------------------
 */
void speedLEDs_update(void){

    SpeedState_t currentSpeedState;

    static SpeedState_t prevSpeedState = SpeedState_OFF;

    currentSpeedState = speedSwitches_getCurrentSpeed();

    if(currentSpeedState != prevSpeedState){
        switch(currentSpeedState){
            default:
                IfxPort_setPinState(LOW_LED, IfxPort_State_low);
                IfxPort_setPinState(MED_LED, IfxPort_State_low);
                IfxPort_setPinState(HIGH_LED, IfxPort_State_low);
                break;
            case SpeedState_LOW:
                IfxPort_setPinState(LOW_LED, IfxPort_State_high);
                IfxPort_setPinState(MED_LED, IfxPort_State_low);
                IfxPort_setPinState(HIGH_LED, IfxPort_State_low);
                break;
            case SpeedState_MEDIUM:
                IfxPort_setPinState(LOW_LED, IfxPort_State_high);
                IfxPort_setPinState(MED_LED, IfxPort_State_high);
                IfxPort_setPinState(HIGH_LED, IfxPort_State_low);
                break;
            case SpeedState_HIGH:
                IfxPort_setPinState(LOW_LED, IfxPort_State_high);
                IfxPort_setPinState(MED_LED, IfxPort_State_high);
                IfxPort_setPinState(HIGH_LED, IfxPort_State_high);
                break;
        }
    }
    else{

    }

    prevSpeedState = currentSpeedState;

}
