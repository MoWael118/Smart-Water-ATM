/*
 * main.h
 *
 *  Created on: Dec 1, 2022
 *      Author: moham
 */

#ifndef MAIN_H_
#define MAIN_H_



#define EXIST     1
#define NON_EXIST 0





/*PROTOTYPES*/

u8 MainMenu(void) ;

void Refill_Mode(void) ;

void Menu_Choosing(void) ;

void BottleNeddedMode(void) ;

void BackToMainMenu(void) ;

void BottleRecycle(void) ;

void ISR1_Sensing_Bottle_Exist(void) ;

void Bottle_Filling (void) ;


#endif /* 3_APP_MAIN_H_ */
