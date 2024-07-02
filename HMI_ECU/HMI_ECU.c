/*
 * HMI_ECU.c
 *
 *  Created on: Nov 3, 2023
 *      Author: Ahmed
 */


#include "keypad.h"
#include "lcd.h"
#include "timer1.h"
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

	uint8 UART_data [15];
	uint8 counter,key;
	uint8 sel_key = '0';
	uint8 case_select = 0;
	uint8 wrongPass = 0;

	LCD_init();

	UART_ConfigType UART_Con = {Bit_8,Disabled,One,9600};
	UART_init(&UART_Con);

	Timer1_setCallBack (timer1CLBK);
	Timer1_ConfigType Timer1_con ;

	SREG |= (1<<7); /* Enable global interrupts in MC */

	LCD_displayString("plz enter pass");
	while(1)
	{
		switch (case_select)
		{
		case 0 :
			LCD_moveCursor(1,0);
			UART_data [0] = '1';
			for(counter = 0 ; counter<5 ; counter++)
			{
				key = KEYPAD_getPressedKey();
				if (key <=13)
					UART_data[counter+1] = key +'0'  ;

				else UART_data[counter+1] = key;
				LCD_displayCharacter('*');
			}

			while(KEYPAD_getPressedKey() != '=');

			UART_data [6] = '$';
			LCD_moveCursor(0,0);
			LCD_displayString("plz re-enter the");
			LCD_moveCursor(1,0);
			LCD_displayString("same pass: ");

			for(counter = 0 ; counter<5 ; counter++)
			{
				key = KEYPAD_getPressedKey();
				if (key <=13)
					UART_data[counter+7] = key +'0'  ;

				else UART_data[counter+7] = key;
				LCD_displayCharacter('*');
			}

			while(KEYPAD_getPressedKey() != '=');

			UART_data[12] = '#';
			UART_data[13] = '\0';
			UART_sendString(UART_data);
			_delay_ms(10);
			UART_receiveString(UART_data);
			_delay_ms(10);

			if (UART_data[1] == 'O')
			{
				LCD_clearScreen();
				LCD_moveCursor(0,0);
				LCD_displayString("Matched!!");
				_delay_ms(250);
				case_select = 1;
			}
			else
			{
				LCD_clearScreen();
				LCD_moveCursor(0,0);
				LCD_displayString("Unmatched!!");
				_delay_ms(500);
				LCD_clearScreen();
				LCD_moveCursor(0,0);
				LCD_displayString("plz enter pass");

			}

			break;

		case 1:
			LCD_clearScreen();
			LCD_moveCursor(0,0);
			LCD_displayString("+ : Open Door");
			LCD_moveCursor(1,0);
			LCD_displayString("- : Change Pass");
			sel_key = KEYPAD_getPressedKey();
			if (sel_key != '+' && sel_key != '-') break;

			case_select = 2;

			break;


		case 2:
			LCD_clearScreen();
			LCD_moveCursor(0,0);
			LCD_displayString("plz enter pass");

			LCD_moveCursor(1,0);
			UART_data [0] = '2';

			for(counter = 0 ; counter<5 ; counter++)
			{
				key = KEYPAD_getPressedKey();
				if (key <=13)
					UART_data[counter+1] = key +'0'  ;

				else UART_data[counter+1] = key;
				LCD_displayCharacter('*');
			}

			while(KEYPAD_getPressedKey() != '=');

			UART_data[6] = '#';
			UART_data[7] = '\0';

			UART_sendString(UART_data);
			_delay_ms(10);
			UART_receiveString(UART_data);
			_delay_ms(10);

			if (UART_data[1] == 'O')
			{
				wrongPass = 0;

				if (sel_key == '+')
				{
					UART_data[0] = '3';
					UART_data[1] = '#';
					UART_data[2] = '\0';
					UART_sendString(UART_data);

					Timer1_con.initial_value = 0;
					Timer1_con.compare_value = 58594;
					Timer1_con.prescaler = PSC_1024;
					Timer1_con.mode = CTC;
					Timer1_init(&Timer1_con);

					LCD_clearScreen();
					LCD_moveCursor(0,0);
					LCD_displayString("    Opening");

					uint8 c =14;
					while(g_clbk == 0)
					{
						LCD_moveCursor(1,7);
						LCD_intgerToString(c);
						if (c<10)
						{
							LCD_moveCursor(1,8);
							LCD_displayCharacter(' ');
						}
						_delay_ms(1000);
						c--;
					}

					Timer1_con.initial_value = 0;
					Timer1_con.compare_value = 31250;
					Timer1_con.prescaler = PSC_256;
					Timer1_con.mode = CTC;
					Timer1_init(&Timer1_con);

					LCD_clearScreen();
					LCD_moveCursor(0,0);
					LCD_displayString("    Holding");
					while(g_clbk == 1);

					Timer1_con.initial_value = 0;
					Timer1_con.compare_value = 58594;
					Timer1_con.prescaler = PSC_1024;
					Timer1_con.mode = CTC;
					Timer1_init(&Timer1_con);

					LCD_clearScreen();
					LCD_moveCursor(0,0);
					LCD_displayString("    Closing");
					c = 14;

					while(g_clbk == 2)
					{
						LCD_moveCursor(1,7);
						LCD_intgerToString(c);
						if (c<10)
						{
							LCD_moveCursor(1,8);
							LCD_displayCharacter(' ');
						}
						_delay_ms(1000);
						c--;
					}

					Timer1_deInit();
					LCD_clearScreen();
					g_clbk=0;

					//*********
					case_select = 1;

				}
				else if (sel_key == '-')
				{
					LCD_clearScreen();
					LCD_moveCursor(0,0);
					LCD_displayString("plz enter pass");
					case_select=0;
				}

			}
			else
			{
				wrongPass ++;
				if (wrongPass == 3)
				{
					LCD_clearScreen();
					LCD_moveCursor(0,0);
					LCD_displayString("WRONG PASS !!");
					_delay_ms(500);

					UART_data[0] = '4';
					UART_data[1] = '#';
					UART_data[2] = '\0';
					UART_sendString(UART_data);

					Timer1_con.initial_value = 0;
					Timer1_con.compare_value = 58594;
					Timer1_con.prescaler = PSC_1024;
					Timer1_con.mode = CTC;
					Timer1_init(&Timer1_con);

					LCD_clearScreen();
					LCD_moveCursor(0,0);
					LCD_displayString("  E R R O R !!  ");
					uint8 c = 60;
					while(g_clbk <4){
						LCD_moveCursor(1,7);
						LCD_intgerToString(c);
						if (c<10)
						{
							LCD_moveCursor(1,8);
							LCD_displayCharacter(' ');
						}
						_delay_ms(1000);
						c--;
					}

					Timer1_deInit();

					g_clbk=0;

					case_select = 1;

				}

				else
				{
					LCD_clearScreen();
					LCD_moveCursor(0,0);
					LCD_displayString(" WRONG PASS !!");
					LCD_moveCursor(1,0);
					LCD_displayString("  TRY AGAIN  ");
					_delay_ms(500);
					case_select = 2;
				}

			}

			break;
		}

	}


	return 0;
}
