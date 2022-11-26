/*
 * IR_Sensor.h
 *
 *  Created on: Nov 26, 2022
 *      Author: mhmd waleed
 */

#ifndef IR_SENSOR_IR_SENSOR_H_
#define IR_SENSOR_IR_SENSOR_H_
#include "../../1-MCAL/DIO/DIO_Interface.h"

#define IR_SensorPort      DIO_u8PORTA
#define IR_SensorPin       DIO_u8Pin4

u8 IR_Sensor_u8Read(void);

#endif /* IR_SENSOR_IR_SENSOR_H_ */
