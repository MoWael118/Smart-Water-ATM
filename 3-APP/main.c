/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHORS : SW_TEAM               ***************************/
/*************                LAYER :    APP  			      ***************************/
/*************                VERSION : 2.00		          ***************************/
/*************                DATE : 3/12/2022		          ***************************/
/****************************************************************************************/
/****************************************************************************************/



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


u16 Flow_Volume = NULL ;

u16 Flow_Rate   = NULL ;

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
	PORT_voidInit( ) ;
	DIO_u8GetPinValue( DIO_u8PORTD , DIO_u8Pin2 , &Bottle_Exist ) ;     // To check if bottle exist before program started
	GIE_voidEnable( ) ;
	EXTI_voidInit0( ) ;
	EXTI_u8Int0CallBack( &ISR1_Sensing_Bottle_Exist ) ;
	CLCD_voidInit( ) ;
	FLOWMETER_Init( &Flow_Volume , &Flow_Rate ) ;
	CLCD_u8GoToRowColumn(0,0) ;
	CLCD_u8SendString("Welcome") ;
	_delay_ms(2000) ;

	while(1)
	{
		BackToMainMenu( ) ;
	}
}



void BackToMainMenu (void)
{
	CLCD_voidClearScreen( ) ;
	User_Choice = MainMenu( ) ;
	Menu_Choosing( ) ;
	PTR_To_User_Choice( ) ;
}



u8 MainMenu(void)
{
	u8 Local_Choice=NULL;
	CLCD_voidClearScreen();
	CLCD_u8SendString("Enter Your Choice");
	CLCD_u8GoToRowColumn(1,0);
	CLCD_u8SendString("1- Bottle Recycle");
	CLCD_u8GoToRowColumn(2,0);
	CLCD_u8SendString("2- Bottle needed");
	CLCD_u8GoToRowColumn(3,0);
	CLCD_u8SendString("3- Refill");
	Local_Choice = KEYPAD_u8PollingUntilKeyPressed() ;
	if((Local_Choice >'3') || (Local_Choice<='0'))
	{
		CLCD_voidClearScreen();
		CLCD_u8SendString("Wrong Input");
		CLCD_u8GoToRowColumn(1,0);
		CLCD_u8SendString("Please enter number");
		CLCD_u8GoToRowColumn(2,0);
		CLCD_u8SendString("from(1-3)");
		_delay_ms(2000);
		CLCD_voidClearScreen();
		MainMenu();
	}
	return Local_Choice;
}



void Menu_Choosing(void)
{
	switch (User_Choice)
	{

	case '1': // set global pointer to bottle recycle function
		PTR_To_User_Choice=&BottleRecycle;
		break;
	case '2': // set global pointer to 2- Bottle needed function
		PTR_To_User_Choice = &BottleNeddedMode;
		break;
	case '3': // set global pointer to Refill function
		PTR_To_User_Choice=&Refill_Mode;
		break;
	}
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




/*
 * Prototype   : void BottleNeddedMode(void)
 *
 * Description : Bottle Needed Mode IS Executed
 *
 * Arguments   : void
 *
 * return      : void
 *
 */


void BottleNeddedMode(void)
{
	/* Local Variable to Hold Pressed Key Value */
	u8 Local_u8KeypadState = KEYPAD_NO_PRESSED_KEY ;

	/* Clear LCD Display */
	CLCD_voidClearScreen( ) ;

	/* Cursor on First Address Row 0 , Column 0 */
	CLCD_u8GoToRowColumn( ROW_1 , COL_1 ) ;
	CLCD_u8SendString("Select an Option :");

	/* Displaying First Option */
	CLCD_u8GoToRowColumn( ROW_2 , COL_1 ) ;
	CLCD_u8SendString("1- Size = 500mL");

	/* Displaying Second Option*/
	CLCD_u8GoToRowColumn( ROW_3 , COL_1 ) ;
	CLCD_u8SendString("2- Size = 1L");

	/* Displaying Third Option */
	CLCD_u8GoToRowColumn( ROW_4 , COL_1 ) ;
	CLCD_u8SendString("3- Back to Main Menu");

	/* Polling Until Any Key is Pressed */
	Local_u8KeypadState = KEYPAD_u8PollingUntilKeyPressed();

	/* Checking On Pressed Key */
	switch( Local_u8KeypadState )
	{
	/* User Pressed 1 OR 2 */
	case '1' :
	case '2' :
		/*If User Pressed 1 OR 2 This Block of Code will Be Executed*/

		/* Checking On Pressed Key to Set the Right Price and Size for Each Option */

		if( Local_u8KeypadState == '1' )
		{
			/* User Pressed 1 */
			/* Setting Price and Size of Bottle For First Option */
			Price = 3   /* 3 EGP   */ ;
			Size  = 500 /* 500 mL  */ ;
		}
		else if ( Local_u8KeypadState == '2' )
		{
			/* User Pressed 2 */
			/* Setting Price and Size of Bottle For Second Option */
			Price = 4    /* 4 EGP   */ ;
			Size  = 1000 /* 1000 mL */ ;
		}

		/* Clear Screen From Options */
		CLCD_voidClearScreen ( ) ;

		/* Return to Home Address */
		CLCD_u8GoToRowColumn( ROW_1 , COL_1 ) ;

		/* Check if User Have Credit From Recycling Process */

		/* User Don't Have Credit From Recycling Process */
		if( Credit_Recycle == NULL )
		{
			/* Display Bottle Price Depending On What User Chose */
			CLCD_u8SendString( "Price Needed =" ) ;
			CLCD_WriteFloatingNumber( Price , 2 , ROW_1 , COL_16 ) ;
		}

		/* User Have Credit From Recycling Process */

		else if( Credit_Recycle != NULL )
		{
			/* Displaying Bottle Price */
			CLCD_u8SendString( "Price =" ) ;
			CLCD_WriteFloatingNumber( Price , 2 , ROW_1 , COL_9 ) ;

			/* Display ( EGP ) */
			CLCD_u8GoToRowColumn( ROW_1 , COL_14 ) ;
			CLCD_u8SendString( "EGP" ) ;

			/* Displaying Credit that User Have From Recycling Process */
			CLCD_u8GoToRowColumn( ROW_2 , COL_1 ) ;
			CLCD_u8SendString( "Credit =" ) ;

			CLCD_WriteFloatingNumber( Credit_Recycle , 2 , ROW_2 , COL_10 );

			/* Display ( EGP ) */
			CLCD_u8GoToRowColumn( ROW_2 , COL_15 ) ;
			CLCD_u8SendString( "EGP" ) ;

			/* Displaying Price Needed For Bottle After Deducting From it Credit From Recycling Process */
			CLCD_u8GoToRowColumn( ROW_3 , COL_1 ) ;
			CLCD_u8SendString( "Price Needed =" ) ;

			CLCD_WriteFloatingNumber( ( Price - Credit_Recycle ) , 2 , ROW_3 , COL_16 ) ;

		}

		/* 1 Second Delay */
		_delay_ms( _1_SEC );

		/* Clearing Display */
		CLCD_voidClearScreen( ) ;

		/* Displaying Price Needed For Bottle and Keep Deducting From it While User Insert Coins */
		CLCD_u8SendString( "Price Needed =" ) ;

		CLCD_WriteFloatingNumber( ( Price - Credit_Recycle - Coin_Module_Price ) , 2 , ROW_1 , COL_16 ) ;

		/* Polling Until User Insert Required Amount of Coins */
		while( Coin_Module_Price != ( Price - Credit_Recycle ) )
		{
			/* Polling Until User Insert A Coin and Adding it to Variable ( Coin_Module_Price ) */
			/* Coin_Value Returns Value of Inserted Coin */
			Coin_Module_Price = Coin_Module_Price + Coin_Value( ) ;

			/* When User Add A Coin Display will Show Price Needed is Being Decreased */
			CLCD_WriteFloatingNumber( ( Price - Credit_Recycle - Coin_Module_Price ) , 2 , ROW_1 , COL_16 ) ;
		}

		/* While is Terminated When User Inserts Right Amount of Coins Required for His Choice */

		/* 1 Second Delay */
		_delay_ms( _1_SEC );

		/* Clearing Display  */
		CLCD_voidClearScreen( ) ;

		CLCD_u8SendString( "Payment is Received" ) ;

		/* Checking On Size of Bottle User Chose To Control A Motor From the 2 Motors */
		if( Size == 500 )  /* 500 mL */
		{
			/* User Chose 500 mL Bottle */

			/* Stepper Motor 1 ON ---> Connected to PIN D0 */

			STEPPER_NEMA17_Control( STEPPER_MOTOR_1_500mL_PORT , STEPPER_MOTOR_1_500mL_PIN , 360 ) ;

		}
		else if ( Size == 1000 )  /* 1000 mL */
		{
			/* User Chose 1000 mL Bottle */

			/* Stepper Motor 2 ON ---> Connected to PIN D1 */

			STEPPER_NEMA17_Control( STEPPER_MOTOR_2_1000mL_PORT , STEPPER_MOTOR_2_1000mL_PIN , 360 ) ;
		}

		/* 1 Second Delay */
		_delay_ms( _1_SEC ) ;

		/* Clearing Display  */
		CLCD_voidClearScreen( ) ;

		/* Displaying On First Address */
		CLCD_u8GoToRowColumn( ROW_1 , COL_1 ) ;
		CLCD_u8SendString( "Take Your Bottle" ) ;

		/* 2 Second Delay */
		_delay_ms( _2_SEC );

		/* Return Credit Back To Zero */
		/* If There was Recycle Credit User definitely used it */
		/* If There was not Recycle Credit then It's Default Value is 0 ( NULL ) */
		Credit_Recycle = NULL ;
		break;

		/* User Pressed 3 to Return Back to Main Menu */
	case '3':

		/*Back to Main Menu Option*/
		BackToMainMenu( ) ;
		break;

		/* User Pressed Any Key Other Than 1 , 2 , 3 */
	default :

		/* Clearing Display */
		CLCD_voidClearScreen( ) ;

/* Display Wrong Option and Right Options Should be Chosen */
		CLCD_u8GoToRowColumn( ROW_1 , COL_1 ) ;
		CLCD_u8SendString("WRONG OPTION") ;

		CLCD_u8GoToRowColumn( ROW_2 , COL_1 ) ;
		CLCD_u8SendString( "PLEASE ENTER NUMBER" ) ;

		CLCD_u8GoToRowColumn( ROW_3 , COL_1 );
		CLCD_u8SendString( "FROM 1 -> 3" ) ;

		/* 2 Second Delay */
		_delay_ms( _2_SEC ) ;

		/* Recursive Call For Function To Go Into Right Option */
		BottleNeddedMode( ) ;
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
