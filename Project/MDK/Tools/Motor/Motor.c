#include "Motor.h"

pid_t Motor[4];
int16 encoder[4];
float speed[4];
float speedx,speedy,speedt;

void Getspeed()
{
		encoder[2] = -qtimer_quad_get(QTIMER_1,QTIMER1_TIMER0_C0 );
    encoder[3] = qtimer_quad_get(QTIMER_1,QTIMER1_TIMER2_C2 );
    encoder[1] = qtimer_quad_get(QTIMER_2,QTIMER2_TIMER0_C3 );
    encoder[0] = -qtimer_quad_get(QTIMER_3,QTIMER3_TIMER2_B18);
        
    qtimer_quad_clear(QTIMER_1,QTIMER1_TIMER0_C0 );
    qtimer_quad_clear(QTIMER_1,QTIMER1_TIMER2_C2 );
    qtimer_quad_clear(QTIMER_2,QTIMER2_TIMER0_C3 );
    qtimer_quad_clear(QTIMER_3,QTIMER3_TIMER2_B18);
}

void MotorOutput(pid_t *Mot,float *Target)
{
	Getspeed();
	for(int i=0;i<4;i++)
	{
		speed[i] = Position_PID_Realize(&Mot[i], Target[i],(float)encoder[i]);
		EnableMotor(speed[i],i);
	}
}

void CalculateSpeed(float speedx_t, float speedy_t, float speedw_t, float k)
{
	speed[0] = speedy_t-speedx_t+k*speedw_t;
	speed[1] = speedy_t+speedx_t-k*speedw_t;
	speed[2] = speedy_t-speedx_t-k*speedw_t;
	speed[3] = speedy_t+speedx_t+k*speedw_t;
}

int error;


void FixDirection(float k,float sum1)
{
	float w,y;
	w=k*10;
	y=(-sum1)*20;
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


