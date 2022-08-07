/* File Comment
 * ---------------------------------------------------------------------------------------------------
 * [FILE NAME]: <GPT12_timer_interrupt.c>
 *
 * [AUTHOR]: Abdallah Hossam-Eldin Hosni
 *
 * [DATE CREATED]: <6 - 8 - 2022>
 *
 * [DESCRIPTION]: This source file is the timer driver used to bypass the electricity to the motor at the required position
 * ---------------------------------------------------------------------------------------------------
 */


#include "GPT12_Timer_Interrupt.h"

/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/
#define ISR_PRIORITY_GPT12_TIMER    6                       /* Define the GPT12 Timer interrupt priority            */
#define ISR_PROVIDER_GPT12_TIMER    IfxSrc_Tos_cpu0         /* Interrupt provider                                   */
#define RELOAD_VALUE                975u                  /* Reload value to have an interrupt each 500ms         */
#define LED                         &MODULE_P10, 2          /* LED which toggles in the Interrupt Service Routine   */

static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*********************************************************************************************************************/
/*--------------------------------------------Function Implementations-----------------------------------------------*/
/*********************************************************************************************************************/
/* Macro defining the Interrupt Service Routine */
IFX_INTERRUPT(interruptGpt12, 0, ISR_PRIORITY_GPT12_TIMER);

/* Function to initialize the GPT12 and start the timer */
void initGpt12Timer(void)
{
    /* Initialize the GPT12 module */
    IfxGpt12_enableModule(&MODULE_GPT120);                                          /* Enable the GPT12 module      */
    IfxGpt12_setGpt1BlockPrescaler(&MODULE_GPT120, IfxGpt12_Gpt1BlockPrescaler_16); /* Set GPT1 block prescaler     */

    /* Initialize the Timer T3 */
    IfxGpt12_T3_setMode(&MODULE_GPT120, IfxGpt12_Mode_timer);                       /* Set T3 to timer mode         */
    IfxGpt12_T3_setTimerDirection(&MODULE_GPT120, IfxGpt12_TimerDirection_down);    /* Set T3 count direction       */
    IfxGpt12_T3_setTimerPrescaler(&MODULE_GPT120, IfxGpt12_TimerInputPrescaler_64); /* Set T3 input prescaler       */
    IfxGpt12_T3_setTimerValue(&MODULE_GPT120, RELOAD_VALUE);                        /* Set T3 start value           */

    /* Initialize the Timer T2 */
    IfxGpt12_T2_setMode(&MODULE_GPT120, IfxGpt12_Mode_reload);                      /* Set T2 to reload mode        */
    IfxGpt12_T2_setReloadInputMode(&MODULE_GPT120, IfxGpt12_ReloadInputMode_bothEdgesTxOTL); /* Set reload trigger  */
    IfxGpt12_T2_setTimerValue(&MODULE_GPT120, RELOAD_VALUE);                        /* Set T2 reload value          */

    /* Initialize the interrupt */
    volatile Ifx_SRC_SRCR *src = IfxGpt12_T3_getSrc(&MODULE_GPT120);                /* Get the interrupt address    */
    IfxSrc_init(src, ISR_PROVIDER_GPT12_TIMER, ISR_PRIORITY_GPT12_TIMER);           /* Initialize service request   */
    IfxSrc_enable(src);                                                             /* Enable GPT12 interrupt       */




}


/* Function Comment
 * ---------------------------------------------------------------------------------------------------
 * [FUNCTION NAME]:     interruptGpt12
 *
 * [DESCRIPTION]:       function to be executed if the interrupt is lunched
 *
 * [Args]:              None
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
void interruptGpt12(void)
{
    if(g_callBackPtr != NULL_PTR)
    {
        /* Call the Call Back function in the application after the edge is detected */
        (*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
    }


}

/* Function Comment
 * ---------------------------------------------------------------------------------------------------
 * [FUNCTION NAME]: MotorControl_setCallBack
 *
 * [DESCRIPTION]:   Function to set the callback
 *
 * [Args]:          void(*a_ptr)(void)
 *
 * [IN]:            void(*a_ptr)(void): pointer to the function to be executed if the interrupt is occured
 *
 * [OUT]:           None
 *
 * [IN / OUT]:      None
 *
 * [RETURNS]:       void
 * ---------------------------------------------------------------------------------------------------
 */
void GPT12_Timer_setCallBack(void(*a_ptr)(void)){
    g_callBackPtr = a_ptr;
}
