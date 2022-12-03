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
u8 MainMenu(void) ;

void Refill_Mode(void) ;

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
void Menu_Choosing(void) ;

void BottleNeddedMode(void) ;

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
void BackToMainMenu(void) ;

void BottleRecycle(void) ;

void Bottle_Filling (void) ;

void ISR1_Sensing_Bottle_Exist(void) ;

#endif /* 3_APP_MAIN_H_ */
