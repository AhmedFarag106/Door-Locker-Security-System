/*
 * Control_ECU.c
 *
 *  Created on: Nov 3, 2023
 *      Author: Ahmed
 */

#include "buzzer.h"
#include "external_eeprom.h"
#include "DCmotor.h"
#include "timer1.h"
#include "twi.h"
#include "uart.h"

#include "std_types.h"

#include <avr/interrupt.h>
#include "util/delay.h"

uint8 g_ticks = 0;
uint8 g_clbk = 0;

void timer1CLBK()
{
	g_ticks ++;
	if (g_ticks ==2)
	{
		g_clbk ++;
		g_ticks = 0;
	}
}

int main (void)
{

	uint8 UART_data[15];
	uint8 EE_data = 0;
	uint8 repeatedPass = 1;
	uint8 counter =0;


	Buzzer_init();
	DcMotor_Init();

	UART_ConfigType UART_Con = {Bit_8,Disabled,One,9600};
	UART_init(&UART_Con);

	TWI_ConfigType TWI_Con = {1,400000};
	TWI_init(&TWI_Con);

	Timer1_setCallBack (timer1CLBK);

	Timer1_ConfigType Timer1_con ;


	SREG |= (1<<7); /* Enable global interrupts in MC */

	while(1)
	{
		UART_receiveString(UART_data);
		switch (UART_data[0])
		{
		case '1':
			repeatedPass = 1;
			for (counter = 1 ; counter <6 ; counter++){
				if (UART_data[counter] !=  UART_data[counter+6] )
				{
					repeatedPass = 0 ;
					break;
				}
			}
			if (repeatedPass)
			{
				for (counter = 1 ; counter <6 ; counter++){
					EEPROM_writeByte((0x0310 + counter ), UART_data[counter]);
					_delay_ms(20);

				}
				UART_sendString("1OK#");
			}
			else
			{
				UART_sendString("1NO#");
			}
			break;
		case '2':
			repeatedPass = 1;
			for (counter = 1 ; counter <6 ; counter++){
				EEPROM_readByte((0x0310 + counter ),&EE_data);

				if (UART_data[counter] != EE_data)
				{
					repeatedPass = 0;
					break;
				}
			}
			if (repeatedPass) UART_sendString("2OK#");
			else UART_sendString("2NO#");
			break;

		case '3':

			//UART_sendString("3OK#");

			Timer1_con.initial_value = 0;
			Timer1_con.compare_value = 58594;
			Timer1_con.prescaler = PSC_1024;
			Timer1_con.mode = CTC;
			Timer1_init(&Timer1_con);

			DcMotor_Rotate(CW,100);
			while(g_clbk == 0);

			Timer1_con.initial_value = 0;
			Timer1_con.compare_value = 31250;
			Timer1_con.prescaler = PSC_256;
			Timer1_con.mode = CTC;
			Timer1_init(&Timer1_con);

			DcMotor_Rotate(STOP,100);
			while(g_clbk == 1);

			Timer1_con.initial_value = 0;
			Timer1_con.compare_value = 58594;
			Timer1_con.prescaler = PSC_1024;
			Timer1_con.mode = CTC;
			Timer1_init(&Timer1_con);

			DcMotor_Rotate(CCW,100);
			while(g_clbk == 2);

			Timer1_deInit();
			DcMotor_Rotate(STOP,0);
			g_clbk=0;

			break;

		case '4':
			Timer1_con.initial_value = 0;
			Timer1_con.compare_value = 58594;
			Timer1_con.prescaler = PSC_1024;
			Timer1_con.mode = CTC;
			Timer1_init(&Timer1_con);

			Buzzer_on();
			while(g_clbk <4);

			Buzzer_off();
			g_clbk=0;

			break;
		}
	}


	return 0;
}



