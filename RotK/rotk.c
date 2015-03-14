#include <stdio.h>
#include <stdlib.h>

int rot_k(char* message, int k)
{
    printf("a) k = %d\n", k);
    if (message == NULL)
    {
        return -1; // nothing to rotate
    }
    if ((k < 0) || (k >= 26))
    {
        k %= 26;
    }
    printf("b) k = %d\n", k);
    if (k < 0)
    {
        k += 26;
    }
    printf("c) k = %d\n", k);


    printf("\n");
    return 0;
}
