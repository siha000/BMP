#define HEIGHT 1500
#define WIDTH 2000
#define file_name "car.bmp"
#define file_save "car1.bmp"
char RGB[HEIGHT][WIDTH * 3];
char record[HEIGHT][WIDTH * 3];
char result[HEIGHT][WIDTH * 3];
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

void open()
{
	FILE *read = fopen(file_name, "rb");
	header header;
	DIBHEADER DIBHEADER;
	fread(&header, sizeof(header), 1, read);
	fread(&DIBHEADER, sizeof(DIBHEADER), 1, read);
	fread(RGB, sizeof(char), HEIGHT * WIDTH * 3, read);
	fclose(read);
}

void save_image()
{
	FILE *write = fopen(file_save, "wb");
	header header1;
	DIBHEADER DIBHEADER1;
	fwrite(&header1, sizeof(header1), 1, write);
	fwrite(&DIBHEADER1, sizeof(DIBHEADER1), 1, write);
	fwrite(result, sizeof(char), HEIGHT * WIDTH * 3, write);
	fclose(write);
}
