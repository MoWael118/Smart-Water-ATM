/*
 * main.c
 *
 *  Created on: Oct 29, 2022
 *      Author: moham
 */
#include "../4-LIB/STD_TYPES.h"
#include "../4-LIB/BIT_MATH.h"
#include "../1-MCAL/DIO/DIO_Interface.h"
#include "../1-MCAL/EXTI/EXTI_Interface.h"
#include "../2-HAL/CLCD/CLCD_Interface.h"
#include "../2-HAL/KEYPAD/KEYPAD_Interface.h"
#include "../1-MCAL/PORT/PORT_Interface.h"
#include "../2-HAL/IR_Sensor/IR_Sensor.h"
#include "../1-MCAL/GIE/GIE_Interface.h"
#include "../2-HAL/Coin_Module/Coin_Module.h"
#include "../2-HAL/FlowMeter/FlowMeter_Interface.h"
#include "../2-HAL/STEPPER/STEPPER_Interface.h"
#include "main.h"
#include <util/delay.h>



s16 Flow_Volume = NULL ;

s16 Flow_Rate   = NULL ;

u8 User_Choice = NULL ;

void (* PTR_To_User_Choice)(void) = NULL ;

u8 NoOfBottlesInserted = NULL ;

f32 Credit_Recycle = NULL ;

u8 Bottle_Exist = NON_EXIST ;

u16 Water_Capacity = NULL ;

u16 Size = NULL ;

f32 Price = NULL ;

f32 Coin_Module_Price = NULL;





void main(void)
{
	/* PORT Initialization */
	PORT_voidInit( ) ;

	/* Check If Bottle Exist At The Beginning */
	DIO_u8GetPinValue( DIO_u8PORTD , DIO_u8Pin2 , &Bottle_Exist ) ;

	/* Global Interrupt Enable For IR Sensor */
	GIE_voidEnable( ) ;

	/* Interrupt 0 Enable For IR Sensor To Check Bottle Existant */
	EXTI_voidInit0( ) ;

	/* Call ISR For Interrupt 0 */
	EXTI_u8Int0CallBack( &ISR1_Sensing_Bottle_Exist ) ;

	/* LCD Initialization */
	CLCD_voidInit( ) ;

	/*FLOWMETER Initialization */
	FLOWMETER_Init( &Flow_Volume , &Flow_Rate ) ;

	/*Going To Position Of Row One And Column One On LCD*/
	CLCD_u8GoToRowColumn(0,0) ;

	/* Displaying Welcome On LCD */
	CLCD_u8SendString("Welcome") ;

	/* Delay For 2 Seconds To Be Able To See Welcome On LCD */
	_delay_ms(2000) ;

	while(1)
	{

		/* Calling Back To Main Menu Function */
		BackToMainMenu( ) ;

	}

}

/*
 * Prototype   : void BackToMainMenu (void)
 *
 * Description : It Sets The User Choice And Call Mode Wanted By The User
 *
 * Arguments   : void
 *
 * return      : void
 *
 */

void BackToMainMenu (void)
{
	/* Clearing LCD Screen */
	CLCD_voidClearScreen( ) ;

	/* Setting User Choice (Global Variable) With Return Of Main Menu Function That Return The Mode Wanted By User */
	User_Choice = MainMenu( ) ;

	/* Calling Menu Choosing Function That Set Pointer To User Choice With Selected Mode */
	Menu_Choosing( ) ;

	/* Calling The Selected Mode By Calling Pointer To User Choice */
	PTR_To_User_Choice( ) ;

}

/*
 * Prototype   : u8 MainMenu(void)
 *
 * Description : Interfacing With User To Select Specific Mode
 *
 * Arguments   : void
 *
 * return      : u8 Local Choice
 *
 */

u8 MainMenu(void)
{
	/* Initialization Local Variable To Store Number Of Mode Wanted */
	u8 Local_Choice=NULL;

	/* Clearing LCD Screen */
	CLCD_voidClearScreen();

	/* Displaying Enter Your Choice On LCD */
	CLCD_u8SendString("Enter Your Choice");

	/* Going To Position Of Row Two And Column One On LCD */
	CLCD_u8GoToRowColumn(1,0);

	/* Displaying 1- Bottle Recycle On LCD */
	CLCD_u8SendString("1- Bottle Recycle");

	/* Going To Position Of Row Three And Column One On LCD */
	CLCD_u8GoToRowColumn(2,0);

	/* Displaying 2- Bottle needed On LCD */
	CLCD_u8SendString("2- Bottle needed");

	/* Going To Position Of Row Three And Column One On LCD */
	CLCD_u8GoToRowColumn(3,0);

	/* Displaying 3- Refill needed On LCD */
	CLCD_u8SendString("3- Refill");

	/* Setting Local Choice (Local Variable) To KeyPad Input Return */
	Local_Choice = KEYPAD_u8PollingUntilKeyPressed() ;

	/* Check If The Local Choice Is Not Available Choice */
	if((Local_Choice >'3') || (Local_Choice<='0'))
	{
		/* Clearing LCD Screen */
		CLCD_voidClearScreen();

		/* Displaying Wrong Input On LCD */
		CLCD_u8SendString("Wrong Input");

		/* Going To Position Of Row Two And Column One On LCD */
		CLCD_u8GoToRowColumn(1,0);

		/* Displaying Please enter number On LCD */
		CLCD_u8SendString("Please enter number");

		/* Going To Position Of Row Three And Column One On LCD */
		CLCD_u8GoToRowColumn(2,0);

		/* Displaying from(1-3) On LCD */
		CLCD_u8SendString("from(1-3)");

		/* Delay For 2 Seconds To Be Able To Read LCD */
		_delay_ms(2000);

		/* Clearing LCD Screen */
		CLCD_voidClearScreen();

		/* Calling Main Menu Again So The User Will Be Able To Choose Available Mode*/
		MainMenu();

	}

	/* Returning Local Choice */
	return Local_Choice;

}

/*
 * Prototype   : void Menu_Choosing(void)
 *
 * Description : It Sets Global Pointer To The Mode Selected By The User
 *
 * Arguments   : void
 *
 * return      : void
 *
 */
void Menu_Choosing(void)
{
	/* Check User Choice Of Wanted Mode*/
	switch (User_Choice)
	{

	case '1':

		/* Setting Pointer To User Choice (Global Pointer) To Bottle Recycle Function */
		PTR_To_User_Choice=&BottleRecycle;

		break;

	case '2':

		/* Setting Pointer To User Choice (Global Pointer) To Bottle Needed Mode Function */
		PTR_To_User_Choice = &BottleNeddedMode;

		break;

	case '3':

		/* Setting Pointer To User Choice (Global Pointer) To Refill Mode Function */
		PTR_To_User_Choice=&Refill_Mode;

		break;

	}

	/* Setting User Choice To Null So Next User Can Choose His Mode*/
	User_Choice=NULL;

}
void Refill_Mode(void)
{
	u8 KeyPad_State = KEYPAD_NO_PRESSED_KEY;
	/*Show The Refill Menu*/
	CLCD_voidClearScreen();
	CLCD_u8GoToRowColumn(0,0);
	CLCD_u8SendString("select an option :");
	CLCD_u8GoToRowColumn(1,0);
	CLCD_u8SendString("1- Capacity = 500mL");
	CLCD_u8GoToRowColumn(2,0);
	CLCD_u8SendString("2- Capacity = 1L");
	CLCD_u8GoToRowColumn(3,0);
	CLCD_u8SendString("3- Back to Main Menu");
	/*GET pressed key from user*/
	KeyPad_State = KEYPAD_u8PollingUntilKeyPressed();

	switch (KeyPad_State)
	{
	/*Show Needed Price For 500mL */
	case '1' :
	case '2' :

		if( KeyPad_State == '1' )
		{
			Price = 3 ;
			Water_Capacity = 500 ;
		}
		else if ( KeyPad_State == '2' )
		{
			Price = 5 ;
			Water_Capacity = 1000 ;
		}

		CLCD_voidClearScreen();
		CLCD_u8GoToRowColumn(0,0);

		if(Credit_Recycle == NULL)
		{
			CLCD_u8SendString( "Price Needed =" ) ;
			CLCD_WriteFloatingNumber( Price , 1 , 0 , 14 ) ;

		}
		else if(Credit_Recycle != NULL)
		{
			CLCD_u8SendString( "Price =" ) ;
			CLCD_WriteFloatingNumber( Price , 1 , 0 , 8 ) ;
			CLCD_u8SendString( "EGP" ) ;
			CLCD_u8GoToRowColumn( 1 , 0 ) ;
			CLCD_u8SendString( "Credit = " ) ;
			CLCD_WriteFloatingNumber( Credit_Recycle , 2 , 1 , 9 );
			CLCD_u8GoToRowColumn( 2 , 0 ) ;
			CLCD_u8SendString( "Price Needed =" ) ;
			CLCD_WriteFloatingNumber( (Price-Credit_Recycle) , 2 , 2 , 14 );
		}
		_delay_ms(2000);

		CLCD_voidClearScreen();
		CLCD_u8SendString( "Price Needed =" ) ;

		CLCD_WriteFloatingNumber( (Price-Credit_Recycle-Coin_Module_Price) , 2 , 0 , 14 );

		while( Coin_Module_Price != ( Price - Credit_Recycle ) )
		{
			Coin_Module_Price += Coin_Value();
			CLCD_WriteFloatingNumber( (Price-Credit_Recycle-Coin_Module_Price) , 2 , 0 , 14 );
		}

		_delay_ms(1500);
		CLCD_voidClearScreen();
		CLCD_u8SendString( "Payment is Received" ) ;

		_delay_ms(1500);
		CLCD_voidClearScreen(  ) ;

		if( Bottle_Exist == NON_EXIST )
		{
			CLCD_u8SendString( "Put Your Bottle" ) ;
		}

		Bottle_Filling();

		while ( Bottle_Exist == NON_EXIST  )
		{
			CLCD_u8GoToRowColumn(0,0);
			CLCD_u8SendString( "Return Your Bottle" ) ;
			Bottle_Filling();
		}

		_delay_ms(2000);
		CLCD_voidClearScreen();
		CLCD_u8SendString( "Enjoy Your Water" );
		_delay_ms(2000);
		Coin_Module_Price = NULL ;
		Credit_Recycle=NULL;
		break;

	case '3' :
		/*Call For Main menu Function*/
		BackToMainMenu();
		break;
		/*Display Wrong input and try again*/
	default :
		CLCD_voidClearScreen();
		CLCD_u8GoToRowColumn(0,0);
		CLCD_u8SendString("Wrong Input");
		CLCD_u8GoToRowColumn(1,0);
		CLCD_u8SendString("Please Try Again");
		_delay_ms(2000);
		Refill_Mode();
	}

}
void BottleNeddedMode(void)
{
	u8 KeyPad_State = KEYPAD_NO_PRESSED_KEY ;
	/*Clear LCD Display*/
	CLCD_voidClearScreen();

	CLCD_u8GoToRowColumn(0,0);
	CLCD_u8SendString("Select an Option :");

	CLCD_u8GoToRowColumn(1,0);
	CLCD_u8SendString("1- Size = 500mL");
	CLCD_u8GoToRowColumn(2,0);
	CLCD_u8SendString("2- Size = 1L");
	CLCD_u8GoToRowColumn(3,0);
	CLCD_u8SendString("3- Back to Main Menu");

	KeyPad_State = KEYPAD_u8PollingUntilKeyPressed();

	switch( KeyPad_State )
	{
	/*Show Needed Price For 500mL */
		case '1' :
		case '2' :

			if( KeyPad_State == '1' )
			{
				Price = 3 ;
				Size = 500 ;
			}
			else if ( KeyPad_State == '2' )
			{
				Price = 4 ;
				Size = 1000 ;
			}

			CLCD_voidClearScreen();
			CLCD_u8GoToRowColumn(0,0);

			if(Credit_Recycle == NULL)
			{
				CLCD_u8SendString( "Price Needed =" ) ;
				CLCD_WriteFloatingNumber( Price , 1 , 0 , 14 ) ;

			}
			else if(Credit_Recycle != NULL)
			{
				CLCD_u8SendString( "Price =" ) ;
				CLCD_WriteFloatingNumber( Price , 1 , 0 , 8 ) ;
				CLCD_u8SendString( "EGP" ) ;
				CLCD_u8GoToRowColumn( 1 , 0 ) ;
				CLCD_u8SendString( "Credit = " ) ;
				CLCD_WriteFloatingNumber( Credit_Recycle , 2 , 1 , 9 );
				CLCD_u8GoToRowColumn( 2 , 0 ) ;
				CLCD_u8SendString( "Price Needed =" ) ;
				CLCD_WriteFloatingNumber( (Price-Credit_Recycle) , 2 , 2 , 14 );
			}
			_delay_ms(1000);

			CLCD_voidClearScreen();
			CLCD_u8SendString( "Price Needed =" ) ;

			CLCD_WriteFloatingNumber( (Price-Credit_Recycle-Coin_Module_Price) , 2 , 0 , 14 );

			while( Coin_Module_Price != ( Price - Credit_Recycle ) )
			{
				Coin_Module_Price += Coin_Value();
				CLCD_WriteFloatingNumber( (Price-Credit_Recycle-Coin_Module_Price) , 2 , 0 , 14 );
			}

			_delay_ms(1500);
			CLCD_voidClearScreen();
			CLCD_u8SendString( "Payment is Received" ) ;

			if( Size == 500 )
			{
				/*Stepper Motor 1 ON*/
				STEPPER_NEMA17_Control( DIO_u8PORTD , DIO_u8Pin0 , 360 ) ;

			}
			else if ( Size == 1000 )
			{
				/*Stepper Motor 2 ON*/
				STEPPER_NEMA17_Control( DIO_u8PORTD , DIO_u8Pin1 , 360 ) ;
			}

			_delay_ms(1000);
			CLCD_voidClearScreen() ;
			CLCD_u8SendString( "Take Your Bottle" ) ;
			_delay_ms(1000);
			Credit_Recycle=NULL;
			break;
	case '3':
		/*Back to Main Menu Option*/
		BackToMainMenu();
		break;
	default :
		CLCD_voidClearScreen();
		CLCD_u8GoToRowColumn(0,0);
		CLCD_u8SendString("WRONG OPTION");
		CLCD_u8GoToRowColumn(1,0);
		CLCD_u8SendString("PLEASE ENTER NUMBER");
		CLCD_u8GoToRowColumn(2,0);
		CLCD_u8SendString("FROM 1 -> 3");
		_delay_ms(2000);
		BottleNeddedMode();
		break;
	}
}
void BottleRecycle(void)
{
	/*To get sure screen is clear*/
	CLCD_voidClearScreen();
	/*Start counting number of bottles inserted*/
	CLCD_u8SendString("Press 0 to exit");
	while (KEYPAD_u8GetPressedKey() !=  '0' )
	{
		if(IR_Sensor_u8Read() == 1)
		{
			while(IR_Sensor_u8Read()== 1);
			NoOfBottlesInserted++;
		}
		CLCD_u8GoToRowColumn(1,0);
		CLCD_u8SendString("Number of bottles ");
		CLCD_u8GoToRowColumn(2,0);
		CLCD_u8SendString("inserted =");
		CLCD_voidWriteIntegerNumber(NoOfBottlesInserted,2,11);
		CLCD_u8GoToRowColumn(3,0);
		CLCD_u8SendString("Your Credit=");
		CLCD_WriteFloatingNumber((f32)(NoOfBottlesInserted/2.0),2,3,12);
		CLCD_u8GoToRowColumn(3,17);
		CLCD_u8SendString("EGP");
	}
	Credit_Recycle= (f32)(NoOfBottlesInserted/2.0);
	BackToMainMenu();
}

void ISR1_Sensing_Bottle_Exist(void)
{
	DIO_u8GetPinValue(DIO_u8PORTD,DIO_u8Pin2,&Bottle_Exist);
}

void Bottle_Filling (void)
{
	u8 Flag=0;
	while( Bottle_Exist == NON_EXIST ) ;
	CLCD_voidClearScreen();
	while( ( Bottle_Exist == EXIST ) && ( Flow_Volume < Water_Capacity ) )
	{
		if(Flag ==0){
			/*Pump on */
			DIO_u8SetPinValue( DIO_u8PORTA , DIO_u8Pin5 , DIO_u8PIN_HIGH ) ;

			/*valve on*/
			DIO_u8SetPinValue( DIO_u8PORTA , DIO_u8Pin6 , DIO_u8PIN_HIGH ) ;

			CLCD_u8GoToRowColumn(1,0);
			CLCD_u8SendString("Volume = ") ;
			//CLCD_u8GoToRowColumn(0,0);
			//CLCD_u8SendString( "Flow Rate = " );
			Flag =1;
		}
		FLOWMETER_voidGetVolume( &Flow_Volume , &Flow_Rate ) ;


		//CLCD_voidWriteIntegerNumber( (s32)Flow_Rate  , 0 , 12 );

		CLCD_voidWriteIntegerNumber( (s32)Flow_Volume , 1 , 9 ) ;

	}

	FLOWMETER_voidFinished();

	/*pump off*/
	DIO_u8SetPinValue( DIO_u8PORTA , DIO_u8Pin5 , DIO_u8PIN_LOW ) ;

	/*Valve off*/
	DIO_u8SetPinValue( DIO_u8PORTA , DIO_u8Pin6 , DIO_u8PIN_LOW  ) ;
	_delay_ms(1000);
	CLCD_voidClearScreen();
}
