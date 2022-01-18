#include "Follow.h"

void Follow(uint16 CenterLine[MT9V03X_CSI_H])
{
	float Excp,Vari;
	float w;
	Excp=CalculateError(CenterLine);
	Vari=CalculateErrorSqr(CenterLine);
//	w=Position_PID_Realize(&)
}

float CalculateError(uint16 CenterLine[MT9V03X_CSI_H])
{
	float a,b,c;
	float a2,b2,c2;
	float sum1 = 0;
  float sum2 = 0;
	float k;
	for(int i=MT9V03X_CSI_H-1;i>0;i--)
	{
		if(i>79)
		{
			a+= (CenterLine[i]-94)*3;
			a2+= (CenterLine[i]-94)*(CenterLine[i]-94)*3;
		}
		else if(i>39)
		{
			b += (CenterLine[i]-94)*2;
			b2 += (CenterLine[i]-94)*(CenterLine[i]-94)*2;
		}
		else
		{
			c += CenterLine[i]-94;
			c2 += (CenterLine[i]-94)*(CenterLine[i]-94);
		}
	}
	k=((CenterLine[0]-CenterLine[119])/120+(CenterLine[1]-CenterLine[118])/118)/2;
	sum1=(a+b+c)/120;
	sum2=(a2+b2+c2)/120;
	return sum1;
}

float CalculateErrorSqr(uint16 CenterLine[MT9V03X_CSI_H])
{
	float a2,b2,c2;
	float sum2 = 0;
	for(int i=MT9V03X_CSI_H-1;i>0;i--)
	{
		if(i>79)
		{
			a2+= (CenterLine[i]-94)*(CenterLine[i]-94)*3;
		}
		else if(i>39)
		{
			b2 += (CenterLine[i]-94)*(CenterLine[i]-94)*2;
		}
		else
		{
			c2 += (CenterLine[i]-94)*(CenterLine[i]-94);
		}
	}
	sum2=(a2+b2+c2)/120;
	return sum2;
}
