#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <assert.h>

/**
 * compare 2 values and return the larger
 */
#ifndef GET_MAX
#define GET_MAX(a, b) (a > b ? a : b)
#endif

/**
 * define a byte type if it is not already available
 */
#ifndef byte
typedef unsigned char byte;
#endif

/**
 * Calculate the maximum number of characters that can be stored in the image array
 *
 * @param arraysize - [in] the number of chars in the image array
 * @return the maximum number of characters able to be stored
 */
int GetMaxChars(int arraysize)
{
    int sz = arraysize / 8; // 8 bits per char, 1 bit per pixel
    return GET_MAX(0, sz);
}


/**
 * Populate a character array with a binary representation of the specified byte
 *
 * @param src - [in] the byte to represent
 * @param buf - [out] a pre allocated array to store the generated string
 * @param bufSize - [in] the available number of characters in the buffer
 * @return the populated string
 * @note This function will exert with an assertion failure if the buffer is invalid or too small
 */
const char *BinString(const byte src, char *buf, const int bufSize)
{
    assert(buf != NULL);
    assert(bufSize >= 8);
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

/**
 * Binary value used to mask off the 7 most significant bits (clearing the LSB)
 */
const static byte pixMask = 0xFE;
/**
* Binary value used to mask off the least significant bit (clearing 7 most significant bits)
*/
const static byte bitMask = 0x01;

/**
 * Extract the pixel (7 bits) and bit (1 bit) values from a src byte
 *
 * @param src - [in] the source byte to extract values from
 * @param pPixel - [out] a pointer to a character to receive the extracted pixel
 * @param pBit - [out] a pointer to a character to receive the extracted bit
 */
void GetBitVals(const byte src, byte *pPixel, byte *pBit)
{
    if (pPixel)
    {
        byte pix = src & pixMask;   // Mask off the part of the pixel to keep
        *pPixel = pix;              // return it
    }
    
    if (pBit)
    {
        byte bit = src & bitMask;   // Mask off the LSB of the bit/message
        *pBit = bit;                // return it
    }
}

/**
 * Set (combine) a pixel and a bit value.
 * 
 * @param pixel [in] - the image data to be masked and merged.
 * @param messageBit [in] - a byte to extract the least significant bit and merge with the pixel
 * 
 * @return the combined pixel and bit
 */
const byte SetMessageBit(const byte pixel, const byte messageBit)
{
    byte result = 0;
    result = (byte)((pixel & pixMask) | (messageBit & bitMask)); // mask and combine the bit and pixel
    return result;
}

/**
 * Extract a single character from an array of pixels
 *
 * @param pixels - [in] an array of at least 8 pixels to extract a character from
 * @param pixelsSize - [in] the number os chars in the array
 * @pChar - [out] a pointer to a character to recieve the extracted character
 * @return 0 if successful and -1 if failed
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
* Embed a single character into an array of pixels
*
* @param pixels - [in/out] an array of at least 8 pixels to recieve the embedded character
* @param pixelsSize - [in] the number of chars in the array
* @msgChar - [in] a character to embed in the array
* @return 0 if successful and -1 if failed
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
    for (c = msgChar, idx = 0; idx < 8; ++idx)
    {
        pix = pixels[idx];      // the pixel (image component) to hold the encoded bit
        pix &= pixMask;         // the pixel with the last bit set to 0

        // now we need to get the right most bit
        maskC = c & bitMask;    // the msg char with all but the last bit as 0

        // combine the 2
        pixels[idx] = pix | maskC;
        c >>= 1;    // shift right for the next bit
    }
    return 0;
}

