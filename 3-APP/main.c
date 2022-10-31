/*
 * main.c
 *
 *  Created on: Oct 29, 2022
 *      Author: moham
 */

#include "../4-LIB/STD_TYPES.h"
#include "../4-LIB/BIT_MATH.h"
#include "../1-MCAL/DIO/DIO_Interface.h"
#include "../2-HAL/CLCD/CLCD_Interface.h"
#include "../2-HAL/KEYPAD/KEYPAD_Interface.h"
#include "../1-MCAL/PORT/PORT_Interface.h"
#include <util/delay.h>
u8 User_Choice =NULL;
void (* PTR_To_User_Choice)(void) =NULL;
u8 MainMenu(void);
void main(void)
{
	PORT_voidInit();
	CLCD_voidInit();
	CLCD_u8SendString("Welcome");
	CLCD_voidClearScreen();
	User_Choice = MainMenu();
	PTR_To_User_Choice();
}
u8 MainMenu(void)
{
	u8 Local_Choice=NULL;
	CLCD_u8SendString("Please enter your choice");
	CLCD_u8GoToRowColumn(1,0);
	CLCD_u8SendString("1- Bottle Recycle");
	CLCD_u8GoToRowColumn(2,0);
	CLCD_u8SendString("2- Bottle needed");
	CLCD_u8GoToRowColumn(3,0);
	CLCD_u8SendString("3- Refill");
	Local_Choice =KEYPAD_u8PollingUntilKeyPressed();
	if((Local_Choice >3) || (Local_Choice<=0))
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
	switch (User_Choice){
	case 1: // set global pointer to bottle recycle function
		break;
	case 2: // set global pointer to 2- Bottle needed function
		break;
	case 3: // set global pointer to Refill function
		break;
	}
}
