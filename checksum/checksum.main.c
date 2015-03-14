#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
#define PRINTNULL(str) (str == NULL ? "NULL" : str)
#define SAFEFREE(ptr) { if (ptr) { free(ptr); ptr = NULL; }}

// Externs
extern int checksum(char* data_string, char* key_string, char** checksum_string);

// Locals
static void TestChecksum();

int main(int argc, char *argv[])
{
    char *testStr_0 = "100100100110111101001010010"; // bin 0
    char *keyStr_0 = "1100010"; // key 0
    char * testStr_7 = "111000111011010111000101101010"; // bin 7
    char *keyStr_29 = "1100010"; // key 29
    char *resultStr = NULL;
    int rc = 0;

    rc = checksum(testStr_7, keyStr_29, &resultStr);


    return 0;
}

//=============================================================================
static BOOL TestChecksumFunc(const char *checksumStr, const char *keyStr, 
                         const int expectedRC, const char *expectedResult)
{
    char *result = NULL;
    char *data = NULL;
    int rc = 0;
    BOOL fnResult = FALSE;

    printf("Test checksumstring \"%s\"\n\tagainst key \"%s\" expecting %d && \"%s\" : ",
        PRINTNULL(checksumStr), PRINTNULL(keyStr), expectedRC, PRINTNULL(expectedResult));
    
    rc = checksum((char *)checksumStr, (char *)keyStr, &result); // I SHOULD NOT HAVE TO SOPY OR CAST THESE
                                                                 // THEY SHOULD BE CONST CHAR *
    printf("received %d && %s : ", rc, PRINTNULL(result));
    
    // check return code
    if (expectedRC != rc)
    {
        goto cleanup;
    }

    // check result string
    if (strcmp(result, expectedResult) == 0)
    {
        fnResult = TRUE;
    }

cleanup:
    printf("%s\n", (fnResult == TRUE ? "[OK]" : "[FAILED]"));
    SAFEFREE(result);
    return fnResult;
}

#define TESTCHECKSUM(chk, key, rc, exstr, testStr)                          \
{                                                                           \
    printf("%s:\n\t", ( testStr != NULL ? testStr : "(UNKNOWN TEST)" ));    \
    assert(TestChecksumFunc(chk, key, rc, exstr) && testStr);               \
    printf("\n");                                                           \
}

static void TestChecksum()
{
    char *testStr_0 = "100100100110111101001010010"; // bin 0
    char *keyStr_0 = "1100010"; // key 0
    char *result_0_0 = "";
    char *testStr_7 = "111000111011010111000101101010"; // bin 7
    char *keyStr_29 = "1100010"; // key 29
    char *result_7_29 = "";

    printf("\n");
    printf("------------------------------\n");
    printf("Test checksum function\n");
    printf("------------------------------\n");

    printf("\n");
    printf("------------------------------\n");
    printf("Done\n");
    printf("------------------------------\n");
}