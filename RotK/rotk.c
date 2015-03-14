#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Utility funcs
#define PRINTC(a) (isprint((unsigned char)a) ? a : '.')
#define PRINTNULL(str) (str == NULL ? "NULL" : (*str == 0 ? "EMPTY" : str))
#define SAFEFREE(ptr) { if (ptr) { free(ptr); ptr = NULL; }}
#define TORFSTR(b) (b ? "true" : "false");

int rot_k(char* message, int k)
{
    char c = 0;
    char rotc = 0;
    char adj = 0;
    size_t len = 0;
    size_t idx = 0;
    size_t count = 0;

    if (message == NULL)
    {
        return -1;  // nothing to rotate
    }

    len = strlen(message);
    if (len < 1)
    {
        return -1;  // nothing to rotate
    }

    if ((k < 0) || (k >= 26))
    {
        k %= 26;
    }

    while (k < 0)
    {
        k += 26;    // adjust so only vals are positive
    }
//    printf("Rotate by k = %d", k);

    // for each char in message
    for (idx = 0; idx < len; ++idx)
    {
//        if ((idx % 3) == 0)
//        {
//            printf("\n");
//        }
        c = message[idx];
//        printf("[0x%02x '%c'] -> ", c, PRINTC(c));
        if (('a' <= c) && (c <= 'z'))
        {
            adj = 'a';
            ++count;
        }
        else if (('A' <= c) && (c <= 'Z'))
        {
            adj = 'A';
            ++count;
        }
        else
        {
//            printf("[0x%02x '%c'], ", c, PRINTC(c));
            continue; // not in our enc list
        }
        rotc = c - adj;
        rotc += k;
        rotc %= 26;
        rotc += adj;
        message[idx] = rotc;
//        printf("[0x%02x '%c'], ", rotc, PRINTC(rotc));
    }

//    printf("\n");
    return count;
}

// return true is ch is in the ranga 'a' <= ch <= 'z' || 'A' <= ch <= 'Z'
#define ISLETTER(ch) (((('A' <= ch) && (ch <= 'Z')) || (('a' <= ch) && (ch <= 'z'))) ? 1 : 0 )

int FindWholeWord(const char *msg, const char *find)
{
    char *foundPtr = NULL;
    size_t msgLen = 0;
    size_t findLen = 0;

    if ((msg == NULL) || (find == NULL))
    {
        return -1;      // cant find anything in null
    }

    msgLen = strlen(msg);
    findLen = strlen(find);
    if (msgLen < findLen)
    {
        return -1;  // cant find a long message in a short one
    }

    foundPtr = strstr(msg, find);
    if (foundPtr == NULL)
    {
        return -1;  // not found
    }

    // quick exit if found and same length -> must be the whole word
    if (msgLen == findLen)
    {
        return 0;
    }

    if ((foundPtr != msg) && ISLETTER(*(foundPtr - 1)))
    {
        // found a letter before the start
        return -1;
    }

    // calculate the 'end' ptr (i.e. the pointer to the null at the end of both strings
    // if not the same check the next letter
    if (((foundPtr + findLen) != (msg + msgLen)) && ISLETTER(*(foundPtr + findLen)))
    {
        // found a letter after the word
        return -1;
    }
    return 0;
}

int crack(char* encoded, char* known_word, char** message)
{
    int rot = 0;
    size_t idx = 0;
    char *buf = NULL;
    char *rotKey = NULL;

    if ((encoded == NULL) || (known_word == NULL) || (message == NULL))
    {
        return -1;      // null pointer issue
    }
    if (*message != NULL)
    {
        return -1;      // may already be allocated
    }

    for (idx = 0; idx < 26; ++idx)
    {
        rotKey = _strdup(known_word);
        if (rotKey == NULL)
        {
            return -1;  // Out of memory
        }

        if (rot_k(rotKey, idx) == -1)
        {
            SAFEFREE(rotKey);   // Failed to rotate
            return -1;
        }

        if (FindWholeWord(encoded, rotKey) == 0)
        {
            rot = (26 - idx) % 26;
            buf = _strdup(encoded);
            if (buf == NULL)
            {
                return -1;      // out of memory
            }
            if (rot_k(buf, rot) == -1)
            {
                // should never happen, but just in case
                SAFEFREE(buf);
                SAFEFREE(rotKey);
                return -1;
            }
            *message = buf;
            return rot;      // we found it
        }

        SAFEFREE(rotKey);
    }


    return -1;
}
