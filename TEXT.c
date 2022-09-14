#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#pragma pack(1)

typedef struct BITMAP_header
{
	char name[2];
	unsigned int size;
	int garbage;
	unsigned int image_offset;
} header;

struct DIB_HEADER
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
};

int main()
{
	FILE *fp = fopen("Lenna.bmp", "rb");
	FILE *write = fopen("Lenna1.bmp", "wb");
	header text, text1;
	struct DIB_HEADER dibheader, dibheader1;
	fread(&text, sizeof(text), 1, fp);
	printf("FIRST Two Char %c %c\n", text.name[0], text.name[1]);
	printf("size :%d\n", text.size);
	fread(&dibheader, sizeof(struct DIB_HEADER), 1, fp);
	printf("header_size :%d\n width :%d\n height :%d\ncolor plane :%d\n bitsperpixel:%d\n compression :%d\n image_size :%d\n biXPelsPerMeter: %d \n biYPelsPerMeter :%d \n biClrUsed : %d \n biClrImportant :%d \n",
		   dibheader.header_size, dibheader.width, dibheader.height, dibheader.colorplanes, dibheader.bitsperpixel,
		   dibheader.compression, dibheader.image_size, dibheader.biXPelsPerMeter, dibheader.biYPelsPerMeter,
		   dibheader.biClrUsed, dibheader.biClrImportant);
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