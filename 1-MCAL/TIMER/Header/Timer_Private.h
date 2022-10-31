/*
 * Timer_Private.h
 *
 *  Created on: Sep 19, 2022
 *      Author: mhmd wael
 */

#ifndef HEADER_TIMER_PRIVATE_H_
#define HEADER_TIMER_PRIVATE_H_

#define	NumberOfINTs	                 8
/*Interrupt IDs*/
#define TIMER0_OVFINT	                 0
#define TIMER0_COMPINT	                 1
#define TIMER1_OVFINT	                 2
#define TIMER1_COMPBINT	                 3
#define TIMER1_COMPAINT	                 4
#define TIMER1_CAPTINT	                 5
#define TIMER2_OVFINT	                 6
#define TIMER2_COMPINT	                 7
/**/
#define TIMER0		0
#define TIMER1		1
#define TIMER2		2
#define TIMER1A		3
#define TIMER1B		4
/*Compare Match OUTPUT MODE FOR TIMER0 in mode CTC*/
#define TIMER0_CompareModeOFF 			(1)
#define TIMER0_CompareModeSET           (2)
#define TIMER0_CompareModeCLR           (3)
#define TIMER0_CompareModeTOGGLE        (4)
/*Compare Match OUTPUT MODE FOR TIMER0 in mode fast PWM*/
#define TIMER0_CompareModeFastPWMOFF			(5)
#define TIMER0_CompareModeFastPWMNonInverted	(6)
#define TIMER0_CompareModeFastPWMInverted		(7)
/*Compare Match OUTPUT MODE FOR TIMER0 in mode phase correct PWM*/
#define TIMER0_CompareModePhaseCorrectPWMOFF         8
#define TIMER0_CompareModePhaseCorrectPWMNonInverted 9
#define TIMER0_CompareModePhaseCorrectPWMInverted    10
/*	Timer0 MODES	*/
#define TIMER0_NormalMode						110
#define TIMER0_CTCMode							111
#define TIMER0_PWMPhaseCorrectMode				112
#define TIMER0_FastPWMMode						113
/*PRESCALER VALUES TIMER0*/
#define TIMER0_PRESCALER_NOCS		         (0x00)
#define TIMER0_PRESCALER_NoPS		         (0x01)
#define TIMER0_PRESCALER_8			         (0x02)
#define TIMER0_PRESCALER_64			         (0x03)
#define TIMER0_PRESCALER_256		         (0x04)
#define TIMER0_PRESCALER_1024                (0x05)
#define TIMER0_PRESCALER_CountFalling        (0x06)
#define TIMER0_PRESCALER_CountRising         (0x07)
/*Masking*/
#define PRESCALER_MASK						0b11111000
/**************************************************************/
/* TIMER 1 MODES */
#define TIMER1_NormalMode                    1
#define TIMER1_PWMPhaseCorrect8BitsMode      2
#define TIMER1_PWMPhaseCorrect9BitsMode      3
#define TIMER1_PWMPhaseCorrect10BitsMode     4
#define TIMER1_CTCOnOCR1AMode                5
#define TIMER1_FastPWM8BitsMode              6
#define TIMER1_FastPWM9BitsMode              7
#define TIMER1_FastPWM10BitsMode             8
#define TIMER1_PWMPhaseCorrectOnOCR1Mode     9
#define TIMER1_PWMPhaseCorrectOnICR1Mode     10
#define TIMER1_CTCOnICR1Mode                 11
#define TIMER1_FastPWMOnOCR1Mode             12
#define TIMER1_FastPWMOnICR1Mode             13
#define TIMER1_CTCOnOCR1BMode				14
/*PRESCALER VALUES FOR TIMER1*/
#define TIMER1_PRESCALER_NOCS		         (0x00)
#define TIMER1_PRESCALER_NoPS		         (0x01)
#define TIMER1_PRESCALER_8			         (0x02)
#define TIMER1_PRESCALER_64			         (0x03)
#define TIMER1_PRESCALER_256		         (0x04)
#define TIMER1_PRESCALER_1024                (0x05)
#define TIMER1_PRESCALER_CountFalling        (0x06)
#define TIMER1_PRESCALER_CountRising         (0x07)
/*Compare Match OUTPUT MODE FOR TIMER1 in mode CTC*/
#define TIMER1_CompareModeOFFChannelA 			(11)
#define TIMER1_CompareModeSETChannelA           (22)
#define TIMER1_CompareModeCLRChannelA           (33)
#define TIMER1_CompareModeTOGGLEChannelA        (44)
#define TIMER1_CompareModeOFFChannelB 			(55)
#define TIMER1_CompareModeSETChannelB           (66)
#define TIMER1_CompareModeCLRChannelB           (77)
#define TIMER1_CompareModeTOGGLEChannelB        (88)
/*Compare Match OUTPUT MODE FOR TIMER0 in mode fast PWM*/
#define TIMER1_CompareModeFastPWMOFFChannelA			(5)
#define TIMER1_CompareModeFastPWMNonInvertedChannelA	(6)
#define TIMER1_CompareModeFastPWMInvertedChannelA		(7)
#define TIMER1_CompareModeFastPWMOFFChannelB			(8)
#define TIMER1_CompareModeFastPWMNonInvertedChannelB	(9)
#define TIMER1_CompareModeFastPWMInvertedChannelB		(10)


/***************************************************/
#define ICU_Rising_Edge 	1
#define ICU_Falling_Edge 	2
#define Enabled			1
#define Disabled		2
#endif /* HEADER_TIMER_PRIVATE_H_ */
