#ifndef __POSITION_PID_H_
#define __POSITION_PID_H_

//#include "main.h"

typedef struct{
		int SetValue;
		int ActualValue;
		int err;
		int err_last;
		float Kp,Ki,Kd;
		float result;
		float voltage;
		int integral;
		int maxintegral;
		int integrallimit;
		int maxout;
}pid_t; 


typedef struct
{
		signed short 	ActualValue;
		float	 				a;
		signed short  Result_Last;
		signed short  Result;
}lowpass_t; 

extern float target;


void 	Position_PID_Init(pid_t *PID_Motor, float Kp,float Ki,float Kd,int maxintegral,int integrallimit,int maxout);
float Position_PID_Realize(pid_t *PID_Motor,float v,float v_r);

void Position_LWF_Init(void);
signed short Position_LWF_Realize(signed short Value,float a);

int Calculate(int target,int speed,float Kp,float Ki,float Kd,int intergralmax,int limit);

#endif
