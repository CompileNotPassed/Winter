#include "headfile.h"

//运算行
#define ROAD_MAIN_ROW 40
//检测开始
#define ROAD_START_ROW 115
//检测结束
#define ROAD_END_ROW 10

uint8_t sideLine[128][2];
uint8_t updownLine[2][160];

void edgeDetect(unsigned char image[128][160])
{
    int16 nr; //行
    int16 nc; //列

    for (nr = 1; nr < 128 - 1; nr++)
    {
        for (nc = 1; nc < 160 - 1; nc++)
        {
            if ((image[nr][nc] == 0) && (image[nr - 1][nc] == 0) && (image[nr + 1][nc] == 0) && (image[nr][nc + 1] == 0) && (image[nr][nc - 1] == 0))
            {
                image[nr][nc] = 1;
                nr++;
                nc++;
            }
        }
    }
}

void RoadNoSideProcess(uint8_t imageInput[128][160], uint8_t imageOut[128][2], uint8_t mode, uint8_t lineIndex)
{
    uint8_t i = 0, j = 0, count = 0;

    switch (mode)
    {
    case 1:
        for (i = imageOut[lineIndex][1]; i > 1; i--)
        {
            count++;
            for (j = lineIndex; j > ROAD_END_ROW && lineIndex > count; j--)
            {
                if (imageInput[j][i])
                {
                    imageOut[lineIndex - count][0] = 0;
                    imageOut[lineIndex - count][1] = i;
                    break;
                }
            }
        }
        break;

    case 2:
        for (i = imageOut[lineIndex][0]; i < 159; i++)
        {
            count++;
            for (j = lineIndex; j > ROAD_END_ROW && lineIndex > count; j--)
            {
                if (imageInput[j][i])
                {
                    imageOut[lineIndex - count][0] = i;
                    imageOut[lineIndex - count][1] = 159;
                    break;
                }
            }
        }
        break;
    }
}

uint8_t RoadIsNoSide(uint8_t imageInput[128][160], uint8_t imageOut[128][2], uint8_t lineIndex)
{
    uint8_t state = 0;
    uint8_t i = 0;
    static uint8_t last = 78;

    imageOut[lineIndex][0] = 0;
    imageOut[lineIndex][1] = 159;
    /* 用距离小车比较近的行 判断是否丢线 */
    for (i = last; i > 1; i--)
    {
        if (imageInput[lineIndex][i])
        {
            imageOut[lineIndex][0] = i;
            break;
        }
    }

    if (i == 1)
    {
        /* 左边界丢线 */
        state = 1;
    }

    for (i = last; i < 159; i++)
    {
        if (imageInput[lineIndex][i])
        {
            imageOut[lineIndex][1] = i;
            break;
        }
    }

    if (i == 159)
    {
        /* 左右边界丢线 */
        if (state == 1)
        {
            state = 3;
        }

        /* 右边界丢线 */
        else
        {
            state = 2;
        }
    }
    if (imageOut[lineIndex][1] <= imageOut[lineIndex][0])
    {
        state = 4;
    }
    return state;
}
//Border Detect
uint8_t ImageGetSide(uint8_t imageInput[128][160], uint8_t imageOut[128][2])
{
    uint8_t i = 0, j = 0;

    RoadIsNoSide(imageInput, imageOut, ROAD_START_ROW);

    /* 离车头近的40行 寻找边线 */
    for (i = ROAD_START_ROW - 1; i > ROAD_END_ROW; i--)
    {
        imageOut[i][0] = 0;
        imageOut[i][1] = 159;

        /* 根据边界连续特性 寻找边界 */
        for (j = imageOut[i + 1][0] + 10; j > 0; j--)
        {
            if (!imageInput[i][j])
            {
                imageOut[i][0] = j;
                break;
            }
        }
        for (j = imageOut[i + 1][1] - 10; j < 160; j++)
        {
            if (!imageInput[i][j])
            {
                imageOut[i][1] = j;
                break;
            }
        }
        /* 如果左边界 即将超出中线 则检查是否右丢线 */
        if (imageOut[i][0] > (160 / 2 - 10) && imageOut[i][1] > (160 - 5))
        {
            /* 右丢线处理 */
            RoadNoSideProcess(imageInput, imageOut, 2, i);

            if (i > 70)
            {
                imageOut[i][0] += 50;
            }
            return 1;
        }

        /* 如果右边界 即将超出中线 则检查是否左丢线 */
        if (imageOut[i][1] < (160 / 2 + 10) && imageOut[i][0] < (5))
        {
            /* 左丢线处理 */
            RoadNoSideProcess(imageInput, imageOut, 1, i);

            if (i > 70)
            {
                imageOut[i][1] -= 50;
            }
            return 2;
        }
    }
    return 0;
}

uint8_t UpdownSideGet(uint8_t imageInput[128][160], uint8_t imageOut[2][160])
{
    uint8_t i = 0, j = 0;
    uint8_t last = 60;

    imageOut[0][159] = 0;
    imageOut[1][159] = 119;
    /* 用中线比较近的行 判断是否丢线 */
    for (i = last; i >= 0; i--)
    {
        if (!imageInput[i][80])
        {
            imageOut[0][80] = i;
            break;
        }
    }

    for (i = last; i < 128; i++)
    {
        if (!imageInput[i][80])
        {
            imageOut[1][80] = i;
            break;
        }
    }

    /* 中线往左 寻找边线 */
    for (i = 80 - 1; i > 0; i--)
    {
        imageOut[0][i] = 0;
        imageOut[1][i] = 119;

        /* 根据边界连续特性 寻找边界 */
        for (j = imageOut[0][i + 1] + 10; j > 0; j--)
        {
            if (!imageInput[j][i])
            {
                imageOut[0][i] = j;
                break;
            }
        }
        for (j = imageOut[1][i + 1] - 10; j < 128; j++)
        {
            if (!imageInput[j][i])
            {
                imageOut[1][i] = j;
                break;
            }
        }
    }
    /*中线往右 寻找边线*/
    for (i = 80 + 1; i < 159; i++)
    {
        imageOut[0][i] = 0;
        imageOut[1][i] = 119;

        /* 根据边界连续特性 寻找边界 */
        for (j = imageOut[0][i - 1] + 10; j > 0; j--)
        {
            if (!imageInput[j][i])
            {
                imageOut[0][i] = j;
                break;
            }
        }
        for (j = imageOut[1][i - 1] - 10; j < 128; j++)
        {
            if (!imageInput[j][i])
            {
                imageOut[1][i] = j;
                break;
            }
        }
    }
    return 0;
}

uint8_t verticalSideGet(uint8_t imageInput[128][160], uint8_t imageOut[2][160])
{
    uint8 i, j;
    for (i = 80 - 1; i > 0; i--)
    {
        for (j = ROAD_MAIN_ROW; j > 0; j--)
        {
            if (imageInput[j][i] != imageInput[j + 1][i])
            {
                imageOut[0][i] = j;
                break;
            }
        }
        for (j = ROAD_MAIN_ROW + 1; j < 128; j++)
        {
            if (imageInput[j][i] != imageInput[j + 1][i])
            {
                imageOut[1][i] = j;
                break;
            }
        }
    }
    for (i = 80; i < 160; i++)
    {
        for (j = ROAD_MAIN_ROW; j > 0; j--)
        {
            if (imageInput[j][i] != imageInput[j + 1][i])
            {
                imageOut[1][i] = j;
                break;
            }
        }
        for (j = ROAD_MAIN_ROW + 1; j < 128; j++)
        {
            if (imageInput[j][i] != imageInput[j + 1][i])
            {
                imageOut[1][i] = j;
                break;
            }
        }
    }

    return 0;
}

/*void borderDetect(uint8 in[][160],uint8 out[][160]){
		uint8 i,left,right,color=in[128][80];
		for(i=128;i>128;i--){
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
/*
uint16 LeftLine[128], RightLine[128], CenterLine[128];
void borderDetect(uint8 (*in)[160], uint8 (*out)[160])
{
	uint16 i, left, right, minus = (160 - 160) / 2;
	for (i = 128 - 1; i > 110; i--)
	{
		left = 160 / 2;
		right = 160 / 2;
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
				for (left = 160 / 2; (!in[i][left]) && (left < 187); left++)
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
				for (right = 160; (!in[i][right]) && (right > 0); right--)
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
}*/