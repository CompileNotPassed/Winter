#ifndef __BORDER_H
#define __BORDER_H

#include "headfile.h"
#include "beep.h"
#include "Cross.h"
#include "Commondef.h"
#include "Loss.h"

uint8_t UpdownSideGet(uint8_t imageInput[MT9V03X_CSI_H][MT9V03X_CSI_W], uint8_t imageOut[2][MT9V03X_CSI_W]);

#endif