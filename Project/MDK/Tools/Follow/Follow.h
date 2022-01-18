#ifndef __FOLLOW_H
#define __FOLLOW_H

#include "headfile.h"
#include "beep.h"
#include "Position_PID.h"

void Follow(uint16 CenterLine[MT9V03X_CSI_H]);
float CalculateError(uint16 CenterLine[MT9V03X_CSI_H]);
float CalculateErrorSqr(uint16 CenterLine[MT9V03X_CSI_H]);

#endif 