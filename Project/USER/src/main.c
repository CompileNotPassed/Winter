#include "headfile.h"
#include <lib/function.h>
int i,j,cnt=0;
int8 a[2]={100,70};
uint8 frame[128][160];

uint8 uart_flag = 0;		
uint8 uart_data = 0;

extern int16 encoder[4];
extern pid_t Motor[4];

//TESTUSE
float setTarget=1500;

int main(void)
{
    DisableGlobalIRQ();
    board_init();   	//��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���
    
	systick_delay_ms(300);	//��ʱ300ms���ȴ��������������ϵ�ɹ�

    bspInit();
    //Position_PID_Init(Motor,25,0.1,0,30000,15000);
	wirelessInit();
	
    //��ʾģʽ����Ϊ3  ����ģʽ
    //��ʾģʽ��SEEKFREE_18TFT.h�ļ��ڵ�TFT_DISPLAY_DIR�궨������
    lcd_init();     	//��ʼ��TFT��Ļ
    lcd_showstr(0,0,"Initializing...");
    //�����Ļû���κ���ʾ��������Ļ����
    
	initMenu();
    //mt9v03x_csi_init();	//��ʼ������ͷ ʹ��CSI�ӿ�
    //�����Ļһֱ��ʾ��ʼ����Ϣ����������ͷ����
    //���ʹ�����壬һֱ����while(!uart_receive_flag)�������Ƿ�������OK?
    //���ͼ��ֻ�ɼ�һ�Σ����鳡�ź�(VSY)�Ƿ�����OK?
    
    lcd_showstr(0,1,"Init OK.");
    systick_delay_ms(500);
    
    EnableGlobalIRQ(0);
	//lcd_clear(WHITE);
	//showFirstMenu(0);
    buzzer(100);
    lcd_clear(WHITE);
    while(1)
    {

		//while(!mt9v03x_csi_finish_flag){} 
    
		//mt9v03x_csi_finish_flag = 0;
		/*for(int i=0; i<128;i++){
			for(int j=0;j<160; j++){
				frame[i][j]=mt9v03x_csi_image[i][j];
			}
		}*/
        //lcdOutput(frame[0], 160, 128, 160, 128);
		//sendImage(frame[0], 160*128);
		//sendImage(mt9v03x_csi_image[0], 168*128);

        lcd_showint16(0,1,encoder[0]);
        lcd_showint16(0,2,encoder[1]);
        lcd_showint16(0,3,encoder[2]);
        lcd_showint16(0,4,encoder[3]);
        getEncoder();
        MotorOutput(Motor,&setTarget);
        sendWare(encoder,sizeof(encoder));
	}
}





