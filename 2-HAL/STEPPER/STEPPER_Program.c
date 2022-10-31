/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  MOHAMMED AYMAN        ***************************/
/*************                LAYER :   HAL 			      ***************************/
/*************                SWC :     STEPPER	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/

#include "../../4-LIB/STD_TYPES.h"
#include "util/delay.h"

#include "../../1-MCAL/DIO/DIO_Interface.h"
#include "STEPPER_Config.h"
#include "STEPPER_Interface.h"
#include "STEPPER_Private.h"


void STEPPER_Init( u8 Copy_u8Port , u8 Copy_u8BluePin , u8 Copy_u8PinkPin , u8 Copy_u8YellowPin , u8 Copy_u8OrangePin  )
{
	DIO_u8SetPinDirection( Copy_u8Port , Copy_u8BluePin , DIO_u8PIN_OUTPUT ) ;
	DIO_u8SetPinDirection( Copy_u8Port , Copy_u8PinkPin , DIO_u8PIN_OUTPUT ) ;
	DIO_u8SetPinDirection( Copy_u8Port , Copy_u8YellowPin , DIO_u8PIN_OUTPUT ) ;
	DIO_u8SetPinDirection( Copy_u8Port , Copy_u8OrangePin , DIO_u8PIN_OUTPUT ) ;
}


void STEPPER_GoForward(  u8 Copy_u8Port , u8 Copy_u8BluePin , u8 Copy_u8PinkPin , u8 Copy_u8YellowPin , u8 Copy_u8OrangePin , u32 Copy_u32Steps )
{
	u32 Local_u32Iterator = 0 ;
	for( Local_u32Iterator=0 ; Local_u32Iterator < Copy_u32Steps ; Local_u32Iterator++ )
	{
		DIO_u8SetPinValue( Copy_u8Port , Copy_u8BluePin   , DIO_u8PIN_LOW   ) ;
		DIO_u8SetPinValue( Copy_u8Port , Copy_u8PinkPin   , DIO_u8PIN_HIGH  ) ;
		DIO_u8SetPinValue( Copy_u8Port , Copy_u8YellowPin , DIO_u8PIN_HIGH  ) ;
		DIO_u8SetPinValue( Copy_u8Port , Copy_u8OrangePin , DIO_u8PIN_HIGH  ) ;

		_delay_ms( 2 ) ;

		DIO_u8SetPinValue( Copy_u8Port , Copy_u8BluePin   , DIO_u8PIN_HIGH  ) ;
		DIO_u8SetPinValue( Copy_u8Port , Copy_u8PinkPin   , DIO_u8PIN_LOW   ) ;
		DIO_u8SetPinValue( Copy_u8Port , Copy_u8YellowPin , DIO_u8PIN_HIGH  ) ;
		DIO_u8SetPinValue( Copy_u8Port , Copy_u8OrangePin , DIO_u8PIN_HIGH  ) ;

		_delay_ms( 2 ) ;

		DIO_u8SetPinValue( Copy_u8Port , Copy_u8BluePin   , DIO_u8PIN_HIGH  ) ;
		DIO_u8SetPinValue( Copy_u8Port , Copy_u8PinkPin   , DIO_u8PIN_HIGH  ) ;
		DIO_u8SetPinValue( Copy_u8Port , Copy_u8YellowPin , DIO_u8PIN_LOW   ) ;
		DIO_u8SetPinValue( Copy_u8Port , Copy_u8OrangePin , DIO_u8PIN_HIGH  ) ;

		_delay_ms( 2 ) ;

		DIO_u8SetPinValue( Copy_u8Port , Copy_u8BluePin   , DIO_u8PIN_HIGH  ) ;
		DIO_u8SetPinValue( Copy_u8Port , Copy_u8PinkPin   , DIO_u8PIN_HIGH  ) ;
		DIO_u8SetPinValue( Copy_u8Port , Copy_u8YellowPin , DIO_u8PIN_HIGH  ) ;
		DIO_u8SetPinValue( Copy_u8Port , Copy_u8OrangePin , DIO_u8PIN_LOW   ) ;

		_delay_ms( 2 ) ;
	}
}


void STEPPER_GoBackward(  u8 Copy_u8Port , u8 Copy_u8BluePin , u8 Copy_u8PinkPin , u8 Copy_u8YellowPin , u8 Copy_u8OrangePin , u32 Copy_u32Steps )
{
	u32 Local_u32Iterator = 0 ;
	for( Local_u32Iterator=0 ; Local_u32Iterator < Copy_u32Steps ; Local_u32Iterator++ )
	{
		DIO_u8SetPinValue( Copy_u8Port , Copy_u8BluePin   , DIO_u8PIN_HIGH   ) ;
		DIO_u8SetPinValue( Copy_u8Port , Copy_u8PinkPin   , DIO_u8PIN_HIGH  ) ;
		DIO_u8SetPinValue( Copy_u8Port , Copy_u8YellowPin , DIO_u8PIN_HIGH  ) ;
		DIO_u8SetPinValue( Copy_u8Port , Copy_u8OrangePin , DIO_u8PIN_LOW  ) ;

		_delay_ms( 2 ) ;

		DIO_u8SetPinValue( Copy_u8Port , Copy_u8BluePin   , DIO_u8PIN_HIGH  ) ;
		DIO_u8SetPinValue( Copy_u8Port , Copy_u8PinkPin   , DIO_u8PIN_HIGH   ) ;
		DIO_u8SetPinValue( Copy_u8Port , Copy_u8YellowPin , DIO_u8PIN_LOW  ) ;
		DIO_u8SetPinValue( Copy_u8Port , Copy_u8OrangePin , DIO_u8PIN_HIGH  ) ;

		_delay_ms( 2 ) ;

		DIO_u8SetPinValue( Copy_u8Port , Copy_u8BluePin   , DIO_u8PIN_HIGH  ) ;
		DIO_u8SetPinValue( Copy_u8Port , Copy_u8PinkPin   , DIO_u8PIN_LOW  ) ;
		DIO_u8SetPinValue( Copy_u8Port , Copy_u8YellowPin , DIO_u8PIN_HIGH   ) ;
		DIO_u8SetPinValue( Copy_u8Port , Copy_u8OrangePin , DIO_u8PIN_HIGH  ) ;

		_delay_ms( 2 ) ;

		DIO_u8SetPinValue( Copy_u8Port , Copy_u8BluePin   , DIO_u8PIN_LOW  ) ;
		DIO_u8SetPinValue( Copy_u8Port , Copy_u8PinkPin   , DIO_u8PIN_HIGH  ) ;
		DIO_u8SetPinValue( Copy_u8Port , Copy_u8YellowPin , DIO_u8PIN_HIGH  ) ;
		DIO_u8SetPinValue( Copy_u8Port , Copy_u8OrangePin , DIO_u8PIN_HIGH   ) ;

		_delay_ms( 2 ) ;
	}
}


void STEPPER_TurnOFF( u8 Copy_u8Port , u8 Copy_u8BluePin , u8 Copy_u8PinkPin , u8 Copy_u8YellowPin , u8 Copy_u8OrangePin  )
{
	DIO_u8SetPinValue( Copy_u8Port , Copy_u8BluePin   , DIO_u8PIN_HIGH  ) ;
	DIO_u8SetPinValue( Copy_u8Port , Copy_u8PinkPin   , DIO_u8PIN_HIGH  ) ;
	DIO_u8SetPinValue( Copy_u8Port , Copy_u8YellowPin , DIO_u8PIN_HIGH  ) ;
	DIO_u8SetPinValue( Copy_u8Port , Copy_u8OrangePin , DIO_u8PIN_HIGH   ) ;
}
