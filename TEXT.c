#include <stdio.h>
#include <stdlib.h>
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
unsigned char RGB[1500][2000 * 3];
unsigned char record[1500][2000 * 3];
int main()
{
	FILE *fp = fopen("car.bmp", "rb");
	FILE *write = fopen("car1.bmp", "wb");
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
	printf("%d \n", sizeof(text));
	fread(RGB, sizeof(char), dibheader.height * dibheader.width * 3, fp);
	for (int c = 0; c < 1500; c++)
	{
		for (int d = 0; d < 2000 * 3; d += 3)
		{
			int temp = (RGB[c][d] + RGB[c][d + 1] + RGB[c][d + 2]) / 3;
			record[c][d + 2] = record[c][d + 1] = record[c][d] = temp;
		}
	}

	fwrite(&text, sizeof(text), 1, write);
	fwrite(&dibheader, sizeof(dibheader), 1, write);
	fwrite(RGB, sizeof(unsigned char), dibheader.height * dibheader.width * 3, write);

	fclose(fp);
	fclose(write);
}