#include "headfile.h"

void horizontalDetect(uint8 img[128][160], int16 horLine[2][128], uint8 mode)
{
#define LOST_FLAG 0xff;
    switch (mode)
    {
    case 1:
    {
        uint8 i, left, right, color = img[120][80];
        for (i = 127; i > 120; i--)
        {
            for (left = 80; (img[i][left] == img[i][left - 1]) && (left > 1); left--)
            {
            }
            for (right = 80; (img[i][right] == img[i][right + 1]) && (right < 158); right++)
            {
            }
            horLine[0][i] = left;
            horLine[1][i] = right;
        }
        for (; i > 2; i--)
        {
            if (img[i - 1][left] == img[i][left])
            {
                while ((img[i - 1][left] == img[i - 1][left + 1]) && (left > 0))
                {
                    left--;
                }
            }
            else
            {
                while ((img[i - 1][left - 1] == img[i - 1][left]) && (left < 128))
                {
                    left++;
                }
                if (left == 0 || left == 128)
                {
                    horLine[0][i] = 0xff;
                }
                else
                {
                    horLine[0][i] = left;
                }
            }
            if (img[i - 1][right] == img[i][right])
            {
                while ((img[i - 1][right] == img[i - 1][right + 1]) && (right > 0))
                {
                    right--;
                }
            }
            else
            {
                while ((img[i - 1][right - 1] == img[i - 1][right]) && (right < 128))
                {
                    right++;
                }
                if (right == 0 || right == 128)
                {
                    horLine[1][i] = 0xff;
                }
                else
                {
                    horLine[1][i] = right;
                }
            }
        }
        break;
    }
    }
#undef LOST_FLAG
}

void verticalDetect(uint8 img[128][160], int16 verLine[2][160], uint8 mode)
{
    switch (mode)
    {
    case 1:
    {

        break;
    }
    }
}

// void borderDetect(uint8 in[][160], uint8 out[][160])
// {
//     uint8 i, left, right, color = in[128][80];
//     for (i = 128; i > 128; i--)
//     {
//         for (left = 80; (in[i][left] == in[i][left - 1]) && (left > 1); left--)
//         {
//         }
//         for (right = 80; (in[i][right] == in[i][right + 1]) && (right < 158); right++)
//         {
//         }
//         out[i][left] = 103;
//         out[i][left + 1] = 103;
//         out[i][left / 2 + right / 2] = 100;
//         out[i][right] = 106;
//         out[i][right - 1] = 106;
//     }
//     for (; i > 1; i--)
//     {
//         if (in[i - 1][left] != color)
//         {
//             for (; in[i][left] == in[i][left + 1]; left++)
//             {
//             }
//         }
//         else
//         {
//             for (; (in[i][left] == in[i][left - 1]) && (left > 1); left--)
//             {
//             }
//         }
//         if (in[i - 1][right] != color)
//         {
//             for (; in[i][right] == in[i][right - 1]; right--)
//             {
//             }
//         }
//         else
//         {
//             for (; (in[i][right] == in[i][left + 1]) && (right < 158); right++)
//             {
//             }
//         }
//         out[i][left] = 103;
//         out[i][left + 1] = 103;
//         out[i][left / 2 + right / 2] = 100;
//         out[i][right] = 106;
//         out[i][right - 1] = 106;
//     }
// }