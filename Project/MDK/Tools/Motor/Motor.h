#ifndef __MOTOR_H_
#define __MOTOR_H_

#include "headfile.h"
#include "SEEKFREE_18TFT.h"
#include "Position_PID.h"

extern pid_t Motor[4];
void CalculateSpeed(float speedx,float speedy,float speedw,float k);
void EnableMotor(float speed,uint8 num);
void Getspeed();
void MotorOutput(pid_t *Mot,float *Target);


#endif