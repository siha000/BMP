#include <stdio.h>
#include <stdlib.h>
#include "../TEXT.h"
#define HEIGHT 256
#define WEIGHT 256
unsigned char RGB[HEIGHT][WEIGHT * 3];
unsigned char result[HEIGHT * 2][WEIGHT * 3 * 2];
unsigned char record[HEIGHT * 2][WEIGHT * 3 * 2];
int main()
{
    FILE *read = fopen("colorbird.bmp", "rb");
    FILE *write = fopen("colorbird1.bmp", "wb");
    header HEADER;
    DIBHEADER dibheader;
    fread(&HEADER, sizeof(HEADER), 1, read);
    fread(&dibheader, sizeof(dibheader), 1, read);
    fread(RGB, sizeof(unsigned char), HEIGHT * WEIGHT * 3, read);
    for (int c = 0; c < HEIGHT * 2; c += 2)
    {
        for (int d = 0; d < WEIGHT * 3 * 2; d += 6)
        {
            record[c][d] = RGB[c][d];
            record[c][d + 1] = RGB[c][d + 1];
            record[c][d + 2] = RGB[c][d + 2];
        }
    }

    for (int c = 2; c < HEIGHT - 1; c += 2)
    {
        for (int d = 2; d < (WEIGHT - 1) * 2 * 3; d += 2)
        {
            record[c - 1][d] = (record[c][d] + record[c - 2][d]) / 2;             //[1][2]
            record[c - 2][d - 1] = (record[c - 2][d - 2] + record[c - 2][d]) / 2; //[0][1]
            record[c][d - 1] = (record[c][d] + record[c][d - 2]) / 2;             //[2][1]
            record[c - 1][d - 2] = (record[c - 2][d - 2] + record[c][d - 2]) / 2; //[1][0]
            record[c - 1][d - 1] = (record[c - 1][d] + record[c - 1][d - 2]) / 2;
        }
    }
    fwrite(&HEADER, sizeof(HEADER), 1, write);
    fwrite(&dibheader, sizeof(dibheader), 1, write);
    fwrite(RGB, sizeof(unsigned char), HEIGHT * WEIGHT * 3, write);
    fclose(read);
    fclose(write);
    return 0;
}