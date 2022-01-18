#include "Border.h"

//uint16 i,left,right;
//uint16 LeftLine[MT9V03X_CSI_H],RightLine[MT9V03X_CSI_H],CenterLine[MT9V03X_CSI_H];
//uint16 Crosstime,Crosstimecopy,lastcross,CrossStart;

//void borderDetect(uint8 (*in)[MT9V03X_CSI_W],uint8 (*out)[MT9V03X_CSI_W])
//{
//	uint16 minus=(MT9V03X_CSI_W-188)/2;
//	for(i=MT9V03X_CSI_H-1;i>110;i--)
//	{
//		left=MT9V03X_CSI_W/2;
//		right=MT9V03X_CSI_W/2;
//		if(in[i][left])
//		{
//			for(;in[i][left]&&(left>0);left--)
//			{
//			}
//			LeftLine[i]=left;
//			in[i][left]=103;
//		}
//		else
//		{
//			for(;(!in[i][left])&&(left>0);left--)
//			{
//			}
//			if(left==0)
//			{
//				for(left=MT9V03X_CSI_W/2;(!in[i][left])&&(left<187);left++)
//				{
//				}
//			}
//			else
//			{
//				for(;(in[i][left])&&(left>0);left--)
//				{
//				}
//			}
//			in[i][left]=103;
//			LeftLine[i]=left;
//		}
//		if(in[i][right])
//		{
//			for(;in[i][right]&&(right<187);right++)
//			{
//			}
//			if(right==187) in[i][186]=101;
//			else in[i][right]=101;
//			RightLine[i]=right;
//			CenterLine[i]=(LeftLine[i]+RightLine[i])/2;
//		}
//		else
//		{
//			for(;(!in[i][right])&&(right<187);right++)
//			{
//			}
//			if(right==187)
//			{
//				for(right=MT9V03X_CSI_W;(!in[i][right])&&(right>0);right--)
//				{
//				}
//			}
//			else
//			{
//				for(;(in[i][right])&&(right<187);right++)
//				{
//				}
//			}
//			if(right==187) in[i][186]=101;
//			else in[i][right]=101;
//			in[i][(left+right)/2]=100;
//			RightLine[i]=right;
//			CenterLine[i]=(LeftLine[i]+RightLine[i])/2;
//		}
//	}
//	
//	
//	for(;i>1;i--)
//	{
//		if(in[i][left])
//		{
//			for(;in[i][left]&&(left>0);left--)
//			{
//			}
//			in[i][left]=103;
//			LeftLine[i]=left;
//		}
//		else
//		{
//			for(;(!in[i][left])&&(left<187);left++)
//			{
//			}
//			in[i][left]=103;
//			LeftLine[i]=left;
//		}
//		if(in[i][right])
//		{
//			for(;in[i][right]&&(right<187);right++)
//			{
//			}
//			RightLine[i]=right;
//			CenterLine[i]=(LeftLine[i]+RightLine[i])/2;
//			if(right==187) in[i][186]=101;
//			else in[i][right] = 101;
//		}
//		else
//		{
//			for(;(!in[i][right])&&(right>0);right--)
//			{
//			}
//			RightLine[i]=right;
//			CenterLine[i]=(LeftLine[i]+RightLine[i])/2;
//			in[i][right] = 101;
//		}
//		
//		
//		if(left>=right)
//		{
//			in[i][left]=0;
//			in[i][right]=0;
//			in[i][(left+right)/2]=255;
//		}
//		in[i][(left+right)/2]=100;
//	}
//	JudgeCross(LeftLine,RightLine,CenterLine,40);
//}


uint8_t ImageGetSide(uint8_t imageInput[MT9V03X_CSI_H][MT9V03X_CSI_W],uint8_t imageOut[MT9V03X_CSI_H][2])
{
  uint8_t i=0,j=0;

  RoadIsNoSide(imageInput, imageOut, ROAD_START_ROW);

  /* 离车头近的40行 寻找边线 */
  for(i=ROAD_START_ROW-1;i>ROAD_END_ROW;i--)
  {
    imageOut[i][0]=0;
    imageOut[i][1]=187;

    /* 根据边界连续特性 寻找边界 */
    for (j=imageOut[i+1][0]+10;j>0;j--)
    {
      if(!imageInput[i][j]){
				imageOut[i][0]=j;
        break;
      }
    }
    for(j=imageOut[i+1][1]-10;j<187;j++)
    {
      if(!imageInput[i][j]){
        imageOut[i][1]=j;
        break;
      }
    }
    /* 如果左边界 即将超出中线 则检查是否右丢线 */
    if (imageOut[i][0]>(MT9V03X_CSI_W/2-10)&&imageOut[i][1]>(MT9V03X_CSI_W-5)){
        /* 右丢线处理 */
      RoadNoSideProcess(imageInput,imageOut,2,i);

      if (i > 70){
        imageOut[i][0]+=50;
      }
      return 1;
    }

    /* 如果右边界 即将超出中线 则检查是否左丢线 */
    if (imageOut[i][1]<(MT9V03X_CSI_W/2+10)&&imageOut[i][0]<5){
        /* 左丢线处理 */
      RoadNoSideProcess(imageInput,imageOut,1,i);
      if(i>70){
        imageOut[i][1]-=50;
      }
      return 2;
    }
  }
  return 0;
}

uint8_t UpdownSideGet(uint8_t imageInput[MT9V03X_CSI_H][MT9V03X_CSI_W], uint8_t imageOut[2][MT9V03X_CSI_W])
{
  uint8_t i=0,j=0;
  uint8_t last=60;

  imageOut[0][187]=0;
  imageOut[1][187]=119;
    /* 用中线比较近的行 判断是否丢线 */
  for(i=last;i>0;i--)
  {
    if(!imageInput[i][94]){
      imageOut[0][94]=i;
      break;
    }
		else if(i==0){
			imageOut[0][94]=0;
		}
  }

  for(i=last;i<120;i++)
  {
    if(!imageInput[i][94]){
      imageOut[1][94]=i;
      break;
    }
  }

    /* 中线往左 寻找边线 */
  for(i=94-1;i>0;i--)
  {
    imageOut[0][i]=0;
    imageOut[1][i]=119;

        /* 根据边界连续特性 寻找边界 */
//    for(j=imageOut[0][i+1]+10;j>0;j--)
//    {
//      if (!imageInput[j][i]){
//        imageOut[0][i] = j;
//        break;
//       }
//    }
		int templ=imageOut[0][i+1];
		int tempi=i;
		if(imageInput[tempi][templ]){
			for(;imageInput[tempi][templ];tempi--)
			{
			}
			imageOut[0][i]=tempi;
		}
		if(!imageInput[tempi][templ]){
			for(;!imageInput[tempi][templ];tempi++)
			{
			}
			imageOut[0][i]=tempi;
		}
		
		int tempr=imageOut[1][i+1];
		int tempii=i;
		if(imageInput[tempii][tempr]){
			for(;!imageInput[tempii][tempr];tempii--)
			{
			}
			imageOut[1][i]=tempii;
		}
		if(!imageInput[tempii][tempr]){
			for(;imageInput[tempii][tempr];tempii++)
			{
			}
			imageOut[1][i]=tempii;
		}
		
//		for(j=imageOut[1][i+1]-10;j<119;j++)
//		{
//			if (!imageInput[j][i]){
//				imageOut[1][i] = j;
//				break;
//			}
//    }
  }
    /*中线往右 寻找边线*/
  for (i=94+1;i<187;i++)
  {
    imageOut[0][i]=0;
    imageOut[1][i]=119;

        /* 根据边界连续特性 寻找边界 */
    for(j=imageOut[0][i-1]+10;j>0;j--)
    {
      if (!imageInput[j][i]){
        imageOut[0][i]=j;
        break;
      }
    }
    for(j=imageOut[1][i-1]-10;j<119;j++)
    {
      if (!imageInput[j][i]){
        imageOut[1][i] = j;
        break;
      }
    }
  }
  return 0;
}


