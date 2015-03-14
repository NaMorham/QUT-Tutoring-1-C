#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

extern int rot_k(char* message, int k);


int main(int argc, char *argv[])
{
    char msg1[] = "Hello there.";

    rot_k(msg1, 0);
    rot_k(msg1, 1);
    rot_k(msg1, 26);
    rot_k(msg1, -1);
    rot_k(msg1, 50);
    rot_k(msg1, -50);

    return 0;
}
