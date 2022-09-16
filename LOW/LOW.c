#include <stdio.h>
#include <stdlib.h>
#include <../TEXT.h>
#define HEIGHT 1500
#define WEIGHT 2000

int main()
{
    FILE *read = fopen("car.bmp", "rb");
    FILE *write = fopen("car1.bmp", "wb");
    header header;
    DIBHEADER DIBHEADER;
    fread(&header, sizeof(header), 1, read);
    fread(&DIBHEADER, sizeof(DIBHEADER), 1, read);
    char *RGB = (char *)malloc(sizoef(char) * HEIGHT * WEIGHT * 3);
    char *result = (char *)malloc(sizeof(char) * WEIGHT * HEIGHT * 3);
    char *record = (char *)calloc((HEIGHT + 2)(WEIGHT * 3 + 6),sizeof(char));

    fread(RGB, sizoef(char), HEIGHT * WEIGHT * 3, read);
    for(int c=WEIGHT*3+2;c<HEIGHT*WEIGHT*3;c++)
    {
        
    }
    return 0;
}