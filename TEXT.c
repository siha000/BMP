#include <stdio.h>
#include <stdlib.h>
#include "TEXT.h"
#define HEIGHT 256
#define WEIGHT 256


// int data=(24*WEIGHT+31)/32*4;
char RGB[HEIGHT][WEIGHT * 3];
char result[HEIGHT][WEIGHT * 3];
char record[HEIGHT][WEIGHT * 3] = {0};

int main()
{
	FILE *fp = fopen("colorbird.bmp", "rb");
	FILE *write = fopen("colorbird1.bmp", "wb");
	header text;
	DIBHEADER dibheader;
	fread(&text, sizeof(text), 1, fp);
	fread(&dibheader, sizeof(dibheader), 1, fp);
	fread(&RGB, sizeof(char), HEIGHT * (WEIGHT)*3, fp);
	for (int c = 1; c < HEIGHT; c++)
	{
		for (int d = 3; d < WEIGHT * 3; d++)
		{
			record[c][d] = RGB[c - 1][d - 3];
		}
	}

	for (int c = 1; c < HEIGHT; c++)
	{
		for (int d = 3; d < WEIGHT * 3; d += 3)
		{
			char record_R = (record[c][d] * (-8) + record[c][d + 3] + record[c][d - 3] + record[c - 1][d] + record[c - 1][d + 3] + record[c - 1][d - 3] + record[c + 1][d] + record[c + 1][d + 3] + record[c + 1][d - 3]);
			char record_G = (record[c][d + 1] * (-8) + record[c][d + 4] + record[c][d - 2] + record[c - 1][d + 1] + record[c - 1][d + 4] + record[c - 1][d - 2] + record[c + 1][d + 1] + record[c + 1][d + 4] + record[c + 1][d - 2]);
			char record_B = (record[c][d + 2] * (-8) + record[c][d + 5] + record[c][d - 1] + record[c - 1][d + 2] + record[c - 1][d + 5] + record[c - 1][d - 1] + record[c + 1][d + 2] + record[c + 1][d + 5] + record[c + 1][d - 1]);
			result[c - 1][d - 3] = record_R < 0 ? 0 : record_R;
			result[c - 1][d - 2] = record_G < 0 ? 0 : record_G;
			result[c - 1][d - 1] = record_B < 0 ? 0 : record_B;
		}
	}

	fwrite(&text, sizeof(text), 1, write);
	fwrite(&dibheader, sizeof(dibheader), 1, write);
	fwrite(result, sizeof(char), HEIGHT*WEIGHT*3, write);
	fclose(fp);
	fclose(write);
	free(RGB);
	// free(record);
}