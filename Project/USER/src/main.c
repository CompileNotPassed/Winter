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
    board_init();   	//务必保留，本函数用于初始化MPU 时钟 调试串口
    
	systick_delay_ms(300);	//延时300ms，等待主板其他外设上电成功

    bspInit();
    //Position_PID_Init(Motor,25,0.1,0,30000,15000);
	wirelessInit();
	
    //显示模式设置为3  竖屏模式
    //显示模式在SEEKFREE_18TFT.h文件内的TFT_DISPLAY_DIR宏定义设置
    lcd_init();     	//初始化TFT屏幕
    lcd_showstr(0,0,"Initializing...");
    //如果屏幕没有任何显示，请检查屏幕接线
    
	initMenu();
    //mt9v03x_csi_init();	//初始化摄像头 使用CSI接口
    //如果屏幕一直显示初始化信息，请检查摄像头接线
    //如果使用主板，一直卡在while(!uart_receive_flag)，请检查是否电池连接OK?
    //如果图像只采集一次，请检查场信号(VSY)是否连接OK?
    
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





