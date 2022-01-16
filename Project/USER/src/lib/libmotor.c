#include "headfile.h"
#include "function.h"

extern int16 encoder[4];

float speed[4];
void MotorOutput(pid_t *Mot,float *Target)
{
	for(int i=0;i<4;i++)
	{
		speed[i] = Position_PID_Realize(&Mot[i], Target[i], encoder[i]);
		EnableMotor(speed[i],i);
	}
}
void EnableMotor(float speed,uint8 num)
{
	if(num==0){
		if(speed>=0){
			gpio_set(D14,0);
			pwm_duty(PWM1_MODULE0_CHA_D12,(uint32)speed);
		}
		else {
			gpio_set(D14,1);
			pwm_duty(PWM1_MODULE0_CHA_D12,(uint32)(-speed));
		}
	}
	else if(num==1) {
		if(speed>=0){
			gpio_set(D15,0);
			pwm_duty(PWM1_MODULE0_CHB_D13,(uint32)speed);
		}
		else {
			gpio_set(D15,1);
			pwm_duty(PWM1_MODULE0_CHB_D13,(uint32)(-speed));
		}
	}
	else if(num==2) {
		if(speed>=0){
			gpio_set(D0,1);
			pwm_duty(PWM2_MODULE3_CHA_D2,(uint32)speed);
		}
		else {
			gpio_set(D0,0);
			pwm_duty(PWM2_MODULE3_CHA_D2,(uint32)(-speed));
		}
	}
	else if(num==3) {
		if(speed>=0){
			gpio_set(D1,0);
			pwm_duty(PWM2_MODULE3_CHB_D3,(uint32)speed);
		}
		else {
			gpio_set(D1,1);
			pwm_duty(PWM2_MODULE3_CHB_D3,(uint32)(-speed));
		}
	}
}