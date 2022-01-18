#include "Zebra.h"

uint8_t JudgeZebra(uint8_t *image[MT9V03X_CSI_W])
{
    int i=0,j=0;
    int count=0;
    for(i=ROAD_MAIN_ROW-30;i>ROAD_MAIN_ROW+30;i++)
    {
			for(j = 1; j < MT9V03X_CSI_W; j++)
      {
				if(image[i][j]&&image[i][j-1]==0){
					count ++;
        }
      }
      if(count > 5){
				Beep_on();
        return 1;
        }
    }
    return 0;
}
