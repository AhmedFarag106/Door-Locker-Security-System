/*
 * timer1.c
 *
 *  Created on: Nov 3, 2023
 *      Author: Ahmed
 */
# include "timer1.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void(*callBack)(void) ;

void Timer1_init(const Timer1_ConfigType * Config_Ptr)
{
	TCCR1A = (1<<FOC1A);


	TCCR1B = (Config_Ptr->mode << WGM12);

	TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->prescaler & 0x7) ;

	TCNT1 = Config_Ptr->initial_value ;

	OCR1A =Config_Ptr->compare_value ;

	if (Config_Ptr->mode) 	TIMSK |= (1<<OCIE1A);
	else  					TIMSK |= (1<<TOIE1);
}


void Timer1_deInit(void)
{
	TCCR1B = 0;
}

void Timer1_setCallBack(void(*a_ptr)(void))
{
	callBack = a_ptr;
}

ISR(TIMER1_COMPA_vect)
{
	callBack();
}

ISR(TIMER1_OVF_vect)
{
	callBack();
}

