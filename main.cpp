#include <iostream>
#include "bmp.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
int R[MaxBMPSizeX][MaxBMPSizeY]; // MaxBMPSizeX and MaxBMPSizeY are defined in "bmp.h"
int G[MaxBMPSizeX][MaxBMPSizeY];
int B[MaxBMPSizeX][MaxBMPSizeY];

int r[MaxBMPSizeX][MaxBMPSizeY];
int g[MaxBMPSizeX][MaxBMPSizeY];
int b[MaxBMPSizeX][MaxBMPSizeY];
char input[11]="Lenna.bmp";
char ouput[11]="haha.bmp";
int main(int argc, char *argv[])
{
	int width, height;
	int i, j;

	// �}�Ҩ�Ū�����m(24bits)bmp �v������
	// RGB �T�� channel ���Ȧs�J R, G, B �T�Ӧۭq���}�C��
	// �}�C�j�p���o�j�� 1024x1024

	open_bmp(input, R, G, B, width, height); //for true color images
	//open_bmp("lena.bmp", R, R, R, width, height); // for gray images

    

	// �x�s�B�z���G�ܷs�����ɤ�
	//save_bmp("lenna_new1.bmp", r, g, b); // for true color images
	save_bmp(ouput, r, r, r); // for gray images
	printf("Job Finished!\n");

	// ���� bmp �v������
	close_bmp();

	//system("PAUSE"); /* so that the command window holds a while */
	return 0;
}
