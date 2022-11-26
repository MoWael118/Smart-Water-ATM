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
#include <util/delay.h>

u8 User_Choice = NULL ;
void (* PTR_To_User_Choice)(void) = NULL ;
u8 NoOfBottlesInserted=NULL;
f32 Credit_Recycle=NULL;
u8 Bottle_Exist =NULL;
f32 Price = NULL;


u8 MainMenu(void);
void Refill_Mode(void);
void Menu_Choosing(void);
void BottleNeddedMode(void);
void BackToMainMenu(void);
void BottleRecycle(void);
void Sensing_Bottle_Exist(void);

void main(void)
{
	PORT_voidInit();
	GIE_voidEnable();
	CLCD_voidInit();
	CLCD_u8GoToRowColumn(0,0);
	CLCD_u8SendString("Welcome");
	_delay_ms(2000);

	EXTI_voidInit0();
	EXTI_u8Int0CallBack(&Sensing_Bottle_Exist);

	while(1)
	{
		BackToMainMenu();

	}
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

		Price = 3 ;
		CLCD_voidClearScreen();
		CLCD_u8GoToRowColumn(0,0);
		if(Credit_Recycle == NULL)
		{
			CLCD_u8SendString( "Price Needed =" ) ;
			CLCD_WriteFloatingNumber( Price , 1 , 0 , 14 ) ;
			CLCD_u8SendString("EGP") ;


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

		break;
	case '2' :

		Price = 5 ;
		CLCD_voidClearScreen();
		CLCD_u8GoToRowColumn(0,0);
		if(Credit_Recycle == NULL)
		{
			CLCD_u8SendString( "Price Needed =" ) ;
			CLCD_WriteFloatingNumber( Price , 1 , 0 , 14 ) ;
			CLCD_u8SendString("EGP") ;


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
	u8 Local_u8PressedKey = KEYPAD_NO_PRESSED_KEY ;
	/*Clear LCD Display*/
	CLCD_voidClearScreen();

	CLCD_u8GoToRowColumn(0,0);
	CLCD_u8SendString("Select an Option :");

	CLCD_u8GoToRowColumn(1,0);
	CLCD_u8SendString("1- Capacity = 500mL");
	CLCD_u8GoToRowColumn(2,0);
	CLCD_u8SendString("2- Capacity = 1L");
	CLCD_u8GoToRowColumn(3,0);
	CLCD_u8SendString("3- Back to Main Menu");

	Local_u8PressedKey = KEYPAD_u8PollingUntilKeyPressed();

	switch( Local_u8PressedKey )
	{
	case '1':
		/*500mL Option*/
		CLCD_voidClearScreen();
		CLCD_u8SendString("Please Insert 4 EGP");
		/*Function Polling until Right amount of money is inserted*/

		/*Motor 1 ON For Specified Angle*/

		/*Display to user that bottle is ready to get it from the درج*/
		_delay_ms(1000);
		CLCD_voidClearScreen();
		CLCD_u8SendString("Your Bottle is Ready");
		_delay_ms(1500);
		break;
	case '2':
		/*1L Option*/
		CLCD_voidClearScreen();
		CLCD_u8SendString("Please Insert 6 EGP");
		/*Function Polling until Right amount of money is inserted*/

		/*Motor 2 ON For Specified Angle*/

		/*Display to user that bottle is ready to get it from the درج*/
		_delay_ms(1000);
		CLCD_voidClearScreen();
		CLCD_u8SendString("Your Bottle is Ready");
		_delay_ms(1500);
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
void BackToMainMenu (void)
{
	CLCD_voidClearScreen();
	User_Choice = MainMenu();
	Menu_Choosing();
	PTR_To_User_Choice();
}
void Sensing_Bottle_Exist(void)
{
	TOGGLE_BIT(Bottle_Exist,0);
}
