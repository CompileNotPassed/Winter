#include "Addline.h"

void ImageAddingLine(uint8_t imageSide[MT9V03X_CSI_H][2],uint8_t status,uint8_t startX,uint8_t startY,uint8_t endX,uint8_t endY)  //status为1:左补线  2：右补线
{
  int i=0;
  float k=0.0f,b=0.0f;
  switch(status)
  {
    case 1:
    {
      k=(float)((float)endX-(float)startX)/(float)((float)endY-(float)startY);
      b=(float)startX-(float)startY*k;
      for(i=startY;i<endY;i++)
      {
        imageSide[i][0]=(uint8_t)(k*i+b);
      }
      break;
    }
    case 2:
    {
      k = (float)((float)endX-(float)startX)/(float)((float)endY-(float)startY);
      b = (float)startX-(float)startY * k;
      for(i=startY;i<endY;i++)
      {
        imageSide[i][1] =(uint8_t)(k*i+b);
      }
      break;
    }
  }
}
