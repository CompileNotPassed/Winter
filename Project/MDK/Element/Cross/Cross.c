#include "Cross.h"

uint16 crosstime,crosstimecopy;

void JudgeCross(uint16 LeftLine[MT9V03X_CSI_H],uint16 RightLine[MT9V03X_CSI_H],uint16 CenterLine[MT9V03X_CSI_H],uint16 Require_Crosstime)
{
	bool crossflag;
	uint16 lasttime;
	uint16 cout,lastcross;
	uint16 crossstart,crossend;
	float slope,slope_l,slope_r;
	for(int i=MT9V03X_CSI_H-21;i>10;i--)
	{
		if(LeftLine[i]==0&&RightLine[i]==187)
		{	
			if(crossflag==0)
			{
				if((LeftLine[lasttime+1]-LeftLine[lasttime+2]<3)&&(RightLine[lasttime+2]-RightLine[lasttime+1]<3)&&(LeftLine[i+1]-LeftLine[i]>20)&&(RightLine[i]-RightLine[i+1]>20))
				{
					crossflag=1;
				}
			}
			if((lastcross-i==1)&&crossflag&&crossstart)
			{
				if((LeftLine[i-1]-LeftLine[i]>20)&&(RightLine[i]-RightLine[i-1]>20)) crossend=i-1;
				crosstime++;
				lastcross=i;
			}
			else
			{
				crossstart=i+1;
				crosstime=0;
				lastcross=i;
				crosstime++;
			}
		}
		else
		{
			lasttime=i;
		}
	}
	if(crosstime>=Require_Crosstime)
	{
		gpio_set(B9,0);
		crossflag=0;
		slope_l=Slope_Calculate(crossstart,187,LeftLine);
		slope_r=Slope_Calculate(crossstart,187,RightLine);
		slope=Slope_Calculate(crossstart,187,CenterLine);
		
	}
	else
	{
		Beep_on();
	}
	crosstimecopy=crosstime;
	crosstime=0;
}