#include <stdio.h>
#include <stdlib.h>
#include "TEXT.h"

int main()
{
	FILE *fp = fopen("cameraman.bmp", "rb");
	FILE *write = fopen("cameraman1.bmp", "wb");
	header text;
	DIBHEADER dibheader;
	fread(&text, sizeof(text), 1, fp);
	fread(&dibheader,sizeof(dibheader),1,fp);
	int height = dibheader.height;
	int width = dibheader.width;
	printf("%d \n", sizeof(text));
	char *RGB = (char *)malloc(sizeof(char) * height * width * 3);
	char *record = (char *)malloc(sizeof(char) * height * width * 3);
	fread(RGB, sizeof(char), height * width * 3, fp);
	for (int c = 0; c < height * width * 3; c+=3)
	{
		int temp = (RGB[c+1] + RGB[c+1] + RGB[c+2]) / 3;
		record[c+2] = record[c+1] = record[c] = temp;
	}

	fwrite(&text, sizeof(text), 1, write);
	fwrite(&dibheader, sizeof(dibheader), 1, write);
	fwrite(record, sizeof(char), dibheader.height * dibheader.width * 3, write);
	fclose(fp);
	fclose(write);
	free(RGB);
	free(record);
	
}