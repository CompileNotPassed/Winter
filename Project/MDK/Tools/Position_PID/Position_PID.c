#include "Position_PID.h"
#include "stdio.h"

lowpass_t	LWF_Motor;
float ControlSpeed = 0;
float Pwm;
float fspeed;
int integral;
int last_error;

void Position_PID_Init(pid_t *PID_Motor, float Kp,float Ki,float Kd,int maxintegral,int integrallimit,int maxout){
		PID_Motor->SetValue= 0;
		PID_Motor->ActualValue= 0;
		PID_Motor->err= 0;
		PID_Motor->err_last=0;
		PID_Motor->integral= 0;
		PID_Motor->Kp= Kp;
		PID_Motor->Ki= Ki;
		PID_Motor->Kd= Kd;
		PID_Motor->maxintegral=maxintegral;
		PID_Motor->integrallimit=integrallimit;
		PID_Motor->maxout=maxout;
	}


	
float Position_PID_Realize(pid_t *PID_Motor,float Target, float Input){
			PID_Motor->SetValue = Target;
			PID_Motor->ActualValue = Input;
			PID_Motor->err = PID_Motor->SetValue - PID_Motor->ActualValue;
			if(PID_Motor->err<=PID_Motor->integrallimit&&PID_Motor->err>=-PID_Motor->integrallimit)
			{
				PID_Motor->integral += PID_Motor->err;
				PID_Motor->result = PID_Motor->Kp * PID_Motor->err + PID_Motor->Ki * PID_Motor->integral + PID_Motor->Kd * ( PID_Motor->err - PID_Motor->err_last);
			}
			else
			{
				PID_Motor->result = PID_Motor->Kp * PID_Motor->err + PID_Motor->Kd * ( PID_Motor->err - PID_Motor->err_last);
				PID_Motor->integral=0;
			}
			if(PID_Motor->integral>=PID_Motor->maxintegral) 
				PID_Motor->integral = PID_Motor->maxintegral;
			if(PID_Motor->integral<=-PID_Motor->maxintegral) 
				PID_Motor->integral = -PID_Motor->maxintegral;
			if(PID_Motor->result>=PID_Motor->maxout) PID_Motor->result=PID_Motor->maxout;
			if(PID_Motor->result<=-PID_Motor->maxout) PID_Motor->result=-PID_Motor->maxout;
			PID_Motor->err_last = PID_Motor->err;
			return PID_Motor->result;
	}

void Position_LWF_Init(void){
		LWF_Motor.Result_Last = 0;
}





signed short Position_LWF_Realize(signed short Value,float a){
		LWF_Motor.Result= (1-a)*Value + a*LWF_Motor.Result_Last;
		LWF_Motor.Result_Last = LWF_Motor.Result;
		return LWF_Motor.Result;
	}

