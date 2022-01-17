#include "headfile.h"

//Frame Process

short GetOSTU (unsigned char tmImage[128][160])
{
    signed short i, j;
    unsigned long Amount = 0;
    unsigned long PixelBack = 0;
    unsigned long PixelshortegralBack = 0;
    unsigned long Pixelshortegral = 0;
    signed long PixelshortegralFore = 0;
    signed long PixelFore = 0;
    float OmegaBack, OmegaFore, MicroBack, MicroFore, SigmaB, Sigma; // 类间方差;
    signed short MinValue, MaxValue;
    signed short Threshold = 0;
    unsigned char HistoGram[256];              //

    for (j = 0; j < 256; j++)
        HistoGram[j] = 0; //初始化灰度直方图

    for (j = 0; j < 128; j++)
    {
        for (i = 0; i < 160; i++)
        {
            HistoGram[tmImage[j][i]]++; //统计灰度级中每个像素在整幅图像中的个数
        }
    }

    for (MinValue = 0; MinValue < 256 && HistoGram[MinValue] == 0; MinValue++);        //获取最小灰度的值
    for (MaxValue = 255; MaxValue > MinValue && HistoGram[MinValue] == 0; MaxValue--); //获取最大灰度的值

    if (MaxValue == MinValue)
        return MaxValue;         // 图像中只有一个颜色
    if (MinValue + 1 == MaxValue)
        return MinValue;        // 图像中只有二个颜色

    for (j = MinValue; j <= MaxValue; j++)
        Amount += HistoGram[j];        //  像素总数

    Pixelshortegral = 0;
    for (j = MinValue; j <= MaxValue; j++)
    {
        Pixelshortegral += HistoGram[j] * j;        //灰度值总数
    }
    SigmaB = -1;
    for (j = MinValue; j < MaxValue; j++)
    {
        PixelBack = PixelBack + HistoGram[j];     //前景像素点数
        PixelFore = Amount - PixelBack;           //背景像素点数
        OmegaBack = (float) PixelBack / Amount;   //前景像素百分比
        OmegaFore = (float) PixelFore / Amount;   //背景像素百分比
        PixelshortegralBack += HistoGram[j] * j;  //前景灰度值
        PixelshortegralFore = Pixelshortegral - PixelshortegralBack;  //背景灰度值
        MicroBack = (float) PixelshortegralBack / PixelBack;   //前景灰度百分比
        MicroFore = (float) PixelshortegralFore / PixelFore;   //背景灰度百分比
        Sigma = OmegaBack * OmegaFore * (MicroBack - MicroFore) * (MicroBack - MicroFore);   //计算类间方差
        if (Sigma > SigmaB)                    //遍历最大的类间方差g //找出最大类间方差以及对应的阈值
        {
            SigmaB = Sigma;
            Threshold = j;
        }
    }
    return Threshold;                        //返回最佳阈值;
}

/*!
 * @brief    基于soble边沿检测算子的一种边沿检测
 *
 * @param    imageIn    输入数组
 *           imageOut   输出数组      保存的二值化后的边沿信息
 *           Threshold  阈值
 *
 * @return
 *
 * @note
 *
 * @example
 *
 * @date     2020/5/15
 */
void lq_sobel (unsigned char imageIn[128][160], unsigned char imageOut[128][160], unsigned char Threshold)
{
    /** 卷积核大小 */
    short KERNEL_SIZE = 3;
    short xStart = KERNEL_SIZE / 2;
    short xEnd = 160 - KERNEL_SIZE / 2;
    short yStart = KERNEL_SIZE / 2;
    short yEnd = 128 - KERNEL_SIZE / 2;
    short i, j, k;
    short temp[4];
    for (i = yStart; i < yEnd; i++)
    {
        for (j = xStart; j < xEnd; j++)
        {
            /* 计算不同方向梯度幅值  */
            temp[0] = -(short) imageIn[i - 1][j - 1] + (short) imageIn[i - 1][j + 1]     //{{-1, 0, 1},
            - (short) imageIn[i][j - 1] + (short) imageIn[i][j + 1]        // {-1, 0, 1},
            - (short) imageIn[i + 1][j - 1] + (short) imageIn[i + 1][j + 1];    // {-1, 0, 1}};

            temp[1] = -(short) imageIn[i - 1][j - 1] + (short) imageIn[i + 1][j - 1]     //{{-1, -1, -1},
            - (short) imageIn[i - 1][j] + (short) imageIn[i + 1][j]       // { 0,  0,  0},
            - (short) imageIn[i - 1][j + 1] + (short) imageIn[i + 1][j + 1];    // { 1,  1,  1}};

            temp[2] = -(short) imageIn[i - 1][j] + (short) imageIn[i][j - 1]       //  0, -1, -1
            - (short) imageIn[i][j + 1] + (short) imageIn[i + 1][j]       //  1,  0, -1
            - (short) imageIn[i - 1][j + 1] + (short) imageIn[i + 1][j - 1];    //  1,  1,  0

            temp[3] = -(short) imageIn[i - 1][j] + (short) imageIn[i][j + 1]       // -1, -1,  0
            - (short) imageIn[i][j - 1] + (short) imageIn[i + 1][j]       // -1,  0,  1
            - (short) imageIn[i - 1][j - 1] + (short) imageIn[i + 1][j + 1];    //  0,  1,  1

            temp[0] = abs(temp[0]);
            temp[1] = abs(temp[1]);
            temp[2] = abs(temp[2]);
            temp[3] = abs(temp[3]);

            /* 找出梯度幅值最大值  */
            for (k = 1; k < 4; k++)
            {
                if (temp[0] < temp[k])
                {
                    temp[0] = temp[k];
                }
            }

            if (temp[0] > Threshold)
            {
                imageOut[i][j] = 255;
            }
            else
            {
                imageOut[i][j] = 0;
            }
        }
    }
}

/*!
 * @brief    基于soble边沿检测算子的一种自动阈值边沿检测
 *
 * @param    imageIn    输入数组
 *           imageOut   输出数组      保存的二值化后的边沿信息
 *
 * @return
 *
 * @note
 *
 * @example
 *
 * @date     2020/5/15
 */
void lq_sobelAutoThreshold (unsigned char imageIn[128][160], unsigned char imageOut[128][160])
{
    /** 卷积核大小 */
    short KERNEL_SIZE = 3;
    short xStart = KERNEL_SIZE / 2;
    short xEnd = 160 - KERNEL_SIZE / 2;
    short yStart = KERNEL_SIZE / 2;
    short yEnd = 128 - KERNEL_SIZE / 2;
    short i, j, k;
    short temp[4];
    for (i = yStart; i < yEnd; i++)
    {
        for (j = xStart; j < xEnd; j++)
        {
            /* 计算不同方向梯度幅值  */
            temp[0] = -(short) imageIn[i - 1][j - 1] + (short) imageIn[i - 1][j + 1]     //{{-1, 0, 1},
            - (short) imageIn[i][j - 1] + (short) imageIn[i][j + 1]       // {-1, 0, 1},
            - (short) imageIn[i + 1][j - 1] + (short) imageIn[i + 1][j + 1];    // {-1, 0, 1}};

            temp[1] = -(short) imageIn[i - 1][j - 1] + (short) imageIn[i + 1][j - 1]     //{{-1, -1, -1},
            - (short) imageIn[i - 1][j] + (short) imageIn[i + 1][j]       // { 0,  0,  0},
            - (short) imageIn[i - 1][j + 1] + (short) imageIn[i + 1][j + 1];    // { 1,  1,  1}};

            temp[2] = -(short) imageIn[i - 1][j] + (short) imageIn[i][j - 1]       //  0, -1, -1
            - (short) imageIn[i][j + 1] + (short) imageIn[i + 1][j]       //  1,  0, -1
            - (short) imageIn[i - 1][j + 1] + (short) imageIn[i + 1][j - 1];    //  1,  1,  0

            temp[3] = -(short) imageIn[i - 1][j] + (short) imageIn[i][j + 1]       // -1, -1,  0
            - (short) imageIn[i][j - 1] + (short) imageIn[i + 1][j]       // -1,  0,  1
            - (short) imageIn[i - 1][j - 1] + (short) imageIn[i + 1][j + 1];    //  0,  1,  1

            temp[0] = abs(temp[0]);
            temp[1] = abs(temp[1]);
            temp[2] = abs(temp[2]);
            temp[3] = abs(temp[3]);

            /* 找出梯度幅值最大值  */
            for (k = 1; k < 4; k++)
            {
                if (temp[0] < temp[k])
                {
                    temp[0] = temp[k];
                }
            }

            /* 使用像素点邻域内像素点之和的一定比例    作为阈值  */
            temp[3] = (short) imageIn[i - 1][j - 1] + (short) imageIn[i - 1][j] + (short) imageIn[i - 1][j + 1]
                    + (short) imageIn[i][j - 1] + (short) imageIn[i][j] + (short) imageIn[i][j + 1]
                    + (short) imageIn[i + 1][j - 1] + (short) imageIn[i + 1][j] + (short) imageIn[i + 1][j + 1];

            if (temp[0] > temp[3] / 12.0f)
            {
                imageOut[i][j] = 0;
            }
            else
            {
                imageOut[i][j] = 1;
            }

        }
    }
}
/*************************************************************************
 *  参数说明：mode  ：
 *    0：使用大津法阈值
 *    1：使用平均阈值
 *    2: sobel 算子改进型  手动阈值，同时输出改为提取边沿的图像
 *    3：sobel 算子改进型   动态阈值，同时输出改为提取边沿的图像
 *************************************************************************/
void Get_Bin_Image (unsigned char mode,unsigned char Image_Use[][160],unsigned char Bin_Image[][160])
{
    unsigned short i = 0, j = 0;
    unsigned short Threshold = 0;
    unsigned long tv = 0;
    //char txt[16];

    if (mode == 0)
    {
        Threshold = GetOSTU(Image_Use);  //大津法阈值
    }
    if (mode == 1)
    {
        //累加
        for (i = 0; i < 128; i++)
        {
            for (j = 0; j < 160; j++)
            {
                tv += Image_Use[i][j];   //累加
            }
        }
        Threshold =(unsigned short)(tv / 128 / 160);   //求平均值,光线越暗越小，全黑约35，对着屏幕约160，一般情况下大约100
        Threshold = Threshold + 20;      //此处阈值设置，根据环境的光线来设定
    }
    else if (mode == 2)
    {
        Threshold = 170;                          //手动调节阈值
        lq_sobel(Image_Use, Bin_Image, (unsigned char) Threshold);

        return;

    }
    else if (mode == 3)
    {
        lq_sobelAutoThreshold(Image_Use, Bin_Image);  //动态调节阈值
        return;
    }
    /* 二值化 */
    for (i = 0; i < 128; i++)
    {
        for (j = 0; j < 160; j++)
        {
            if (Image_Use[i][j] > Threshold) //数值越大，显示的内容越多，较浅的图像也能显示出来
                Bin_Image[i][j] = 255;
            else
                Bin_Image[i][j] = 0;
        }
    }
}
void picGamma(uint8 in_array[][160], uint8 out_array[][160], long height, long width)
{
    for (int i = 0; i < height; i++){
        for (int j = 0; j <width; j++)
             out_array[i][j] = (uint8)pow(in_array[i][j], 1.02);
    }
}

#define Gourd 256
uint8 OTSU(uint8 *pic,uint16 num)
{
   uint16 i=0;
   uint16 Histogram[Gourd];
   for (i=0;i<Gourd;i++)
       Histogram[i]=0;

   for (i=0;i<num;i++)
   {
       Histogram[(int)pic[i]*Gourd/256]++;
   }

  float pt[Gourd],w[Gourd],u[Gourd],o[Gourd],Ut;

  pt[0]=(float)Histogram[0]/num;
  w[0]=pt[0];
  u[0]=w[0];

  for(i=1;i<Gourd;i++)
  {
    pt[i]=(float)Histogram[i]/num; 
    w[i]=w[i-1]+pt[i];
    u[i]=u[i-1]+i*pt[i];
  };
  Ut=u[Gourd-1];

  for(i=0;i<Gourd;i++)
  {
    o[i]=(1-pt[i])*(u[i]*u[i]/w[i]+(u[i]-Ut)*(u[i]-Ut)/(1-w[i]));
  };

  int maxi=0;
  float maxo=0;

  for(i=0;i<Gourd;i++)
  {
    if(o[i]!=0x7FC0000)
    if(o[i]>maxo){maxo=o[i];maxi=i;}

  }
  return maxi*256/Gourd;
}