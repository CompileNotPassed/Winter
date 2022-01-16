#include "headfile.h"
#include <lib/function.h>
int i,j,cnt=0;
unsigned char (*frame)[160];

uint8 uart_flag = 0;		
uint8 uart_data = 0;

extern int16 encoder[4];
extern pid_t Motor[4];
extern float speed[4];

extern uint8_t sideLine[128][2];
extern uint8_t updownLine[2][160];

//TESTUSE
float setTarget[4]={400,400,400,400};

int main(void)
{
    DisableGlobalIRQ();
 
    board_init();   	
	systick_delay_ms(300);	
    
    bspInit();
    Position_PID_Init(&Motor[0],25,0.1,0,30000,15000);
    Position_PID_Init(&Motor[1],25,0.1,0,30000,15000);
    Position_PID_Init(&Motor[2],25,0.1,0,30000,15000);
    Position_PID_Init(&Motor[3],25,0.1,0,30000,15000);
	wirelessInit();
	
    lcd_init();     
    lcd_showstr(0,0,"Initializing...");
    
	initMenu();
    mt9v03x_csi_init();
    
    lcd_showstr(0,1,"Init OK.");
    systick_delay_ms(500);
    
    EnableGlobalIRQ(0);
	lcd_clear(WHITE);
	//showFirstMenu(0);
    buzzer(200);
    lcd_clear(WHITE);
    while(1)
    { 

		while(!mt9v03x_csi_finish_flag){} 
        for (uint8 i = 0; i < MT9V03X_CSI_H; i++)
        {
            for (uint8 j = 0; j < MT9V03X_CSI_W; j++)
            {
                frame[i][j]=mt9v03x_csi_image[i][j];
            }
            
        }
        Get_Bin_Image(1,frame,frame);
        Bin_Image_Filter(frame);
        ImageGetSide(frame, sideLine);
        UpdownSideGet(frame, updownLine);
         
        //sendImage(frame[0],160*128);
        lcdOutput(frame[0],160, 128, 160, 128);
	}
}





