#include "function.h"

pid_t Motor[4];

void Position_PID_Init(pid_t *PID_Motor, float Kp, float Ki, float Kd, int maxintegral, int integrallimit)
{
    PID_Motor->SetValue = 0;
    PID_Motor->ActualValue = 0;
    PID_Motor->err = 0;
    PID_Motor->err_last = 0;
    PID_Motor->integral = 0;
    PID_Motor->Kp = Kp;
    PID_Motor->Ki = Ki;
    PID_Motor->Kd = Kd;
    PID_Motor->maxintegral = maxintegral;
    PID_Motor->integrallimit = integrallimit;
}

float Position_PID_Realize(pid_t *PID_Motor, float Target, float Input)
{
    PID_Motor->SetValue = Target;
    PID_Motor->ActualValue = Input;
    PID_Motor->err = PID_Motor->SetValue - PID_Motor->ActualValue;
    if (PID_Motor->err <= PID_Motor->integrallimit && PID_Motor->err >= -PID_Motor->integrallimit)
    {
        PID_Motor->integral += PID_Motor->err;
        PID_Motor->result = PID_Motor->Kp * PID_Motor->err + PID_Motor->Ki * PID_Motor->integral + PID_Motor->Kd * (PID_Motor->err - PID_Motor->err_last);
    }
    else
    {
        PID_Motor->result = PID_Motor->Kp * PID_Motor->err + PID_Motor->Kd * (PID_Motor->err - PID_Motor->err_last);
        PID_Motor->integral = 0;
    }
    if (PID_Motor->integral >= PID_Motor->maxintegral)
        PID_Motor->integral = PID_Motor->maxintegral;
    if (PID_Motor->integral <= -PID_Motor->maxintegral)
        PID_Motor->integral = -PID_Motor->maxintegral;
    PID_Motor->err_last = PID_Motor->err;
    return PID_Motor->result;
}