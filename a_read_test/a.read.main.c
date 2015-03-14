#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: Implement NoString.h

extern int read_image(char* file_name, char** image_data, int* width, int* height);
extern int write_image(char* file_name, int width, int height, char* image_data, int data_length);
extern const char *ReadVal(FILE *fp, char *buf, const size_t bufSize);
extern int calcMax(char* image_data, int data_length);

void TestReadVal();
void TestReadImage();
void TestCalcMax();
void TestWriteImage();

int main(int argc, char *argv[])
{
    TestReadVal();
    TestReadImage();
    TestCalcMax();
    TestWriteImage();

    return 0;
}

//=============================================================================
void TestReadVal()
{
    printf("\n");
    printf("------------------------------\n");
    printf("Test ReadVal function\n");
    printf("------------------------------\n");


    printf("------------------------------\n");
    printf("Done\n");
    printf("------------------------------\n");
}

//=============================================================================
void TestReadImage()
{
    printf("\n");
    printf("------------------------------\n");
    printf("Test ReadImage function\n");
    printf("------------------------------\n");


    printf("------------------------------\n");
    printf("Done\n");
    printf("------------------------------\n");
}

//=============================================================================
void TestCalcMax()
{
    printf("\n");
    printf("------------------------------\n");
    printf("Test WriteImage function\n");
    printf("------------------------------\n");


    printf("------------------------------\n");
    printf("Done\n");
    printf("------------------------------\n");
}

//=============================================================================
void TestWriteImage()
{
    printf("\n");
    printf("------------------------------\n");
    printf("Test WriteImage function\n");
    printf("------------------------------\n");


    printf("------------------------------\n");
    printf("Done\n");
    printf("------------------------------\n");
}
