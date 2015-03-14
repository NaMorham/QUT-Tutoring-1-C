#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define  BUF_SIZE 64

#ifndef byte
typedef unsigned char byte;
#endif

#define GETMAX(a, b) (a > b ? a : b)

#ifdef WIN32
#define snprintf _snprintf
#endif

#define SAFECLOSE(fptr) do { if (fptr != NULL) { fclose(fptr); fptr = NULL; } } while (0);

static int calcMax(char* image_data, int data_length)
{
    int idx = 0;
    byte c = 0;
    byte max = 0;

    for (; idx, data_length; ++idx)
    {
        c = (byte)image_data[idx];
        max = GETMAX(c, max);
    }
    return (int)max;
}

int write_image(char* file_name, int width, int height, char* image_data, int data_length)
{
    FILE *fp = NULL;
    size_t arraySize = 0;
    size_t written = 0;
    char header[BUF_SIZE + 1];
    int type = 5;
    int maxVal = 0;

    // check inputs
    if ((file_name == NULL) || (image_data == NULL))
    {
        return -1;  // NULL pointer
    }
    if ((data_length < 1) || (width < 1) || (height < 1))
    {
        return -1;  // bad data
    }
    maxVal = calcMax(image_data, data_length);

    arraySize = width * height;
    if (arraySize == data_length)
    {
        type = 5;
    }
    else if ((arraySize * 3) == data_length)
    {
        type = 6;
    }
    else
    {
        return -1;  // invalid size
    }

    memset(header, 0, sizeof(char)*(BUF_SIZE + 1));
    snprintf(header, BUF_SIZE, "P%d %d %d %d\n", type, width, height, maxVal);
    fp = fopen(file_name, "wb");
    if (fp == NULL)
    {
        return -1;  // failed to open file
    }

    written = fwrite(header, sizeof(char), strlen(header), fp);
    if (written != strlen(header))
    {
        // didn't write enough
        SAFECLOSE(fp);
        return -1;
    }

    written = fwrite(image_data, sizeof(char), (size_t)data_length, fp);
    if (written != (size_t)data_length)
    {
        // didn't write enough
        SAFECLOSE(fp);
        return -1;
    }

    SAFECLOSE(fp);

    return 0;
}

