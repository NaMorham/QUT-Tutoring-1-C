#include <stdio.h>
#include <stdlib.h>
#ifdef _ALLOW_STRING_H_
#include <string.h>
#endif
#include <assert.h>

#define GETMIN(a, b) (a < b ? a : b)

// assumes the buffer is not NULL and size is valid
static void *ClearMem(void *buf, const unsigned char fill, const size_t sz)
{
#ifdef _ALLOW_STRING_H_
    assert(buf != NULL);
    assert(sz > 0);
    return memset(buf, fill, sz);
#else
    size_t idx = 0;
    assert(buf != NULL);
    assert(sz > 0);
    
    for (idx = 0; idx < sz; ++idx)
    {
        ((char*)buf)[idx] = fill;
    }
    return buf;
#endif
}

// assumes the string is not NULL and properly terminated
static const size_t GetStringLength(const char *str)
{
#ifdef _ALLOW_STRING_H_
    assert(str != NULL);
    return strlen(str);
#else
    size_t idx = 0;
    while (str[idx++] != 0);
    return idx-1; // dont count the 0
#endif
}

// assumes the string is not NULL and properly terminated
static char *FindFirstChar(const char *str, const char findChar)
{
#ifdef _ALLOW_STRING_H_
    assert(str != NULL);
    return strchr(str, findChar);
#else
    char *found = NULL;
    size_t idx = 0;
    size_t len = GetStringLength(str);
    // loop through until we find the char
    for (idx = 0; idx < len; ++idx)
    {
        if (str[idx] == 0)
        {
            // not found
            break;
        }
        if (str[idx] == findChar)
        {
            // found it
            found = (char*)str + idx; // BLECCH - Casting away const is BAAAAD
            break;
        }
    }
    return found;
#endif
}

// assumes the string is not NULL and properly terminated
static char *AllocAndCopyString(const char *str)
{
#ifdef _ALLOW_STRING_H_
    assert(str != NULL);
    return _strdup(str);
#else
    size_t len = 0;
    size_t idx = 0;
    char *newStr = NULL;

    assert(str != NULL);
    len = GetStringLength(str);

    newStr = (char*)malloc(len + 1);
    if (newStr == NULL)
    {
        return NULL; // failed to allocate
    }
    ClearMem(newStr, 0, len + 1); // 0 fill
    for (idx = 0; idx < len; ++idx)
    {
        newStr[idx] = str[idx];
    }
    return newStr;
#endif
}

static const char XORChar(const char a, const char b)
{
    return (a == b ? '0' : '1');
}

// assumes good pointers and keysize is <= data len
static void XORKey(char *data, const char *key, const int keySize)
{
    int idx = 0;
    char c = 0;

    assert(data != NULL);
    assert(key != NULL);
    assert(keySize >= 1);

    for (idx = 0; idx < keySize; ++idx)
    {
        c = data[idx];
        data[idx] = XORChar(c, key[idx]);
    }
}

#define SAFEFREE(ptr) { if (ptr) { free(ptr); ptr = NULL; } }

int checksum(char* data_string, char* key_string, char** checksum_string)
{
    size_t idx = 0;
    size_t keyLen = 0;
    size_t dataLen = 0;
    size_t last = 0;
    char *pos = NULL;
    char *data = NULL;

    if (data_string == NULL || key_string == NULL || checksum_string == NULL)
    {
        printf("NULL pointer passed to checksum function.\n");
        return -1;
    }
    if (*data_string == 0)
    {
        printf("Empty string passed as data\n");
        return -1;
    }
    if (*key_string == 0)
    {
        printf("Empty string passed as key\n");
        return -1;
    }
    if (*checksum_string != NULL)
    {
        printf("checksum string pointer may already be allocated\n");
        return -1;
    }

    // because data_string is possibly REALLY a const (STUPID HEAD SHOULD MAKE THIS CONST) we need a copy to mangle
    data = AllocAndCopyString(data_string);
    if (data == NULL)
    {
        printf("Could not allocate memory for data string.\n");
        return -1;
    }

    dataLen = GetStringLength(data);
    keyLen = GetStringLength(key_string);
    last = dataLen - keyLen;
    printf("Final string = %s\n", data + last);

    printf("data_string = \"%s\"\n", data);

    pos = FindFirstChar(data, '1');
    if (pos == NULL)
    {
        printf("No 1's in data string, return the last %d chars of data_string\n", (int)keyLen-1);
        SAFEFREE(data);
        *checksum_string = AllocAndCopyString(data_string + last + 1);
        if (*checksum_string == NULL)
        {
            printf("Could not allocate memory for checksum.\n");
            return -1;
        }
        return 0;
    }

    printf("\nLoop through adjusting data\n---------------------------");
    while (pos)
    {
        idx = pos - data;
        if (idx > last)
        {
            // we've reached end
            break;
        }
        printf("\nFound '1' at idx = %d\n", (int)idx);
        printf("1. chksum: %s\n", data);
        printf("      key: %c%*s%s\n", (idx ? ' ' : '\b'), (int)idx-1, " ", key_string);
        XORKey(pos, key_string, keyLen);
        printf("2. chksum: %s\n", data);
        pos = FindFirstChar(data, '1');
    }
    // we have reduced the list to a small group 
    // return the last keyLen-1 chars
//*
    if (idx == last && 0)
    {
        printf("\n1. chksum: %s\n", data);
        printf("      key: %c%*s%s\n", (idx ? ' ' : '\b'), (int)idx - 1, " ", key_string);
        XORKey(data + last, key_string, keyLen);
        printf("2. chksum: %s\n", data);
    }
//*/
    *checksum_string = AllocAndCopyString(data + last + 1);
    SAFEFREE(data);
    if (*checksum_string == NULL)
    {
        printf("Could not allocate memory for checksum.\n");
        return -1;
    }

    printf("Found checksum is \"%s\"\n\n", *checksum_string);
    return 0;
}

