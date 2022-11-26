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

u8 IR_Sensor_u8Read(void)
{
	u8 Local_IR_Read=NULL;
	DIO_u8GetPinValue(IR_SensorPort,IR_SensorPin,&Local_IR_Read);
	return Local_IR_Read;
}
