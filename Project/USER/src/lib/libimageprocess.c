#include "headfile.h"

//Frame Process
void picGamma(uint8 in_array[][168], uint8 out_array[][168], long height, long width)
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