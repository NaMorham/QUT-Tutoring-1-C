#include <stdlib.h>
#include <stdio.h>
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

const char *TrimSpace(const char *str, int len, char *buf, int bufSize)
{
    int size = 0;
    int start = 0;
    int end = len-1;

    if ((str == NULL) || (*str == 0))
    {
        return NULL;    // nothing to trim
    }
    if (len < 1)
    {
        return NULL;    // nothing to trim
    }
    if (buf == NULL)
    {
        return NULL;    // nowhere to put result
    }
    if (bufSize < 1)
    {
        return NULL;    // nowhere to put result
    }

    // loop from start looking for any char that is not white space
    for (start = 0; start < len; ++start)
    {
        char c = str[start];

        if ((c != ' ') && (c != '\t') && (c != '\v'))
        {
            break;
        }
    }

    // loop from back looking for any char that is not white space
    for (end = len - 1; end > start; --end)
    {
        char c = str[end];

        if ((c != ' ') && (c != '\t') && (c != '\v'))
        {
            break;
        }
    }

    size = end - start + 1;
    if (size >= bufSize)
    {
        return NULL;
    }

    memset(buf, 0, sizeof(char)*bufSize);

    memcpy(buf, str + start, sizeof(char)*size);

    return buf;
}

int charToInt(const char c)
{
    return c - '0';
}

// return 
bool StringToInt(const char *str, int len, int *pInt)
{
    int idx = 0;    // position in the string
    int result = 0;
    int signMultiplier = 1;
    int numCount = 0;
    bool rc = true;
    char *buf = NULL;

    if (pInt == NULL)
    {
        return false; // nowhere to put the result
    }
    if ((str == NULL) || (*str == 0))
    {
        return false; // nothing to read from
    }

    // trim whitespace
    buf = (char*)malloc(sizeof(char)*(len + 2));
    if (buf == NULL)
    {
        return false;
    }
    memset(buf, 0, sizeof(char)*(len + 2));
    if (TrimSpace(str, len, buf, len+1) == NULL)
    {
        // we cannot trim, so cleanup and bail
        free(buf);
        buf = NULL;
        return false;
    }

    // check for a sign indicator
    if (buf[0] == '-')
    {
        signMultiplier = -1;
        ++idx;
    }
    else if (buf[0] == '+')
    {
        // nothing to do really
        ++idx;
    }

    while (idx < len)
    {
        char ch = buf[idx];

        // check for a valid char
        if ((ch < '0') || (ch > '9'))
        {
            rc = false;
            break; // invalid char found
        }

        // we have a number 
        if (numCount > 0)
        {
            result *= 10;
        }
        result += charToInt(ch);
        ++numCount;
        ++idx;
    }

    free(buf);
    buf = NULL;

    if (rc)
    {
        result *= signMultiplier;
        *pInt = result;
    }
    return rc;
}

