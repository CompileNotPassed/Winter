#ifndef __Cross_H
#define __Cross_H

#include "headfile.h"
#include "Otsu.h"
#include "beep.h"

void JudgeCross(uint16 LeftLine[MT9V03X_CSI_H],uint16 RightLine[MT9V03X_CSI_H],uint16 CenterLine[MT9V03X_CSI_H],uint16 Require_Crosstime);

#endif