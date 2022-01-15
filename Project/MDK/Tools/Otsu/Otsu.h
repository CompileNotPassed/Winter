#ifndef __OTSU_H_
#define __OTSU_H_

#include "headfile.h"
#include "SEEKFREE_18TFT.h"

uint8 otsuThreshold(uint8 *image, uint16 width, uint16 height);
void JudgeMid(uint8 (*a)[MT9V03X_CSI_W],uint8 (*image)[MT9V03X_CSI_W], uint16 width, uint16 height);
void borderDetect(uint8 (*in)[MT9V03X_CSI_W],uint8 (*out)[MT9V03X_CSI_W]);
void JudgeCross(uint16 LeftLine[MT9V03X_CSI_H],uint16 RightLine[MT9V03X_CSI_H],uint16 CenterLine[MT9V03X_CSI_H],uint16 Require_Crosstime);
float Slope_Calculate(uint8 begin,uint8 end,uint16 *p);


void TurnLeft();
void TurnRight();

#endif