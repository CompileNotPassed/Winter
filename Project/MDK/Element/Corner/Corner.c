#include "Corner.h"

void JudgeCorner(int16 LeftLine[MT9V03X_CSI_H],int16 RightLine[MT9V03X_CSI_H],int16 CenterLine[MT9V03X_CSI_H])
{
	uint16 leftsignal_l,rightsignal_l,leftsignal_r,rightsignal_r;
	uint16 leftsignal,rightsignal;
	bool left,right;
	for(int i=118;i>0;i--)
	{
		if(LeftLine[i]-LeftLine[i+1]>5) leftsignal_l++;
		else if(LeftLine[i]-LeftLine[i+1]<-5) rightsignal_l++;
		if(RightLine[i]-RightLine[i+1]>5) leftsignal_r++;
		else if(RightLine[i]-RightLine[i+1]<-5) rightsignal_r++;
		if(CenterLine[i]-CenterLine[i+1]>5) leftsignal++;
		else if(CenterLine[i]-CenterLine[i+1]<-5) rightsignal++;
	}
	if(leftsignal_l>5&&leftsignal_r>5&&leftsignal>5)
	{
		left=1;
	}
	else if(rightsignal_l>5&&rightsignal_r>5&&rightsignal>5)
	{
		right=1;
	}
}

