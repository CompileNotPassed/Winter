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
		Beep_on();
		crossflag=0;
		slope_l=Slope_Calculate(crossstart,187,LeftLine);
		slope_r=Slope_Calculate(crossstart,187,RightLine);
		slope=Slope_Calculate(crossstart,187,CenterLine);
		
	}
	else
	{
		Beep_off();
	}
	crosstimecopy=crosstime;
	crosstime=0;
}

uint16 left,right;
uint16 templeft[MT9V03X_CSI_H],tempright[MT9V03X_CSI_H];
uint16 LeftLine[MT9V03X_CSI_H],RightLine[MT9V03X_CSI_H],CenterLine[MT9V03X_CSI_H];
void JudgeCrossRoad(uint8 (*in)[MT9V03X_CSI_W],uint8 require_crosstime)
{
	
	int16 k_left,k_right;
	
	for(int i=MT9V03X_CSI_H;i>110;i--)
	{
		left=MT9V03X_CSI_W/2;
		right=MT9V03X_CSI_W/2;
		if(in[i][left]){
			for(;in[i][left]&&(left>0);left--)
			{
			}
			templeft[i]=left;
//			in[i][left]=103;
		}
		else{
			for(;(!in[i][left])&&(left>0);left--)
			{
			}
			if(left==0){
				for(left=MT9V03X_CSI_W/2;(!in[i][left])&&(left<187);left++)
				{
				}
			}
			else{
				for(;(in[i][left])&&(left>0);left--)
				{
				}
			}
//			in[i][left]=103;
			templeft[i]=left;
		}
		if(in[i][right]){
			for(;in[i][right]&&(right<187);right++)
			{
			}
//			if(right==187) in[i][186]=101;
//			else in[i][right]=101;
			tempright[i]=right;
//			CenterLine[i]=(LeftLine[i]+RightLine[i])/2;
		}
		else
		{
			for(;(!in[i][right])&&(right<187);right++)
			{
			}
			if(right==187){
				for(right=MT9V03X_CSI_W;(!in[i][right])&&(right>0);right--)
				{
				}
			}
			else{
				for(;(in[i][right])&&(right<187);right++)
				{
				}
			}
//			if(right==187) in[i][186]=101;
//			else in[i][right]=101;
//			in[i][(left+right)/2]=100;
			tempright[i]=right;
//			CenterLine[i]=(LeftLine[i]+RightLine[i])/2;
		}
		
		k_left=(templeft[110]-templeft[119])/9;
		k_right=(tempright[110]-tempright[119])/9;
	}
	
	for(int i=109;i>1;i--)
	{
		if(in[i][left]){
			for(;in[i][left]&&(left>0);left--)
			{
			}
			templeft[i]=left;
		}
			else {
			for(;(!in[i][left])&&(left<187);left++)
			{
			}
			templeft[i]=left;
		}
			
		if(in[i][right]){
			for(;in[i][right]&&(right<187);right++)
			{
			}
			tempright[i]=right;
		}
		else {
			for(;(!in[i][right])&&(right>0);right--)
			{
			}
			tempright[i]=right;
		}
		
		
	}
	
	
}
