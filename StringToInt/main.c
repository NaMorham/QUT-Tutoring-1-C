#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <memory.h>


#ifndef bool
typedef unsigned long bool;
#endif
#ifndef true
#define true 1
#endif
#ifndef false
#define false 0
#endif


extern const char *TrimSpace(const char *str, int len, char *buf, int bufSize);
extern bool StringToInt(const char *str, int len, int *pInt);

#ifndef BUF_SIZE
#define BUF_SIZE 256
#endif

static void TestTrim();
static void TestInts();

int main(int argc, char *argv[])
{
    TestTrim();

    TestInts();

    return 0;
}

#define TESTTRIM(s, b, bs, result)                                  \
{                                                                   \
    printf("Trim start and end spaces of \"%s\": ", s);             \
    assert(strcmp(TrimSpace(s, strlen(s), b, bs), result) == 0);    \
    printf("[OK]\n");                                               \
}
#define TESTTRIMFAIL(lbl, s, l, b, bs)                              \
{                                                                   \
    printf(lbl);                                                    \
    assert(TrimSpace(s, l, b, bs) == NULL);                         \
    printf("[OK]\n");                                               \
}

static void TestTrim()
{
    char buf[BUF_SIZE + 1];
    const char *str1 = "   This is a test str   ";
    const char *str2 = "   This is a test str";
    const char *str3 = "This is a test str   "; 
    const char *str4 = "This is a test str";
    const char *rString = "This is a test str";

    memset(buf, 0, BUF_SIZE + 1);

    printf("\n----------------------------------------------------------------------------\n");
    printf("  Test trim functions\n");
    printf("----------------------------------------------------------------------------\n");

    TESTTRIM(str1, buf, BUF_SIZE, rString);
    TESTTRIM(str2, buf, BUF_SIZE, rString);
    TESTTRIM(str3, buf, BUF_SIZE, rString);
    TESTTRIM(str4, buf, BUF_SIZE, rString);
    TESTTRIM("   ONELONGSTRINGOFJUNK   ", buf, BUF_SIZE, "ONELONGSTRINGOFJUNK");
    printf("\n");
    TESTTRIMFAIL("Attempt to trim NULL string: ", NULL, 100, buf, BUF_SIZE);
    TESTTRIMFAIL("Attempt to trim string with 0 size: ", str1, 0, buf, BUF_SIZE);
    TESTTRIMFAIL("Attempt to trim string with NULL buffer: ", str1, strlen(str1), NULL, BUF_SIZE);
    TESTTRIMFAIL("Attempt to trim string with too small buffer: ", str1, strlen(str1), buf, 3);
    TESTTRIMFAIL("Cannot trim an empty string: ", "", 0, buf, BUF_SIZE);
    TESTTRIMFAIL("Cannot trim a NULL string: ", NULL, 100, buf, BUF_SIZE);

    printf("----------------------------------------------------------------------------\n");
    printf("  Done.\n");
    printf("----------------------------------------------------------------------------\n\n");
}

#define TESTINT(s, v, result)               \
{                                           \
    printf("Convert \"%s\" to int: ", s);   \
    assert(StringToInt(s, strlen(s), &v));  \
    assert(v == result);                    \
    printf("[OK]\n");                       \
}
#define TESTINTFAIL(s, v)                           \
{                                                   \
    printf("Fail to convert \"%s\" to int: ", s);   \
    assert(StringToInt(s, strlen(s), &v) == false); \
    printf("[OK]\n");                               \
}


static void TestInts()
{
    const char *str1 = "1";
    const char *str2 = "5";
    const char *str3 = "123";
    const char *str4 = "456";
    int val = 0;

    printf("\n----------------------------------------------------------------------------\n");
    printf("  Test int functions\n");
    printf("----------------------------------------------------------------------------\n");

    TESTINT(str1, val, 1);
    TESTINT(str2, val, 5);
    TESTINT(str3, val, 123);
    TESTINT(str4, val, 456);
    TESTINT("-15", val, -15);
    TESTINT("+25", val, 25);
    printf("\n");
    TESTINTFAIL("42bad", val);
    TESTINTFAIL("doomsauce", val);
    TESTINTFAIL("10.2", val);

    printf("----------------------------------------------------------------------------\n");
    printf("  Done.\n");
    printf("----------------------------------------------------------------------------\n\n");
}
