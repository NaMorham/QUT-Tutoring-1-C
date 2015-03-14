#include "assignment_1.h"

//  COPY EVERYTHING IN AND HOPE IT WORKS 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int pixelMessage(char* imageArray, char character, int arraysize);

const char *BinString(const char src, char *buf, const int bufSize)
{
    assert(buf != NULL);
    assert(bufSize > 8);
    memset(buf, 0, bufSize * sizeof(char));
    char val = src;
    int i = 0;
    for (; i < 8; ++i)
    {
        static const char mask = 0x80;
        buf[i] = ((mask & val) == mask ? '1' : '0');
        val = val << 1;
    }
    return buf;
}

/*========================================================*/


int embed(char* image_data, int data_length, char* message, char** encoded)
{
/*

*/	
	char* dataArray = NULL;
	char* encArray = NULL;
	int idx = 0;
	int messageidx = 0;
	size_t messagelen = 0;
	
	messagelen = strlen(message);
	if (data_length/8 < messagelen)
	{
		printf("Message wont fit\n");
		return -1;
	}
	
	encArray = (char*)malloc(sizeof(char)*data_length);
	if (encArray == NULL)
	{// checking that the array has been allocated 
		printf("Couldnt allocate memory, possibly out of memory\n");
		return -1;
	}
	
	if (memcpy(encArray,image_data,sizeof(char)*data_length) == NULL)
	{
		printf("Could not copy memory\n");
		free(encArray);
		encArray = NULL;
		return -1;
	}
	
	for (idx; idx<data_length; idx += 8,++messageidx)
	{
		char c = message[messageidx];
		dataArray = image_data + idx; // gets the next eight pixels
		if(pixelMessage(encArray, c,data_length-idx) != 0)
		{
			printf("Failed to embed\n");
			free(encArray);
			return -1;
		}
		if(messageidx >= messagelen)
		{
			printf("Message has been coded\n");
			break;
		}
	}
	
	*encoded = encArray;
	return 0;
}

/*=======================================*/
static const char pixmask = 0xfe; // 1111 1110
static const char messagemask = 0x01; // 0000 0001
char BolAdder(char pixelbit, char messagebit)
{
/*
mask off the first 7 bits of the byte A 
and the last bit of the message
and bitwise and these together
*/
	
	char pixeltemp = 0;
	char messagetemp = 0;
	char combined = 0;
	
	pixeltemp = pixelbit & pixmask;
	messagetemp = messagebit & messagemask;
	combined = pixeltemp | messagetemp;
	
	printf("pixtemp %02x, mtemp %02x , combined %02x\n", pixeltemp,messagetemp,combined);
		
	return combined;
	
}

/*=======================================*/
int pixelMessage(char* imageArray, char character, int arraysize)
{
/*
takes the pixel array and a character and calls BolAdder 8 times
*/

	char idx1 = 0;
	char charIdx = 0;
	char result = 0;
	char pixel = 0;
	char newPixel = 0;
	char idx2 = 0;
	char tempResult = 0;
	char buff [9] = {0,0,0,0,0,0,0,0,0};
	
	if (arraysize < 8) // no room for a full character
	{
		printf("Not enough room for character\n");
		return -1;
	}
	
	
	result = character;
	// for each pixel going backwards ie start at 7
		//get the pixel 
		//mask the pixel
		//mask result and store
		//bitwise OR between masked result and masked pixel
		//shift result right
		//put new pixel into array
	for (idx1 = 7 ; idx1>=0 ; --idx1)
	{
		printf("result:%02x bin:%s\n",result,BinString(result,buff, 9));
		pixel = imageArray[idx1];
		pixel = pixel & pixmask; // care about everything but the last pixel
		tempResult = result & messagemask; // care about the last pixel nothing else
		newPixel = pixel | tempResult; // ORing the masked pixel with masked character
		result = result >> 1;
		imageArray [idx1] = newPixel;
		printf("result:%02x bin:%s\n\n",result,BinString(result,buff, 9));
	}
/*	
	for(charIdx = 7 ; idx1<8 && charIdx >= 0; ++idx1, --charIdx)
	{
			printf("charidx:%d idx1:%d pixel:%02x result:%02x\n",charIdx, idx1, pixel, result);
			pixel = imageArray[idx1];
			result = (character >> charIdx) & pixmask;
						
				printf("pixel:%s\n",BinString(pixel,buff, 9));
				
				printf("character:%s\n",BinString(character,buff, 9));
				
				printf("character:%s\n",BinString((character >> charIdx),buff, 9));
				
				printf("result:%s\n",BinString((character >> charIdx) & pixmask,buff, 9));
				printf("\n");
			//printf("result:%02x shift:%02x\n",result, character >> charIdx);
			newPixel = BolAdder(pixel,result);
			imageArray [idx1] = newPixel;
			//printf("charidx:%d idx1:%d pixel:%02x result:%02x\n",charIdx, idx1, pixel, result);
			
	}
*/	
	return 0;
}

/*=============================================================*/
/*=============================================================*/
int extract(char* image_data, int data_length, char** message)
{
	
	
	
	
	
return 0;
}

/*=======================================*/



/*=======================================*/



