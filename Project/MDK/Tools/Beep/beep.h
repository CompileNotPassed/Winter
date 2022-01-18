#ifndef __BEEP_H
#define __BEEP_H

#include "headfile.h"

#define BEEP_PIN B11

void Beep_on(void);
void Beep_off(void);
void buzzer(uint16 time);

#endif
