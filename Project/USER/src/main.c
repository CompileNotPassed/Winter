/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		main
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		IAR 8.3 or MDK 5.24
 * @Target core		NXP RT1064DVL6A
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 * @note
					接线定义：
					------------------------------------ 
						1.8TFT模块管脚      单片机管脚
						SCL                 查看SEEKFREE_18TFT.H文件中的TFT_SCL  	宏定义     硬件SPI引脚不可随意切换
						SDA                 查看SEEKFREE_18TFT.H文件中的TFT_SDA		宏定义     硬件SPI引脚不可随意切换
						RES                 查看SEEKFREE_18TFT.H文件中的REST_PIN	宏定义   
						DC                  查看SEEKFREE_18TFT.H文件中的DC_PIN		宏定义 
						CS                 	查看SEEKFREE_18TFT.H文件中的TFT_CS		宏定义     硬件SPI引脚不可随意切换
						
						电源引脚
						BL  3.3V电源（背光控制引脚，也可以接PWM来控制亮度）
						VCC 3.3V电源
						GND 电源地
						最大分辨率128*160
					------------------------------------ 
						总钻风模块管脚      单片机管脚
						SDA(51的RX)         查看SEEKFREE_MT9V03X_CSI.h文件中的MT9V03X_CSI_COF_UART_TX	宏定义
						SCL(51的TX)         查看SEEKFREE_MT9V03X_CSI.h文件中的MT9V03X_CSI_COF_UART_RX	宏定义
						场中断(VSY)         查看SEEKFREE_MT9V03X_CSI.h文件中的MT9V03X_CSI_VSYNC_PIN		宏定义
						行中断(HREF)	    不需要使用
						像素中断(PCLK)      查看SEEKFREE_MT9V03X_CSI.h文件中的MT9V03X_CSI_PCLK_PIN		宏定义
						数据口(D0-D7)		B31-B24 B31对应摄像头接口D0
					------------------------------------ 
	
						默认分辨率是        188*120
						默认FPS             50帧
 ********************************************************************************************************************/


//整套推荐IO查看Projecct文件夹下的TXT文本



//打开新的工程或者工程移动了位置务必执行以下操作
//第一步 关闭上面所有打开的文件
//第二步 project  clean  等待下方进度条走完



#include "headfile.h"
#include "string.h"
#include "Otsu.h"
#include "Motor.h"
#include "sendware.h"
#include "beep.h"

extern uint8 (*a)[MT9V03X_CSI_W];

void BspInit(void);

extern int encoder[4];


int main(void)
{
    DisableGlobalIRQ();
    board_init();   	//务必保留，本函数用于初始化MPU 时钟 调试串口
    BspInit();
		systick_delay_ms(300);	//延时300ms，等待主板其他外设上电成功
	
    //显示模式设置为3  竖屏模式
    //显示模式在SEEKFREE_18TFT.h文件内的TFT_DISPLAY_DIR宏定义设置
    lcd_init();     	//初始化TFT屏幕
    lcd_showstr(0,0,"SEEKFREE MT9V03x");
    lcd_showstr(0,1,"Initializing...");
    
    mt9v03x_csi_init();	
    
    lcd_showstr(0,1,"     OK...     ");
    systick_delay_ms(500);
    
    EnableGlobalIRQ(0);
    while(1)
    {
			if(mt9v03x_csi_finish_flag)
      {
				mt9v03x_csi_finish_flag = 0;
				JudgeMid(a,mt9v03x_csi_image,MT9V03X_CSI_W, MT9V03X_CSI_H);
       }
//			vcan_sendware(encoder,sizeof(encoder));
    }
}


void BspInit()
{
	gpio_init(B11,GPO,0,GPIO_PIN_CONFIG); 
	gpio_init(D0,GPO,1,GPIO_PIN_CONFIG);  //leftbot
	gpio_init(D1,GPO,0,GPIO_PIN_CONFIG);  //rightbot
	gpio_init(D14,GPO,0,GPIO_PIN_CONFIG);  //lefttop
	gpio_init(D15,GPO,0,GPIO_PIN_CONFIG);  //righttop
	
  pwm_init(PWM2_MODULE3_CHB_D3 , 17000, 0);  //  0  rightbot
  pwm_init(PWM2_MODULE3_CHA_D2 , 17000, 0);  // 1  leftbot
	pwm_init(PWM1_MODULE0_CHB_D13, 17000, 0);  //  0  righttop
	pwm_init(PWM1_MODULE0_CHA_D12, 17000, 0);  // 0  lefttop
	
	qtimer_quad_init(QTIMER_1,QTIMER1_TIMER0_C0,QTIMER1_TIMER1_C1);   //初始化 QTIMER_1 A相使用QTIMER1_TIMER2_C2 B相使用QTIMER1_TIMER3_C24
  qtimer_quad_init(QTIMER_1,QTIMER1_TIMER2_C2,QTIMER1_TIMER3_C24);    
  qtimer_quad_init(QTIMER_2,QTIMER2_TIMER0_C3,QTIMER2_TIMER3_C25);
  qtimer_quad_init(QTIMER_3,QTIMER3_TIMER2_B18,QTIMER3_TIMER3_B19);
	
	Position_PID_Init(&Motor[0],120,0.1,0,30000,10000,30000);
	Position_PID_Init(&Motor[1],120,0.1,0,30000,10000,30000);
	Position_PID_Init(&Motor[2],120,0.1,0,30000,10000,30000);
	Position_PID_Init(&Motor[3],120,0.1,0,30000,10000,30000);
	seekfree_wireless_init();
	buzzer(200);
	
	pit_init();                     //初始化pit外设
  pit_interrupt_ms(PIT_CH0,10);  //初始化pit通道0 周期
	NVIC_SetPriority(PIT_IRQn,0); 
	
}



