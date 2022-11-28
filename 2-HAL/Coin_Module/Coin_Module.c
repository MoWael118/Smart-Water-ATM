/*
 * Coin_Module.c
 *
 *  Created on: Nov 27, 2022
 *      Author: mhmd waleed
 */
#include "../../4-LIB/STD_TYPES.h"
#include "../../4-LIB/BIT_MATH.h"
#include "../../1-MCAL/DIO/DIO_Interface.h"
#include "../../1-MCAL/EXTI/EXTI_Interface.h"
#include "Coin_Module.h"
#include <util/delay.h>

u8 Coin_Module_NO_Pulses = NULL ;
u8 Coin_Module_Temp = NULL ;


f32 Coin_Value(void)
{
	EXTI_voidInit1();

	EXTI_u8Int1CallBack(	&ISR_Coin_module	);

	while(	Coin_Module_NO_Pulses == NULL	) ;

	_delay_ms(1);

	Coin_Module_Temp	=	Coin_Module_NO_Pulses	;

	Coin_Module_NO_Pulses = NULL	;

	EXTI_u8IntDisable(	INT1  )	;

	return ( Coin_Module_Temp / OneEGP_Pulses ) ;
}

void ISR_Coin_module(void)
{
	Coin_Module_NO_Pulses ++;
}
