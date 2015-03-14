#include <stdlib.h>
#include <stdio.h>
#include <string.h>



int openfiletype=0;
static int char_to_int(char c) 		//convert a numerical character to integer value
{
	return c - '0';
}
static int read_2(FILE* fp, char** image_data, int* width, int* height);
static int read_3(FILE* fp, char** image_data, int* width, int* height);
static int read_5(FILE* fp, char** image_data, int* width, int* height);
static int read_6(FILE* fp, char** image_data, int* width, int* height);


int read_image(char* file_name, char** image_data, int* width, int* height)

{
	FILE* imgfp=NULL;
	char tp;
	int sizerc=0;		//Size of the data array from reading
	imgfp=fopen(file_name, "rb");

	if (imgfp==NULL)	//Reports that the file is not able to open
	{
		printf("File type incorrect!\n");
		return -1;
	}

    printf("Opened file \"%s\"\n", file_name);
	tp=fgetc(imgfp);
	if(tp!='P')
	{
		printf("File type incorrect!\n");
		fclose(imgfp);		
		imgfp=NULL;	
		return -1;	
	}
//read the file type
	tp=fgetc(imgfp);
	openfiletype=char_to_int(tp);
	if (openfiletype==2)
	{
		printf("File is P2\n");
		sizerc=read_2(imgfp, image_data, width, height);
	}
	else if (openfiletype==3)
	{
		printf("File is P3\n");
		sizerc=read_3(imgfp, image_data, width, height);
	}	
	else if (openfiletype==5)
	{
		printf("File is P5\n");
		sizerc=read_5(imgfp, image_data, width, height);
	}
	else if (openfiletype==6)
	{
		printf("File is P6\n");
		sizerc=read_6(imgfp, image_data, width, height);
	}	
	else 
	{
		printf("File is not supported\n");
		fclose(imgfp);		
		imgfp=NULL;	
		return -1;
	}
	if (imgfp!=NULL)	 
	{
		fclose(imgfp);		
		imgfp=NULL;		//not req'd but good habit
	}
	return sizerc;
}

/* 
* This function will loop reading a character from the file every time. 
* Compare if the character is a space or a new line.
* Exit loop. Else, put in to buffer. At the end, convert buffer to int.
*/
static int getval(FILE* fp, char* buffer, const int buffsize)	//Assume all parameters are valid
{
	char tpp;
	int id;
	int count;
	// Next for loop is clearing the buffer
	for (id=0; id<buffsize; id++)
	{
		buffer[id]=0;			
	}
	id=0;

	//checks each character and stops loop at space or /n.
	count=0;
	while(count < buffsize)
	{
		tpp=fgetc(fp);
		if ((tpp==' ') || (tpp=='\n'))		//remember this checks each possible value to see if either is true.
		{
			return atoi(buffer);
		}
		else if (tpp>='0'&& tpp<='9')
		{
			buffer[id]=tpp;
			id++;
		}	
		else 
		{
			return -1;		//as returned rubbish in tpp
		}
		count++;
	}	
	return -1;	
}


static int read_2(FILE* fp, char** image_data, int* width, int* height) 	
{
	int arrsize;
	char* localdata;

	//Begin get header
	char rtp;
	char buff[20];
	int imgwid;
	int imght;
	int maxval;
    int idx = 0;

	rtp=fgetc(fp);
	if (rtp !=' ')
	{
		printf("Invalid File\n");
		return -1;
	}
	imgwid=getval(fp, buff, 20);
	if (imgwid==-1)
	{
		printf("Invalid Width %d\n", imgwid);
		return -1;
	}
	imght=getval(fp, buff, 20);
	if (imght==-1)
	{
		printf("Invalid Height %d\n", imght);
		return -1;
	}
	maxval=getval(fp, buff, 20);
	if (maxval==-1)
	{
		printf("Invalid Maximum %d\n", maxval);
		return -1;
	}
	//End get header
	printf("Width = %d, Height = %d, Max = %d\n", imgwid, imght, maxval);

	//Begin read data
	//To read image data call getval array size times. Each time putting to the next idx of localdata. For loop (start, continue cond, and increment)
	arrsize=imgwid*imght;				
	localdata=malloc(arrsize*sizeof(char));
	if (localdata==NULL)
	{
		printf("You are out of memory. \n");
		return -1;
	}
	for (idx=0; idx<arrsize; idx++)
	{
		rtp=getval(fp, buff, arrsize);
		localdata[idx]=rtp;
	}
		
	*image_data=localdata;
	*width=imgwid;
	*height=imght;
	return arrsize;
	//End read data	

	
}
static int read_3(FILE* fp, char** image_data, int* width, int* height)
{
	int arrsize;
	char* localdata;

	//Begin get header
	char rtp;
	char buff[20];
	int imgwid;
	int imght;
	int maxval;
    int idx = 0;

	rtp=fgetc(fp);
	if (rtp !=' ')
	{
		printf("Invalid File\n");
		return -1;
	}
	imgwid=getval(fp, buff, 20);
	if (imgwid==-1)
	{
		printf("Invalid Width %d\n", imgwid);
		return -1;
	}
	imght=getval(fp, buff, 20);
	if (imght==-1)
	{
		printf("Invalid Height %d\n", imght);
		return -1;
	}
	maxval=getval(fp, buff, 20);
	if (maxval==-1)
	{
		printf("Invalid Maximum %d\n", maxval);
		return -1;
	}
	//End get header
	printf("Width = %d, Height = %d, Max = %d\n", imgwid, imght, maxval);

	//Begin read data
	//To read image data call getval array size times. Each time putting to the next idx of localdata. For loop (start, continue cond, and increment)
	arrsize=imgwid*imght*3;				
	localdata=malloc(arrsize*sizeof(char));
	if (localdata==NULL)
	{
		printf("You are out of memory. \n");
		return -1;
	}
	for (idx=0; idx<arrsize; idx++)
	{
		rtp=getval(fp, buff, arrsize);
		localdata[idx]=rtp;
	}
		
	*image_data=localdata;
	*width=imgwid;
	*height=imght;
	return arrsize;
	//End read data	

}
static int read_5(FILE* fp, char** image_data, int* width, int* height)
{
	int arrsize;
	char* localdata;

	//Begin get header
	char rtp;
	char buff[20];
	int imgwid;
	int imght;
	int maxval;
    int idx = 0;

	rtp=fgetc(fp);
	if (rtp !=' ')
	{
		printf("Invalid File\n");
		return -1;
	}
	imgwid=getval(fp, buff, 20);
	if (imgwid==-1)
	{
		printf("Invalid Width %d\n", imgwid);
		return -1;
	}
	imght=getval(fp, buff, 20);
	if (imght==-1)
	{
		printf("Invalid Height %d\n", imght);
		return -1;
	}
	maxval=getval(fp, buff, 20);
	if (maxval==-1)
	{
		printf("Invalid Maximum %d\n", maxval);
		return -1;
	}
	//End get header
	printf("Width = %d, Height = %d, Max = %d\n", imgwid, imght, maxval);
	
	//Begin read data
	arrsize=imgwid*imght;				/// alter to *3 for P6.
	localdata=malloc(arrsize*sizeof(char));
	if (localdata==NULL)
	{
		printf("You are out of memory. \n");
		return -1;
	}
	if (fread(localdata, sizeof(char), arrsize, fp)!=(arrsize*sizeof(char)))
	{
		printf("Failed to read file.\n");
		free(localdata);
		localdata=NULL;
		return -1;
	}
	*image_data=localdata;
	*width=imgwid;
	*height=imght;
	return arrsize;
	//End read data	
}


static int read_6(FILE* fp, char** image_data, int* width, int* height)
{
	int arrsize;
	char* localdata;

	//Begin get header
	char rtp;
	char buff[20];
	int imgwid;
	int imght;
	int maxval;
    int idx = 0;

	rtp=fgetc(fp);
	if (rtp !=' ')
	{
		printf("Invalid File\n");
		return -1;
	}
	imgwid=getval(fp, buff, 20);
	if (imgwid==-1)
	{
		printf("Invalid Width %d\n", imgwid);
		return -1;
	}
	imght=getval(fp, buff, 20);
	if (imght==-1)
	{
		printf("Invalid Height %d\n", imght);
		return -1;
	}
	maxval=getval(fp, buff, 20);
	if (maxval==-1)
	{
		printf("Invalid Maximum %d\n", maxval);
		return -1;
	}
	//End get header
	printf("Width = %d, Height = %d, Max = %d\n", imgwid, imght, maxval);
	
	//Begin read data
	arrsize=imgwid*imght*3;			
	localdata=malloc(arrsize*sizeof(char));
	if (localdata==NULL)
	{
		printf("You are out of memory. \n");
		return -1;
	}
	if (fread(localdata, sizeof(char), arrsize, fp)!=(arrsize*sizeof(char)))
	{
		printf("Failed to read file.\n");
		free(localdata);
		localdata=NULL;
		return -1;
	}
	*image_data=localdata;
	*width=imgwid;
	*height=imght;
	return arrsize;
	//End read data
	
}