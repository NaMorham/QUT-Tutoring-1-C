#include "assignment_1.h"

//  COPY EVERYTHING IN AND HOPE IT WORKS 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*================================================*/
// functions for the read functions
int readgrey(FILE* imgfile, char** image_data, int* width, int* height);
int readRGB(FILE* imgfile, char** image_data, int* width, int* height);
int readASCIIgrey(FILE* imgfile, char** image_data, int* width, int* height);
int readASCIIrgb(FILE* imgfile, char** image_data, int* width, int* height);
char* readTOspace(FILE* file, char* buff, int size);
/*=================================================*/
// functions for the write function
int writeGREY(FILE* imgfile, int width, int height, char* image_data, int data_length);
int findMAXval(char* imgData, int length);
/*================================================*/
// functions for the embed function
int pixelMessage(char* imageArray, char character, int arraysize);


/*================================================*/
// functions for the 




/*================================================*/
// functions for the 



/*==================================================*/
/*==================================================*/
//	READING FUNCTION
int read_image(char* file_name, char** image_data, int* width, int* height)
{
	char identifier[4] = {0,0,0,0};
	
	FILE* image = fopen(file_name,"rb"); 
	
// check to open a file
	if (image == NULL ) // equivalent to if (!image)
	{
		printf("could not open file"); // checks to see if the file could be opened
		return -1;
	}
	
	size_t numread = fread(identifier,sizeof(char),3,image);
	printf("Read %u bytes\n",numread);
	
// can we read 3 characters from file
	if (numread != 3)
	{
		printf("could not read identifier file\n");
		fclose(image);
		return -1;
	}
	
// checking valid pgm
	printf("%s\n",identifier);
	if (identifier[0] != 'P' || identifier[2] != ' ')
	{
		printf("identifier not correct");
		fclose(image);
		return -1;
	}
		
// checking the file type
// need three sub functions each to check if file is binary or ASCII
		
	int result = -1; 
	if (identifier[1] == '5')
	{
		 result = readgrey( image,  image_data,  width,  height);
	}
	else if (identifier [1] == '6')
	{
		result = readRGB( image,  image_data, width, height);
	}
	else if(identifier[1] == '2')
	{
		result = readASCIIgrey( image,  image_data, width, height);
	}
	else if(identifier[1] == '3')
	{
		result = readASCIIrgb( image,  image_data, width, height);
	}
	else 
	{
		printf("Format not supported!!!");
	}
	
	fclose(image);
	return result;
}
/*===================================*/
int readgrey(FILE* imgfile, char** image_data, int* width, int* height)
{ // checking for P5 format
	int intensity = 0;
	int arraysze = 0;
	char* imagedata = NULL;
	
	if ( readDIMs(imgfile, width, height, &intensity) != 0)
	{
		printf("could not read DIMS\n");
		return -1;
	}
	printf("read grey\n");
	printf("w:%d h:%d i:%d\n",*width,*height,intensity);
	//CHECK FOR VALID WIDTH AND HEIGHT
		if(*width < 1)
	{
		printf("Invalid width\n");
		return -1;
	}
			if(*height < 1)
	{
		printf("Invalid height\n");
		return -1;
	}
	
	//calculate the array size width * height
	arraysze = (*width) * (*height);
	//attempt to allocate memory for the array,
	imagedata = (char*)malloc(sizeof(char)*arraysze);
	printf("arraysze:%d\n",arraysze);
	//after allocating the memory check for NULL
	if(imagedata == NULL)
	{
		printf("Failed to allocate memory, Possibly out of memory\n");
		return -1;
	}
	//if not null memset
	memset(imagedata,0,sizeof(char)*arraysze);
	//read the file into the array 
	/*
	if(fread(imagedata,sizeof(char),arraysze,imgfile) != arraysze)
	{
		printf("failed to read imagedata\n");
		return -1;
	}
	/*/
	{
		int idxrd = 0;
		char c = 0;
		for (; idxrd < arraysze; ++idxrd)
		{
			fread(&c, 1, 1, imgfile);
			printf("DBG: Idx = %d, char = (%02x) %c\n", idxrd, c, (isprint(c) ? c : '.'));
			imagedata[idxrd] = c;
		}
	}
	//*/
	*image_data = imagedata;
	
	return arraysze;
}
/*===============================*/
int readRGB(FILE* imgfile, char** image_data, int* width, int* height)
{ // checking for P6 format
		int intensity = 0;
		int arraysze = 0;
		char* imagedata = NULL;
		
	if ( readDIMs(imgfile, width, height, &intensity) != 0)
	{
		printf("could not read DIMS\n");
		return -1;
	}
	printf("read ASCII RGB\n");
	printf("w:%d h:%d i:%d\n",*width,*height,intensity);
	
	//CHECK FOR VALID WIDTH AND HEIGHT
		if(*width < 1)
	{
		printf("Invalid width\n");
		return -1;
	}
			if(*height < 1)
	{
		printf("Invalid height\n");
		return -1;
	}
	
	//calculate the array size width * height * 3
	arraysze = (*width) * (*height) *3;
	//attempt to allocate memory for the array,
	imagedata = (char*)malloc(sizeof(char)*arraysze);
	printf("arraysze:%d\n",arraysze);
	//after allocating the memory check for NULL
	if(imagedata == NULL)
	{
		printf("Failed to allocate memory, Possibly out of memory\n");
		return -1;
	}
	//if not null memset
	memset(imagedata,0,sizeof(char)*arraysze);
	//read the file into the array 
	if(fread(imagedata,sizeof(char),arraysze,imgfile) != arraysze)
	{
		printf("failed to read imagedata\n");
		return -1;
	}
	*image_data = imagedata;
	return arraysze;
}
/*============================*/
//	readASCIIgrey SAME AS THE OTHER READ FUNCTIONS
int readASCIIgrey(FILE* imgfile, char** image_data, int* width, int* height)
{ // checking for P2 format
		int intensity = 0;
		int arraysze = 0;
		char* imagedata = NULL;
		
	if ( readDIMs(imgfile, width, height, &intensity) != 0)
	{
		printf("could not read DIMS\n");
		return -1;
	}
	printf("read ASCII grey\n");
	printf("w:%d h:%d i:%d\n",*width,*height,intensity);
	
	//CHECK FOR VALID WIDTH AND HEIGHT
		if(*width < 1)
	{
		printf("Invalid width\n");
		return -1;
	}
			if(*height < 1)
	{
		printf("Invalid height\n");
		return -1;
	}
	
	//calculate the array size width * height * 3
	arraysze = (*width) * (*height);
	//attempt to allocate memory for the array,
	imagedata = (char*)malloc(sizeof(char)*arraysze);
	printf("arraysze:%d\n",arraysze);
	//after allocating the memory check for NULL
	if(imagedata == NULL)
	{
		printf("Failed to allocate memory, Possibly out of memory\n");
		return -1;
	}
	//if not null memset
	memset(imagedata,0,sizeof(char)*arraysze);
	//read the file into the array 
	if(fread(imagedata,sizeof(char),arraysze,imgfile) != arraysze)
	{
		printf("failed to read imagedata\n");
		return -1;
	}
	*image_data = imagedata;
	return arraysze;
}

/*====================================================*/
//	readASCIIrgb SAME AS THE OTHER READ FUNCTIONS
int readASCIIrgb(FILE* imgfile, char** image_data, int* width, int* height)
{ // checking for P3 format
		int intensity = 0;
		int arraysze = 0;
		char* imagedata = NULL;
		
	if ( readDIMs(imgfile, width, height, &intensity) != 0)
	{
		printf("could not read DIMS\n");
		return -1;
	}
	printf("read RGB\n");
	printf("w:%d h:%d i:%d\n",*width,*height,intensity);
	
	//CHECK FOR VALID WIDTH AND HEIGHT
		if(*width < 1)
	{
		printf("Invalid width\n");
		return -1;
	}
			if(*height < 1)
	{
		printf("Invalid height\n");
		return -1;
	}
	
	//calculate the array size width * height * 3
	arraysze = (*width) * (*height) *3;
	//attempt to allocate memory for the array,
	imagedata = (char*)malloc(sizeof(char)*arraysze);
	printf("arraysze:%d\n",arraysze);
	//after allocating the memory check for NULL
	if(imagedata == NULL)
	{
		printf("Failed to allocate memory, Possibly out of memory\n");
		return -1;
	}
	//if not null memset
	memset(imagedata,0,sizeof(char)*arraysze);
	//read the file into the array 
	if(fread(imagedata,sizeof(char),arraysze,imgfile) != arraysze)
	{
		printf("failed to read imagedata\n");
		return -1;
	}
	*image_data = imagedata;
	return arraysze;
}

/*============================*/
char* readTOspace(FILE* file, char* buff, int size)
{//
	if (size<1)
	{
		return NULL;// no room in the buffer
	}
	if (file == NULL)
	{
		return NULL; // no file to read from 
	}
	if (buff)// read unitl we find a space, equivalent to != null
	{
		int idx = 0;
		char c = 0;
		//char* buffer = *buff; // improved to readability of the program by eleminating a pointer
		
		while ((c = fgetc(file)) != -1)
		{
			if (isspace(c))
			{
				return buff; // can use either buffer or *buff
			}
			else 
			{
				buff [idx] = c;
				idx++;
			}
			if (idx>=size)
			{
				return NULL;
			}
		
		}
	 
	}
	else
	{
		return NULL; // no buffer to write to 
	}
	
}
/*================================*/
// returns 1 is successful or 0 if failed
int scanint(char* str, int* val)
{ 
	if (str && *str) // *str is checking the first letter of the string and str is checking that we have a sting in the forst place and checking aginst null
	{
		if (val != NULL)
		{
			return sscanf(str,"%d",val) == 1;	
		}
	}
	return 0;
}

/*================================*/
int readDIMs(FILE* dims, int* width, int* height, int* intensity)
{// call read to space 3 times and atoi function from strings.h

	int w = 0;
	int h = 0;
	int itn = 0;
	int buffsize = 10;
	
	char buff[buffsize+1];
	memset(buff, 0, (buffsize+1)*sizeof(char));
	
	// READING WIDTH 
	if(readTOspace( dims, buff, buffsize) == NULL)
	{
		printf("Failed to read width\n");
		return -1;
	}
	
	 if (scanint( buff, &w) != 1)
	 {
		printf("Failed to PARSE width\n");
		return -1;
	 }
	
	//READING HEIGHT
	memset(buff, 0, buffsize*sizeof(char));
	if(readTOspace( dims, buff, buffsize) == NULL)
	{
		printf("Failed to read height\n");
		return -1;
	}
	
	 if (scanint( buff, &h) != 1)
	 {
		printf("Failed to PARSE height\n");
		return -1;
	 }
		
	//READING INTENSITY
	// only reading type p5 and p6 the intensity will be a max of 3 characters
	memset(buff, 0, buffsize*sizeof(char));//resetting buff to a zero array
	if(readTOspace( dims, buff, buffsize) == NULL)
	{
		printf("Failed to read max value\n");
		return -1;
	}
	
	 if (scanint( buff, &itn) != 1)
	 {
		printf("Failed to PARSE max value\n");
		return -1;
	 }
			 
	// POPULATE THREE INTS WIDTH, HEIGHT, INTENSITY
	*width = w;
	*height = h;
	*intensity = itn;
	printf("%10.10s\n",buff);
	return 0;
}

/*=========================================================================*/
/*=========================================================================*/
//	WRITE FUNCTION 
int writeGREY(FILE* imgfile, int width, int height, char* image_data, int data_length);
int writeRGB(FILE* imgfile, int width, int height, char* image_data, int data_length);
int findMAXval(char* imgData, int length);

int write_image(char* file_name, int width, int height, char* image_data, int data_length)
{
	int *imagedata = NULL;
	int *imgcopy = NULL;
	int result = 0;
	
	
	FILE* img = fopen(file_name,"wb");
	if(img == NULL) //checking that the file successfully opened
	{
		printf("Failed to open file.\n");
		return -1;
	}
	
	
	
	if (width*height != data_length)
	{
		result = writeRGB( img,  width,  height,  image_data, data_length);
		
	}else
	{
		
		result = writeGREY( img,  width,  height,  image_data, data_length);
	}
	
	
	fclose(img);
	img = NULL;
	return result;
}	

/*===========================================================*/
	int writeGREY(FILE* imgfile, int width, int height, char* image_data, int data_length)
	{//assume that all parameters are valid
	
	static const char* type = "P5";//grey binary file
	static const int buffsize = 256;
	char buff [buffsize+1];
	int strlength = 0;
	int maxval = 127;
	size_t lthstr = 0;
	
	memset(buff,0,(buffsize+1)*sizeof(char));
	maxval = findMAXval(image_data,  data_length);
		
	strlength = snprintf(buff,buffsize,"%s %d %d %d\n",type,width,height,maxval);
	printf("%d %s\n", strlength, buff);
	
	if(buff[0] == 0 || strlength < 8) //minimum length P5.1.1.1 ie 8places
	{
		printf("Invalid header\n");
		return -1;
	}
	
	lthstr = fwrite(buff, sizeof(char), strlength, imgfile);
	printf("wrote %u bytes\n",lthstr);
	
	if(lthstr != strlength*sizeof(char))
	{
		printf("Failed to write header\n");
		return -1;
	}

	lthstr = fwrite(image_data, sizeof(char), data_length, imgfile);
	if (lthstr != data_length*sizeof(char)) //checking that the file has successfully written
	{
		printf("Failed to write image data.\n");
		return -1;
	}

	return 0;
}
/*============================================================*/
int writeRGB(FILE* imgfile, int width, int height, char* image_data, int data_length)
	{//assume that all parameters are valid
	
	static const char* type = "P6";//grey binary file
	static const int buffsize = 256;
	char buff [buffsize+1];
	int strlength = 0;
	int maxval = 127;
	size_t lthstr = 0;
	
	memset(buff,0,(buffsize+1)*sizeof(char));
	maxval = findMAXval(image_data,  data_length);
		
	strlength = snprintf(buff,buffsize,"%s %d %d %d\n",type,width,height,maxval);
	printf("%d %s\n", strlength, buff);
	
	if(buff[0] == 0 || strlength < 8) //minimum length P5.1.1.1 ie 8places
	{
		printf("Invalid header\n");
		return -1;
	}
	
	lthstr = fwrite(buff, sizeof(char), strlength, imgfile);
	printf("wrote %u bytes\n",lthstr);
	
	if(lthstr != strlength*sizeof(char))
	{
		printf("Failed to write header\n");
		return -1;
	}

	lthstr = fwrite(image_data, sizeof(char), data_length, imgfile);
	if (lthstr != data_length*sizeof(char)) //checking that the file has successfully written
	{
		printf("Failed to write image data.\n");
		return -1;
	}

	return 0;
}	
/*===========================================================*/
	static	int HeaderMax(int charlie)
	{
		if (charlie < 128)
		{
			return 127;
		}else
		{
			return 255;
		}
	}
	
	static unsigned char GetMAX(unsigned char a, unsigned char b)
	{
		if(a>b)
		{
			return a;
		} else
		{
			return b;
		}
	
	}
	
	int findMAXval(char* imgData, int length)
	{
		unsigned char max = 0;
		unsigned char c = 0;
		int idx = 0;
		
		for(idx; idx<length; ++idx)
		{
			max = GetMAX(imgData[idx],max) ;
			
		}
	return HeaderMax(max);
	}

/*=========================================================================*/
/*=========================================================================*/
// EMBED FUNCTION
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
		//printf("result:%02x bin:%s\n",result,BinString(result,buff, 9));
		pixel = imageArray[idx1];
		pixel = pixel & pixmask; // care about everything but the last pixel
		tempResult = result & messagemask; // care about the last pixel nothing else
		newPixel = pixel | tempResult; // ORing the masked pixel with masked character
		result = result >> 1;
		imageArray [idx1] = newPixel;
		//printf("result:%02x bin:%s\n\n",result,BinString(result,buff, 9));
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


/*=========================================================================*/
/*=========================================================================*/
//

/*=========================================================================*/
/*=========================================================================*/
//