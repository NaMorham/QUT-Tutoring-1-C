#include "assignment_1.h"

void printimage( char* image_data, int data_length);
extern int pixelMessage(char* imageArray, char character, int arraysize);

int main()
{
	int image_width = 0;
	int image_height = 0; 
	char *data = NULL;
	
	int COLimage_width = 0;
	int COLimage_height = 0; 
	char *COLdata = NULL;
	
	char* encoded = NULL;
	int arraysize = 0;
	
	char* outData = NULL;
	

//LOADING THE GREY SCALE IMAGE
	arraysize = read_image("small_32.pgm", &data, &image_width, &image_height);
	
	if(arraysize != -1)
	{
		printf("it worked :) (read)\n");
	}
	else
	{
		printf("didn't work :( (read)\n");
	}
	
	printimage( data, image_width*image_height);
	printf("\n\n");
	
if(0)
{
	char array1[] = {0,0,0,0,0,0,0,0};
	char array2[] = {0,0,0,0,0,0,0,0};
	int idx = 0;
	
	pixelMessage( array1,  'H' , 8);
	for (idx; idx<8; ++idx)
	{
	printf("array1:%02x\n",array1[idx]);
	}
	
	pixelMessage( array2,  'I' , 8);
	for (idx=0; idx<8; ++idx)
	{
	printf("array2:%02x\n",array2[idx]);
	}
}
	//printf("%02x\n", 0x80 >> 7);
	//printf("%02x\n", 0x01 >> 0);
	
	
//EMBEDING 

	if(embed(data,arraysize,"greedy",&encoded) == 0)
	{
		printf("It worked (encode)\n");
		outData = encoded;
	}else{
		printf("It didnt work (encode)\n");
		outData = data;
		return 0;
	}
	
//WRITING THE GREY IMAGE

	if(write_image("test.out.pgm",image_width,image_height,outData, image_width*image_height) == 0)
	{
		printf("It worked (write)\n");
	}else
	{
		printf("It didnt work (write)\n");
	}
	
	if(data != NULL)
	{
		free(data);
		data = NULL;
	}
	if(COLdata != NULL)
	{
		COLdata = NULL;
		free(COLdata);
	}
	if(encoded != NULL)
	{
		free(encoded);
		encoded = NULL;
	}
	return 0;
}

/*=========================================*/

void printimage( char* image_data, int data_length)
{
	int idx = 0;
	char c = 0;
	for(idx;idx<data_length;++idx )
	{
		c = image_data[idx];
		printf("(0x%02x) ", c);
		if (isprint(c))
		{
			printf("%c", c);
		}else
		{
			printf(".");
		}
	}
}