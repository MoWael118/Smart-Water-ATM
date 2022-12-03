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
	CLCD_u8GoToRowColumn(ROW_1,COL_1) ;

	/* Displaying Welcome On LCD */
	CLCD_u8SendString("Welcome") ;

	/* Delay For 2 Seconds To Be Able To See Welcome On LCD */
	_delay_ms(_2_SEC) ;

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
	CLCD_u8GoToRowColumn(ROW_2,COL_1);

	/* Displaying 1- Bottle Recycle On LCD */
	CLCD_u8SendString("1- Bottle Recycle");

	/* Going To Position Of Row Three And Column One On LCD */
	CLCD_u8GoToRowColumn(ROW_3,COL_1);

	/* Displaying 2- Bottle needed On LCD */
	CLCD_u8SendString("2- Bottle needed");

	/* Going To Position Of Row Three And Column One On LCD */
	CLCD_u8GoToRowColumn(ROW_4,COL_1);

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
		CLCD_u8GoToRowColumn(ROW_2,COL_1);

		/* Displaying Please enter number On LCD */
		CLCD_u8SendString("Please enter number");

		/* Going To Position Of Row Three And Column One On LCD */
		CLCD_u8GoToRowColumn(ROW_3,COL_1);

		/* Displaying from(1-3) On LCD */
		CLCD_u8SendString("from(1-3)");

		/* Delay For 2 Seconds To Be Able To Read LCD */
		_delay_ms(_2_SEC);

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




/*
 * Prototype   : void Refill_Mode(void)
 *
 * Description : Executing Refill Mode Piece Of Code
 *
 * Arguments   : void
 *
 * return      : void
 *
 */
void Refill_Mode(void)
{
	/*Initializing a Variable to Hold State Of KeyPad*/
	u8 KeyPad_State = KEYPAD_NO_PRESSED_KEY;

	/*Clearing Screen From Previous Showed Screen*/
	CLCD_voidClearScreen();

	/*Moving Cursor To First Row and First Column of LCD*/
	CLCD_u8GoToRowColumn(ROW_1,COL_1);

	/*Displaying a Message On LCD To Select an option*/
	CLCD_u8SendString("select an option :");

	/*Moving Cursor To Second Row and First Column of LCD*/
	CLCD_u8GoToRowColumn(ROW_2,COL_1);

	/*Displaying The First option On LCD*/
	CLCD_u8SendString("1- Capacity = 500mL");

	/*Moving Cursor To Third Row and First Column of LCD*/
	CLCD_u8GoToRowColumn(ROW_3,COL_1);

	/*Displaying The Second option On LCD*/
	CLCD_u8SendString("2- Capacity = 1L");

	/*Moving Cursor To Fourth Row and First Column of LCD*/
	CLCD_u8GoToRowColumn(ROW_4,COL_1);

	/*Displaying The Third Option On LCD*/
	CLCD_u8SendString("3- Back to Main Menu");

	/*Assigning The Keypad Pressed Key value to KeyPad_State*/
	KeyPad_State = KEYPAD_u8PollingUntilKeyPressed();

	/*Checking Which KeyPad Button is pressed */
	switch (KeyPad_State)
	{

	/*Case 1 : the Pressed Key is '1' */
	/*Note : No Break in this case Because it has the same piece of code from upcoming case*/
	case '1' :

		/*Case 2 : the Pressed Key is '2'*/
	case '2' :

		/*Checking Pressed Key if equal 1 To Assign Suitable Price and Capacity to our Variables*/
		if( KeyPad_State == '1' )

		{
			/*Assigning Price to 3*/
			Price = _500mL_Price ;

			/*Assigning Water_Capacity to 500 mL*/
			Water_Capacity = _500mL ;

		}
		/*Checking Pressed Key if equal 2 To Assign Suitable Price and Capacity to our Variables*/
		else if ( KeyPad_State == '2' )

		{
			/*Assigning Price to 3*/
			Price = _1L_Price ;

			/*Assigning Water_Capacity to 1000 mL*/
			Water_Capacity = _1L ;

		}

		/*Clearing LCD From Previous Page*/
		CLCD_voidClearScreen();

		/*Moving Cursor To First Row and First Column of LCD*/
		CLCD_u8GoToRowColumn(ROW_1,COL_1);

		/*Checking User Credit*/

		/*If There is no Credit For User*/
		if(Credit_Recycle == NULL)
		{
			/*Displaying The Needed Price From User On LCD*/
			CLCD_u8SendString( "Price Needed =" ) ;

			/*Writing The Price Value to User*/
			CLCD_WriteFloatingNumber( Price , _1Number_After_DecimalPoint , ROW_1 , COL_15 ) ;

		}

		/*If the User Have Credit Value from Recycling Bottles*/
		else if(Credit_Recycle != NULL)
		{

			/*Displaying Message Price = */
			CLCD_u8SendString( "Price =" ) ;

			/*Writing The Price Value (Before Discount) to User*/
			CLCD_WriteFloatingNumber( Price , _1Number_After_DecimalPoint , ROW_1 , COL_9 ) ;

			/*Displaying EGP for Egyptian Pound*/
			CLCD_u8SendString( "EGP" ) ;

			/*Going To Second Line ON LCD To Display The Credit*/
			CLCD_u8GoToRowColumn( ROW_2 , COL_1 ) ;

			/*Displaying Message Credit = */
			CLCD_u8SendString( "Credit = " ) ;

			/*Writing The Credit Value on LCD*/
			CLCD_WriteFloatingNumber( Credit_Recycle , _2Numbers_After_DecimalPoint , ROW_2 , COL_10 );

			/*Going To the start of Third Line of LCD */
			CLCD_u8GoToRowColumn( ROW_3 , COL_1) ;

			/*Displaying Message Price Needed = */
			CLCD_u8SendString( "Price Needed =" ) ;

			/*Sending the Value of the Price After Discount*/
			CLCD_WriteFloatingNumber( (Price-Credit_Recycle) , _2Numbers_After_DecimalPoint , ROW_3 , COL_15 );
		}

		/*Going To the start of Second Line of LCD */
		CLCD_u8GoToRowColumn( ROW_4 , COL_1) ;

		/*Displaying Message Please Insert Coins */
		CLCD_u8SendString( "please Insert Coins" ) ;

		/* Waiting until Coins inserted value will be equal to The Net Price*/
		while( Coin_Module_Price != ( Price - Credit_Recycle ) )
		{
			/* Updating Value of Coins Inserted*/
			Coin_Module_Price += Coin_Value();

			/*Checking Credit Recycle Value To Determine Which Page on LCD Is Displayed*/
			if (Credit_Recycle==NULL)
			{
				/*Displaying The Remaining Price needed to be inserted on LCD At Line 1*/
				CLCD_WriteFloatingNumber( (Price-Coin_Module_Price) , _2Numbers_After_DecimalPoint , ROW_1 , COL_15 );

			}
			else if (Credit_Recycle!=NULL)
			{
				/*Displaying The Remaining Price needed to be inserted on LCD At Line 3*/
				CLCD_WriteFloatingNumber( (Price-Credit_Recycle-Coin_Module_Price) , _2Numbers_After_DecimalPoint , ROW_3 , COL_15 );
			}
		}

		/*1 Second Waiting*/
		_delay_ms(_1_SEC);

		/*Clearing LCD Screen*/
		CLCD_voidClearScreen();

		/*Display a Message To user to indicate for Successful Payment Transaction */
		CLCD_u8SendString( "Payment is Received" ) ;

		/*2 Seconds Waiting So the user can see the previous Message*/
		_delay_ms(_2_SEC);

		/*Clearing LCD*/
		CLCD_voidClearScreen(  ) ;

		/*Check Whether Bottle is Exist or not*/
		if( Bottle_Exist == NON_EXIST )

		{
			/*If Bottle doesn't Exist Displaying message to User to put his bottle*/
			CLCD_u8SendString( "Put Your Bottle" ) ;

		}
		/*Executing Function Bottle_Filling (Waiting until bottle is put and then starting to fill the bottle)*/
		Bottle_Filling();

		/*if Existence of bottle changed at any time While Filling...
		 * An interrupt Will be generated to Change The Bottle_Exist State To NON_EXIST*/

		/* While Bottle Existence State is Negative*/
		while ( Bottle_Exist == NON_EXIST  )
		{
			/*Going To the start of First Line on LCD */
			CLCD_u8GoToRowColumn(ROW_1,COL_1);

			/*Displaying Warning Message To user to put his bottle back*/
			CLCD_u8SendString( "Return Your Bottle" ) ;

			/*Executing Function Bottle_Filling (Waiting until bottle is put and then starting to fill the bottle)*/
			Bottle_Filling();
		}
		/*Waiting 1 Second*/
		_delay_ms(_1_SEC);

		/*Clearing LCD Screen*/
		CLCD_voidClearScreen();

		/*Displaying Message When Filling is Done*/
		CLCD_u8SendString( "Enjoy Your Water" );

		/*Waiting 2 Second*/
		_delay_ms(_2_SEC);

		/*Assigning Coin_Module_Price to Zero To Start The New Mode*/
		Coin_Module_Price = NULL ;

		/*Assigning User Credit to Zero To Calculate The new Credit for new User if required*/
		Credit_Recycle=NULL;

		/*Breaking Out This Case*/
		break;

		/*Case 3 : the Pressed Key is '3'*/
	case '3' :

		/*Going Back To the Main menu Page*/
		BackToMainMenu();

		/*Breaking Out This Case*/
		break;

		/*Default Case : the Pressed Key is Neither 1,2 nor 3*/
	default :

		/*Clearing LCD Screen*/
		CLCD_voidClearScreen();

		/*Going To The Start of First Line of LCD*/
		CLCD_u8GoToRowColumn(ROW_1,COL_1);

		/*Displaying Error Message To indicate for Wrong Input*/
		CLCD_u8SendString("Wrong Input");

		/*Going To The Start of Second Line of LCD*/
		CLCD_u8GoToRowColumn(ROW_2,COL_1);

		/*Displaying Message To Make User Try Again*/
		CLCD_u8SendString("Please Try Again");

		/*2 Seconds Waiting So the User Can see The message*/
		_delay_ms(_2_SEC);

		/*Starting Our Mode Again*/
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

		/* Return Coin Module Price Back To Zero */
		Coin_Module_Price=NULL;
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



/*
 * Prototype   : void BottleRecycle(void)
 *
 * Description : Determine Number of bottles inserted to recycle And calculate the Corresponding Credit Value
 *
 * Arguments   : void
 *
 * return      : void
 *
 */
void BottleRecycle(void)
{
	/*LCD CLEARING */
	CLCD_voidClearScreen();

	/*Displaying Option To Exit Recycling Process*/
	CLCD_u8SendString("Press 0 to exit");

	/* waiting While The User didn't Exit This Process*/
	while (KEYPAD_u8GetPressedKey() !=  '0' )
	{
		/*Checking Sensor Read */
		/*If Sensor Reads Signal then there is Bottle inserted*/
		if(IR_Sensor_u8Read() == 1)
		{
			/*Waiting until The Whole Bottle Crossed the sensor*/
			while(IR_Sensor_u8Read()== 1);

			/*Increasing Number Of bottles */
			NoOfBottlesInserted++;
		}

		/*Going To the start of second line of LCD*/
		CLCD_u8GoToRowColumn(ROW_2,COL_1);

		/*Displaying Message Number of bottles inserted*/
		CLCD_u8SendString("Number of bottles ");

		/*Going To the start of Third line of LCD*/
		CLCD_u8GoToRowColumn(ROW_3,COL_1);

		/*Displaying Message Number of bottles inserted*/
		CLCD_u8SendString("inserted =");

		/*Writing The Number Of bottles Inserted To User*/
		CLCD_voidWriteIntegerNumber(NoOfBottlesInserted,ROW_3,COL_12);

		/*Going To the start of Fourth line of LCD*/
		CLCD_u8GoToRowColumn(ROW_4,COL_1);

		/*Displaying Message Your Credit =*/
		CLCD_u8SendString("Your Credit=");

		/*Writing The Equivalent Value Of bottles Inserted To User*/
		CLCD_WriteFloatingNumber( (f32)( NoOfBottlesInserted / 2.0 ) , _2Numbers_After_DecimalPoint , ROW_4 , COL_13 );

		/*Going To the start of Fourth line of LCD*/
		CLCD_u8GoToRowColumn(ROW_4 , COL_18);

		/*Displaying Message Number of bottles inserted*/
		CLCD_u8SendString("EGP");
	}

	/*Dividing Number of Recycled Bottles by 2 To Get Equivalent Credit Value*/
	Credit_Recycle= (f32)( NoOfBottlesInserted / 2.0 );
	BackToMainMenu();
}

/*
 * Prototype   : void ISR1_Sensing_Bottle_Exist(void)
 *
 * Description : Getting the value of IR Sensor
 *
 * Arguments   : void
 *
 * return      : void
 *
 */
void ISR1_Sensing_Bottle_Exist(void)
{
	/*Getting IR Sensor Value And save it at Global Variable*/
	DIO_u8GetPinValue(DIO_u8PORTD,DIO_u8Pin2,&Bottle_Exist);
}


/*
 * Prototype   : void Bottle_Filling(void)
 *
 * Description : Starting To Fill Water To the Bottle
 *
 * Arguments   : void
 *
 * return      : void
 *
 */

void Bottle_Filling (void)
{
	/*Declared Variable Flag*/
	u8 Flag=0;

	/*Busy Waiting until User Put A Bottle*/
	while( Bottle_Exist == NON_EXIST ) ;

	/*Clearing LCD*/
	CLCD_voidClearScreen();


	while( ( Bottle_Exist == EXIST ) && ( Flow_Volume < Water_Capacity ) )
	{
		/*Checking Flag Value*/
		if(Flag ==0)
		{
			/*Pump on */
			DIO_u8SetPinValue( DIO_u8PORTA , DIO_u8Pin5 , DIO_u8PIN_HIGH ) ;

			/*valve on*/
			DIO_u8SetPinValue( DIO_u8PORTA , DIO_u8Pin6 , DIO_u8PIN_HIGH ) ;

			/*Going To The Start of Second LINE*/
			CLCD_u8GoToRowColumn(ROW_2,0);

			/*Displaying Message VOLUME = */
			CLCD_u8SendString("Volume = ") ;
			//CLCD_u8GoToRowColumn(0,0);
			//CLCD_u8SendString( "Flow Rate = " );

			/*Assigning Flag To 1 So that This Condition not repeated again*/
			Flag =1;
		}

		/*Getting Volume Passed Through flow meter and the flow rate USING Function FLOWMETER_voidGetVolume */
		FLOWMETER_voidGetVolume( &Flow_Volume , &Flow_Rate ) ;


		//CLCD_voidWriteIntegerNumber( (s32)Flow_Rate  , 0 , 12 );

		/*Writing Filled Volume On LCD*/
		CLCD_voidWriteIntegerNumber( (s32)Flow_Volume , ROW_2 , COL_10 ) ;

	}

	/*Finishing FLOW METER WORK*/
	FLOWMETER_voidFinished();

	/*pump off*/
	DIO_u8SetPinValue( DIO_u8PORTA , DIO_u8Pin5 , DIO_u8PIN_LOW ) ;

	/*Valve off*/
	DIO_u8SetPinValue( DIO_u8PORTA , DIO_u8Pin6 , DIO_u8PIN_LOW  ) ;

	/*Waiting 1 Second*/
	_delay_ms(_1_SEC);

	/*Clearing LCD*/
	CLCD_voidClearScreen();
}
