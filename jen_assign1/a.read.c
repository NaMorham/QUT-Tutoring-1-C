#include "assignment_1.h"

#define  BUF_SIZE 64

static const char *ReadVal(FILE *fp, char *buf, const size_t bufSize);


int read_image(char* file_name, char** image_data, int* width, int* height)
{
    FILE *fp = NULL;
    int fType = 5; // default to grey scale binary
    int w = 0, h = 0, maxVal = 0;
    int arraySize = 0;
    char buf[BUF_SIZE+1];
    char * data = NULL;
    size_t readSize = 0;

    if (file_name == NULL)
    {
        printf("NULL file name.\n");
        return -1;
    }
    if (*file_name == 0)
    {
        printf("Empty file name.\n");
        return -1;
    }
    if (image_data == NULL)
    {
        printf("NULL pointer for image data pointer.\n");
        return -1;
    }
    if (width == NULL)
    {
        printf("NULL pointer for image width.\n");
        return -1;
    }
    if (height == NULL)
    {
        printf("NULL pointer for image height.\n");
        return -1;
    }
    if (*image_data != NULL)
    {
        printf("Image data pointer may already be allocated.\n");
        return -1;
    }

    fp = fopen(file_name, "rb");
    if (fp == NULL)
    {
        printf("Failed to open image file \"%s\"\n", file_name);
        return -1;
    }

    // ready to read
    memset(buf, 0, (BUF_SIZE + 1)*sizeof(char));

    // read the type
    ReadVal(fp, buf, BUF_SIZE);
    if (buf[0] != 'P')
    {
        printf("Missing magic byte.\n");
        return -1;
    }
    if ((buf[1] < '0') || (buf[1] > '9'))
    {
        printf("Invalid magic number.\n");
        return -1;
    }
    fType = buf[1] - '0';
    if ((fType < 2) || (fType > 6) || (fType == 4))
    {
        printf("Unsupported file type.\n");
        return -1;
    }

    // read the width 
    ReadVal(fp, buf, BUF_SIZE);
    w = atoi(buf);
    if (w < 1)
    {
        printf("Invalid width.\n");
        return -1;
    }

    // read the height 
    ReadVal(fp, buf, BUF_SIZE);
    h = atoi(buf);
    if (h < 1)
    {
        printf("Invalid height.\n");
        return -1;
    }

    // read the max val
    ReadVal(fp, buf, BUF_SIZE);
    maxVal = atoi(buf);
    if (maxVal < 1)
    {
        printf("Invalid Maximum value.\n");
        return -1;
    }

    // calc the array size
    arraySize = w * h;
    if ((fType == 3) || (fType == 6)) // colour file
    {
        arraySize *= 3;
    }

    // it's good, so malloc
    data = (char *)malloc(sizeof(char)*arraySize);
    if (data == NULL)
    {
        printf("Out of memory, could not allocate %d bytes.\n", (int)(sizeof(char))*arraySize);
        arraySize = -1;
        goto cleanup;
    }

    // read the image data
    if ((fType == 5) || (fType == 6))
    {
        readSize = fread(data, sizeof(char), arraySize, fp);
    }
    else
    {
        int idx;
        for (idx = 0; idx < arraySize; ++idx)
        {
            if (ReadVal(fp, buf, BUF_SIZE) == NULL)
            {
                break;
            }
            data[idx] = atoi(buf);
        }
        if (idx != arraySize)
        {
            printf("Error reading ascii data.\n");
            arraySize = -1;
            free(data);
            data = NULL;
            goto cleanup;
        }
    }

    // return everything
    *width = w;
    *height = h;
    *image_data = data;

cleanup:
    if (fp != NULL)
    {
        fclose(fp);
        fp = NULL;
    }
    return arraySize;
}

// return -1 on fail
const char *ReadVal(FILE *fp, char *buf, const size_t bufSize)
{
    size_t idx = 0;
    char c = 0;

    memset(buf, 0, sizeof(char)*bufSize);

    while (idx < bufSize)
    {
        if (feof(fp))
        {
            // ran out of file, bail
            return buf;
        }
        c = fgetc(fp);
        if ((c == ' ') || (c == '\n'))
        {
            // reached end of value
            return buf;
        }
        buf[idx++] = c;
    }

    return NULL;
}

