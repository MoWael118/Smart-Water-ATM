/*
 * main.c
 *
 *  Created on: Oct 29, 2022
 *      Author: moham
 */

#include "../4-LIB/STD_TYPES.h"
#include "../1-MCAL/DIO/DIO_Interface.h"
#include "../2-HAL/CLCD/CLCD_Interface.h"

void main(void)
{
	CLCD_voidInit();
	CLCD_u8GoToRowColumn(0,0);
	CLCD_u8SendString("Ayman");
	CLCD_voidWriteIntegerNumber(112,1,0);



	while(1)
	{

	}
}
