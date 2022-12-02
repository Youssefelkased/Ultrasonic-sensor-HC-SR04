/******************************************************************************
 *
 * Module: Ultrasonic
 *
 * File Name: ultrasonic.c
 *
 * Description: Source file for the AVR Ultrasonic driver
 *
 * Author: Youssef Mamdouh
 *
 *******************************************************************************/

#include "ultrasonic.h"
#include "common_macros.h"
#include "gpio.h"
#include <avr/delay.h>
#include <avr/io.h>
#include "icu.h"
/*******************************************************************************
 *                         Global Variables                                    *
 *******************************************************************************/
uint8 g_tick=0;
uint16 highTime=0;
Icu_ConfigType Icu_Config = {F_CPU_8,RISING};
/*******************************************************************************
 *                         Functions Definition                                *
 *******************************************************************************/
void Ultrasonic_init(void)
{
	Icu_init(&Icu_Config);
	Icu_setCallBack(Ultrasonic_edgeProcessing);
	GPIO_setupPinDirection(PORTB_ID, PIN5_ID, PIN_OUTPUT);
}
void Ultrasonic_Trigger(void)
{
	GPIO_writePin(PORTB_ID, PIN5_ID, LOGIC_HIGH);
	_delay_ms(10);
	GPIO_writePin(PORTB_ID, PIN5_ID, LOGIC_LOW);
}
uint16 Ultrasonic_readDistance(void)
{
	Ultrasonic_Trigger();
	return (uint16)((float)highTime/58.8);
}
void Ultrasonic_edgeProcessing(void)
{

	if(g_tick==0)
	{
		Icu_clearTimerValue();
		Icu_setEdgeDetectionType(FALLING);
		g_tick=1;
	}
	else if(g_tick==1)
	{
		highTime=Icu_getInputCaptureValue();
		Icu_setEdgeDetectionType(RISING);
		g_tick=0;
		Icu_clearTimerValue();
	}

}

