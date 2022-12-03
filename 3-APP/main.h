/*
 * main.h
 *
 *  Created on: Dec 1, 2022
 *      Author: moham
 */

#ifndef MAIN_H_
#define MAIN_H_



#define EXIST          1
#define NON_EXIST      0
#define _1_SEC         1000
#define _2_SEC         2000

#define STEPPER_MOTOR_1_500mL_PORT     DIO_u8PORTD
#define STEPPER_MOTOR_2_1000mL_PORT    DIO_u8PORTD

#define STEPPER_MOTOR_1_500mL_PIN      DIO_u8Pin0
#define STEPPER_MOTOR_2_1000mL_PIN     DIO_u8Pin1

/*PROTOTYPES*/

u8 MainMenu(void) ;

void Refill_Mode(void) ;

void Menu_Choosing(void) ;


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
void BottleNeddedMode(void) ;

void BackToMainMenu(void) ;

void BottleRecycle(void) ;

void ISR1_Sensing_Bottle_Exist(void) ;

void Bottle_Filling (void) ;


#endif /* 3_APP_MAIN_H_ */
