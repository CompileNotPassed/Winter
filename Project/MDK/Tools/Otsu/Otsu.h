#ifndef __OTSU_H_
#define __OTSU_H_

#include "headfile.h"
#include "SEEKFREE_18TFT.h"

uint8 otsuThreshold(uint8 *image, uint16 width, uint16 height);
void JudgeMid(uint8 (*a)[MT9V03X_CSI_W],uint8 (*image)[MT9V03X_CSI_W], uint16 width, uint16 height);
void borderDetect(uint8 (*in)[MT9V03X_CSI_W],uint8 (*out)[MT9V03X_CSI_W]);
float Slope_Calculate(uint8 begin,uint8 end,uint16 *p);
void UpdownShow(uint8 (*a)[MT9V03X_CSI_W],uint8_t imageOut[2][MT9V03X_CSI_W]);


void TurnLeft();
void TurnRight();

#endif