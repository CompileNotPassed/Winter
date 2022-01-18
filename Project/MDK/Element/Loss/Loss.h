#ifndef __LOSS_H
#define __LOSS_H

#include "headfile.h"
#include "beep.h"
#include "Commondef.h"

void RoadNoSideProcess(uint8_t imageInput[MT9V03X_CSI_H][MT9V03X_CSI_W],uint8_t imageOut[MT9V03X_CSI_H][2],uint8_t mode,uint8_t lineIndex);
uint8_t RoadIsNoSide(uint8_t imageInput[MT9V03X_CSI_H][MT9V03X_CSI_W],uint8_t imageOut[MT9V03X_CSI_H][2],uint8_t lineIndex);

#endif