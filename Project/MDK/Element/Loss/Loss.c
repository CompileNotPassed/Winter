#include "Loss.h"

//void JudgeLoss(uint16 LeftLine[MT9V03X_CSI_H],uint16 RightLine[MT9V03X_CSI_H],uint16 CenterLine[MT9V03X_CSI_H])
//{
//	uint16 LeftLoss,RightLoss;
//	uint16 LeftLossStart,RightLossStart;
//	for(int i=118;i>0;i--)
//	{
//		if(LeftLine[i]==0&&(RightLine[i]-RightLine[i+1]<3)&&(RightLine[i]!=187))
//		{
//			if(!LeftLossStart) LeftLossStart=i;
//			LeftLoss++;
//		}
//		if(RightLine[i]==187&&(LeftLine[i+1]-LeftLine[i]<3)&&(LeftLine[i]!=0))
//		{
//			if(!RightLossStart) RightLossStart=i;
//			RightLoss++;
//		}
//	}
//}

uint8_t RoadIsNoSide(uint8_t imageInput[MT9V03X_CSI_H][MT9V03X_CSI_W],uint8_t imageOut[MT9V03X_CSI_H][2],uint8_t lineIndex)
{
  uint8_t state=0;
  uint8_t i=0;
  static uint8_t last=92;

  imageOut[lineIndex][0]=0;
  imageOut[lineIndex][1]=187;
  /* 用距离小车比较近的行 判断是否丢线 */
  for(i=last;i>0;i--)
  {
    if(imageInput[lineIndex][i]){
      imageOut[lineIndex][0]=i;
      break;
    }
  }
		
  if(!i){
    /* 左边界丢线 */
    state=1;
  }

  for(i=last;i<187;i++)
  {
    if(imageInput[lineIndex][i]){
      imageOut[lineIndex][1]=i;
      break;
    }
  }

  if(i==187){
    /* 左右边界丢线 */
    if(state==1){
      state=3;
    }

    /* 右边界丢线 */
    else{
      state = 2;
    }
  }
  if(imageOut[lineIndex][1]<=imageOut[lineIndex][0]){
		state=4;
  }
  return state;
}

void RoadNoSideProcess(uint8_t imageInput[MT9V03X_CSI_H][MT9V03X_CSI_W],uint8_t imageOut[MT9V03X_CSI_H][2],uint8_t mode,uint8_t lineIndex)
{
  uint8_t i=0,j=0,count=0;
  switch(mode)
  {
    case 1:
    for(i=imageOut[lineIndex][1];i>0;i--)
    {
      count++;
			for(j=lineIndex;j>ROAD_END_ROW&&lineIndex>count;j--)
      {
				if(imageInput[j][i]){
					imageOut[lineIndex-count][0] = 0;
          imageOut[lineIndex-count][1] = i;
          break;
        }
      }
    }
    break;
		
		case 2:
    for(i=imageOut[lineIndex][0];i<187;i++)
    {
      count++;
      for(j=lineIndex;j>ROAD_END_ROW&&lineIndex>count;j--)
      {
				if(imageInput[j][i]){
					imageOut[lineIndex-count][0]=i;
          imageOut[lineIndex-count][1]=187;
          break;
        }
			}
    }
    break;
  }
}
