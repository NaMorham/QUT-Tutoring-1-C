#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <assert.h>

#ifndef GET_MAX
#define GET_MAX(a, b) (a > b ? a : b)
#endif

#ifndef byte
typedef unsigned char byte;
#endif

int GetMaxChars(int arraysize)
{
    int sz = arraysize / 8; // 8 bits per char, 1 bit per pixel
    return GET_MAX(0, sz);
}


/**
 */
const char *BinString(const byte src, char *buf, const int bufSize)
{
    assert(buf != NULL);
    assert(bufSize > 8);
    memset(buf, 0, bufSize * sizeof(char));
    byte val = src;
    int i = 0;
    for (; i < 8; ++i)
    {
        static const byte mask = 0x80;
        buf[i] = ((mask & val) == mask ? '1' : '0');
        val = val << 1;
    }
    return buf;
}

const static byte pixMask = 0xFE;
const static byte bitMask = 0x01;

/**
 */
void GetBitVals(const byte src, byte *pPixel, byte *pBit)
{
    if (pPixel)
    {
        byte pix = src & pixMask;
        *pPixel = pix;
    }
    
    if (pBit)
    {
        byte bit = src & bitMask;
        *pBit = bit;
    }
}

/**
 */
const byte SetMessageBit(const byte pixel, const byte messageBit)
{
    byte result = 0;
    result = (byte)((pixel & pixMask) | (messageBit & bitMask));
    return result;
}

/**
 * 
 */
int GetCharFromArray(char *pixels, const int pixelsSize, char *pChar)
{
    int idx = 0;
    char result = 0;
    char c = 0;

    if (pixels == NULL)
    {
        return -1;  // nothing to read from
    }
    if (pChar == NULL)
    {
        return -1;  // nothing to write to
    }
    if (GetMaxChars(pixelsSize) < 1)
    {
        return -1;  // not enough to read from 
    }

    // loop through 8 chars in the pixel array
    for (idx = 0; idx < 8; ++idx)
    {
        // extract the last bit, 
        c = pixels[idx];
        c &= bitMask;

        // bitwise or with result
        if (idx > 0)
        {
            // shift left if not the first loop
            result <<= 1;
        }

        result |= c;
    }
    *pChar = result;
    return 0;
}


/**
*
*/
int PutCharIntoArray(char *pixels, const int pixelsSize, char msgChar)
{
    int idx = 0;
    char result = 0;
    char c = 0;
    char maskC = 0;
    char pix = 0;

    if (pixels == NULL)
    {
        return -1;  // nothing to read from
    }
    if (pixelsSize < 8)
    {
        return -1; // not enough room for a character
    }
    if (GetMaxChars(pixelsSize) < 1)
    {
        return -1;  // not enough to read from 
    }

    // loop through the array backwards
    for (c = msgChar, idx = 7; idx >= 0; --idx)
    {
        pix = pixels[idx];      // the pixel (image component) to hold the encoded bit
        pix &= pixMask;         // the pixel with the last bit set to 0

        // now we need to get the right most bit
        maskC = c & bitMask;    // the msg char with all but the last bit as 0

        // combine the 2
        pixels[idx] = pix | maskC;
        c >>= 1;
    }
    return 0;
}
