/* File Comment
 * ---------------------------------------------------------------------------------------------------
 * [FILE NAME]: <switch_dust.c>
 *
 * [AUTHOR]: Abdallah Hossam-Eldin Hosny
 *
 * [DATE CREATED]: <2 - 8 - 2022>
 *
 * [DESCRIPTION]: <The source file for the switch which is responsible if the dust sensor is on or not>
 * ---------------------------------------------------------------------------------------------------
 */


#include "switch_dust.h"

#define DUST_SWITCH         &MODULE_P10,1

static SwitchState_t g_switchState = Switch_State_OFF;

/* Function Comment
 * ---------------------------------------------------------------------------------------------------
 * [FUNCTION NAME]: switch_init
 *
 * [DESCRIPTION]:   Switch Initialization
 *
 * [Args]:          None
 *
 * [IN]:            None
 *
 * [OUT]:           None
 *
 * [IN / OUT]:      None
 *
 * [RETURNS]:       Void
 * ---------------------------------------------------------------------------------------------------
 */
void dustSwitch_init(void){
    IfxPort_setPinModeInput(DUST_SWITCH, IfxPort_InputMode_pullDown);

}


/* Function Comment
 * ---------------------------------------------------------------------------------------------------
 * [FUNCTION NAME]: switch_get
 *
 * [DESCRIPTION]:   It updates the state of the Switch
 *
 * [Args]:          None
 *
 * [IN]:            None
 *
 * [OUT]:           None
 *
 * [IN / OUT]:      None
 *
 * [RETURNS]:       Void
 * ---------------------------------------------------------------------------------------------------
 */
void dustSwitch_update(void){
    boolean switch_state = IfxPort_getPinState(DUST_SWITCH);
    g_switchState = switch_state ? Switch_State_ON : Switch_State_OFF;

}
/* Function Comment
 * ---------------------------------------------------------------------------------------------------
 * [FUNCTION NAME]: switch_get
 *
 * [DESCRIPTION]:   This function is responsible to pass the state of the switch
 *
 * [Args]:          None
 *
 * [IN]:            None
 *
 * [OUT]:           None
 *
 * [IN / OUT]:      None
 *
 * [RETURNS]:       Void
 * ---------------------------------------------------------------------------------------------------
 */
SwitchState_t dustSwitch_get(void){
    return g_switchState;
}

