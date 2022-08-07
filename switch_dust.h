/* File Comment
 * ---------------------------------------------------------------------------------------------------
 * [FILE NAME]: <switch_dust.h>
 *
 * [AUTHOR]: Abdallah Hossam-Eldin Hosny
 *
 * [DATE CREATED]: <2 - 8 - 2022>
 *
 * [DESCRIPTION]: <The header file for the switch which is responsible if the dust sensor is on or not>
 * ---------------------------------------------------------------------------------------------------
 */

#ifndef SWITCH_DUST_H_
#define SWITCH_DUST_H_

#include "IfxPort.h"
#include "Bsp.h"


/******************************************************************************/
/*--------------------------------Enumerations--------------------------------*/
/******************************************************************************/

typedef enum
{
    Switch_State_OFF = 0,  /**< \brief port controlled by PORT Module */
    Switch_State_ON = 1   /**< \brief Port controlled by HSCT Module */
} SwitchState_t;



/*********************************************************************************************************************/
/*------------------------------------------------Function Prototypes------------------------------------------------*/
/*********************************************************************************************************************/
void dustSwitch_init(void);
void dustSwitch_update(void);
SwitchState_t dustSwitch_get(void);


#endif /* SWITCH_DUST_H_ */
