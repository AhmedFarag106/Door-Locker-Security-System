/*
 * DCmotor.c
 *
 *  Created on: Oct 13, 2023
 *      Author: Ahmed
 */

#include "DCmotor.h"
#include "gpio.h"
#include "PWM.h"
#include "std_types.h"
#include "common_macros.h"


void DcMotor_Init(void)
{
	GPIO_setupPinDirection (IN1_PORT,IN1_PIN,PIN_OUTPUT);
	GPIO_setupPinDirection (IN2_PORT,IN2_PIN,PIN_OUTPUT);
	GPIO_setupPinDirection (EN1_PORT,EN1_PIN,PIN_OUTPUT);

	GPIO_writePin(IN1_PORT,IN1_PIN,LOGIC_LOW);
	GPIO_writePin(IN2_PORT,IN2_PIN,LOGIC_LOW);
	GPIO_writePin(EN1_PORT,EN1_PIN,LOGIC_LOW);
}

void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{

	if (state == STOP){
		GPIO_writePin(IN1_PORT,IN1_PIN,LOGIC_LOW);
		GPIO_writePin(IN2_PORT,IN2_PIN,LOGIC_LOW);
	}

	else if (state == CW){
		GPIO_writePin(IN1_PORT,IN1_PIN,LOGIC_LOW);
		GPIO_writePin(IN2_PORT,IN2_PIN,LOGIC_HIGH);
	}
	else if (state == CCW){
		GPIO_writePin(IN1_PORT,IN1_PIN,LOGIC_HIGH);
		GPIO_writePin(IN2_PORT,IN2_PIN,LOGIC_LOW);
	}

	uint8 pwm = (uint8)((uint32)speed * 255 / 100);

	Timer0_PWM_Init(pwm);

}
