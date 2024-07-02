/*
 * DCmotor.h
 *
 *  Created on: Oct 13, 2023
 *      Author: Ahmed
 */

#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#include "common_macros.h"
#include "std_types.h"
#include "gpio.h"


#define IN1_PIN PIN0_ID
#define IN1_PORT PORTB_ID

#define IN2_PIN PIN1_ID
#define IN2_PORT PORTB_ID

#define EN1_PIN PIN3_ID
#define EN1_PORT PORTB_ID


#define IN3_PIN
#define IN3_PORT

#define IN4_PIN
#define IN4_PORT

#define EN2_PIN
#define EN2_PORT

typedef enum {
	STOP,CCW,CW
}DcMotor_State;

void DcMotor_Init(void);

void DcMotor_Rotate(DcMotor_State state,uint8 speed);

#endif /* DCMOTOR_H_ */
