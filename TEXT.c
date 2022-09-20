#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define HEIGHT 256
#define WEIGHT 256
#define PI 3.14159265
#define val 180.0 / PI
char RGB[HEIGHT][WEIGHT * 3];
char record[HEIGHT + 2][WEIGHT * 3 + 6] = {0};
char result[128][64 * 3];
double record_gamma[HEIGHT][WEIGHT * 3];
double record_angle[HEIGHT][WEIGHT * 3];

#pragma pack(1)

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
	FILE *fp = fopen("colorbird.bmp", "rb");
	FILE *write = fopen("colorbird1.bmp", "wb");
	header text;
	DIBHEADER dibheader;
	fread(&text, sizeof(text), 1, fp);
	fread(&dibheader, sizeof(dibheader), 1, fp);
	fread(&RGB, sizeof(char), HEIGHT * (WEIGHT)*3, fp);
	for (int c = 40; c < 168; c++)
	{
		for (int d = 63; d < 127 * 3; d++)
		{
			result[c - 40][d - 63] = RGB[c][d];
		}
	}
	/*for (int c = 1; c < HEIGHT; c++)
	{
		for (int d = 3; d < WEIGHT * 3; d++)
		{
			record[c][d] = RGB[c-1][d - 3];
		}
	}
	/*for (int c = 1; c < HEIGHT; c++)
	{
		for (int d = 3; d < WEIGHT * 3; d++)
		{
			record_gamma[c-1][d-3] =sqrt((record[c+1][d]+record[c-1][d])*(record[c+1][d]+record[c-1][d])+(record[c][d-1]+record[c][d+1])*(record[c][d-1]+record[c][d+1]));
			record_angle[c-1][d-3]=atan((record[c+1][d]+record[c-1][d])/(record[c][d-1]+record[c][d+1]))*val;
			//printf("%lf\n",record_angle[c-1][d-3]);
		}
	}

	for(int c=0;c<HEIGHT;c++)
	{
		for(int d=0;d<WEIGHT*3;d++)
		{
			result[c][d]=record[c+1][d+3];
		}
	}*/
	dibheader.height = 128;
	dibheader.width = 64;
	text.size = dibheader.height * dibheader.width + 54;
	fwrite(&text, sizeof(text), 1, write);
	fwrite(&dibheader, sizeof(dibheader), 1, write);
	fwrite(result, sizeof(char), 64 * 128 * 3, write);
	fclose(fp);
	fclose(write);
}