#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

static const char PixelMask=0xfe;		//Binary 11111110
static const char BitMask=0x01;		//Binary 00000001
int EmbedChar(int arrsize, char eb, char* source, char* dest);

#define PRINTC(a) (isprint((unsigned char)a)?a:'.')

const char *BinString(const unsigned char src, char *buf, const int bufSize)
{
    assert(buf != NULL);
    assert(bufSize >= 8);
    memset(buf, 0, bufSize * sizeof(char));
    unsigned char val = src;
    int i = 0;
    for (; i < 8; ++i)
    {
        static const unsigned char mask = 0x80;
        buf[i] = ((mask & val) == mask ? '1' : '0');
        val = val << 1;
    }
    return buf;
}
// Image Data Manipulation Functions
/**
 * This function is responsible for embedding a message into an array of image data and placing the resulting array into encoded
 *
 * @param char* image_data  - The image data array which will be used to embed the message
 * @param int data_length   - The length of the image data array
 * @param char* message     - The message to be encoded
 * @param char** encoded    - A new array containing the image data embedded with message
 *
 * @return int - the numeric value 0 on success, -1 if the message is too large for the image data array
 */
int embed(char* image_data, int data_length, char* message, char** encoded)
{
	int idx;
	int mesidx;
	char* localdata;
    int msglen = 0;

    msglen = (int)strlen(message);
	if ((data_length/8) < (msglen+1))
	{
		printf("Not enough room!!\n");
		return -1;
	}
	if (image_data==NULL)
	{
		printf("No data available.\n");
		return -1;
	}

	localdata=malloc(data_length*sizeof(char));	

	if (localdata==NULL)
	{
		printf("Out of memory! \n");
		return -1;
	}
	memcpy(localdata, image_data, data_length*sizeof(char));

	/*
    for(idx=0, mesidx=0; idx<data_length; idx+=8, mesidx++)
	{
        if (mesidx < data_length)
        {
            if (EmbedChar(data_length, message[mesidx], image_data + idx, localdata + idx) == -1)
            {
                printf("Failed to embed a character... :(\n");
                free(localdata);
                localdata = NULL;
                return -1;
            }
        }
        else
        {
            // should not need to do anything
        }
	}
    /*/
    for (idx = 0, mesidx = 0; mesidx < msglen; idx += 8, mesidx++)
    {
        if (EmbedChar(data_length-idx, message[mesidx], image_data + idx, localdata + idx) == -1)
        {
            printf("Failed to embed a character... :(\n");
            free(localdata);
            localdata = NULL;
            return -1;
        }
    }
    // trailing null
    if (EmbedChar(data_length-idx, 0x00, image_data + idx, localdata + idx) == -1)
    {
        printf("Failed to embed a character... :(\n");
        free(localdata);
        localdata = NULL;
        return -1;
    }
    //*/
	*encoded=localdata;
	localdata=NULL;
	return 0;
}


int MaskBit(char Pixel, char Bit, char* Output)
{
	char temppixel=0;
	char tempbit=0;

    char buff[9];

    buff[8] = 0;

	if (Output==NULL)
	{
		return -1;
	}
	
    temppixel = Pixel&PixelMask;
    tempbit = Bit&BitMask;
	*Output=temppixel|tempbit;
	return 0;

}

int EmbedChar(int arrsize, char eb, char* source, char* dest)
{
	int idx;
	char pixel;
	char bitshift;
	char buff[9];
	buff[8]=0;	
	bitshift=eb;

	if (source==NULL || dest==NULL)
	{
		printf("Invalid Data! \n");
		return -1;
	}
	if (arrsize<8)
	{
		printf("Array to small!\n");
		return -1;
	}
	

	for (idx=0; idx<8; idx++)
	{
		pixel=source[idx];
		MaskBit(pixel, bitshift, dest+idx);
		bitshift>>=1;
		bitshift&=0x7f;
	}
	return 0;
}


















