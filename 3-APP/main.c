/*
 * main.c
 *
 *  Created on: Oct 29, 2022
 *      Author: moham
 */

#include "../4-LIB/STD_TYPES.h"
#include "../1-MCAL/DIO/DIO_Interface.h"
#include "../2-HAL/CLCD/CLCD_Interface.h"
#include "../2-HAL/KEYPAD/KEYPAD_Interface.h"

void Refill_Mode(void);
void main(void)
{
	CLCD_voidInit();
	KEYPAD_voidInit();
	Refill_Mode();
	while(1)
	{

	}
}
void Refill_Mode(void)
{
	u8 KeyPad_State =0xff;
	/*Show The Refill Menu*/
	CLCD_voidClearScreen();
	CLCD_u8GoToRowColumn(0,0);
	CLCD_u8SendString("select an option :");
	CLCD_u8GoToRowColumn(1,0);
	CLCD_u8SendString("1- Capacity = 500mL");
	CLCD_u8GoToRowColumn(2,0);
	CLCD_u8SendString("2- Capacity = 1L");
	CLCD_u8GoToRowColumn(3,0);
	CLCD_u8SendString("3-Back to Main Menu");
	/*GET pressed key from user*/
	KeyPad_State = KEYPAD_u8PollingUntilKeyPressed();
	switch (KeyPad_State)
	{
	/*Show Needed Price For 500mL */
	case 1 :
		CLCD_voidClearScreen();
		CLCD_u8GoToRowColumn(0,0);
		CLCD_u8SendString("Price needed = 3 EGP");
		break;
	/*Show Needed Price For 1L */
	case 2 :
		CLCD_voidClearScreen();
		CLCD_u8GoToRowColumn(0,0);
		CLCD_u8SendString("Price needed = 5 EGP");
		break;
	/*Get Back To Main Menu*/
	case 3 :
		/*Call For Main menu Function*/
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
