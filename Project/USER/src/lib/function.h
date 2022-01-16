#include <headfile.h>

#define L 'L'
#define R 'R'
//ImageProcess
void picGamma(uint8 in_array[][168], uint8 out_array[][168], long height, long width);
uint8 OTSU(uint8 *pic, uint16 num);

//BorderDetect
//void borderDetect(uint8 in[][160], uint8 out[][160]);
void borderDetect(uint8 (*in)[MT9V03X_CSI_W], uint8 (*out)[MT9V03X_CSI_W]);

//Calc
float linearFitting(uint8 line[MT9V03X_CSI_H],int16 lineFitted[MT9V03X_CSI_H]);

//Element Recognize
char regRing(int16 leftLine[MT9V03X_CSI_H],int16 rightLine[MT9V03X_CSI_H],char directrion);

//Menu
void initMenu(void);
void readKey(void);
void showFirstMenu(char sel);

//PID
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
}pid_t;

void Position_PID_Init(pid_t *PID_Motor, float Kp, float Ki, float Kd, int maxintegral, int integrallimit);
float Position_PID_Realize(pid_t *PID_Motor, float Target, float Input); 

//Motor
void MotorOutput(pid_t *Mot,float *Target);
void EnableMotor(float speed,uint8 num);

//Move
void mecmove(uint8 vx, uint8 vy, uint8 va);

//Wireless
void wirelessInit(void);
uint32 sendBuff(uint8 *buff, uint32 len);
void sendWare(void *wareaddr, uint32 waresize);
void sendImage(void *wareaddr, uint32 waresize);

//BSP
void bspInit(void);

//Encoder
void getEncoder(void);

//Buzzer
void buzzer(uint8 timems);
void Beep_on(void);
void Beep_off(void);

