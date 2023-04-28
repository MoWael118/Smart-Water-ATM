/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  MOHAMMED AYMAN        ***************************/
/*************                LAYER :   MCAL			      ***************************/
/*************                SWC :     PORT	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/

#ifndef PORT_CONFIG_H_
#define PORT_CONFIG_H_



/*
                                  ______________________________________
                                  |             ATMEGA32               |
  LCD CTRL ( RS PIN )      <----  | B0                              A0 |  ----> KEYPAD COLUMN PIN 1
  LCD CTRL ( RW PIN )      <----  | B1                              A1 |  ----> KEYPAD COLUMN PIN 2
  FLOWMETER SENSOR         <----  | B2                              A2 |  ----> KEYPAD COLUMN PIN 3
  LCD CTRL ( E PIN )       <----  | B3                              A3 |  ----> KEYPAD COLUMN PIN 4
    KEYPAD ROW PIN 1       <----  | B4                              A4 |  ----> IR SENSOR ( RECYCLE )
    KEYPAD ROW PIN 2       <----  | B5                              A5 |  ----> DC PUMP
    KEYPAD ROW PIN 3       <----  | B6                              A6 |  ----> SOLENOID VALVE
    KEYPAD ROW PIN 4       <----  | B7                              A7 |
                                  |                                    |
Stepper Motor 1( 500 mL )  <----  | D0                              C0 |   ----> LCD DATA PIN D0
Stepper Motor 2( 1 L )     <----  | D1                              C1 |   ----> LCD DATA PIN D1
 IR SENSOR ( REFILL )      <----  | D2                              C2 |   ----> LCD DATA PIN D2
 COIN ACCEPTOR MODULE      <----  | D3                              C3 |   ----> LCD DATA PIN D3
                                  | D4                              C4 |   ----> LCD DATA PIN D4
                                  | D5                              C5 |   ----> LCD DATA PIN D5
                                  | D6                              C6 |   ----> LCD DATA PIN D6
                                  | D7                              C7 |   ----> LCD DATA PIN D7
                                  |____________________________________|                                                     */



/*
 * Choose : 0  FOR INPUT
 *          1  FOR OUTPUT
 *
 */

/* DIRECTION*/
#define PORTA_PIN0_DIR  1
#define PORTA_PIN1_DIR  1
#define PORTA_PIN2_DIR  1
#define PORTA_PIN3_DIR  1
#define PORTA_PIN4_DIR  0 /*IR Recycle*/
#define PORTA_PIN5_DIR  1 /*Pump*/
#define PORTA_PIN6_DIR  1 /*Valve*/
#define PORTA_PIN7_DIR  0

#define PORTB_PIN0_DIR  1
#define PORTB_PIN1_DIR  1
#define PORTB_PIN2_DIR  0
#define PORTB_PIN3_DIR  1
#define PORTB_PIN4_DIR  0
#define PORTB_PIN5_DIR  0
#define PORTB_PIN6_DIR  0
#define PORTB_PIN7_DIR  0

#define PORTC_PIN0_DIR  1
#define PORTC_PIN1_DIR  1
#define PORTC_PIN2_DIR  1
#define PORTC_PIN3_DIR  1
#define PORTC_PIN4_DIR  1
#define PORTC_PIN5_DIR  1
#define PORTC_PIN6_DIR  1
#define PORTC_PIN7_DIR  1

#define PORTD_PIN0_DIR  1 /*STEPPER MOTOR 1*/
#define PORTD_PIN1_DIR  1 /*STEPPER MOTOR 2*/
#define PORTD_PIN2_DIR  0
#define PORTD_PIN3_DIR  0
#define PORTD_PIN4_DIR  0
#define PORTD_PIN5_DIR  0
#define PORTD_PIN6_DIR  0
#define PORTD_PIN7_DIR  0


/*INTIAL VALUE*/

/* Choose : 0  IF Output (LOW)  , IF Input (FLOATING)
 *          1  IF OUTPUT (HIGH) , IF INPUT (PULL UP)
 */

#define PORTA_PIN0_INTIAL_VALUE  1
#define PORTA_PIN1_INTIAL_VALUE  1
#define PORTA_PIN2_INTIAL_VALUE  1
#define PORTA_PIN3_INTIAL_VALUE  1
#define PORTA_PIN4_INTIAL_VALUE  0
#define PORTA_PIN5_INTIAL_VALUE  0
#define PORTA_PIN6_INTIAL_VALUE  0
#define PORTA_PIN7_INTIAL_VALUE  0

#define PORTB_PIN0_INTIAL_VALUE  0
#define PORTB_PIN1_INTIAL_VALUE  0
#define PORTB_PIN2_INTIAL_VALUE  0
#define PORTB_PIN3_INTIAL_VALUE  0
#define PORTB_PIN4_INTIAL_VALUE  1
#define PORTB_PIN5_INTIAL_VALUE  1
#define PORTB_PIN6_INTIAL_VALUE  1
#define PORTB_PIN7_INTIAL_VALUE  1

#define PORTC_PIN0_INTIAL_VALUE  0
#define PORTC_PIN1_INTIAL_VALUE  0
#define PORTC_PIN2_INTIAL_VALUE  0
#define PORTC_PIN3_INTIAL_VALUE  0
#define PORTC_PIN4_INTIAL_VALUE  0
#define PORTC_PIN5_INTIAL_VALUE  0
#define PORTC_PIN6_INTIAL_VALUE  0
#define PORTC_PIN7_INTIAL_VALUE  0

#define PORTD_PIN0_INTIAL_VALUE  0
#define PORTD_PIN1_INTIAL_VALUE  0
#define PORTD_PIN2_INTIAL_VALUE  0
#define PORTD_PIN3_INTIAL_VALUE  1
#define PORTD_PIN4_INTIAL_VALUE  0
#define PORTD_PIN5_INTIAL_VALUE  0
#define PORTD_PIN6_INTIAL_VALUE  0
#define PORTD_PIN7_INTIAL_VALUE  0


#endif /* 1_MCAL_PORT_PORT_CONFIG_H_ */
