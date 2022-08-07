/* File Comment
 * ---------------------------------------------------------------------------------------------------
 * [FILE NAME]: <STM_Interrupt.c>
 *
 * [AUTHOR]: Abdallah Hossam-Eldin Hosny
 *
 * [DATE CREATED]: <5 - 8 - 2022>
 *
 * [DESCRIPTION]: <Source file of the STM driver>
 * ---------------------------------------------------------------------------------------------------
 */



#include "STM_Interrupt.h"



/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/
#define ISR_PRIORITY_STM        40                              /* Priority for interrupt ISR                       */
#define TIMER_INT_TIME          10                             /* Time between interrupts in ms                    */

#define LED                     &MODULE_P10,2                   /* LED toggled in Interrupt Service Routine (ISR)   */
#define STM                     &MODULE_STM0                    /* STM0 is used in this example                     */

/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/
IfxStm_CompareConfig g_STMConf;                                 /* STM configuration structure                      */
Ifx_TickTime g_ticksFor500ms;                                   /* Variable to store the number of ticks to wait    */

static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*********************************************************************************************************************/
/*------------------------------------------------Function Prototypes------------------------------------------------*/
/*********************************************************************************************************************/

void initSTM(void);

/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/
/* Macro to define Interrupt Service Routine.
 * This macro makes following definitions:
 * 1) Define linker section as .intvec_tc<vector number>_<interrupt priority>.
 * 2) define compiler specific attribute for the interrupt functions.
 * 3) define the Interrupt service routine as ISR function.
 *
 * IFX_INTERRUPT(isr, vectabNum, priority)
 *  - isr: Name of the ISR function.
 *  - vectabNum: Vector table number.
 *  - priority: Interrupt priority. Refer Usage of Interrupt Macro for more details.
 */
IFX_INTERRUPT(isrSTM, 0, ISR_PRIORITY_STM);

void STM_setCallBack(void(*a_ptr)(void)){
    g_callBackPtr = a_ptr;
}

void isrSTM(void)
{
    IfxStm_increaseCompare(STM, g_STMConf.comparator, g_ticksFor500ms);
    IfxPort_setPinState(LED, IfxPort_State_toggled);
    if(g_callBackPtr != NULL_PTR)
    {
        /* Call the Call Back function in the application after the edge is detected */
        (*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
    }
}

/* Function to initialize the LED */
void initLED(void)
{
    IfxPort_setPinMode(LED, IfxPort_Mode_outputPushPullGeneral);    /* Initialize LED port pin                      */
    IfxPort_setPinState(LED, IfxPort_State_high);                   /* Turn off LED (LED is low-level active)       */
}

/* Function to initialize the STM */
void initSTM(void)
{
    IfxStm_initCompareConfig(&g_STMConf);           /* Initialize the configuration structure with default values   */

    g_STMConf.triggerPriority = ISR_PRIORITY_STM;   /* Set the priority of the interrupt                            */
    g_STMConf.typeOfService = IfxSrc_Tos_cpu0;      /* Set the service provider for the interrupts                  */
    g_STMConf.ticks = g_ticksFor500ms;              /* Set the number of ticks after which the timer triggers an
     * interrupt for the first time                                 */
    IfxStm_initCompare(STM, &g_STMConf);            /* Initialize the STM with the user configuration               */
}

/* Function to initialize all the peripherals and variables used */
void STM_init(void)
{
    /* Initialize time constant */
    g_ticksFor500ms = IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, TIMER_INT_TIME);
    initSTM();                                      /* Configure the STM module                                     */
}
