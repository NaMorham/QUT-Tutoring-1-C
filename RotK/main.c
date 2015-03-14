#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
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
#define PRINTC(a) (isprint((unsigned char)a) ? a : '.')
#define PRINTNULL(str) (str == NULL ? "NULL" : (*str == 0 ? "EMPTY" : str))
#define SAFEFREE(ptr) { if (ptr) { free(ptr); ptr = NULL; }}
#define TORFSTR(b) (b ? "true" : "false");

// Externs
extern int rot_k(char* message, int k);
extern int crack(char* encoded, char* known_word, char** message);
//extern int FindWholeWord(const char *msg, const char *find);

// Test funcs
void TestRotK();
void TestCrack();
//void TestFindWholeWord();

int main(int argc, char *argv[])
{
    TestRotK();
//    TestFindWholeWord();
    TestCrack();

    return 0;
}


//=============================================================================
// TEST DATA
static const char msg1[] = "abc";
static const char msg2[] = "Hello there.";
static const char msg3[] = "abc-def ghi.jkl mno pqr stu vwx yz?";

static const char enc1[] = "bcd";       // msg 1 rot 1
static const char enc2[] = "zab";       // msg 1 rot -1
static const char enc3[] = "fgh";       // msg 1 rot 5
static const char enc4[] = "yza";       // msg 1 rot 50
static const char enc5[] = "cde";       // msg 1rot -50

static const char enc6[] = "Ifmmp uifsf.";        // msg2 rotate by 1
static const char enc7[] = "Mjqqt ymjwj.";        // msg2 rotate by 5

static const char enc10[] = "bcd-efg hij.klm nop qrs tuv wxy za?";
static const char enc11[] = "hij-klm nop.qrs tuv wxy zab cde fg?";

//=============================================================================
void TESTROTK(const char *str, const int k, const char *expected, const int rc)
{
    char *buf = NULL;
    int result = 0;
    int stringCompare = -1;
    int finalResult = 0;

    assert(expected != NULL);

    printf("\n    Test: \"%s\" rotated by %d : \n", PRINTNULL(str), k);
    printf("  Expect: \"%s\" returning %d : \n", expected, rc);

    if (str)
    {
        buf = _strdup(str);  // need a local copy since it will be changed
    }

    result = rot_k(buf, k);
    printf("Received: \"%s\" and %d : ", buf, result);
    if (buf)
    {
        stringCompare = strcmp(buf, expected);
    }
    if ((rc == -1) && (result == -1))
    {
        finalResult = 1;
        printf("[OK]");
    }
    else if ((rc != -1) && (rc == result) && (stringCompare == 0))
    {
        finalResult = 1;
        printf("[OK]");
    }
    else
    {
        finalResult = 0;
        printf("[FAILED]");
    }
    printf("\n\n");

    //cleanup
    SAFEFREE(buf);

    assert(finalResult == 1);
}

void TestRotK()
{    
    printf("\n");
    printf("------------------------------\n");
    printf("Test rotk function\n");
    printf("------------------------------\n");

    TESTROTK(NULL, 0, "", -1);

    TESTROTK(msg1, 0, msg1, 3);
    TESTROTK(msg1, 26, msg1, 3);
    TESTROTK(msg1, 1, enc1, 3);
    TESTROTK(msg1, -1, enc2, 3);
    TESTROTK(msg1, 5, enc3, 3);
    TESTROTK(msg1, 50, enc4, 3);
    TESTROTK(msg1, -50, enc5, 3);

    TESTROTK(msg2, 0, msg2, 10);
    TESTROTK(msg2, 26, msg2, 10);
    TESTROTK(msg2, 1, enc6, 10);
    TESTROTK(msg2, 5, enc7, 10);

    TESTROTK(msg3, 1, enc10, 26);
    TESTROTK(msg3, 0, msg3, 26);
    TESTROTK(msg3, 7, enc11, 26);

    printf("------------------------------\n");
    printf("Done\n");
    printf("------------------------------\n");
}

//=============================================================================
/*
void TESTFINDWHOLEWORD(const char *enc, const char *kw, const int rc)
{
    int retc = 0;
    int finalResult = 0;

    printf("\n    Test: Search for \"%s\" in \"%s\" : \n", PRINTNULL(kw), PRINTNULL(enc));
    printf("  Expect: result %d : \n", rc);

    retc = FindWholeWord(enc, kw);

    printf("Received: result %d : ", retc);
    if (retc == rc)
    {
        finalResult = 1;
        printf("[OK]\n");
    }
    else
    {
        finalResult = 0;
        printf("[FAILED]\n");
    }
    assert(finalResult == 1);
}

void TestFindWholeWord()
{
    printf("\n");
    printf("------------------------------\n");
    printf("Test FindWholeWord function\n");
    printf("------------------------------\n");

    TESTFINDWHOLEWORD(NULL, "", -1);
    TESTFINDWHOLEWORD("", NULL, -1);
    TESTFINDWHOLEWORD(NULL, NULL, -1);

    TESTFINDWHOLEWORD(msg1, msg1, 0);   // same string
    TESTFINDWHOLEWORD(msg1, "zyx", -1); // not found at all
    TESTFINDWHOLEWORD(msg1, "bc", -1);  // found at end with letter preceeding
    TESTFINDWHOLEWORD(msg1, "ab", -1);  // found at start with letter trailing
    TESTFINDWHOLEWORD("abcd", "bc", -1);// found in middle with preceeding and trailing letter

    // longer tests - "abc-def ghi.jkl mno pqr stu vwx yz?"
    TESTFINDWHOLEWORD(msg3, "abc", 0);
    TESTFINDWHOLEWORD(msg3, "bcd", -1);
    TESTFINDWHOLEWORD(msg3, "def", 0);
    TESTFINDWHOLEWORD(msg3, "abc-def", 0);
    TESTFINDWHOLEWORD(msg3, "yz", 0);
    TESTFINDWHOLEWORD(msg3, "yz?", 0);
    TESTFINDWHOLEWORD(msg3, "mno pqr", 0);


    printf("\n");
    printf("------------------------------\n");
    printf("Done\n");
    printf("------------------------------\n");
}
*/

//=============================================================================
void TESTCRACK(const char *enc, const char *kw, const int rc, const char *expected)
{
    char *msg = NULL;
    int retc = 0;
    int stringCompare = -1;
    int finalResult = 0;

    assert(expected != NULL);

    printf("\n    Test: \"%s\" by searching for %s : \n", PRINTNULL(enc), PRINTNULL(kw));
    printf("  Expect: \"%s\" returning %d : \n", expected, rc);

    retc = crack((char*)enc, (char*)kw, &msg);

    printf("Received: \"%s\" and %d : ", PRINTNULL(msg), retc);

    if (msg)
    {
        stringCompare = strcmp(expected, msg);
    }
    if ((retc == -1) && (rc == -1))
    {
        printf("[OK]");
        finalResult = 1;    // we're good
    }
    else if ((retc != -1) && (retc == rc) && (stringCompare == 0))
    {
        printf("[OK]");
        finalResult = 1;    // we're good
    }
    else
    {
        printf("[FAILED]");
        finalResult = 0;    // we're good
    }

    printf("\n");

    SAFEFREE(msg);

    assert(finalResult == 1);
}

void TestCrack()
{
    printf("\n");
    printf("------------------------------\n");
    printf("Test crack function\n");
    printf("------------------------------\n");

    TESTCRACK(NULL, "abc", -1, "");         // Test null encoded
    TESTCRACK("abc", NULL, -1, "");         // test null known
    TESTCRACK("abc", "abcd", -1, "");       // test known too long

    TESTCRACK(enc1, msg1, 25, msg1);        // test to ensure we find the whole word if the length is the same
    TESTCRACK(enc1, "ab", -1, msg1);        // test to ensure that we only find the whole word end 
    TESTCRACK(enc1, "bc", -1, msg1);        // test to ensure that we only find the whole word start 

    TESTCRACK(msg1, msg1, 0, msg1);
    TESTCRACK(enc2, msg1, 1, msg1);
    TESTCRACK(enc3, msg1, 21, msg1);
    TESTCRACK(enc4, msg1, 2, msg1);
    TESTCRACK(enc5, msg1, 24, msg1);

    TESTCRACK(msg2, "Hello", 0, msg2);
    TESTCRACK(msg2, "there", 0, msg2);
    TESTCRACK(msg2, "there.", 0, msg2);

    TESTCRACK(enc6, "DOOOOOM", -1, "");
    TESTCRACK(enc6, "Hello", 25, msg2);
    TESTCRACK(enc6, "there", 25, msg2);
    TESTCRACK(enc6, "there.", 25, msg2);

    TESTCRACK(enc7, "Hello", 21, msg2);
    TESTCRACK(enc7, "there", 21, msg2);
    TESTCRACK(enc7, "there.", 21, msg2);

    printf("\n");
    printf("------------------------------\n");
    printf("Done\n");
    printf("------------------------------\n");
}
