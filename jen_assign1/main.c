#include <assert.h>
#include <ctype.h>
#include "assignment_1.h"

#define RC_SUCCESS      0
#define RC_FAILED_READ  1
#define RC_INVALID_IMG  2
#define RC_FAILED_WRITE 3

static void DumpImage(const char *array, const size_t arrSize);

int main(int argc, char *argv[])
{
    int arraySize = 0;
    char *imgData = NULL;
    int width = 0;
    int height = 0;
    int rc = 0;

    arraySize = read_image("./test.pgm", &imgData, &width, &height);
    if (arraySize < 0)
    {
        printf("Failed to read file\n");
        return RC_FAILED_READ;
    }
    else if (arraySize == 0)
    {
        printf("Did not read any image data\n");
        return RC_INVALID_IMG;
    }
    else
    {
        printf("Read image [%d, %d], array size = %d\n", width, height, arraySize);
    }

    printf("Read image = {");
    DumpImage(imgData, arraySize);
    printf(" }\n\n");

    // write the data
    rc = write_image("testfile.out.pgm", width, height, imgData, arraySize);
    if (rc == -1)
    {
        printf("Failed to write new image file.\n");
        return RC_FAILED_WRITE;
    }

    // cleanup
    if (imgData != NULL)
    {
        free(imgData);
        imgData = NULL;
    }

    return RC_SUCCESS;
}

void DumpImage(const char *array, const size_t arrSize)
{
    char c = 0;
    size_t idx = 0;
    size_t wrap = 0;

    for (idx = 0; idx < arrSize; ++idx, ++wrap)
    {
        if ((wrap % 6) == 0)
        {
            printf("\n");
        }
        c = array[idx];
        printf("(0x%02x) ", c);
        if (isprint(c))
        {
            printf("'%c' ", c);
        }
        else
        {
            printf("'.' ");
        }
    }
}
