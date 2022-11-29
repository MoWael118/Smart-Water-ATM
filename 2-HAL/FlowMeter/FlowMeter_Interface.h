/*
 * FloeMeter_Interface.h
 *
 *  Created on: Nov 6, 2022
 *      Author: moham
 */

#ifndef FLOWMETER_INTERFACE_H_
#define FLOWMETER_INTERFACE_H_

/*
 * NOTE: This Function is used in FLOWMETER_voidGetVolume
 *          kindly do not use it */
void FLOWMETER_Init( s16 * Copy_pu16VolumeInSec , s16 * Copy_pu16FlowRate ) ;

/*
 * NOTE: Function Will Not Work Correctly if GIE is disable
 *        make sure to enable it before Calling Function*/
void FLOWMETER_voidGetVolume( s16 * Copy_pu16VolumeInSec , s16 * Copy_pu16FlowRate ) ;

/*
 * NOTE : Function Should Be Called After Finishing Flow meter Job in Order to
 *            Disable timer peripheral and EXTI */
void FLOWMETER_voidFinished( void );

/*EXTI2 & Timer0 For Flow meter to Work Properly*/
void EXTI (void) ;
void TIMER_ISR(void);

#endif /* 2_HAL_FLOWMETER_FLOEMETER_INTERFACE_H_ */
