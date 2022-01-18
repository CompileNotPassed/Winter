#include "beep.h"

void Beep_on()
{
	gpio_set(BEEP_PIN,1);
}

void Beep_off()
{
	gpio_set(BEEP_PIN,0);
}

void buzzer(uint16 time)
{
	Beep_on();
	systick_delay_ms(200);
	Beep_off();
}
