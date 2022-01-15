#include "beep.h"

void Beep_on()
{
	gpio_set(BEEP_PIN,1);
}

void Beep_off()
{
	gpio_set(BEEP_PIN,0);
}
