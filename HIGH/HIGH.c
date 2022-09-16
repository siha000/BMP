#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main()
{
    open();
    for (int c = 1; c < HEIGHT; c++)
    {
        for (int d = 3; d < WIDTH * 3; d++)
        {
            record[c][d] = RGB[c - 1][d - 3];
        }
    }

    for (int c = 1; c < HEIGHT; c++)
    {
        for (int d = 3; d < WIDTH * 3; d += 3)
        {
            char record_R = (record[c][d] * (-8) + record[c][d + 3] + record[c][d - 3] + record[c - 1][d] + record[c - 1][d + 3] + record[c - 1][d - 3] + record[c + 1][d] + record[c + 1][d + 3] + record[c + 1][d - 3]);
            char record_G = (record[c][d + 1] * (-8) + record[c][d + 4] + record[c][d - 2] + record[c - 1][d + 1] + record[c - 1][d + 4] + record[c - 1][d - 2] + record[c + 1][d + 1] + record[c + 1][d + 4] + record[c + 1][d - 2]);
            char record_B = (record[c][d + 2] * (-8) + record[c][d + 5] + record[c][d - 1] + record[c - 1][d + 2] + record[c - 1][d + 5] + record[c - 1][d - 1] + record[c + 1][d + 2] + record[c + 1][d + 5] + record[c + 1][d - 1]);
            result[c - 1][d - 3] = record_R < 0 ? 0 : record_R;
            result[c - 1][d - 2] = record_G < 0 ? 0 : record_G;
            result[c - 1][d - 1] = record_B < 0 ? 0 : record_B;
        }
    }

    save_image();
}