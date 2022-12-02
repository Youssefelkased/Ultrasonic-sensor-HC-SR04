#include"lcd.h"
#include "ultrasonic.h"
#include <avr/interrupt.h>
int main()
{
	sei();
	uint16 distance=0;
	LCD_init();
	LCD_displayString("Distance =    cm");
	Ultrasonic_init();

	while(1)
	{
		LCD_moveCursor(0,11);
		distance=Ultrasonic_readDistance();
		LCD_intgerToString(distance);
	}
}
