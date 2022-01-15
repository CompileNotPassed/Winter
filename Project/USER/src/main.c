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
#include <lib/function.h>
int i,j,cnt=0;
int8 a[2]={100,70};
uint8 frame[128][160];

uint8 uart_flag = 0;		
uint8 uart_data = 0;

int main(void)
{
    DisableGlobalIRQ();
    board_init();   	//��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���
    
	systick_delay_ms(300);	//��ʱ300ms���ȴ��������������ϵ�ɹ�

	wirelessInit();
	
    //��ʾģʽ����Ϊ3  ����ģʽ
    //��ʾģʽ��SEEKFREE_18TFT.h�ļ��ڵ�TFT_DISPLAY_DIR�궨������
    lcd_init();     	//��ʼ��TFT��Ļ
    lcd_showstr(0,0,"Initializing...");
    //�����Ļû���κ���ʾ��������Ļ����
    
	initMenu();
    mt9v03x_csi_init();	//��ʼ������ͷ ʹ��CSI�ӿ�
    //�����Ļһֱ��ʾ��ʼ����Ϣ����������ͷ����
    //���ʹ�����壬һֱ����while(!uart_receive_flag)�������Ƿ�������OK?
    //���ͼ��ֻ�ɼ�һ�Σ����鳡�ź�(VSY)�Ƿ�����OK?
    
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





