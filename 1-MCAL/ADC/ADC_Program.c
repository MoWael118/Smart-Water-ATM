/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  MOHAMMED AYMAN        ***************************/
/*************                LAYER :   MCAL			      ***************************/
/*************                SWC :     ADC 		          ***************************/
/*************                VERSION : 1.00		          ***************************/
/*************                DATE : 12-10-2022		          ***************************/
/****************************************************************************************/
/****************************************************************************************/
#include "../../4-LIB/STD_TYPES.h"
#include "../../4-LIB/BIT_MATH.h"
#include <util/delay.h>

#include "ADC_Config.h"
#include "ADC_Register.h"
#include "ADC_Private.h"
#include "ADC_Interface.h"




/***Static Because Global Variables will not be used in another file
     Global Variable to Use Local Variable in another Function*****/
static u16* ADC_pu16Reading = NULL ;
static void(*ADC_pvCallBackNotificationFunc)(void) = NULL ;

/*Flag to Check on Conversion if Completed when using Asynchronous Function*/
u8 ADC_u8BusyState = IDLE ;





void ADC_voidInit(void)
{
	/*REFERENCE VOLTAGE CONFIGURATION*/
#if ADC_REFERENCE_SELECT == AREF
	// REFS0    REFS1
	ADMUX &= (~ ( (1<<ADMUX_REFS0) | (1<<ADMUX_REFS1) ) ) ;    	  //  	0         0      -> AREF


#elif ADC_REFERENCE_SELECT == AVCC
	// REFS0    REFS1
	ADMUX |= (1<<ADMUX_REFS0) ;								       //    1         0      -> AVCC
	ADMUX &= (~(1<<ADMUX_REFS1));

#elif ADC_REFERENCE_SELECT == INTERNAL2_56V
	// REFS0    REFS1
	ADMUX |= (1<<ADMUX_REFS1) | (1<<ADMUX_REFS0);                //   1        1         -> 2.56v Internal

#else

#error "WRONG ADC_REFERENCE_SELECT Configuration Option"

#endif

	/*RESOLUTION OF ADC : No Of Bits Of Each Sample*/

#if ADC_RESOLUTION == _10_BIT
	/*Right Adjust*/
	ADMUX &= (~(1<<ADMUX_ADLAR)) ;

#elif ADC_RESOLUTION == _8_BIT
	/*Left Adjust*/
	ADMUX |= (1<<ADMUX_ADLAR) ;

#else

#error "WRONG ADC_RESOLUTION Configuration Option"

#endif


	/*Set ADC Prescaler Using BIT MASKING*/
	ADCSRA &= ADC_PRESCALER_MASK ;
	ADCSRA |= ADC_PRESCALER ;

	/*ADC Enable*/
#if ADC_ENABLE == ENABLED

	ADCSRA |= ( 1 << ADCSRA_ADEN );

#elif ADC_ENABLE == DISABLED

	ADCSRA &= (~( 1 << ADCSRA_ADEN ));
#else

#error "WRONG ADC_ENABLE Configuration Option"

#endif



#if ADC_INTERRUPT_ENABLE == ENABLED
	ADCSRA |= (1<<ADCSRA_ADIE) ;
#elif ADC_INTERRUPT_ENABLE == DISABLED
	ADCSRA &= (~(1<<ADCSRA_ADIE)) ;
#else
#error "WRONG ADC_INTERRUPT_ENABLE Configutration Option"
#endif


#if ADC_AUTO_TRIGGER_ENABLE  == ENABLED

	/*Enable Auto Trigger Mode*/
	ADCSRA |= (1<<ADCSRA_ADATE) ;

	/*Set Auto Trigger Source*/
	SFIOR &= ( ADC_AUTO_TRIGGER_MASK ) ;
	SFIOR |= ( ADC_AUTO_TRIGGER_SOURCE << ADC_AUTO_TRIGGER_BITS_STARTING_FROM ) ;

#elif ADC_AUTO_TRIGGER_ENABLE == DISABLED

	ADCSRA &= (~(1<<ADCSRA_ADATE)) ;

#else

#error "WRONG ADC_AUTO_TRIGGER_ENABLE Configuration Option"

#endif
}


u8 ADC_u8StartConversionSynch( u8 Copy_u8Channel , u16* Copy_pu16Reading )
{
	/*SINGLE CONVERSION MODE*/

	u8 Local_u8ErrorState =OK;
	u32 Local_u32Counter=0;

	if( ADC_u8BusyState == IDLE )
	{
		/*ADC is Now BUSY*/
		ADC_u8BusyState = BUSY ;
		/*Clear the MUX Bits in ADMUX Register*/
		ADMUX &= ADC_ANALOG_CHANNEL_MASK ;

		/*Set Required Channel into MUX Bits*/
		ADMUX |= ( Copy_u8Channel ) ;

		/*Start Conversion*/
		ADCSRA |= (1 << ADCSRA_ADSC);

		/*Polling (Busy Waiting) Until the Conversion Complete (Flag is Set) or Counter Equals Timeout Value*/
		while( (GET_BIT( ADCSRA , ADCSRA_ADIF )==0) && (Local_u32Counter != ADC_u32TIME_OUT) )
		{
			Local_u32Counter++;
		}
		if( Local_u32Counter == ADC_u32TIME_OUT )
		{
			/*Loop is Broken Because The Timeout is Reached*/
			Local_u8ErrorState = NOK;
		}
		else
		{
			/*Loop is Broken Because Complete Conversion Flag is Set*/

			/*Clear the Conversion Complete Flag*/
			ADCSRA |= (1<<ADCSRA_ADIF);

#if ADC_RESOLUTION == _8_BIT
			/*Return Reading of 8 Bits*/
			*Copy_pu16Reading = ADCH;
#elif ADC_RESOLUTION == _10_BIT
			/*Return Reading of 10 Bits*/
			*Copy_pu16Reading = ADC ;
#else
#error "WRONG ADC_RESOLUTION Configuration Option"
#endif

			/*ADC Finished , Return to IDLE*/
			ADC_u8BusyState = IDLE ;
		}

	}
	else
	{
		Local_u8ErrorState = BUSY_FUNC ;
	}
	return Local_u8ErrorState;
}



u8 ADC_u8StartConversionAsynch( u8 Copy_u8Channel , u16*Copy_pu16Reading ,  void(*Copy_pvNotificationFunc)(void) )
{

	u8 Local_u8ErrorState = OK;

	if( ADC_u8BusyState == IDLE )
	{
		if( Copy_pu16Reading == NULL || Copy_pvNotificationFunc == NULL )
		{
			Local_u8ErrorState = NULL_POINTER ;
		}
		else
		{
			/*Make ADC Busy in order Not to Work until being IDLE*/
			ADC_u8BusyState = BUSY ;
			/*Initialize reading variable and the call back notification function globaly
		  to use it in ISR*/
			ADC_pvCallBackNotificationFunc = Copy_pvNotificationFunc ;
			ADC_pu16Reading = Copy_pu16Reading ;

			/*Clear the MUX Bits in ADMUX Register*/
			ADMUX &= ADC_ANALOG_CHANNEL_MASK ;
			/*Set Required Channel into MUX Bits*/
			ADMUX |= (Copy_u8Channel) ;

#if ( (ADC_AUTO_TRIGGER_SOURCE == FREE_RUNNING_MODE)  &&  (ADC_AUTO_TRIGGER_ENABLE == ENABLED) )  || (ADC_AUTO_TRIGGER_ENABLE==DISABLED)
			/*Start  Conversion*/
			ADCSRA |= (1<<ADCSRA_ADSC);
#endif
			/*Enalbe Interrupt*/
			ADCSRA |= (1<<ADCSRA_ADIE);
		}
	}
	else
	{
		Local_u8ErrorState = BUSY_FUNC ;
	}
	return Local_u8ErrorState ;
}



void __vector_16(void) __attribute__((signal));
void __vector_16(void)
{

	/*Read ADC Result*/
#if ADC_RESOLUTION == _8_BIT
	/*Return Reading of 8 Bits*/
	*ADC_pu16Reading = ADCH;
#elif ADC_RESOLUTION == _10_BIT
	/*Return Reading of 10 Bits*/
	*ADC_pu16Reading = ADC ;
#else
#error "WRONG ADC_RESOLUTION Configuration Option"
#endif

	/*Make ADC State Be IDLE Because Conversion is Finished*/
	ADC_u8BusyState = IDLE;

	/*Invoke the Call Back Notification Function*/
	ADC_pvCallBackNotificationFunc();

	/*Disable ADC Conversion Complete Interrupt*/
	ADCSRA &= (~(1<<ADCSRA_ADIE));
}
