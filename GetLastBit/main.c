#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>


void TestGetMaxChars();
void TestGetBitVals();
void TestBinString();
void TestSetMessageBit();
void TestGetCharFromArray();

int main(int argc, char *argv[])
{
    TestGetMaxChars();
    TestBinString();
    TestGetBitVals();
    TestSetMessageBit();
    TestGetCharFromArray();

    return 0;
}

//============================================================================
extern int GetMaxChars(int arraysize);

#define TESTGETMAXCHARS(val, result)        \
{                                           \
    printf("Get max chars %5d == %-5d: ", val, result);  \
    assert(GetMaxChars(val) == result);     \
    printf("[OK]\n");                       \
}

void TestGetMaxChars()
{
    printf("\n----------------------------------------------------------------------------\n");
    printf("  Test GetMaxChars()\n");
    printf("----------------------------------------------------------------------------\n");

    TESTGETMAXCHARS(8, 1);
    TESTGETMAXCHARS(16, 2);
    TESTGETMAXCHARS(9, 1);
    TESTGETMAXCHARS(7, 0);
    TESTGETMAXCHARS(-5, 0);
    TESTGETMAXCHARS(80, 10);

    printf("----------------------------------------------------------------------------\n");
    printf("  Done.\n");
    printf("----------------------------------------------------------------------------\n\n");
}


//============================================================================
#ifndef byte
typedef unsigned char byte;
#endif

extern const char *BinString(const byte src, char *buf, const int bufSize);

#define TESTBINSTRING(val, result)              \
{                                               \
    char buf[9];                                \
    printf("Get Binary string %02x = \"%s\": ", val, result);   \
    const char *res = BinString(val, buf, 9);         \
    assert(strcmp(res, result) == 0);           \
    printf("[OK]\n");                           \
}

void TestBinString()
{
    printf("\n----------------------------------------------------------------------------\n");
    printf("  Test BinString()\n");
    printf("----------------------------------------------------------------------------\n");

    TESTBINSTRING(0x00, "00000000");
    TESTBINSTRING(0xFF, "11111111");
    TESTBINSTRING(0x7F, "01111111");
    TESTBINSTRING(0xFE, "11111110");
    TESTBINSTRING(0x77, "01110111");
    TESTBINSTRING(0x88, "10001000");

    printf("----------------------------------------------------------------------------\n");
    printf("  Done.\n");
    printf("----------------------------------------------------------------------------\n\n");
}


//============================================================================
#ifndef byte
typedef unsigned char byte;
#endif

extern void GetBitVals(const byte src, byte *pPixel, byte *pBit);

#define TESTGETBITVALS(val, pixResult, bitResult)   \
{                                                   \
    byte pix = 0, bit = 0;                          \
    char srcBuf[9], pixBuf[9], msgBuf[9];           \
    printf("Get bit values 0x%02x \"%s\" ==  ", val, BinString(val, srcBuf, 9)); \
    printf("0x%02x \"%s\", ", pixResult, BinString(pixResult, pixBuf, 9));   \
    printf("0x%02x \"%s\": ", bitResult, BinString(bitResult, msgBuf, 9));   \
    GetBitVals(val, &pix, &bit);                    \
    assert((pix & pixResult) == pixResult);         \
    assert((bit & bitResult) == bitResult);         \
    printf("[OK]\n");                               \
}

void TestGetBitVals()
{
    printf("\n----------------------------------------------------------------------------\n");
    printf("  Test GetGetBitVals()\n");
    printf("----------------------------------------------------------------------------\n");

    TESTGETBITVALS(0xff, 0xfe, 0x01);
    TESTGETBITVALS(0x00, 0x00, 0x00);
    TESTGETBITVALS(0xfe, 0xfe, 0x00);
    TESTGETBITVALS(0x88, 0x88, 0x00);
    TESTGETBITVALS(0x81, 0x80, 0x01);
    TESTGETBITVALS(0x66, 0x66, 0x00);
    TESTGETBITVALS(0xDD, 0xDC, 0x01);

    printf("----------------------------------------------------------------------------\n");
    printf("  Done.\n");
    printf("----------------------------------------------------------------------------\n\n");
}

//============================================================================
extern const byte SetMessageBit(const byte pixel, const byte messageBit);

#define TESTSETMESSAGEBIT(pix, msg, res)                            \
{                                                                   \
    char resBuf[9], pixBuf[9], msgBuf[9];                           \
    printf("Set msg (0x%02x)\"%s\" ", msg, BinString(msg, msgBuf, 9));  \
    printf("in pix (0x%02x)\"%s\": ", pix, BinString(pix, pixBuf, 9));  \
    printf("(0x%02x)\"%s\": ", res, BinString(res, resBuf, 9));     \
    assert(SetMessageBit(pix, msg) == res);                         \
    printf("[OK]\n");                                               \
}

void TestSetMessageBit()
{
    printf("\n----------------------------------------------------------------------------\n");
    printf("  Test GetSetMessageBit()\n");
    printf("----------------------------------------------------------------------------\n");

    TESTSETMESSAGEBIT(0xff, 0x01, 0xff);
    TESTSETMESSAGEBIT(0xff, 0x00, 0xfe);
    TESTSETMESSAGEBIT(0x00, 0x01, 0x01);
    TESTSETMESSAGEBIT(0x00, 0x00, 0x00);
    TESTSETMESSAGEBIT(0xdc, 0x01, 0xdd);
    TESTSETMESSAGEBIT(0xdc, 0x00, 0xdc);
    TESTSETMESSAGEBIT(0x66, 0x01, 0x67);
    TESTSETMESSAGEBIT(0x66, 0x00, 0x66);

    printf("----------------------------------------------------------------------------\n");
    printf("  Done.\n");
    printf("----------------------------------------------------------------------------\n\n");
}

//============================================================================
extern int GetCharFromArray(const char *pixels, const int pixelsSize, char *pChar);

#define TESTGETCHARFROMARRAY(pixArray, sz, result, outChar)  \
{                                                   \
    char ch = 0, buf[9];                            \
    int idx = 0, rc = 0;                            \
    memset(buf, 0, sizeof(char)*9);                 \
    rc = GetCharFromArray(pixArray, sz, &ch);       \
    printf("[%s:%d] Get char from array (0x%p) of size (%d): {\n", __FILE__, __LINE__, pixArray, sz); \
    if (pixArray && sz > 1) {                       \
        for (idx = 0; idx < sz; ++idx) {            \
            printf("    [%2d]: (0x%02x) \"%s\"\n",  \
                    idx, pixArray[idx], BinString(pixArray[idx], buf, 9));   \
        }                                           \
        if (sz >= 8) { assert(ch = outChar); }      \
    } else {                                        \
        printf("    [Empty or invalid array]\n");   \
    }                                               \
    assert(rc = result);                            \
    printf("} == (0x%02x) %c: ", result, result);   \
    printf("[OK]\n\n");                             \
}

void TestGetCharFromArray()
{
    char *dummy = NULL;
    char result = 0;
    char test1[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    char test2[8] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

    printf("\n----------------------------------------------------------------------------\n");
    printf("  Test GetCharFromArray()\n");
    printf("----------------------------------------------------------------------------\n");

    // Test invalid inputs
    TESTGETCHARFROMARRAY(dummy, 8, -1, 0x00);
    TESTGETCHARFROMARRAY(test1, 0, -1, 0x00);

    TESTGETCHARFROMARRAY(test1, 7, -1, 0x00);
    TESTGETCHARFROMARRAY(test1, -8, -1, 0x00);

    // Test valid data
    //TESTGETCHARFROMARRAY(test1, 8, 0, 0x00);
    //TESTGETCHARFROMARRAY(test2, 8, 0, 0xff);
//    TESTGETCHARFROMARRAY(test1, 8, 0x00);

    printf("----------------------------------------------------------------------------\n");
    printf("  Done.\n");
    printf("----------------------------------------------------------------------------\n\n");
}





void DumpArray(char *arrayData, int len)
{
    int idx = 0;
    char c = 0;
    int vals = 0;

    for (idx = 0; idx < len; ++idx, ++vals)
    {
        if ((vals % 10) == 0)
        {
            printf("\n");
        }
        c = arrayData[idx];
        printf("(0x%2x)", c);
        if (isprint(c))
        {
            printf("%c", c);
        }
        else
        {
            printf(".");
        }
    }
    printf("\n\n");
}



