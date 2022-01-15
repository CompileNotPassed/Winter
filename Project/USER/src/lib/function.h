#include<headfile.h>
//ImageProcess
void picGamma(uint8 in_array[][168], uint8 out_array[][168], long height, long width);
uint8 OTSU(uint8 *pic,uint16 num);
//BorderDetect
void borderDetect(uint8 in[][160],uint8 out[][160]);
//Menu
void initMenu();
void readKey();
void showFirstMenu(char sel);
//Move
//Wireless
void    wirelessInit(void);
uint32  sendBuff(uint8 *buff, uint32 len);
void sendWare(void *wareaddr, uint32 waresize);