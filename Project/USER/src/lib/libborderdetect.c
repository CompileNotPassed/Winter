#include "headfile.h"
//Border Detect
/*void borderDetect(uint8 in[][160],uint8 out[][160]){
		uint8 i,left,right,color=in[120][80];
		for(i=128;i>120;i--){
			for(left=80;(in[i][left]==in[i][left-1])&&(left>1);left--){
			}
			for(right=80;(in[i][right]==in[i][right+1])&&(right<158);right++){
			}
			out[i][left]=103;
			out[i][left+1]=103;
			out[i][left/2+right/2]=100;
			out[i][right]=106;
			out[i][right-1]=106;
		}
		for(;i>1;i--){
			if(in[i-1][left]!=color){
				for(;in[i][left]==in[i][left+1];left++){
				}
			}
			else{
				for(;(in[i][left]==in[i][left-1])&&(left>1);left--){
				}
			}
			if(in[i-1][right]!=color){
				for(;in[i][right]==in[i][right-1];right--){
				}
			}
			else{
				for(;(in[i][right]==in[i][left+1])&&(right<158);right++){
				}
			}
			out[i][left]=103;
			out[i][left+1]=103;
			out[i][left/2+right/2]=100;
			out[i][right]=106;
			out[i][right-1]=106;
		}
}*/

uint16 LeftLine[MT9V03X_CSI_H], RightLine[MT9V03X_CSI_H], CenterLine[MT9V03X_CSI_H];
void borderDetect(uint8 (*in)[MT9V03X_CSI_W], uint8 (*out)[MT9V03X_CSI_W])
{
	uint16 i, left, right, minus = (MT9V03X_CSI_W - 160) / 2;
	for (i = MT9V03X_CSI_H - 1; i > 110; i--)
	{
		left = MT9V03X_CSI_W / 2;
		right = MT9V03X_CSI_W / 2;
		if (in[i][left])
		{
			for (; in[i][left] && (left > 0); left--)
			{
			}
			LeftLine[i] = left;
			in[i][left] = 103;
		}
		else
		{
			for (; (!in[i][left]) && (left > 0); left--)
			{
			}
			if (left == 0)
			{
				for (left = MT9V03X_CSI_W / 2; (!in[i][left]) && (left < 187); left++)
				{
				}
			}
			else
			{
				for (; (in[i][left]) && (left > 0); left--)
				{
				}
			}
			in[i][left] = 103;
			LeftLine[i] = left;
		}
		if (in[i][right])
		{
			for (; in[i][right] && (right < 187); right++)
			{
			}
			if (right == 187)
				in[i][186] = 101;
			else
				in[i][right] = 101;
			RightLine[i] = right;
			CenterLine[i] = (LeftLine[i] + RightLine[i]) / 2;
		}
		else
		{
			for (; (!in[i][right]) && (right < 187); right++)
			{
			}
			if (right == 187)
			{
				for (right = MT9V03X_CSI_W; (!in[i][right]) && (right > 0); right--)
				{
				}
			}
			else
			{
				for (; (in[i][right]) && (right < 187); right++)
				{
				}
			}
			if (right == 187)
				in[i][186] = 101;
			else
				in[i][right] = 101;
			in[i][(left + right) / 2] = 100;
			RightLine[i] = right;
			CenterLine[i] = (LeftLine[i] + RightLine[i]) / 2;
		}
	}

	for (; i > 1; i--)
	{
		if (in[i][left])
		{
			for (; in[i][left] && (left > 0); left--)
			{
			}
			in[i][left] = 103;
			LeftLine[i] = left;
		}
		else
		{
			for (; (!in[i][left]) && (left < 187); left++)
			{
			}
			in[i][left] = 103;
			LeftLine[i] = left;
		}
		if (in[i][right])
		{
			for (; in[i][right] && (right < 187); right++)
			{
			}
			RightLine[i] = right;
			CenterLine[i] = (LeftLine[i] + RightLine[i]) / 2;
			if (right == 187)
				in[i][186] = 101;
			else
				in[i][right] = 101;
		}
		else
		{
			for (; (!in[i][right]) && (right > 0); right--)
			{
			}
			RightLine[i] = right;
			CenterLine[i] = (LeftLine[i] + RightLine[i]) / 2;
			in[i][right] = 101;
		}

		if (left >= right)
		{
			in[i][left] = 0;
			in[i][right] = 0;
			in[i][(left + right) / 2] = 255;
		}
		in[i][(left + right) / 2] = 100;
	}
	JudgeCross(LeftLine, RightLine, CenterLine, 40);
}