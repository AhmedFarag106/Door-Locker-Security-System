/*
 * timer1.h
 *
 *  Created on: Nov 3, 2023
 *      Author: Ahmed
 */

#ifndef TIMER1_H_
#define TIMER1_H_

#include "std_types.h"

typedef enum {

	No_Clock ,
	PSC_1 ,
	PSC_8 ,
	PSC_64 ,
	PSC_256 ,
	PSC_1024 ,
	EXT_F ,
	EXT_R

}Timer1_Prescaler;

typedef enum {

	Normal,
	CTC
}Timer1_Mode;

typedef struct {
	uint16 initial_value;
	uint16 compare_value; // it will be used in compare mode only.
	Timer1_Prescaler prescaler;
	Timer1_Mode mode;
} Timer1_ConfigType;

void Timer1_init(const Timer1_ConfigType * Config_Ptr);
void Timer1_deInit(void);
void Timer1_setCallBack(void(*a_ptr)(void));

#endif /* TIMER1_H_ */
