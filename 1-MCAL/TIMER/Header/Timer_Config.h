/*
 * Timer_Config.h
 *
 *  Created on: Sep 19, 2022
 *      Author: mhmd wael
 */

#ifndef HEADER_TIMER_CONFIG_H_
#define HEADER_TIMER_CONFIG_H_

#define TIMER0_PRESCALER_MODE		TIMER0_PRESCALER_8
#define TIMER0_PreloadValue 		192						//	MAX VALUE = 254
#define TIMER0_CompareMatchValue	250

#define TIMER0_CompareOutputMode    TIMER0_CompareModeFastPWMNonInverted   /*OPTIONS :
																			 *************Non PWM Mode*******************
																			 * 1-TIMER0_CompareModeOFF
																			 * 2-TIMER0_CompareModeSET
																			 * 3-TIMER0_CompareModeCLR
																			 * 4-TIMER0_CompareModeTOGGLE
																			 *************FAST PWM*******************
																			 * 5-TIMER0_CompareModeFastPWMOFF
																			 * 6-TIMER0_CompareModeFastPWMNonInverted
																			 * 7-TIMER0_CompareModeFastPWMInverted
																			 * *************PHASE CORRECT PWM*******************
																			 * 5-TIMER0_CompareModePhaseCorrectPWMOFF
																			 * 6-TIMER0_CompareModePhaseCorrectPWMNonInverted
																			 * 7-TIMER0_CompareModePhaseCorrectPWMInverted
																			 *****************************************************/
#define TIMER1_PRESCALER_MODE		TIMER1_PRESCALER_8
#define TIMER1_CompareOutputMode    TIMER1_CompareModeFastPWMNonInvertedChannelB   /*OPTIONS :
																			 *************Non PWM Mode*******************
																			 * 1-TIMER1_CompareModeOFFChannelA
																			 * 2-TIMER1_CompareModeSETChannelA
																			 * 3-TIMER1_CompareModeCLRChannelA
																			 * 4-TIMER1_CompareModeTOGGLEChannelA
																			 * 5-TIMER1_CompareModeOFFChannelB
																			 * 6-TIMER1_CompareModeSETChannelB
																			 * 7-TIMER1_CompareModeCLRChannelB
																			 * 8-TIMER1_CompareModeTOGGLEChannelB
																			 *************FAST PWM*******************
																			 * 1-TIMER1_CompareModeFastPWMOFFChannelA
																			 * 2-TIMER1_CompareModeFastPWMNonInvertedChannelA
																			 * 3-TIMER1_CompareModeFastPWMInvertedChannelA
																			 * 4-TIMER1_CompareModeFastPWMOFFChannelB
																			 * 5-TIMER1_CompareModeFastPWMNonInvertedChannelB
																			 * 6-TIMER1_CompareModeFastPWMInvertedChannelB
																			 *****************************************************/
#define ICU_Status				Enabled         //options : Enabled , Disabled

#endif /* HEADER_TIMER_CONFIG_H_ */
