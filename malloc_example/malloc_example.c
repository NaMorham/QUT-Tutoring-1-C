#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define INT_ARRAY_SIZE     10

void DumpArray(const int *pArray, const int size);

int main(int argc, char *argv[])
{
    int idx = 0;            // index into our array
    int *pIntArray = NULL;  // pArray is a pointer to null

    printf("NULL pointer to array -->\n");
    DumpArray(pIntArray, INT_ARRAY_SIZE);

    pIntArray = (int*) malloc(INT_ARRAY_SIZE * sizeof(int));    // if it works pIntArray is now pointing at a block of memory allocated for 10 ints

    // safety check - ALWAYS DO THIS
    if (pIntArray == NULL)
    {
        fprintf(stderr, "Out of memory error, could not allocate %d integers", INT_ARRAY_SIZE);
        return 1;    // out of memory so bail
    }

    printf("Allocated array -->\n");
    DumpArray(pIntArray, INT_ARRAY_SIZE);

    // pIntArray is the right size, but it is full of junk now
    // set the memory to be empty
    memset(pIntArray, 0, sizeof(int)*INT_ARRAY_SIZE);

    printf("Intiialised array -->\n");
    DumpArray(pIntArray, INT_ARRAY_SIZE);

    // fill it with a loop
    // even though it is a pointer, because we allocated room for multiple ints it is also an array
    for (idx = 0; idx < INT_ARRAY_SIZE; ++idx)
    {
        pIntArray[idx] = idx * 10;
    }

    printf("Populated array -->\n");
    DumpArray(pIntArray, INT_ARRAY_SIZE);

    // we can also access it using pointers
    for (idx = 0; idx < INT_ARRAY_SIZE; ++idx)
    {
        int *pItem = pIntArray + idx;   // this is a pointer to th idx(th) item in pIntArray
        int item = (*pItem);            // set item to the value pointed at by pItem
        item /= 2;                      // item = item / 2
        (*pItem) = item;                // update the item pointed at by pItem to be equal to item
    }

    printf("Modified array -->\n");
    DumpArray(pIntArray, INT_ARRAY_SIZE);

    free(pIntArray);

//----------------------------------------------------------------------------
    // DANGEROUS - we are still pointing at memory that may be in use elsewhere
    printf("Freed array (DANGEROUS) -->\n");
    DumpArray(pIntArray, INT_ARRAY_SIZE);
//----------------------------------------------------------------------------

    pIntArray = NULL;   // not needed, but a good habit

    printf("NULL pointer to array -->\n");
    DumpArray(pIntArray, INT_ARRAY_SIZE);

    return 0;
}

void DumpArray(const int *pArray, const int size)
{
    int i = 0;

    printf("Dump array:\n");
    if (pArray == NULL)
    {
        printf("Array pointer is NULL\n\n");
        return;
    }
    if (size < 1)
    {
        printf("An array of size %d is invalid\n\n", size);
        return;
    }
    for (i = 0; i < size; ++i)
    {
        printf("  [%3d] = %d\n", i, pArray[i]);
    }
    printf("\n");
}
