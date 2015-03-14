#include <stdio.h>
#include <stdlib.h>

//Return Value: Open File=0; Fail Open=-3; 
//EOF b4 array full=-1; EOF not reached=-2
int read_basic_csv(char* fileLocation, int numValues, int*
values);
int char_to_int(char c) ;


int main(int argc, char const *argv[])

{
	//Define number
	int numValues = 7;

	//Define array, initalise so that all values start as -1.

	int* values = malloc(numValues*sizeof(int));
	
    // print out pre array
	for(int j = 0; j < numValues; j++) {
       values[j]=-1;
       printf("%d ", values[j]);
    }
#ifdef _WIN32
    int result=read_basic_csv("./sol3array.txt", numValues, values);
#else
    int result=read_basic_csv("/Users/shellieo/Documents/GDrive/Y2-SEM2/CAB202/Prac/Week5-File IO and Bitwise Operations/sol3array.txt", numValues, values);
#endif
    // print out array after
    for (int j = 0; j < numValues; j++) {
        printf("%d ", values[j]);
    }
    printf("Result #1 = %d\n\n", result);

    result = read_basic_csv("./testfile.all.txt", numValues, values);

    // print out array after
    for (int j = 0; j < numValues; j++) {
        printf("%d ", values[j]);
    }
    printf("Result #2 = %d\n\n", result);

    free(values);

	return result;
}

int read_basic_csv(char* fileLocation, int numValues, int*
values)
{

//Open file fopen

FILE* filePointer = fopen(fileLocation, "r");

	if (filePointer==NULL)
	{
		return -3;
	}

	//Check array

	char c; 
	int idx=0;

	while(!feof(filePointer)) {
		//read a character
		c = fgetc(filePointer);
		if (c==-1)
		{
			fclose(filePointer);
			break;
		}
		printf("read %c, ",c );

		// continue past anything that is not between 0 and 9.
		if (c < '0' || c > '9'){
			continue;
		}
		//checking for room in array
		printf("idx = %d, numValues = %d\n",idx,numValues);
		if (idx >= numValues) {
			fclose(filePointer);
			return -2;
		}
		//put value in array
		values[idx]=char_to_int(c);
		//update position in array
		idx++;
	}
	printf("idx = %d, numValues = %d\n",idx,numValues);
	if (idx==numValues)
	{
		fclose(filePointer);
		return 0;
	}
	else
	{
		fclose(filePointer);
		return -1;

	}
}
//Function 
int char_to_int(char c) 
{

return c - '0';
}

