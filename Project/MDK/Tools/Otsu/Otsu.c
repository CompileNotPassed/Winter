#include "Otsu.h"
#include "Motor.h"

//------------------摄像头参数--------------//


//大津法二值化//
#define GrayScale 256

uint8 (*a)[MT9V03X_CSI_W];
uint16 i,left,right;
uint16 LeftLine[MT9V03X_CSI_H],RightLine[MT9V03X_CSI_H],CenterLine[MT9V03X_CSI_H];
uint16 Crosstime,Crosstimecopy,lastcross,CrossStart;

  
uint8 otsuThreshold(uint8 *image, uint16 width, uint16 height)
{
    #define GrayScale 256
    int pixelCount[GrayScale] = {0};//每个灰度值所占像素个数
    float pixelPro[GrayScale] = {0};//每个灰度值所占总像素比例
    int i,j;   
    int Sumpix = width * height;   //总像素点
    uint8 threshold = 0;
    uint8* data = image;  //指向像素数据的指针

    //统计灰度级中每个像素在整幅图像中的个数  
    for (i=0;i<height;i++)
    {
        for (j=0;j<width;j++)
        {
            pixelCount[(int)data[i*width+j]]++;  //将像素值作为计数数组的下标
        }
    }
    float u = 0;  
    for (i = 0; i < GrayScale; i++)
    {
      pixelPro[i] = (float)pixelCount[i] / Sumpix;   //计算每个像素在整幅图像中的比例  
      u += i*pixelPro[i];  //总平均灰度
    }     
    float maxVariance=0;
    float w0=0;
		float avgValue=0;//w0 前景比例 ，avgValue 前景平均灰度
    for(int i = 0; i < 256; i++)     //每一次循环都是一次完整类间方差计算 (两个for叠加为1个)
    {  
      w0 += pixelPro[i];  //假设当前灰度i为阈值, 0~i 灰度像素所占整幅图像的比例即前景比例
      avgValue  += i * pixelPro[i];        
      float variance = pow((avgValue/w0-u),2)*w0/(1-w0);    //类间方差   
      if(variance>maxVariance) 
      {  
				maxVariance=variance;  
        threshold=i;  
      }
    }
    return threshold;  
}

void JudgeMid(uint8 (*a)[MT9V03X_CSI_W],uint8 (*image)[MT9V03X_CSI_W], uint16 width, uint16 height)
{
	static int flag=0;
	static uint8 Threshold;
	if(flag++==0)
	{
		Threshold=otsuThreshold(mt9v03x_csi_image[0], MT9V03X_CSI_H, MT9V03X_CSI_W);
	}
	for(int i=0;i<MT9V03X_CSI_H;i++)
	{
		for(int j=0;j<MT9V03X_CSI_W;j++)
		{
			a[i][j]=image[i][j];	
			if(a[i][j]<Threshold)
			{
				a[i][j]=0;
			}
			else
			{
				a[i][j]=255;
			}
		}
	}
	borderDetect(a,mt9v03x_csi_image);
	lcdOutput(a[0], MT9V03X_CSI_W, MT9V03X_CSI_H, 160, 128);
	Follow(CenterLine);
}




void borderDetect(uint8 (*in)[MT9V03X_CSI_W],uint8 (*out)[MT9V03X_CSI_W])
{
	uint16 minus=(MT9V03X_CSI_W-160)/2;
	for(i=MT9V03X_CSI_H-1;i>110;i--)
	{
		left=MT9V03X_CSI_W/2;
		right=MT9V03X_CSI_W/2;
		if(in[i][left])
		{
			for(;in[i][left]&&(left>0);left--)
			{
			}
			LeftLine[i]=left;
			in[i][left]=103;
		}
		else
		{
			for(;(!in[i][left])&&(left>0);left--)
			{
			}
			if(left==0)
			{
				for(left=MT9V03X_CSI_W/2;(!in[i][left])&&(left<187);left++)
				{
				}
			}
			else
			{
				for(;(in[i][left])&&(left>0);left--)
				{
				}
			}
			in[i][left]=103;
			LeftLine[i]=left;
		}
		if(in[i][right])
		{
			for(;in[i][right]&&(right<187);right++)
			{
			}
			if(right==187) in[i][186]=101;
			else in[i][right]=101;
			RightLine[i]=right;
			CenterLine[i]=(LeftLine[i]+RightLine[i])/2;
		}
		else
		{
			for(;(!in[i][right])&&(right<187);right++)
			{
			}
			if(right==187)
			{
				for(right=MT9V03X_CSI_W;(!in[i][right])&&(right>0);right--)
				{
				}
			}
			else
			{
				for(;(in[i][right])&&(right<187);right++)
				{
				}
			}
			if(right==187) in[i][186]=101;
			else in[i][right]=101;
			in[i][(left+right)/2]=100;
			RightLine[i]=right;
			CenterLine[i]=(LeftLine[i]+RightLine[i])/2;
		}
	}
	
	
	for(;i>1;i--)
	{
		if(in[i][left])
		{
			for(;in[i][left]&&(left>0);left--)
			{
			}
			in[i][left]=103;
			LeftLine[i]=left;
		}
		else
		{
			for(;(!in[i][left])&&(left<187);left++)
			{
			}
			in[i][left]=103;
			LeftLine[i]=left;
		}
		if(in[i][right])
		{
			for(;in[i][right]&&(right<187);right++)
			{
			}
			RightLine[i]=right;
			CenterLine[i]=(LeftLine[i]+RightLine[i])/2;
			if(right==187) in[i][186]=101;
			else in[i][right] = 101;
		}
		else
		{
			for(;(!in[i][right])&&(right>0);right--)
			{
			}
			RightLine[i]=right;
			CenterLine[i]=(LeftLine[i]+RightLine[i])/2;
			in[i][right] = 101;
		}
		
		
		if(left>=right)
		{
			in[i][left]=0;
			in[i][right]=0;
			in[i][(left+right)/2]=255;
		}
		in[i][(left+right)/2]=100;
	}
	JudgeCross(LeftLine,RightLine,CenterLine,40);
}

 
float Slope_Calculate(uint8 begin,uint8 end,uint16 *p)
{
  float xsum=0,ysum=0,xysum=0,x2sum=0;
  uint8 i=0;
  float result=0;
  static float resultlast;
  p=p+begin;
  for(i=begin;i<end;i++)
  {
      xsum+=i;
      ysum+=*p;
      xysum+=i*(*p);
      x2sum+=i*i;
      p=p+1;
  }
	if((end-begin)*x2sum-xsum*xsum) //判断除数是否为零
	{
		result=((end-begin)*xysum-xsum*ysum)/((end-begin)*x2sum-xsum*xsum);
		resultlast=result;
	}
	else
	{
		result=resultlast;
	}
	return result;
}

void AddLine(uint8 (*a)[MT9V03X_CSI_W], uint16 width, uint16 height)
{
	
}

void JudgeLoss(uint16 LeftLine[MT9V03X_CSI_H],uint16 RightLine[MT9V03X_CSI_H],uint16 CenterLine[MT9V03X_CSI_H])
{
	uint16 LeftLoss,RightLoss;
	uint16 LeftLossStart,RightLossStart;
	for(int i=118;i>0;i--)
	{
		if(LeftLine[i]==0&&(RightLine[i]-RightLine[i+1]<3)&&(RightLine[i]!=187))
		{
			if(!LeftLossStart) LeftLossStart=i;
			LeftLoss++;
		}
		if(RightLine[i]==187&&(LeftLine[i+1]-LeftLine[i]<3)&&(LeftLine[i]!=0))
		{
			if(!RightLossStart) RightLossStart=i;
			RightLoss++;
		}
	}
}




void JudgeCorner(uint16 LeftLine[MT9V03X_CSI_H],uint16 RightLine[MT9V03X_CSI_H],uint16 CenterLine[MT9V03X_CSI_H])
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




