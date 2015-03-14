#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void TestPointers();

int main(int argc, char *argv[])
{
    TestPointers();

    return 0;
}

void TestPointers()
{
    char buf[257];
    memset(buf, 0, sizeof(char) * 257);

    char *p = buf;

    strncpy(buf, "AAA This is a test string that is long but does not fill the buffer.", 256);
    *p = 'B';
    const char const *p2 = buf + 1;
    const char *p3 = buf + 1;
    char const *p4 = buf + 1;

    // *p2 = 'C';    // compile error - cannot change content
    p2++;

    //*p3 = 'D';    // compile error - cannot change content
    p3++;

    //*p4 = 'E';    // compile error - cannot change content
    p4++;

    int foo = 0;
}
