/*
 * IR_Sensor.c
 *
 *  Created on: Nov 26, 2022
 *      Author: mhmd waleed
 */
#include "../../4-LIB/STD_TYPES.h"
#include "../../4-LIB/BIT_MATH.h"
#include "../../1-MCAL/DIO/DIO_Interface.h"
#include "IR_Sensor.h"





/*
 * Prototype   : u8 IR_Sensor_u8Read(void);
 *
 * Description : It Checks If The IR Sensor Is Reading Signal Or Not
 *
 * Arguments   : void
 *
 * return      : u8
 *
 */
u8 IR_Sensor_u8Read(void)
{
	/* Initializing Local IR Read (Local Variable) */
	u8 Local_IR_Read=NULL;

	/* Read IR Sensor Digital Pin*/
	DIO_u8GetPinValue(IR_SensorPort,IR_SensorPin,&Local_IR_Read);

	/* Returning  */
	return Local_IR_Read;
}
