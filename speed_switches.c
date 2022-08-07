/* File Comment
 * ---------------------------------------------------------------------------------------------------
 * [FILE NAME]: <speed_switches.c>
 *
 * [AUTHOR]: Abdallah Hossam-Eldin Hosny
 *
 * [DATE CREATED]: <2 - 8 - 2022>
 *
 * [DESCRIPTION]: <The source file to make the user able to change the speed of the vacuum cleaner>
 * ---------------------------------------------------------------------------------------------------
 */

#include "speed_switches.h"

static SpeedSwitchState_t g_incrementSwitch[3] = {Speed_Switch_State_NOT_PRESSED, Speed_Switch_State_NOT_PRESSED, Speed_Switch_State_NOT_PRESSED};
static SpeedSwitchState_t g_decrementSwitch[3] = {Speed_Switch_State_NOT_PRESSED, Speed_Switch_State_NOT_PRESSED, Speed_Switch_State_NOT_PRESSED};
static SpeedState_t g_speedState;


/* Function Comment
 * ---------------------------------------------------------------------------------------------------
 * [FUNCTION NAME]: speedSwitches_init
 *
 * [DESCRIPTION]:   to initialize speed push buttons
 *
 * [Args]:          None
 *
 * [IN]:
 *
 * [OUT]:
 *
 * [IN / OUT]:
 *
 * [RETURNS]:   void
 * ---------------------------------------------------------------------------------------------------
 */
void speedSwitches_init(void){
    decreaseSwitchInit();
    increaseSwitchInit();

}

/* Function Comment
 * ---------------------------------------------------------------------------------------------------
 * [FUNCTION NAME]: speedSwitches_update
 *
 * [DESCRIPTION]:   to update the state of the switches
 *
 * [Args]:          None
 *
 * [IN]:
 *
 * [OUT]:
 *
 * [IN / OUT]:
 *
 * [RETURNS]:       void
 * ---------------------------------------------------------------------------------------------------
 */
void speedSwitches_update(void){
    if(!dustSwitch_get()){
        decreaseSwitchUpdate();
        increaseSwitchUpdate();


        if((g_incrementSwitch[0] == Speed_Switch_State_NOT_PRESSED) && (g_incrementSwitch[1] == Speed_Switch_State_PRE_PRESSED)
                && (g_incrementSwitch[2] == Speed_Switch_State_PRESSED) && (g_speedState != SpeedState_HIGH)){
            g_speedState++;

        }
        else{

        }

        if((g_decrementSwitch[0] == Speed_Switch_State_NOT_PRESSED) && (g_decrementSwitch[1] == Speed_Switch_State_PRE_PRESSED)
                && (g_decrementSwitch[2] == Speed_Switch_State_PRESSED) && (g_speedState != SpeedState_OFF)){
            g_speedState--;
        }
        else{

        }
    }
    else{

    }

}

/* Function Comment
 * ---------------------------------------------------------------------------------------------------
 * [FUNCTION NAME]: speedSwitches_getCurrentSpeed
 *
 * [DESCRIPTION]:   to the the current speed of the vacuum cleaner
 *
 * [Args]:          None
 *
 * [IN]:
 *
 * [OUT]:
 *
 * [IN / OUT]:
 *
 * [RETURNS]:   the current speed state
 * ---------------------------------------------------------------------------------------------------
 */
SpeedState_t speedSwitches_getCurrentSpeed(void){
    return g_speedState;
}


/* Function Comment
 * ---------------------------------------------------------------------------------------------------
 * [FUNCTION NAME]:     speedSwitches_setSpeed
 *
 * [DESCRIPTION]:       to change the speed of the vacuum cleaner
 *
 * [Args]:              SpeedState_t currentSpeed
 *
 * [IN]:                currentSpeed : the speed you want to apply
 *
 * [OUT]:               None
 *
 * [IN / OUT]:          None
 *
 * [RETURNS]:           void
 * ---------------------------------------------------------------------------------------------------
 */
void speedSwitches_setSpeed(SpeedState_t currentSpeed){
    g_speedState = currentSpeed;
}


static void decreaseSwitchInit(void){
    IfxPort_setPinModeInput(DECREASE_SPEED_SWITCH, IfxPort_InputMode_pullDown);
}

static void increaseSwitchInit(void){
    IfxPort_setPinModeInput(INCREASE_SPEED_SWITCH, IfxPort_InputMode_pullDown);
}

static void decreaseSwitchUpdate(void){
    boolean currentState = IfxPort_getPinState(DECREASE_SPEED_SWITCH);

    if(!currentState){
        if(g_decrementSwitch[2] == Speed_Switch_State_NOT_PRESSED){
            insertCurrentState(g_decrementSwitch, Speed_Switch_State_NOT_PRESSED);
        }
        else{
            insertCurrentState(g_decrementSwitch, g_decrementSwitch[2] - 1);
        }
    }
    else{
        if(g_decrementSwitch[2] == Speed_Switch_State_PRESSED){
            insertCurrentState(g_decrementSwitch, Speed_Switch_State_PRESSED);
        }
        else{
            insertCurrentState(g_decrementSwitch, g_decrementSwitch[2] + 1);
        }
    }
}

static void increaseSwitchUpdate(void){
    boolean currentState = IfxPort_getPinState(INCREASE_SPEED_SWITCH);

    if(!currentState){
        if(g_incrementSwitch[2] == Speed_Switch_State_NOT_PRESSED){
            insertCurrentState(g_incrementSwitch, Speed_Switch_State_NOT_PRESSED);
        }
        else{
            insertCurrentState(g_incrementSwitch, g_incrementSwitch[2] - 1);
        }
    }
    else{
        if(g_incrementSwitch[2] == Speed_Switch_State_PRESSED){
            insertCurrentState(g_incrementSwitch, Speed_Switch_State_PRESSED);
        }
        else{
            insertCurrentState(g_incrementSwitch, g_incrementSwitch[2] + 1);
        }
    }


}

static void insertCurrentState(SpeedSwitchState_t* arr, SpeedSwitchState_t currentElement){
    arr[0] = arr[1];
    arr[1] = arr[2];
    arr[2] = currentElement;
}



