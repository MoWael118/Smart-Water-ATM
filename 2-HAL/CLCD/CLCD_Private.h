/*
 * CLCD_Private.h
 *
 *  Created on: Sep 7, 2022
 *      Author: moham
 */

#ifndef CLCD_PRIVATE_H_
#define CLCD_PRIVATE_H_

/*COMMANDS*/
#define CLCD_CLEAR_DISPLAY ( 0x01 )
#define CLCD_RETURN_HOME   ( 0X02 )
#define SET_DDRAM_ADDRESS  ( 0x80 )
#define SET_CGRAM_ADDRESS  ( 0x40 )



/*SOME VALUES*/
#define SECOND_LINE_START_ADDRESS ( 0x40 )

/*FOR MORE THAN 2 ROWS LCDS */
#define THIRD_LINE_START_ADDRESS  ( 0x14 )
#define FOURTH_LINE_START_ADRESS  ( 0x54 )

#define LOCATION_SIZE_IN_CGRAM        8
#define MAX_NUMBER_OF_DIGITS_IN_S32  10
#define ZERO_ASCII                   48

#define LCD_8BIT_MODE    1
#define LCD_4BIT_MODE    2

#define DISPLAY_ENABLE   1
#define DISPLAY_DISABLE  2

#define CURSOR_ENABLE    1
#define CURSOR_DISABLE   2

#define BLINK_ENABLE     1
#define BLINK_DISABLE    2

#define ONE_LINE         1
#define TWO_LINES  		 2

#define FONT_5x8  		 1
#define FONT_5x11 		 2

#define NUMBER_OF_LINES_BIT   3
#define FONT_SIZE_BIT         2

#define RIGHT_LEFT_SHIFT_BIT  2

#define DISPLAY_BIT 		  2
#define CURSOR_BIT  		  1
#define BLINK_BIT   	      0

#define LCD_16X2  1
#define LCD_20X4  2

/* LCD_ 20X4  */
#define ROW_1      0
#define ROW_2      1
#define ROW_3      2
#define ROW_4      3

#define COL_1      0
#define COL_2      1
#define COL_3      2
#define COL_4      3
#define COL_5      4
#define COL_6      5
#define COL_7      6
#define COL_8      7
#define COL_9      8
#define COL_10     9
#define COL_11     10
#define COL_12     11
#define COL_13     12
#define COL_14     13
#define COL_15     14
#define COL_16     15
#define COL_17     16
#define COL_18     17
#define COL_19     18
#define COL_20     19


#endif /* 2_HAL_CLCD_CLCD_PRIVATE_H_ */
