#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

// Types
#ifndef BOOL
typedef unsigned int BOOL;
#endif
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

// Utility funcs
#define PRINTC(ch) (isprint((unsigned char)ch) ? ch : '.')
#define PRINTNULL(str) (str == NULL ? "NULL" : (*str == 0 ? "EMPTY" : str))
#define SAFEFREE(ptr) { if (ptr) { free(ptr); ptr = NULL; }}
#define SAFECLOSE(ptr) { if (ptr) { fclose(ptr); ptr = NULL; }}
#define TORFSTR(b) (b ? "true" : "false");
#define OKBOOL(b) (b ? "[OK]" : "[FAILED]")

#define BUF_SIZE 256

typedef struct _ImageData
{
    int type;
    int width;
    int height;
    int max;
    size_t sz;
    char *data;
} ImageData;

#define INIT_IMAGE(img)     memset(&img, 0, sizeof(ImageData))
#define RESET_IMAGE(img)    { if (img.data) { free(img.data); img.data = NULL; } INIT_IMAGE(img); } 

static void usage(int argc, char *argv[]);
static const char *ReadVal(FILE *fp, char *buf, const size_t bufSize);
static BOOL ReadHeader(FILE* fp, int *pType, int *pWidth, int *pHeight, int *pMaxVal);
static BOOL ReadImage(const char *fname, ImageData *pData);
static void PrintImage(ImageData*pData);
static void CreateCData(ImageData *pData, const char *varName, const int wrapping);
static int Replace(char *buf, char find, char replace);
static char *FindLast(char *buf, const char find, const size_t maxLen);

void Test()
{
    char buf[BUF_SIZE + 1];
    char *ptr;

    memset(buf, 0, sizeof(char)*(BUF_SIZE + 1));
    _snprintf(buf, BUF_SIZE, "Test message/foom/blah/testname.old.pgm");

    ptr = FindLast(buf, '.', -1);

    return;
}

int main(int argc, char *argv[])
{
    const char *fname = NULL;
    char varName[BUF_SIZE + 1];
    char tmp[BUF_SIZE + 1];
    char *ptr = NULL;
    ImageData img;
    int wrapping = 0;

#ifdef _DEBUG
    printf("Wait for debug:");
    gets(tmp);
    _sleep(10000);
#endif

    memset(tmp, 0, sizeof(char)*BUF_SIZE + 1);
    INIT_IMAGE(img);

    if (argc < 2)
    {
        // not enough args must have a filename
        usage(argc, argv);
        return 1;
    }
    fname = argv[1];

    if (ReadImage(fname, &img) == FALSE)
    {
        return 2;
    }

    // get variable anme if needed
    memset(varName, 0, sizeof(char)*(BUF_SIZE + 1));
    if (argc >= 3)
    {
        strncpy(tmp, argv[2], BUF_SIZE);
    }
    else
    {
        strncpy(tmp, fname, BUF_SIZE);
    }

    // cleanup the string for use as a variable name
    Replace(tmp, '\\', '/');
    ptr = FindLast(tmp, '/', -1);
    if (ptr == NULL)
    {
        ptr = tmp;
    }
    else
    {
        ++ptr;
    }
    strncpy(varName, ptr, BUF_SIZE);
    ptr = FindLast(varName, '.', -1);
    if (ptr != NULL)
    {
        *ptr = 0;
    }
    Replace(varName, ' ', '_');
    Replace(varName, '.', '_');

    // get alternate wrapping info if needed
    if (argc >= 4)
    {
        wrapping = atoi(argv[3]);
    }
    if (wrapping < 1)
    {
        wrapping = img.width;
    }

    PrintImage(&img);

    CreateCData(&img, varName, wrapping);

    RESET_IMAGE(img);

    return 0;
}


void usage(int argc, char *argv[])
{
    assert(argc > 0);

    printf("Usage:\n");
    printf("%s <filename> [name] [col wrap]\n", argv[0]);
}


// return NULL on fail
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
            return NULL;
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


BOOL ReadHeader(FILE* fp, int *pType, int *pWidth, int *pHeight, int *pMaxVal)
{
    char buf[BUF_SIZE + 1];

    if ((fp == NULL) || (pType == NULL) || (pWidth == NULL) ||
        (pHeight == NULL) || (pMaxVal == NULL))
    {
        printf("NULL pointer passed to ReadHeader(...)\n");
        return FALSE;
    }

// read type data
    memset(buf, 0, BUF_SIZE + 1);
    if (ReadVal(fp, buf, BUF_SIZE) == NULL)
    {
        printf("Unable to read file marker.\n");
        return FALSE;
    }

    if (strlen(buf) < 2)
    {
        printf("Invalid file marker.\n");
        return FALSE;
    }
    if (buf[0] != 'P')
    {
        printf("Invalid file type marker.\n");
        return FALSE;
    }
    switch (buf[1])
    {
    case '1':
    case '4':
        printf("Unsupported file type '%c'\n", buf[1]);
        return FALSE;
    case '2':
    case '3':
    case '5':
    case '6':
        break;
    default:
        printf("Unknown file type '%c'\n", buf[1]);
        return FALSE;
    }
    *pType = buf[1] - '0';

// Read width
    memset(buf, 0, BUF_SIZE + 1);
    if (ReadVal(fp, buf, BUF_SIZE) == NULL)
    {
        printf("Cannot read width data.\n");
        return FALSE;
    }
    *pWidth = atoi(buf);
    if (*pWidth < 1)
    {
        printf("Invalid width %d read.\n", *pWidth);
        return FALSE;
    }

// Read height
    memset(buf, 0, BUF_SIZE + 1);
    if (ReadVal(fp, buf, BUF_SIZE) == NULL)
    {
        printf("Cannot read height data.\n");
        return FALSE;
    }
    *pHeight = atoi(buf);
    if (*pHeight < 1)
    {
        printf("Invalid width %d read.\n", *pHeight);
        return FALSE;
    }

// Read max val
    memset(buf, 0, BUF_SIZE + 1);
    if (ReadVal(fp, buf, BUF_SIZE) == NULL)
    {
        printf("Cannot read max value data.\n");
        return FALSE;
    }
    *pMaxVal = atoi(buf);
    if (*pMaxVal < 1)
    {
        printf("Invalid max value %d read.\n", *pMaxVal);
        return FALSE;
    }

    return TRUE;
}

static BOOL ReadImage(const char *fname, ImageData *pData)
{
    char buf[BUF_SIZE + 1];
    FILE *fp = NULL;
    size_t arraySz = 0;
    size_t idx = 0;

    memset(buf, 0, BUF_SIZE + 1);

    if (fname == NULL)
    {
        return FALSE;
    }
    if (*fname == 0)
    {
        return FALSE;
    }
    if (pData == NULL)
    {
        return FALSE;
    }

    fp = fopen(fname, "rb");
    if (fp == NULL)
    {
        printf("Unable to open file \"%s\"\n", fname);
        return FALSE;
    }

    if (ReadHeader(fp, &(pData->type), &(pData->width), &(pData->height), &(pData->max)) != TRUE)
    {
        return FALSE;
    }

    arraySz = pData->width * pData->height;
    if (pData->type == 3 || pData->type == 6)
    {
        arraySz *= 3;
    }

    // allocate array
    pData->data = malloc(sizeof(char) * arraySz);
    if (pData->data == NULL)
    {
        SAFECLOSE(fp);
        return FALSE;
    }

    if (pData->type == 5 || pData->type == 6)
    {
        // binary read
        if (fread(pData->data, sizeof(char), arraySz, fp) != arraySz)
        {
            RESET_IMAGE((*pData));
            SAFECLOSE(fp);
            return FALSE;
        }
    }
    else
    {
        for (idx = 0; idx < arraySz; ++idx)
        {
            if (ReadVal(fp, buf, BUF_SIZE) == NULL)
            {
                break;
            }
            pData->data[idx] = atoi(buf);
        }
        if (idx != arraySz)
        {
            printf("Error reading ascii data.\n");
            RESET_IMAGE((*pData));
            pData->data = NULL;
            SAFECLOSE(fp);
            return FALSE;
        }
    }
    pData->sz = arraySz;

    SAFECLOSE(fp);
    return TRUE;
}


void PrintImage(ImageData*pData)
{
    size_t idx = 0;
    char c = 0;

    printf("\n");
    if (pData == NULL)
    {
        return;
    }
    printf("------------------------\n");
    printf("P%d %d %d %d", pData->type, pData->width, pData->height, pData->max);

    for (idx = 0; idx < pData->sz; ++idx)
    {
        if (idx > 0)
        {
            printf(", ");
        }
        if ((idx % pData->width) == 0)
        {
            printf("\n");
        }
        c = pData->data[idx];
        printf("0x%02x '%c'", c, PRINTC(c));
    }
    printf("\n------------------------\n\n");
}


void CreateCData(ImageData *pData, const char *varName, const int wrapping)
{
    FILE *fp = NULL;
    int count = 0;
    size_t idx = 0;
    int wrap = wrapping;

    if ((varName == NULL) || (wrapping < 1) || (pData == NULL))
    {
        return;
    }
    if (pData->sz < 1)
    {
        return;
    }

    fprintf(stderr, "const int %s_type = %d;\n", varName, pData->type);
    fprintf(stderr, "const int %s_width = %d;\n", varName, pData->width);
    fprintf(stderr, "const int %s_height = %d;\n", varName, pData->height);
    fprintf(stderr, "const int %s_maxVal = %d;\n", varName, pData->max);
    fprintf(stderr, "const int %s_arraySize = %lu;\n", varName, pData->sz);
    fprintf(stderr, "const char *%s_data = {\n", varName, pData->width);

    if ((pData->type == 3) || (pData->type == 6))
    {
        wrap *= 3;
    }

    for (idx = 0, count = 1; idx < pData->sz; ++idx)
    {
        if (count == 1)
        {
            fprintf(stderr, "\t");
        }
        fprintf(stderr, "0x%02x", pData->data[idx]);
        if (idx < (pData->sz - 1))
        {
            fprintf(stderr, ", ");
        }
        if (count == wrap)
        {
            fprintf(stderr, "\n");
            count = 0;
        }
        ++count;
    }

    fprintf(stderr, " };\n\n");

}


int Replace(char *buf, char find, char replace)
{
    int count = 0;
    size_t idx = 0;
    size_t len = 0;

    if ((buf == NULL) || (find == 0) || (replace == 0))
    {
        return -1;
    }
    len = strlen(buf);
    for (idx = 0; idx < len; ++idx)
    {
        if (buf[idx] == find)
        {
            buf[idx] = replace;
            ++count;
        }
    }

    return count;
}

char *FindLast(char *buf, const char find, const size_t maxLen)
{
    char *ptr = NULL;
    size_t len = 0;
    size_t idx = 0;
    char c = 0;

    if (buf == NULL)
    {
        return NULL;
    }
    if (find == 0)
    {
        return NULL;
    }

    len = strlen(buf);
    if ((maxLen > 0) && (maxLen != (size_t)-1))
    {
        len = len < maxLen ? len : maxLen;
    }
    for (idx = len, ptr = buf + (len - 1); idx > 0; --idx, --ptr)
    {
        c = buf[idx - 1];
        if (c == find)
        {
            return ptr;
        }
    }

    return NULL;
}
