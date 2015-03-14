#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define PRINTC(a) (isprint(a) ? a : '.')

const static char BITMASK = 0x01;
const static char PIXMASK = 0xFE;

static const char *BinString(const unsigned char src, char *buf, const int bufSize);
static void DumpDummy();

int main()
{
    DumpDummy();

    return 0;
}



void DumpBinString(const char *str)
{
    int idx = 0;
    char c = 0;
    char buf[9];
    int len = 0;

    memset(buf, 0, 9 * sizeof(char));
    len = (int)strlen(str);
    for (idx = 0; idx < len; ++idx)
    {
        c = str[idx];
        printf("[%3d] 0x%02x %c %s\n", idx, c, PRINTC(c), BinString(c, buf, 8));
    }
}

static void DumpImageData(const char *data, const int sz)
{
    int idx = 0;
    char c = 0;
    char buf[9];

    if (data == NULL)
    {
        printf("Invalid data\n");
        return;
    }
    if (sz < 1)
    {
        printf("Not enough data.\n");
        return;
    }

    memset(buf, 0, 9 * sizeof(char));

    printf("Dump dummy test\n");
    printf("sz = %d\n", sz);
    printf("--------------------------------\n");
    // loop through the dummy array and dump binaries
    for (idx = 0; idx < sz; ++idx)
    {
        c = data[idx];
        if ((idx % 8) == 0)
        {
            printf("\n");
        }
        printf("[%3d] 0x%02x '%c' %s %d\n", idx, c, PRINTC(c), BinString(c, buf, 8), (c&BITMASK ? 1 : 0));
    }
    printf("--------------------------------\n");
}

static void DumpDummy()
{
    char dummy[] = {
        0x24, 0x60, 0x4f, 0x2f, 0x7a, 0x0f, 0x1f, 0x6a, 0x0f, 0x40,
        0x18, 0x2a, 0x42, 0x5b, 0x59, 0x38, 0x3e, 0x01, 0x04, 0x22,
        0x51, 0x09, 0x63, 0x26, 0x09, 0x7d, 0x5d, 0x54, 0x04, 0x2d,
        0x51, 0x30, 0x51, 0x48, 0x15, 0x4e, 0x74, 0x4f, 0x11, 0x58,
        0x2a, 0x42, 0x6c, 0x26, 0x7c, 0x7a, 0x5e, 0x72, 0x64, 0x30,
        0x48, 0x51, 0x64, 0x21, 0x25, 0x2d, 0x55, 0x47, 0x2b, 0x25,
        0x16, 0x1c, 0x68, 0x34, 0x61, 0x1a, 0x4f, 0x5f, 0x79, 0x12,
        0x03, 0x26, 0x4f, 0x0a, 0x7b, 0x6d, 0x0f, 0x4e, 0x64, 0x2e
    };
    char* image_data = NULL;
    char testStr[] = "large";
    char c = 0;
    int sz = 0;
    int arrsize = 0;
    int width = 0;
    int height = 0;
    int idx = 0;

    printf("Dump test string \"%s\"\n", testStr);
    DumpBinString(testStr);
    printf("--------------------------------\n");
    printf("\n");

/*
    arrsize = read_image("../inputs/images/small_41.pgm", &image_data, &width, &height);
    if (arrsize <= 0)
    {
    printf("Unable to read image.\n");
    return;
    }
//*/

    sz = (int)(sizeof(dummy) / sizeof(char));
    DumpImageData(dummy, sz);

/*
    if (image_data != NULL)
    {
        free(image_data);
        image_data = NULL;
    }
//*/
}

static const char *BinString(const unsigned char src, char *buf, const int bufSize)
{
    assert(buf != NULL);
    assert(bufSize >= 8);
    memset(buf, 0, bufSize * sizeof(char));
    unsigned char val = src;
    int i = 0;
    for (; i < 8; ++i)
    {
        static const unsigned char mask = 0x80;
        buf[i] = ((mask & val) == mask ? '1' : '0');
        val = val << 1;
    }
    return buf;
}


