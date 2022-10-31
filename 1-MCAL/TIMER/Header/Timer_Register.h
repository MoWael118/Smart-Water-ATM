/*
 * Timer_Register.h
 *
 *  Created on: Sep 19, 2022
 *      Author: mhmd wael
 */

#ifndef HEADER_TIMER_REGISTER_H_
#define HEADER_TIMER_REGISTER_H_
#include "../../../LIBRARY/stdtype.h"
/******************** TIMER0 REGISTERS ***************************/
#define TIMER0_TCCR0		(*(volatile u8*)0x53)
#define TIMER0_TCNT0        (*(volatile u8*)0x52)
#define TIMER0_OCR0         (*(volatile u8*)0x5C)
#define TIMER0_TIMSK        (*(volatile u8*)0x59)
#define TIMER0_TIFR         (*(volatile u8*)0x58)
/********************* TCCR PINS *********************************/
#define	TCCR0_FOC0			7
#define TCCR0_WGM00			6
#define TCCR0_WGM01			3
#define TCCR0_COM00			4
#define TCCR0_COM01			5
#define TCCR0_CS00			0
#define TCCR0_CS01			1
#define TCCR0_CS02			2
/*********************TIMSK PINS***********************************/
#define TIMSK_TOIE0			0
#define TIMSK_OCIE0 		1
/********************TIFR PINS*************************************/
#define TIFR_OCF0			1
#define TIFR_TOV0			0
/******************************************************************/
/******************************************************************/
/******************************************************************/
/********************* TIMER1 REGISTERS ***************************/
#define TIMER1_TCCR1A					(*(volatile u8*)0x4F)
#define TIMER1_TCCR1B                   (*(volatile u8*)0x4E)
#define TIMER1_TCNT1H                   (*(volatile u8*)0x4D)
#define TIMER1_TCNT1L                   (*(volatile u8*)0x4C)
#define TIMER1_TCNT1                   (*(volatile u16*)0x4C)
#define TIMER1_OCR1AH                   (*(volatile u8*)0x4B)
#define TIMER1_OCR1AL                   (*(volatile u8*)0x4A)
#define TIMER1_OCR1A                   (*(volatile u16*)0x4A)
#define TIMER1_OCR1BH                   (*(volatile u8*)0x49)
#define TIMER1_OCR1BL                   (*(volatile u8*)0x48)
#define TIMER1_OCR1B                   (*(volatile u16*)0x48)
#define TIMER1_ICR1H                    (*(volatile u8*)0x47)
#define TIMER1_ICR1L                    (*(volatile u8*)0x46)
#define TIMER1_ICR1                    (*(volatile u16*)0x46)
#define TIMER1_TIMSK       				(*(volatile u8*)0x59)
#define TIMER1_TIFR                     (*(volatile u8*)0x58)

/******************** TCCR1A PINS **********************************/
#define TCCR1A_COM1A1                                7
#define TCCR1A_COM1A0                                6
#define TCCR1A_COM1B1                                5
#define TCCR1A_COM1B0                                4
#define TCCR1A_FOC1A                                 3
#define TCCR1A_FOC1B                                 2
#define TCCR1A_WGM11                                 1
#define TCCR1A_WGM10                                 0
/******************** TCCR1B PINS *********************************/
#define TCCR1B_ICNC1								 7
#define TCCR1B_ICES1								 6
#define TCCR1B_WGM13								 4
#define TCCR1B_WGM12								 3
#define TCCR1B_CS12                                  2
#define TCCR1B_CS11                                  1
#define TCCR1B_CS10                                  0
/*********************TIMSK PINS***********************************/
#define TIMSK_TOIE1			2
#define TIMSK_OCIE1B 		3
#define TIMSK_OCIE1A		4
#define TIMSK_TICIE1		5
/******************************************************************/
/******************************************************************/
/******************* TIMER2 REGISTERS *****************************/
#define TIMER2_TCCR2		(*(volatile u8*)0x45)
#define TIMER2_TCNT2        (*(volatile u8*)0x44)
#define TIMER2_OCR2         (*(volatile u8*)0x43)
#define TIMER2_TIMSK        (*(volatile u8*)0x59)
#define TIMER2_TIFR         (*(volatile u8*)0x58)
/********************* TCCR PINS *********************************/
#define	TCCR2_FOC2			7
#define TCCR2_WGM20			6
#define TCCR2_WGM21			3
#define TCCR2_COM20			4
#define TCCR2_COM21			5
#define TCCR2_CS20			0
#define TCCR2_CS21			1
#define TCCR2_CS22			2
/*********************TIMSK PINS***********************************/
#define TIMSK_TOIE2			6
#define TIMSK_OCIE2 		7
/********************TIFR PINS*************************************/
#define TIFR_OCF2			7
#define TIFR_TOV2			6


















#endif /* HEADER_TIMER_REGISTER_H_ */
