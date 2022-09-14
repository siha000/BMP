BMP
======

### BMP介紹

+ BMP取自位圖Bitmap的縮寫，也稱為DIB（與設備無關的位圖)，BMP文件通常是不壓縮的，所以它們
通常比同一幅圖像的壓縮圖像文件格式要大很多

+ BMP格式的文件從頭到尾依次是如下信息：

    + bmp文件頭（bmp file header）：共 14 byte

    + 位圖信息頭（bitmap information）：共 40 byte

    + 調色板（color palette）：可選

    + 位圖數據

### BMP文件頭

+ 該字節塊位於文件的開頭，用於標識文件。一個典型的應用程序首先讀取這個塊以確保該文件實際
上是一個 BMP 文件並且它沒有被損壞

```
0-1(byte) :2byte用來辨識BMP和DIB文件標頭檔，[0]為'B'，[1]為'M'

2-6(byte) :用來標記BMP文件大小

7-8(byte) :預訂的 實際值取決於創建圖像的應用程序預設為0

9-10(byte) :預訂的 實際值取決於創建圖像的應用程序預設為0

11-14(byte) :表示從文件頭到位圖數據的偏移

```

+ 其資料結構宣告 :

    + 注意要加pragma pack(1)，原因c語言struct會分配最大位元給header，舉例目前header應
    該為14，但編譯器會分配16位元給header，因為header最大位元為4byte，char只有兩個byte
    所以會自動補齊2個byte

```

#include <stdio.h>
#include <stdlib.h>
#pragma pack(1)
typedef struct header
{
    char name[2]; //'B'、'M'
    unsigned int size; //54 + height * width * 3
    int garbage;
    unsigned int image_offset; //預設54(因為開頭14byte + DIB 40byte)
} header;

int main()
{
    FILE *fp = fopen("car.bmp", "rb");
    header text;
    fread(&text, sizeof(text), 1, fp);
    printf("first two char : %c %c \n", text.name[0], text.name[1]); //'B'、'M'
    printf("garbage :%d \n",text.garbage);// '0'
    printf("size : %d \n", text.size);// 2000 * 1500 * 3 + 54
    printf("image_offset : %d \n", text.image_offset); //54
    fclose(fp);
    return 0;
}

```

### DIB位圖信息頭（bitmap information）

+ 位圖信息頭一共40byte，包含如下內容：

    + biSize：4byte，信息頭的大小，即40

    + biWidth：4byte，以像素為單位說明圖像的寬度

    + biHeight：4byte，以像素為單位說明圖像的高度，同時如果為正，說明位圖倒立（即數據表
    示從圖像的左下角到右上角），如果為負說明正向

    + biPlanes：2byte，為目標設備說明顏色平面數，通常設置為1

    + biBitCount：2byte，說明像素數，值有1、2、4、8、16、24、32(如果彩色為24因為rgb佔
    8*3 = 24byte)

    + biCompression：4byte，說明圖像的壓縮類型，通常使用0，表示不壓縮

    + biSizeImages：4byte，說明位圖數據的大小，當用BI_RGB格式時，可以設置為0

    + biXPelsPerMeter：4byte，表示水平分辨率，單位是像素，有符號整數

    + biYPelsPerMeter：4byte，表示垂直分辨率，單位是像素，有符號整數

    + biClrUsed：4byte,說明位圖使用的調色板中的顏色索引數，為0說明使用所有

    + biClrImportant：4byte，說明對圖像顯示有重要影響的顏色索引數，為0說明都重要

+ 其資料結構宣告

    + biXPelsPerMeter以下結構不重要因此就不宣告

```
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
	fread(&dibheader,sizeof(struct DIB_HEADER),1,fp);
	printf("header_size :%d\n width :%d\n height :%d\ncolor plane :%d\n bitsperpixel:%d\n compression :%d\n image_size :%d\n"
	,dibheader.header_size,dibheader.width,dibheader.height,dibheader.colorplanes,
	dibheader.bitsperpixel,dibheader.compression,dibheader.image_size);
	printf("%d \n",sizeof(text));
	fclose(fp);

}

```

