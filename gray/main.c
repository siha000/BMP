#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main()
{
	open();
	for (int c = 0; c < HEIGHT; c++)
	{
		for (int d = 0; d < WIDTH; d++)
		{
			int temp = (RGB[c][d] + RGB[c][d + 1] + RGB[c][d + 2]) / 3;
			record[c][d + 2] = record[c][d + 1] = record[c][d] = temp;
		}
	}
	printf("finish");
	save_image();
	return 0;
}