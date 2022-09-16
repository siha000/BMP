#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main()
{
	open();
	for (int c = 0; c < HEIGHT; c++)
	{
		for (int d = 0; d < WIDTH * 3; d += 3)
		{
			int temp = (RGB[c][d] + RGB[c][d + 1] + RGB[c][d + 2]) / 3;
			result[c][d + 2] = result[c][d + 1] = result[c][d] = temp;
		}
	}
	save_image();
	return 0;
}