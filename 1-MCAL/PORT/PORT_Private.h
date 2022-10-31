/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  MOHAMMED AYMAN        ***************************/
/*************                LAYER :   MCAL			      ***************************/
/*************                SWC :     PORT	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/

#ifndef PORT_PRIVATE_H_
#define PORT_PRIVATE_H_


#define CONC(b7,b6,b5,b4,b3,b2,b1,b0)         CONC_HELPER(b7,b6,b5,b4,b3,b2,b1,b0)

#define CONC_HELPER(b7,b6,b5,b4,b3,b2,b1,b0)  0b##b7##b6##b5##b4##b3##b2##b1##b0

#define PORTA_DIR  CONC( PORTA_PIN7_DIR , PORTA_PIN6_DIR , PORTA_PIN5_DIR , PORTA_PIN4_DIR , PORTA_PIN3_DIR , PORTA_PIN2_DIR , PORTA_PIN1_DIR , PORTA_PIN0_DIR )

#define PORTB_DIR  CONC( PORTB_PIN7_DIR , PORTB_PIN6_DIR , PORTB_PIN5_DIR , PORTB_PIN4_DIR , PORTB_PIN3_DIR , PORTB_PIN2_DIR , PORTB_PIN1_DIR , PORTB_PIN0_DIR )

#define PORTC_DIR  CONC( PORTC_PIN7_DIR , PORTC_PIN6_DIR , PORTC_PIN5_DIR , PORTC_PIN4_DIR , PORTC_PIN3_DIR , PORTC_PIN2_DIR , PORTC_PIN1_DIR , PORTC_PIN0_DIR )

#define PORTD_DIR  CONC( PORTD_PIN7_DIR , PORTD_PIN6_DIR , PORTD_PIN5_DIR , PORTD_PIN4_DIR , PORTD_PIN3_DIR , PORTD_PIN2_DIR , PORTD_PIN1_DIR , PORTD_PIN0_DIR )


#define PORTA_INITIAL_VALUE  CONC( PORTA_PIN7_INTIAL_VALUE , PORTA_PIN6_INTIAL_VALUE , PORTA_PIN5_INTIAL_VALUE , PORTA_PIN4_INTIAL_VALUE , PORTA_PIN3_INTIAL_VALUE , PORTA_PIN2_INTIAL_VALUE , PORTA_PIN1_INTIAL_VALUE , PORTA_PIN0_INTIAL_VALUE  )

#define PORTB_INITIAL_VALUE  CONC( PORTB_PIN7_INTIAL_VALUE , PORTB_PIN6_INTIAL_VALUE , PORTB_PIN5_INTIAL_VALUE , PORTB_PIN4_INTIAL_VALUE , PORTB_PIN3_INTIAL_VALUE , PORTB_PIN2_INTIAL_VALUE , PORTB_PIN1_INTIAL_VALUE , PORTB_PIN0_INTIAL_VALUE  )

#define PORTC_INITIAL_VALUE  CONC( PORTC_PIN7_INTIAL_VALUE , PORTC_PIN6_INTIAL_VALUE , PORTC_PIN5_INTIAL_VALUE , PORTC_PIN4_INTIAL_VALUE , PORTC_PIN3_INTIAL_VALUE , PORTC_PIN2_INTIAL_VALUE , PORTC_PIN1_INTIAL_VALUE , PORTC_PIN0_INTIAL_VALUE  )

#define PORTD_INITIAL_VALUE  CONC( PORTD_PIN7_INTIAL_VALUE , PORTD_PIN6_INTIAL_VALUE , PORTD_PIN5_INTIAL_VALUE , PORTD_PIN4_INTIAL_VALUE , PORTD_PIN3_INTIAL_VALUE , PORTD_PIN2_INTIAL_VALUE , PORTD_PIN1_INTIAL_VALUE , PORTD_PIN0_INTIAL_VALUE  )






/*VALUES*/
#define INPUT  0
#define OUTPUT 1




#endif /* 1_MCAL_PORT_PORT_PRIVATE_H_ */
