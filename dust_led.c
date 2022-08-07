/* File Comment
 * ---------------------------------------------------------------------------------------------------
 * [FILE NAME]: <dust_led.c>
 *
 * [AUTHOR]: Abdallah Hossam-Eldin Hosny
 *
 * [DATE CREATED]: <2 - 8 - 2022>
 *
 * [DESCRIPTION]: <The source file for the led which is responsible to indicate the user is the dust case if filled or not>
 * ---------------------------------------------------------------------------------------------------
 */

#include "dust_led.h"
#include "switch_dust.h"
#include "speed_switches.h"

#define DUST_LED         &MODULE_P10,3


/* Function Comment
 * ---------------------------------------------------------------------------------------------------
 * [FUNCTION NAME]: DustLed_init
 *
 * [DESCRIPTION]:   Initialize the dust led
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
void DustLed_init(void){
    IfxPort_setPinModeOutput(DUST_LED, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinState(DUST_LED, IfxPort_State_low);
}

/* Function Comment
 * ---------------------------------------------------------------------------------------------------
 * [FUNCTION NAME]:     DustLed_update
 *
 * [DESCRIPTION]:       Update the state of the dust led.
 *
 * [Args]:              None
 *
 * [IN]:
 *
 * [OUT]:
 *
 * [IN / OUT]:
 *
 * [RETURNS]:           Void
 * ---------------------------------------------------------------------------------------------------
 */
void DustLed_update(void){

    static uint16 counter = 0;
    SwitchState_t switchState = dustSwitch_get();

    if(switchState){
        IfxPort_setPinState(DUST_LED, IfxPort_State_high);
        counter++;
        SpeedState_t currentSpeed = speedSwitches_getCurrentSpeed();
        if(counter == 3000 && currentSpeed){
            counter = 0;
            speedSwitches_setSpeed(currentSpeed - 1);
        }
    }
    else{
        IfxPort_setPinState(DUST_LED, IfxPort_State_low);
        counter = 0;
    }
}
