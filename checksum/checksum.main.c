#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
#define PRINTNULL(str) (str == NULL ? "NULL" : (*str == 0 ? "EMPTY" : str))
#define SAFEFREE(ptr) { if (ptr) { free(ptr); ptr = NULL; }}
#define TORFSTR(b) (b ? "true" : "false");
#define OKBOOL(b) (b ? "[OK]" : "[FAILED]")

// Externs
extern int checksum(char* data_string, char* key_string, char** checksum_string);

// Locals
static void TestChecksum();

int main(int argc, char *argv[])
{
    TestChecksum();

    return 0;
}

//=============================================================================
static BOOL TestChecksumFunc(const char *checksumStr, const char *keyStr, 
                         const int expectedRC, const char *expectedResult)
{
    char *result = NULL;

    int rc = 0;
    int cmpResult = -1;
    BOOL fnResult = FALSE;

    printf("Test checksumstring \"%s\"\n\tagainst key \"%s\"\n\texpecting %d && \"%s\" : ",
        PRINTNULL(checksumStr), PRINTNULL(keyStr), expectedRC, PRINTNULL(expectedResult));
    
    rc = checksum((char *)checksumStr, (char *)keyStr, &result); // I SHOULD NOT HAVE TO SOPY OR CAST THESE
                                                                 // THEY SHOULD BE CONST CHAR *
    printf("received %d && %s: \n", rc, PRINTNULL(result));

    // check return code
    printf("\tCheck return codes: %d == %d : %s\n", expectedRC, rc, OKBOOL(expectedRC == rc));
    if (expectedRC != rc)
    {
        goto cleanup;
    }
    else if ((expectedRC == -1) && (result == NULL)) // we expect falure and got it
    {
        fnResult = TRUE;
    }

    // check result string
    if (result &&                               // We have a result
        (expectedRC == 0))                      // AND we expect a result
    {
        cmpResult = strcmp(result, expectedResult);
    }
    printf("\tCheck result strings: \"%s\" == \"%s\" : %s\n", 
        PRINTNULL(expectedResult), PRINTNULL(result), OKBOOL(cmpResult == 0));
    if (cmpResult == 0)
    {
        fnResult = TRUE; 
    }

cleanup:
    SAFEFREE(result);
    return fnResult;
}

#define TESTCHECKSUM(chk, key, rc, exstr, testStr)                          \
{                                                                           \
    printf("%s:\n\t", ( testStr != NULL ? testStr : "(UNKNOWN TEST)" ));    \
    assert(TestChecksumFunc(chk, key, rc, exstr) && testStr);               \
    printf("\n");                                                           \
}

// Data extracted from AMS responses using regexs
// Find:    Test #[0-9]+: Failed\nInput: /.*/binary_\([0-9]+\)\.txt /.*/key_\([0-9]+\)\.txt\nMessage: \([01]+\)\nKey: \([01]+\)\nExpected checksum: \([01]+\)\nActual checksum: .+\n
// Replace: \tconst char *testStr_\1 = \"\3\";\n\tconst char *keyStr_\2 = \"\4\";\n\tconst char *result_\1_\2 = \"\5\";\n\n\tTESTCHECKSUM\(testStr_\1, keyStr_\2, 0, result_\1_\2, \"Test checksum_\1 against key_\2\"\);\n
static void TestChecksum()
{
    const char *testStr_0 = "100100100110111101001010010"; // bin 0
    const char *keyStr_0 = "1100010"; // key 0
    const char *result_0_0 = "110000";

    const char *testStr_7 = "111000111011010111000101101010"; // bin 7
    const char *keyStr_29 = "1101101"; // key 29
    const char *result_7_29 = "010100";

    const char *testStr_15 = "10111010001111001101100111000011001";
    const char *keyStr_38 = "11101";
    const char *result_15_38 = "0010";

    const char *testStr_26 = "1000000010101001000010000101111001";
    const char *keyStr_47 = "110000";
    const char *result_26_47 = "01001";

    const char *testStr_50 = "1110010001110111111001001001011";
    const char *keyStr_33 = "1111010";
    const char *result_50_33 = "101011";

    const char *testStr_2 = "111000011000011111111111000";
    const char *keyStr_8 = "1011011";
    const char *result_2_8 = "111010";

    const char *testStr_32 = "10111001111011011101100010110101";
    const char *keyStr_5 = "11000011";
    const char *result_32_5 = "0001010";

    const char *testStr_14 = "10011111110110100101010111001";
    const char *keyStr_14 = "11011";
    const char *result_14_14 = "1010";

    const char *testStr_30 = "11010101010101000011110000011100110";
    const char *keyStr_12 = "1010110";
    const char *result_30_12 = "100000";

    const char *testStr_45 = "110010111010110110011101010";
    const char *keyStr_32 = "11011101";
    const char *result_45_32 = "0010001";

    const char *testStr_16 = "11001101000100110001100010010010001000000";
    const char *keyStr_4 = "1011101";
    const char *result_16_4 = "000011";

    //const char *testStr_0 = "100100100110111101001010010"; // already defined
    const char *keyStr_48 = "111011";
    const char *result_0_48 = "11100";

    printf("\n");
    printf("------------------------------\n");
    printf("Test checksum function\n");
    printf("------------------------------\n");

    TESTCHECKSUM(NULL, keyStr_0, -1, result_0_0, "Test NULL checksum");
    TESTCHECKSUM(testStr_0, NULL, -1, result_0_0, "Test NULL key");
    TESTCHECKSUM("", keyStr_0, -1, result_0_0, "Test empty checksum");
    TESTCHECKSUM(testStr_0, "", -1, result_0_0, "Test empty key");

    TESTCHECKSUM(testStr_0, keyStr_0, 0, result_0_0, "Test checksum_0 against key_0");
    TESTCHECKSUM(testStr_7, keyStr_29, 0, result_7_29, "Test checksum_7 against key_29");
    TESTCHECKSUM(testStr_15, keyStr_38, 0, result_15_38, "Test checksum_15 against key_38");
    TESTCHECKSUM(testStr_26, keyStr_47, 0, result_26_47, "Test checksum_26 against key_47");
    TESTCHECKSUM(testStr_50, keyStr_33, 0, result_50_33, "Test checksum_26 against key_47");
    TESTCHECKSUM(testStr_2, keyStr_8, 0, result_2_8, "Test checksum_2 against key_8");
    TESTCHECKSUM(testStr_32, keyStr_5, 0, result_32_5, "Test checksum_32 against key_5");
    TESTCHECKSUM(testStr_14, keyStr_14, 0, result_14_14, "Test checksum_14 against key_14");
    TESTCHECKSUM(testStr_30, keyStr_12, 0, result_30_12, "Test checksum_30 against key_12");
    TESTCHECKSUM(testStr_45, keyStr_32, 0, result_45_32, "Test checksum_45 against key_32");
    TESTCHECKSUM(testStr_16, keyStr_4, 0, result_16_4, "Test checksum_16 against key_4");
    TESTCHECKSUM(testStr_0, keyStr_48, 0, result_0_48, "Test checksum_0 against key_48");

    printf("\n");
    printf("------------------------------\n");
    printf("Done\n");
    printf("------------------------------\n");
}
