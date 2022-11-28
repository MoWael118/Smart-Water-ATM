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

u8 Coin_Module_Freq=NULL;
u8 Coin_Module_Freq1=NULL;


f32 Coin_Value(void)
{
EXTI_voidInit1();
EXTI_u8Int1CallBack(	&ISR_Coin_module	);
while(	Coin_Module_Freq == NULL	);
Coin_Module_Freq1	=	Coin_Module_Freq	;
Coin_Module_Freq = NULL	;
EXTI_u8IntDisable(	INT1  )	;
return Coin_Module_Freq1/OneEGP_Pulses;
}

void ISR_Coin_module(void)
{
	Coin_Module_Freq ++;
}
