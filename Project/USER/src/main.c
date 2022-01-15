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
#include <lib/function.h>
int i,j,cnt=0;
int8 a[2]={100,70};
uint8 frame[128][160];

uint8 uart_flag = 0;		
uint8 uart_data = 0;

int main(void)
{
    DisableGlobalIRQ();
    board_init();   	//务必保留，本函数用于初始化MPU 时钟 调试串口
    
	systick_delay_ms(300);	//延时300ms，等待主板其他外设上电成功

	wirelessInit();
	
    //显示模式设置为3  竖屏模式
    //显示模式在SEEKFREE_18TFT.h文件内的TFT_DISPLAY_DIR宏定义设置
    lcd_init();     	//初始化TFT屏幕
    lcd_showstr(0,0,"Initializing...");
    //如果屏幕没有任何显示，请检查屏幕接线
    
	initMenu();
    mt9v03x_csi_init();	//初始化摄像头 使用CSI接口
    //如果屏幕一直显示初始化信息，请检查摄像头接线
    //如果使用主板，一直卡在while(!uart_receive_flag)，请检查是否电池连接OK?
    //如果图像只采集一次，请检查场信号(VSY)是否连接OK?
    
    lcd_showstr(0,1,"Init OK.");
    systick_delay_ms(500);
    
    EnableGlobalIRQ(0);
	//lcd_clear(WHITE);
	//showFirstMenu(0);
    while(1)
    {
			//sendBuff(test1,sizeof(test1)-1);
			//sendBuff(test2,sizeof(test2)-1);
			sendWare(a,sizeof(a));
			systick_delay_ms(100);
	}
		
    

}





