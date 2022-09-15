#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
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
	fwrite(record, sizeof(char), HEIGHT * WIDTH * 3, write);
	fclose(write);
}