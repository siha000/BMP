#include <stdio.h>
#include <stdlib.h>
//#include "LOW.h"
#define HEIGHT 316
#define WIDTH 316
#pragma pack(1)
char RGB[HEIGHT * 2][WIDTH * 3];
char record[HEIGHT * 2][WIDTH * 3 * 2] = {0};
char result[HEIGHT * 2][WIDTH * 3 * 2] = {0};
typedef struct BITMAP_header
{
    char name[2];
    unsigned int size;
    int garbage;
    unsigned int image_offset;
} header;

typedef struct DIB_HEADER
{
    unsigned int header_size;
    unsigned int width;
    unsigned int height;
    unsigned short int colorplanes;
    unsigned short int bitsperpixel;
    unsigned int compression;
    unsigned int image_size;
    unsigned int biXPelsPerMeter;
    unsigned int biYPelsPerMeter;
    unsigned int biClrUsed;
    unsigned int biClrImportant;
} DIBHEADER;

int main()
{
    FILE *read = fopen("Lenna.bmp", "rb");
    FILE *write = fopen("Lenna1.bmp", "wb");
    header HEADER, HEADER1;
    DIBHEADER dibheader, dibheader1;
    fread(&HEADER, sizeof(HEADER), 1, read);
    fread(&dibheader, sizeof(dibheader), 1, read);
    fread(RGB, sizeof(unsigned char), HEIGHT * WIDTH * 3, read);
    printf("%d %d \n", dibheader.height, dibheader.width);
    for (int c = 0; c < HEIGHT * 2 - 2; c += 2)
    {
        for (int d = 0; d < WIDTH * 3 * 2 - 6; d += 6)
        {
            record[c][d] = RGB[c / 2][d / 2];
            record[c][d + 1] = RGB[c / 2][d / 2 + 1];
            record[c][d + 2] = RGB[c / 2][d / 2 + 2];
            /*result[c][d] = record[c][d];
            result[c][d + 1] = record[c][d];
            result[c][d + 2] = record[c][d + 2];
        */
        }
    }
    /*for (int c = 0; c < WIDTH * 3 * 2; c += 6)
    {
        record[HEIGHT * 2][c] = RGB[HEIGHT][c / 2];
        record[HEIGHT * 2][c + 1] = RGB[HEIGHT][c / 2 + 1];
        record[HEIGHT * 2][c + 2] = RGB[HEIGHT][c / 2 + 2];
    }
    for (int c = 0; c < HEIGHT * 2; c += 2)
    {
        record[c][HEIGHT * 2 * 3] = RGB[c / 2][HEIGHT * 3];
    }
    for (int c = 2; c < HEIGHT - 1; c += 2)
    {
        for (int d = 2; d < (WIDTH - 1) * 2 * 3; d += 2)
        {
            record[c - 1][d] = (record[c][d] + record[c - 2][d]) / 2;             //[1][2]
            record[c - 2][d - 1] = (record[c - 2][d - 2] + record[c - 2][d]) / 2; //[0][1]
            record[c][d - 1] = (record[c][d] + record[c][d - 2]) / 2;             //[2][1]
            record[c - 1][d - 2] = (record[c - 2][d - 2] + record[c][d - 2]) / 2; //[1][0]
            record[c - 1][d - 1] = (record[c - 1][d] + record[c - 1][d - 2]) / 2;
        }
    }
*/
    dibheader.height = HEIGHT * 2;
    dibheader.width = WIDTH * 2;
    HEADER.size = HEIGHT * WIDTH * 3 * 2 * 2;
    fwrite(&HEADER, sizeof(HEADER), 1, write);
    fwrite(&dibheader, sizeof(dibheader), 1, write);
    fwrite(record, sizeof(unsigned char), HEIGHT * WIDTH * 3 * 2 * 2, write);

    printf("%d %d \n", dibheader.height, dibheader.width);
    fclose(read);
    fclose(write);
    return 0;
}