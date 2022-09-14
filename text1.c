#include<stdio.h>
#include<stdlib.h>
#pragma pack(2)
typedef struct BITMAP_header
{
	char name[2];
	unsigned int size;
	int garbage;
	unsigned int image_offset;
}header;

struct DIB_HEADER
{
	unsigned int header_size; //訊息頭資訊為40byte
	unsigned int width; //寬度
	unsigned int height; //高度
	unsigned short int colorplanes; //顏色平面數通常為1
	unsigned short int bitsperpixel; //像素數(檔案室彩色所以是24byte)
	unsigned int compression; //檔案未經壓縮以0表示
	unsigned int image_size;    //位圖像素大小
};

int main()
{
	FILE *fp=fopen("car.bmp","rb");
	header text;
	struct DIB_HEADER dibheader;
	fread(&text,sizeof(text),1,fp);
    printf("size :%d\n",text.size);
    printf("image_offset :%d \n",text.image_offset);
	fread(&dibheader,sizeof(struct DIB_HEADER),1,fp);
	printf("header_size :%d\n width :%d\n height :%d\ncolor plane :%d\n bitsperpixel:%d\n compression :%d\n image_size :%d\n"
	,dibheader.header_size,dibheader.width,dibheader.height,dibheader.colorplanes,
	dibheader.bitsperpixel,dibheader.compression,dibheader.image_size);
	printf("%d \n",sizeof(text));
    printf("%d \n",sizeof(dibheader));
	fclose(fp);

}