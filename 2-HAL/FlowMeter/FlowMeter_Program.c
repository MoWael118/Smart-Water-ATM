/*
 * FlowMeter_Program.c
 *
 *  Created on: Nov 6, 2022
 *      Author: moham
 */

#include "../../4-LIB/STD_TYPES.h"

#include "FlowMeter_Config.h"
#include "FlowMeter_Interface.h"
#include "FlowMeter_Private.h"
#include "../../1-MCAL/EXTI/EXTI_Interface.h"
#include "../../1-MCAL/TIMER/Header/Timer_Interface.h"

u16 * FLOWMETER_VolumeReading = NULL ;
u16 * FLOWMETER_FlowRate = NULL ;

u16 Frequency  = 0 ;
u16 Volume = 0 ;
u16 FlowRate_ml_s = 0 ;

u8 ISR_Flag = UNDONE ;

u16 Previous_Freq = 0;


void FLOWMETER_Init( u16 * Copy_pu16VolumeInSec , u16 * Copy_pu16FlowRate )
{
	/*Initialize Global Variable to Carry Volume*/
	FLOWMETER_VolumeReading = Copy_pu16VolumeInSec ;

	/*Initialize Global Variable to Carry Flow Rate*/
	FLOWMETER_FlowRate = Copy_pu16FlowRate ;

	/*EXTI2 Set Sense Control & Set Call Back */
	EXTI_u8Int2SenseControl(RISING_EDGE);
	EXTI_u8Int2CallBack( &EXTI ) ;


	/*Timer0 Set Compare Value and Set Call Back*/
	TIMER_SetCallBackFunc( TIMER0_COMPINT , &TIMER_ISR ) ;
	TIMER_VoidSetCompareMatchValue( TIMER0 , COMPARE_MATCH_VALUE ) ;


}

void FLOWMETER_voidGetVolume( u16 * Copy_pu16VolumeInSec , u16 * Copy_pu16FlowRate )
{
	/* Enable INT2 & Timer 0 Peripheral */
	EXTI_u8IntEnable( INT2 ) ;
	TIMER0_VoidInit( TIMER0_CTCMode );


	/*Polling Until Required Number of Interrupts is Reached , In Our Case -> 400 */
	while( ISR_Flag == UNDONE ) ;

	/* To Stop Timer and EXTI Peripheral */
	FLOWMETER_voidFinished();

	/*Flow Rate Equation in ml/s*/
	FlowRate_ml_s = (s16)( ( Previous_Freq * (u32)60000 ) / ( (u32)27000  ) ) ;

	/*Calculating Volume */
	Volume = Volume + FlowRate_ml_s ;

	/*Dereferencing Global Pointer to Volume Variable*/
	*FLOWMETER_VolumeReading = Volume ;

	/*Dereferencing Global Pointer to Flow Rate Variable */
	/* Flow Rate is Calculated with in 1/20 from second so multiplied by 20 in order to make it in one second */
	*FLOWMETER_FlowRate = FlowRate_ml_s * (s16)20 ;

	/*Turn Back ISR_Flag -> (UNDONE)*/
	ISR_Flag = UNDONE ;

	/*Frequency equals zero to make sure that the timer is working correctly*/
	Frequency = 0 ;

}

void FLOWMETER_voidFinished( void )
{
	/*Disable Timer0 Peripheral and EXTI2*/
	EXTI_u8IntDisable(INT2);
	TIMER0_voidStop();
}

void EXTI (void)
{
	Frequency ++ ;
}

void TIMER_ISR(void)
{
	static u16 Local_u16Counter = 0 ;
	Local_u16Counter++ ;

	if( Local_u16Counter == 400 ) /* 1/20 from second passed */
	{
		/*Required Number of Interrupts is Reached*/
		ISR_Flag = DONE ;

		/*Assign Current Frequency into a Variable in order to use it in flow equation*/
		Previous_Freq = Frequency ;

		Frequency = 0 ;

		Local_u16Counter = 0 ;
	}
}
