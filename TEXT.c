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
	unsigned int aaa;
	unsigned int bbb;
	unsigned int cc;
	unsigned int ddd;
};
int main()
{
	FILE *fp=fopen("car.bmp","rb");
	FILE *write=fopen("car1.bmp","wb");
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
	unsigned char RGB[dibheader.height][dibheader.width*3];
	unsigned char record[dibheader.height][dibheader.width*3];
	fread(RGB,sizeof(char),dibheader.height*dibheader.width*3,fp);
	for(int c=0;c<dibheader.height;c++)
	{
		for(int d=0;d<dibheader.width*3;d+=3)
		{
			record[c][d]=RGB[c][d];
			record[c][d+1]=RGB[c][d+1];
			record[c][d+2]=RGB[c][d+2];
		}
	}
	fwrite(&text,sizeof(text),1,write);
	fwrite(&dibheader,sizeof(dibheader),1,write);
	fwrite(record,sizeof(char),dibheader.height*dibheader.width*3,write);
	fclose(fp);

}