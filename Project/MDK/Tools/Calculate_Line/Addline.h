#ifndef __ADDLINE_H
#define __ADDLINE_H

#include "headfile.h"
#include "beep.h"
#include "Commondef.h"

void ImageAddingLine(uint8_t imageSide[MT9V03X_CSI_H][2],uint8_t status,uint8_t startX,uint8_t startY,uint8_t endX,uint8_t endY);

#endif 