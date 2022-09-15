#pragma once
#define HEIGHT 1500
#define WIDTH 2000
#define file_name "carbmp"
#define file_save "car1.bmp"
char RGB[HEIGHT][WIDTH * 3];
char record[HEIGHT][WIDTH * 3];
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

void open();
void save_image();