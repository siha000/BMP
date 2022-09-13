#include<stdio.h>
#include<stdlib.h>
#pragma pack(1)
typedef struct BITMAP_header
{
	char name[2];
	unsigned int size;
	int garbage;
	unsigned int image_offset;
}header;

struct DIB_HEADER
{
	unsigned int header_size;
	unsigned int width;
	unsigned int height;
	unsigned short int colorplanes;
	unsigned short int bitsperpixel;
	unsigned int compression;
	unsigned int image_size;
};

int main()
{
	FILE *fp=fopen("car.bmp","rb");
	header text;
	struct DIB_HEADER dibheader;
	fread(&text,sizeof(text),1,fp);
	//fread(&text.name,2,1,fp);
	//fread(&text.size,3*sizeof(int),1,fp);
	printf("FIRST Two Char %c %c\n",text.name[0],text.name[1]);
	printf("size :%d\n",text.size);
	fread(&dibheader,sizeof(struct DIB_HEADER),1,fp);
	printf("header_size :%d\n width :%d\n height :%d\ncolor plane :%d\n bitsperpixel:%d\n compression :%d\n image_size :%d\n"
	,dibheader.header_size,dibheader.width,dibheader.height,dibheader.colorplanes,
	dibheader.bitsperpixel,dibheader.compression,dibheader.image_size);
	printf("%d \n",sizeof(text));
	fclose(fp);

}