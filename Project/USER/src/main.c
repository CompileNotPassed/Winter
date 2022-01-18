/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		main
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		IAR 8.3 or MDK 5.24
 * @Target core		NXP RT1064DVL6A
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 * @note
					���߶��壺
					------------------------------------ 
						1.8TFTģ��ܽ�      ��Ƭ���ܽ�
						SCL                 �鿴SEEKFREE_18TFT.H�ļ��е�TFT_SCL  	�궨��     Ӳ��SPI���Ų��������л�
						SDA                 �鿴SEEKFREE_18TFT.H�ļ��е�TFT_SDA		�궨��     Ӳ��SPI���Ų��������л�
						RES                 �鿴SEEKFREE_18TFT.H�ļ��е�REST_PIN	�궨��   
						DC                  �鿴SEEKFREE_18TFT.H�ļ��е�DC_PIN		�궨�� 
						CS                 	�鿴SEEKFREE_18TFT.H�ļ��е�TFT_CS		�궨��     Ӳ��SPI���Ų��������л�
						
						��Դ����
						BL  3.3V��Դ������������ţ�Ҳ���Խ�PWM���������ȣ�
						VCC 3.3V��Դ
						GND ��Դ��
						���ֱ���128*160
					------------------------------------ 
						�����ģ��ܽ�      ��Ƭ���ܽ�
						SDA(51��RX)         �鿴SEEKFREE_MT9V03X_CSI.h�ļ��е�MT9V03X_CSI_COF_UART_TX	�궨��
						SCL(51��TX)         �鿴SEEKFREE_MT9V03X_CSI.h�ļ��е�MT9V03X_CSI_COF_UART_RX	�궨��
						���ж�(VSY)         �鿴SEEKFREE_MT9V03X_CSI.h�ļ��е�MT9V03X_CSI_VSYNC_PIN		�궨��
						���ж�(HREF)	    ����Ҫʹ��
						�����ж�(PCLK)      �鿴SEEKFREE_MT9V03X_CSI.h�ļ��е�MT9V03X_CSI_PCLK_PIN		�궨��
						���ݿ�(D0-D7)		B31-B24 B31��Ӧ����ͷ�ӿ�D0
					------------------------------------ 
	
						Ĭ�Ϸֱ�����        188*120
						Ĭ��FPS             50֡
 ********************************************************************************************************************/


//�����Ƽ�IO�鿴Projecct�ļ����µ�TXT�ı�



//���µĹ��̻��߹����ƶ���λ�����ִ�����²���
//��һ�� �ر��������д򿪵��ļ�
//�ڶ��� project  clean  �ȴ��·�����������



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
    board_init();   	//��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���
    BspInit();
		systick_delay_ms(300);	//��ʱ300ms���ȴ��������������ϵ�ɹ�
	
    //��ʾģʽ����Ϊ3  ����ģʽ
    //��ʾģʽ��SEEKFREE_18TFT.h�ļ��ڵ�TFT_DISPLAY_DIR�궨������
    lcd_init();     	//��ʼ��TFT��Ļ
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
	
	qtimer_quad_init(QTIMER_1,QTIMER1_TIMER0_C0,QTIMER1_TIMER1_C1);   //��ʼ�� QTIMER_1 A��ʹ��QTIMER1_TIMER2_C2 B��ʹ��QTIMER1_TIMER3_C24
  qtimer_quad_init(QTIMER_1,QTIMER1_TIMER2_C2,QTIMER1_TIMER3_C24);    
  qtimer_quad_init(QTIMER_2,QTIMER2_TIMER0_C3,QTIMER2_TIMER3_C25);
  qtimer_quad_init(QTIMER_3,QTIMER3_TIMER2_B18,QTIMER3_TIMER3_B19);
	
	Position_PID_Init(&Motor[0],120,0.1,0,30000,10000,30000);
	Position_PID_Init(&Motor[1],120,0.1,0,30000,10000,30000);
	Position_PID_Init(&Motor[2],120,0.1,0,30000,10000,30000);
	Position_PID_Init(&Motor[3],120,0.1,0,30000,10000,30000);
	seekfree_wireless_init();
	buzzer(200);
	
	pit_init();                     //��ʼ��pit����
  pit_interrupt_ms(PIT_CH0,10);  //��ʼ��pitͨ��0 ����
	NVIC_SetPriority(PIT_IRQn,0); 
	
}



