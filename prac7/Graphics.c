/*
 * Graphics.c
 *
 * Created: 20/12/2012 11:59:59 PM
 *  Author: Michael a.k.a Not that there's anything wrong with that
 */

#include "Graphics.h"
#include "LCD.h"

#include <string.h>

/**
 */
static const int CalcOffsetAndShift(const int x, const int y, size_t *offset, size_t *shift);


/**
 */
unsigned char screenBuffer[LCD_BUFFER_SIZE]; // Our screen buffer array

void SetPixel(unsigned char x, unsigned char y, unsigned char value)
{
	unsigned char val = 0;
	unsigned char bit = 0x00;
	size_t offset = 0;
	size_t shift = 0;

    // find out where to set
    if (!CalcOffsetAndShift(x, y, &offset, &shift))
    {
        return;
    }

    // read the current value
    val = screenBuffer[offset];
    bit = (1 << shift);

	if (value)
	{
		// set the bit
		screenBuffer[offset] = val | bit;
	}
	else
	{
		// clear the bit
		screenBuffer[offset] = val & ~bit;
	}
}

void DrawLine(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2)
{

}

void PresentBuffer(void) {
	// (Hint: writes every byte of the buffer to the LCD)
	size_t idx = 0;
	unsigned char val = 0;

	LCDPosition(0, 0);
	for (idx = 0; idx < LCD_BUFFER_SIZE; ++idx)
	{
		val = screenBuffer(idx);
		LCDWrite(LCD_D, val);
	}
}

void ClearBuffer(void) {
	memset(screenBuffer, 0, sizeof(unsigned char)LCD_BUFFER_SIZE);
}

void DrawBall(unsigned char x, unsigned char y){

}

/**
* Extend this file with whatever other graphical functions you may need
*	Remember to include the declaration of any new functions in "Graphics.h"
*/

/**
 */
static const int CalcOffsetAndShift(const int x, const int y, size_t *offset, size_t *shift)
{
	if ((x < 0) || (x >= LCD_X) || (y < 0) || (y >= LCD_Y))
    {
        return -1;
    }
    if ((offset == NULL) || (shift == NULL))
    {
        return -1;
    }

    *offset = x + ((int)(y / 8))*LCD_X;
    *shift = y % 8;

    return 0;
}

void DrawChar(const char c, const int x, const int y)
{
    size_t idx = 0;
    size_t bitIdx = 0;
    const unsigned char *chr = NULL;
    unsigned char ch = 0;
    byte bit = 0;
    byte mask = 0x01;

    chr = ASCII[c - ' '];

    for (idx = 0; idx < 5; ++idx)
    {
        ch = chr[idx];
        for (bitIdx = 0; bitIdx < 8; ++bitIdx)
        {
            bit = (ch >> bitIdx) & mask;
            if (bit)
            {
                SetPixel(x + idx, y + bitIdx);
            }
            else
            {
                ClearPixel(x + idx, y + bitIdx);
            }
        }
    }
}

void DrawString(const char *str, const int x, const int y)
{
    size_t idx = 0;
    size_t len = 0;
    char c = 0;
    int xPos = 0;
    int yPos = y;

    if (str == NULL)
    {
        return;
    }
    if ((x >= LCD_X) || (y >= LCD_Y))
    {
        return;
    }
    len = strlen(str);

    for (xPos = x, idx = 0; idx < len; xPos += 6, ++idx)
    {
        c = str[idx];
        switch (c)
        {
        case '\n':
            yPos += 9;
        case '\r':
            xPos = x-6; // -6 to offset the fact we update xPos immediately
            break;
        default:
            DrawChar(c, xPos, yPos);
        }
    }
}

