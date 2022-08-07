/* File Comment
 * ---------------------------------------------------------------------------------------------------
 * [FILE NAME]: <Cpu0_Main.c>
 *
 * [AUTHOR]: Abdallah Hossam-Eldin Hosni
 *
 * [DATE CREATED]: <7-8-2022>
 *
 * [DESCRIPTION]: We have used only the core 0 to implement the Vacuum cleaner SW.
 * ---------------------------------------------------------------------------------------------------
 */


#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include "STM_Interrupt.h"
#include "switch_dust.h"
#include "dust_led.h"
#include "speed_switches.h"
#include "speed_indicator.h"
#include "STM_Interrupt.h"
#include "motor_control.h"

IFX_ALIGN(4) IfxCpu_syncEvent g_cpuSyncEvent = 0;


/* Function Comment
 * ---------------------------------------------------------------------------------------------------
 * [FUNCTION NAME]: scheduler
 *
 * [DESCRIPTION]:   This function is called periodically each 10 mS [100Hz] to do the vacuum cleaner functionality
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
void scheduler(void){
    motorControl_update();
    dustSwitch_update();
    DustLed_update();
    speedSwitches_update();
    speedLEDs_update();
}

/* Function Comment
 * ---------------------------------------------------------------------------------------------------
 * [FUNCTION NAME]: pulse
 *
 * [DESCRIPTION]:   This function is used to generate the pulse to triac to bypass the electricity to the motor
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
void pulse(void){
    IfxPort_setPinState(MOTOR_CONTROL, IfxPort_State_high);
    waitTime(IfxStm_getTicksFromMicroseconds(BSP_DEFAULT_TIMER, 200));
    IfxPort_setPinState(MOTOR_CONTROL, IfxPort_State_low);
    IfxGpt12_T3_run(&MODULE_GPT120, IfxGpt12_TimerRun_stop);
}



void core0_main(void)
{
    IfxCpu_enableInterrupts();
    
    /* !!WATCHDOG0 AND SAFETY WATCHDOG ARE DISABLED HERE!!
     * Enable the watchdogs and service them periodically if it is required
     */
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());
    
    /* Wait for CPU sync event */
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 1);
    
    STM_init();                                     // Initialize the STM -System Timer-
    initLED();                                      /* Initialize the port pin to which the LED is connected */
    dustSwitch_init();                              // Initialize the dust sensor
    DustLed_init();                                 // Initialize the dust led indicator
    speedSwitches_init();                           // Initialize the speed Switches
    speedLEDs_init();                               // Initialize the speed LEDs
    motorControl_init();                            // Initialize the signal to the triac
    initGpt12Timer();                               // Initialize the timer
    GPT12_Timer_setCallBack(pulse);                // set the callback for the pulse function
    STM_setCallBack(scheduler);                     // set the callback for the scheduler

    while(1)
    {
    }
}
