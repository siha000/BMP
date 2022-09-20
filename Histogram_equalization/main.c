#include <stdio.h>
#include <stdlib.h>
#define HEIGHT 1500
#define WEIGHT 2000
double R[256] = {0}, G[256] = {0}, B[256] = {0};
double record_R[256] = {0}, record_G[256] = {0}, record_B[256] = {0};
double current_R, back_R = 0, current_G, back_G = 0, current_B, back_B = 0;
char RGB[HEIGHT][WEIGHT * 3];
char record[HEIGHT + 2][WEIGHT * 3 + 6] = {0};
char result[HEIGHT][WEIGHT * 3];
char record_gamma[HEIGHT][WEIGHT * 3];
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
	FILE *fp = fopen("car.bmp", "rb");
	FILE *write = fopen("car1.bmp", "wb");
	header text;
	DIBHEADER dibheader;
	fread(&text, sizeof(text), 1, fp);
	fread(&dibheader, sizeof(dibheader), 1, fp);
	fread(&RGB, sizeof(char), HEIGHT * WEIGHT * 3, fp);
	for (int c = 0; c < HEIGHT; c++)
	{
		for (int d = 0; d < WEIGHT * 3; d += 3)
		{
			record_R[RGB[c][d]] += 1;
			record_G[RGB[c][d + 1]] += 1;
			record_B[RGB[c][d + 2]] += 1;
		}
	}

	for (int c = 0; c < 256; c++)
	{
		current_R = record_R[c] / HEIGHT / WEIGHT;
		current_G = record_G[c] / HEIGHT / WEIGHT;
		current_B = record_B[c] / HEIGHT / WEIGHT;

		R[c] = current_R + back_R;
		G[c] = current_G + back_G;
		B[c] = current_B + back_B;

		back_R += current_R;
		back_G += current_G;
		back_B += current_B;

		record_R[c] = (R[c] - R[0]) * 255 / (1 - R[0]);
		record_G[c] = (G[c] - G[0]) * 255 / (1 - G[0]);
		record_B[c] = (B[c] - B[0]) * 255 / (1 - B[0]);
	}

	for (int c = 0; c < HEIGHT; c++)
	{
		for (int d = 0; d < WEIGHT * 3; d += 3)
		{
			result[c][d] = record_R[RGB[c][d]];
			result[c][d + 1] = record_G[RGB[c][d + 1]];
			result[c][d + 2] = record_B[RGB[c][d + 2]];
		}
	}

	fwrite(&text, sizeof(text), 1, write);
	fwrite(&dibheader, sizeof(dibheader), 1, write);
	fwrite(result, sizeof(char), HEIGHT * WEIGHT * 3, write);
	fclose(fp);
	fclose(write);
}