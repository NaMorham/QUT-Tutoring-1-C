#include <stdio.h>


void DumpArgs(int argc, char *argv[]);

void TestPointers();

/*
 */
int main(int argc, char *argv[])
{
    DumpArgs(argc, argv);

    /* parse the args */
    if (argc <= 1)
    {
        fprintf(stderr, "Invalid number of arguments passed to application, needs a positive integer to check.\n");
        return 2;
    }
    else if (argc > 2)
    {
        fprintf(stderr, "Too many args passed to application, only one positive integer can be provided.\n");
        return 2;
    }

    /* we have 1 arg to parse */
    int num = 0;
    if (sscanf(argv[1], "%d", &num) != 1)
    {
        fprintf(stderr, "Invalid arg passed to application, must be a positive integer\n");
        return 2;
    }
    
    /* Check the arg for validity */
    if (num < 0)
    {
        fprintf(stderr, "Invalid value passed to application, must be a positive integer\n");
        return 2;
    }
    /* Special cases, 0, 1 & 2 are prime, no need to loop */
    if (num <= 2)
    {
        printf("%d is a prime\n", num);
        return 0;
    }

    int i = 2;
    int half = num / 2;
    for (; i <= half; ++i)
    {
        int mod = num % i;
#ifdef _DEBUG
        printf("Calc %d %% %d == %d\n", num, i, mod);
#endif
        if (mod == 0)
        {
            printf("%d is not prime\n", num);
            return 1;
        }
    }

    printf("%d is a prime\n", num);
#ifdef _DEBUG
    getch();
#endif
    return 0;
}

#ifdef _DEBUG
void DumpArgs(int argc, char *argv[])
{
    int i = 0;
    printf("%s\nArgs: \n", argv[0]);
    for (i = 1; i < argc; ++i)
    {
        printf("    [%2.d] %s\n", i, argv[i]);
    }
    printf("\n");
}
#else
void DumpArgs(int argc, char *argv[])
{
}
#endif
