#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int embed(char* image_data, int data_length, char* message, char** encoded);
int pixelMessage(char* imageArray, char character, int arraysize);
int arrayCompare(char* actualEncoded, char* expectedEncoded, size_t arraysize);

/*
int main()
{
	// this is the expected data from one of the AMS outputs
	//char* expected_encoded []  = 0x00;
	char expected_encoded [] = {0x4a, 0x5d, 0x3c, 0x2a, 0x26, 0x59, 0x41, 0x4a, 0x77, 0x5c, 0x0d, 0x64, 0x2a, 0x3d, 0x1d, 0x7a, 0x27, 0x14, 0x08, 0x3a, 0x14, 0x53, 0x6b, 0x0e, 0x14, 0x25, 0x0c, 0x68, 0x59, 0x0d, 0x49, 0x54, 0x64, 0x00, 0x44, 0x26, 0x02, 0x24, 0x60, 0x14, 0x5f, 0x34, 0x36, 0x1a, 0x63, 0x1c, 0x2b, 0x73, 0x55, 0x76, 0x1b, 0x13, 0x71, 0x25, 0x1d, 0x73, 0x42, 0x37, 0x7c, 0x5d, 0x31, 0x43, 0x50, 0x0a, 0x18, 0x19, 0x4b, 0x6f, 0x58, 0x08, 0x2a, 0x66, 0x6a, 0x7f, 0x14, 0x71, 0x6d, 0x21, 0x53, 0x1e, 0x79};
	// this is the data from the image used in the above test
	//char* imagedata []  = 0x00;
	char imagedata [] = {0x4a, 0x5d, 0x3c, 0x2b, 0x27, 0x58, 0x40, 0x4a, 0x77, 0x5d, 0x0c, 0x65, 0x2b, 0x3c, 0x1c, 0x7a, 0x26, 0x14, 0x08, 0x3a, 0x15, 0x52, 0x6a, 0x0f, 0x14, 0x24, 0x0d, 0x68, 0x59, 0x0d, 0x49, 0x55, 0x65, 0x01, 0x45, 0x26, 0x02, 0x25, 0x61, 0x15, 0x5f, 0x34, 0x36, 0x1a, 0x63, 0x1C, 0x2b, 0x73, 0x55, 0x76, 0x1b, 0x13, 0x71, 0x25, 0x1d, 0x73, 0x42, 0x37, 0x7c, 0x5d, 0x31, 0x43, 0x50, 0x0a, 0x18, 0x19, 0x4b, 0x6f, 0x58, 0x08, 0x2a, 0x66, 0x6a, 0x7f, 0x14, 0x71, 0x6d, 0x21, 0x53, 0x1e, 0x79, 0x2f};
	
	int datalength =  0;
	
	
	char msg [] = "bear";
	char* actual_encoded = NULL;
	int bed = 0;
	
	datalength = sizeof(imagedata)/sizeof(char);
	bed = embed(imagedata, datalength, msg, &actual_encoded); 
	if (arrayCompare(actual_encoded, expected_encoded, datalength) == 0)// need a separate function that takes to char*'s and a size-t
	{	printf("FAILURE TO EMBED MESSAGE\n");
		return -1;
	}else 
	{	printf("SUCCESSFULLY ENCODED\n\n");
		//printf("EXPECTED IMAGE DATA\n\n %x",imagedata);
		//printf("ACTUAL IMAGE DATA\n\n %x",actual_encoded);
		return 0;
	}
	

return 0;
}
*/



// EMBED FUNCTION
int embed(char* image_data, int data_length, char* message, char** encoded)
{

    char* dataArray = NULL;
    char* encArray = NULL;
    int idx = 0;//index into the image array
    int idx1 = 0;// index into the message array
    size_t messagelen = 0;
    char currentChar = 0;

    if (image_data == NULL || encoded == NULL || message == NULL)
    {
        printf("NULL pointer passed.\n");
        return -1;
    }
	
	messagelen = strlen(message);
	if ((data_length/8) < (messagelen+1))
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
	
	//loop thru message one char at a time 
		//get location in array
		//calculate remaining size
		//pixel message 
	for (idx1=0; idx1<messagelen; ++idx1)// getting the next character of message
	{
		currentChar = message[idx1];// current message character
		printf("%c\n",currentChar);
		dataArray = encArray + idx;// current 8 bits of image data
		
		//printf("dataArray:%p ");
		
		if (pixelMessage(encArray,currentChar, data_length-idx) != 0)
		{
			printf("Failed to embed 1\n");
			if (encArray != NULL)
			{
				free(encArray);
				encArray = NULL;
				
			}
			return -1;
		}
        idx += 8;// getting the next 8 bits of image data

	}
	
	//pixel message trailing zero
	if (pixelMessage(encArray+idx,0, data_length-idx) != 0)
	{
		printf("Failed to embed 2\n");
		if (encArray != NULL)
		{
			free(encArray);
			encArray = NULL;
				
		}
		return -1;
	}

	
	*encoded = encArray;
	return 0;
}

/*=======================================*/

/*====================================================*/
int arrayCompare(char* actualEncoded, char* expectedEncoded, size_t arraysize)
{
	
	size_t idx = 0;
	char actchar = 0;
	char exptdchar = 0;
	size_t cntr = 0;
	
	for (idx; idx<arraysize; ++idx)
	{
		actchar = actualEncoded[idx];
		exptdchar = expectedEncoded[idx];
		printf("[%3d]  A:%02x == E:%02x	", idx, actchar, exptdchar);
		if(actchar == exptdchar)
		{
			printf("true\n");
			cntr++;
		}else
		{
			printf("false\n");
		}		
		
	}
	if (cntr == arraysize)
	{
		return 1;
		
	}	else 
	{
		return 0;
	}
	
}

/*=======================================*/
static const char pixmask = 0xfe; // 1111 1110
static const char messagemask = 0x01; // 0000 0001
int pixelMessage(char* imageArray, char character, int arraysize)
{
	char idx1 = 0;
	char charIdx = 0;
	char result = 0;
	char pixel = 0;
	char newPixel = 0;
	char idx2 = 0;
	char tempResult = 0;
	char buff [9] = {0,0,0,0,0,0,0,0,0};
	
	if (arraysize <= 8) // no room for a full character
	{
		printf("Not enough room for character\n");
		return -1;
	}
	
	// for each pixel going backwards ie start at 8
		//get the pixel 
		//mask the pixel
		//mask result and store
		//bitwise OR between masked result and masked pixel
		//shift result right
		//put new pixel into array
		
	result = character;
	for (idx1 = 0 ; idx1<8 ; ++idx1)
	{
		pixel = imageArray[idx1];
		pixel = pixel & pixmask; // care about everything but the last pixel
		tempResult = result & messagemask; // care about the last pixel nothing else
		newPixel = pixel | tempResult; // ORing the masked pixel with masked character
		result = result >> 1;
		imageArray [idx1] = newPixel;

	}

	return 0;
}
