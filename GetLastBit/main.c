/**
Dietrich Dorner, in his study of decision-making in complex environments,
argues that Failure does not strike like a bolt from the blue; it develops
gradually according to its own logic.
 */

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
void TestPutCharIntoArray();
void TestPutGetIntoArray();

#define TORFSTR(a) (a ? "true" : "false")
#define PRINTC(a) (isprint(a) ? a : '.')


//============================================================================
int main(int argc, char *argv[])
{
    TestGetMaxChars();
    TestBinString();
    TestGetBitVals();
    TestSetMessageBit();
    TestGetCharFromArray();
    TestPutCharIntoArray();
    TestPutGetIntoArray();

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
extern int GetCharFromArray(char *pixels, const int pixelsSize, char *pChar);

void TestGetCharFromArrayEx(const char *fname, const int line, char *pixArray,
    const int sz, const int result, char outChar)
{
    char ch = 0, buf[9];
    int idx = 0, rc = 0;
    memset(buf, 0, sizeof(char) * 9);
    rc = GetCharFromArray(pixArray, sz, &ch);
    printf("[%s:%d] Get char from array (0x%p) of size (%d): {\n", fname, line, pixArray, sz);
    if (pixArray && sz > 1) 
    {
        for (idx = 0; idx < sz; ++idx) 
        {
            printf("    [%2d]: (0x%02.2x) \"%s\"\n",
                idx, (((int)pixArray[idx])&0x000000ff), // horrible hack to ensure only 1 byte is printed
                BinString(pixArray[idx], buf, 9));      // the maths is fine, but the printf insists on 4 bytes
        }
        printf("} == (0x%02x) %c: ", result, result);
        if (sz >= 8) 
        {
            ch = (char)ch; outChar = (char)outChar;
            printf("ch (0x%02x) == outChar (0x%02x) : %s\n", ch, outChar, TORFSTR(ch == outChar));
            assert(ch == (char)outChar); 
        }
    }
    else 
    {
        printf("    [Empty or invalid array]\n");
    }
    assert(rc == result);
    printf("[OK]\n\n");
}
#define TESTGETCHARFROMARRAY(pixArray, sz, result, outChar) TestGetCharFromArrayEx(__FILE__, __LINE__, pixArray, sz, result, outChar)

void TestGetCharFromArray()
{
    char *dummy = NULL;
    char result = 0;
    char test1[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    char test2[8] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
    char test3[8] = { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 };
    char test4[8] = { 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe };
    char test5[8] = { 0xA1, 0xB0, 0xC1, 0xD0, 0xF1, 0xE0, 0x81, 0x70 };
    char test6[8] = { 0xf0, 0xf1, 0xf0, 0xf0, 0xf1, 0xf0, 0xf0, 0xf1 };

    printf("\n----------------------------------------------------------------------------\n");
    printf("  Test GetCharFromArray()\n");
    printf("----------------------------------------------------------------------------\n");

    // Test invalid inputs
    TESTGETCHARFROMARRAY(dummy, 8, -1, 0x00);
    TESTGETCHARFROMARRAY(test1, 0, -1, 0x00);

    TESTGETCHARFROMARRAY(test1, 7, -1, 0x00);
    TESTGETCHARFROMARRAY(test1, -8, -1, 0x00);

    // Test valid data
    TESTGETCHARFROMARRAY(test1, 8, 0, 0x00);
    TESTGETCHARFROMARRAY(test2, 8, 0, 0xff);
    TESTGETCHARFROMARRAY(test3, 8, 0, 0xff);
    TESTGETCHARFROMARRAY(test4, 8, 0, 0x00);
    TESTGETCHARFROMARRAY(test5, 8, 0, 0xaa);
    TESTGETCHARFROMARRAY(test6, 8, 0, 0x49);

    printf("----------------------------------------------------------------------------\n");
    printf("  Done.\n");
    printf("----------------------------------------------------------------------------\n\n");
}



//============================================================================
extern int PutCharIntoArray(char *pixels, const int pixelsSize, char msgChar);

void TestPutCharIntoArrayEx(const char *fname, const int line, char *srcArray,
    const int sz, char msg, const int result, char *resArray)
{
    char *tmpArray = NULL;
    int rc = 0, idx = 0, cmpRes = 0;
    char buf[9];

    memset(buf, 0, sizeof(char) * 9);

    if (srcArray && (sz > 0))
    {
        tmpArray = (char *)malloc(sizeof(char)*sz);
        memcpy(tmpArray, srcArray, sz);
    }
    printf("\n[%s:%d]\nPut char (0x%02x) '%c' into array (0x%p) of size (%d): {\n", 
        fname, line, msg, PRINTC(msg), srcArray, sz);
    if (tmpArray && (sz >= 1))
    {
        for (idx = 0; idx < sz; ++idx)
        {
            printf("    [%2d]: (0x%02.2x) \"%s\"\n",
                idx, (((int)tmpArray[idx]) & 0x000000ff), // horrible hack to ensure only 1 byte is printed
                BinString(tmpArray[idx], buf, 9));      // the maths is fine, but the printf insists on 4 bytes
        }
    }
    rc = PutCharIntoArray(tmpArray, sz, msg);
    printf("  }  == %d : expecting %d\n", rc, result);
    assert(rc == result);
    if (result == 0)
    {
        cmpRes = 1; // assume true
        // check resulting array matches the expected result
        printf("Compare resulting array to expected result\n");
        printf("       expected                       result\n");
        for (idx = 0; idx < sz; ++idx)
        {
            printf("  [%2d]: (0x%02.2x) \"%s\" == ",
                idx, (((int)resArray[idx]) & 0x000000ff), // horrible hack to ensure only 1 byte is printed
                BinString(resArray[idx], buf, 9));      // the maths is fine, but the printf insists on 4 bytes
            printf("(0x%02.2x) \"%s\" : ",
                (((int)tmpArray[idx]) & 0x000000ff), // horrible hack to ensure only 1 byte is printed
                BinString(tmpArray[idx], buf, 9));      // the maths is fine, but the printf insists on 4 bytes
            printf("%s\n", TORFSTR(tmpArray[idx] == resArray[idx]));
            cmpRes = cmpRes && (tmpArray[idx] == resArray[idx]);
        }
        assert(cmpRes != 0);
    }
    if (tmpArray)
    {
        free(tmpArray);
        tmpArray = NULL;
    }
}

#define TESTPUTCHARINTOARRAY(srcArray, sz, msg, result, resArray) TestPutCharIntoArrayEx(__FILE__, __LINE__, srcArray, sz, msg, result, resArray)

void TestPutCharIntoArray()
{
    char *nullArray = NULL; 

    char  test1[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    char  test2[8] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
    char  test3[8] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07 };

    char  result1[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };  // test1 + 0x00
    char  result2[8] = { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 };  // test1 + 0xff
    char  result3[8] = { 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe };  // test2 + 0x00
    char  result4[8] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };  // test2 + 0xff
    char  result5[8] = { 0x00, 0x00, 0x02, 0x02, 0x04, 0x04, 0x06, 0x06 };  // test3 + 0x00
    char  result6[8] = { 0x01, 0x01, 0x03, 0x03, 0x05, 0x05, 0x07, 0x07 };  // test3 + 0xff

    char  result7[8] = { 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00 };  // test1 + 0x48 'H'
    char  result8[8] = { 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01 };  // test1 + 0x49 'I'
    char  result9[8] = { 0xfe, 0xff, 0xfe, 0xfe, 0xff, 0xfe, 0xfe, 0xfe };  // test2 + 0x48 'H'
    char result10[8] = { 0xfe, 0xff, 0xfe, 0xfe, 0xff, 0xfe, 0xfe, 0xff };  // test2 + 0x49 'I'
    char result11[8] = { 0x00, 0x01, 0x02, 0x02, 0x05, 0x04, 0x06, 0x06 };  // test3 + 0x48 'H'
    char result12[8] = { 0x00, 0x01, 0x02, 0x02, 0x05, 0x04, 0x06, 0x07 };  // test3 + 0x48 'I'

    printf("\n----------------------------------------------------------------------------\n");
    printf("  Test PutCharIntoArray()\n");
    printf("----------------------------------------------------------------------------\n");

    TESTPUTCHARINTOARRAY(nullArray, 8, 0x00, -1, result1);
    TESTPUTCHARINTOARRAY(test1, 0, 0x00, -1, result1);
    TESTPUTCHARINTOARRAY(test1, -8, 0x00, -1, result1);
    TESTPUTCHARINTOARRAY(test1, 3, 0x00, -1, result1);

    TESTPUTCHARINTOARRAY(test1, 8, 0x00, 0, result1);
    TESTPUTCHARINTOARRAY(test1, 8, 0xff, 0, result2);

    TESTPUTCHARINTOARRAY(test2, 8, 0x00, 0, result3);
    TESTPUTCHARINTOARRAY(test2, 8, 0xff, 0, result4);

    TESTPUTCHARINTOARRAY(test3, 8, 0x00, 0, result5);
    TESTPUTCHARINTOARRAY(test3, 8, 0xff, 0, result6);

    TESTPUTCHARINTOARRAY(test1, 8, 'H', 0, result7);
    TESTPUTCHARINTOARRAY(test1, 8, 'I', 0, result8);

    TESTPUTCHARINTOARRAY(test2, 8, 'H', 0, result9);
    TESTPUTCHARINTOARRAY(test2, 8, 'I', 0, result10);

    TESTPUTCHARINTOARRAY(test3, 8, 'H', 0, result11);
    TESTPUTCHARINTOARRAY(test3, 8, 'I', 0, result12);

    printf("\n----------------------------------------------------------------------------\n");
    printf("  Done.\n");
    printf("----------------------------------------------------------------------------\n\n");
}


//============================================================================
#define TESTPUTGETARRAY(arr, sz, ch)                    \
{                                                       \
    char chOut = 0;                                     \
    char *tmp = NULL;                                   \
    if (arr && (sz > 1)) {                              \
        tmp = (char*)malloc(sz*sizeof(char));           \
        assert(tmp != NULL);                            \
        memcpy(tmp, arr, sizeof(char)*sz);              \
    }                                                   \
    assert(PutCharIntoArray(tmp, sz, ch) == 0);         \
    assert(GetCharFromArray(tmp, sz, &chOut) == 0);     \
    printf("Compare input and output chars (0x%02x) '%c' == (0x%02x) '%c' == %s : ", \
        (byte)ch, PRINTC(ch), (byte)chOut, PRINTC(chOut), TORFSTR((byte)ch == (byte)chOut)); \
    assert((byte)ch == (byte)chOut);                    \
    printf("[OK]\n");                                   \
}

void TestPutGetIntoArray()
{
    char *nullArray = NULL;

    char test1[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    char test2[8] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
    char test3[8] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07 };

    printf("\n----------------------------------------------------------------------------\n");
    printf("  Test PutGetIntoArray()\n");
    printf("----------------------------------------------------------------------------\n");

    TESTPUTGETARRAY(test1, 8, 0x00);
    TESTPUTGETARRAY(test1, 8, 0xff);
    TESTPUTGETARRAY(test2, 8, 0x00);
    TESTPUTGETARRAY(test2, 8, 0xff);
    TESTPUTGETARRAY(test3, 8, 0x00);
    TESTPUTGETARRAY(test3, 8, 0xff);

    TESTPUTGETARRAY(test1, 8, 'H');
    TESTPUTGETARRAY(test1, 8, 'I');
    TESTPUTGETARRAY(test2, 8, ' ');
    TESTPUTGETARRAY(test2, 8, 'L');
    TESTPUTGETARRAY(test3, 8, 'O');
    TESTPUTGETARRAY(test3, 8, 'W');

    printf("\n----------------------------------------------------------------------------\n");
    printf("  Done.\n");
    printf("----------------------------------------------------------------------------\n\n");
}

//============================================================================
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
        printf("(0x%2x) %c", c, PRINTC(c));
    }
    printf("\n\n");
}



