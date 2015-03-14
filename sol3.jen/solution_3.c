#include <stdio.h>


int read_basic_csv(char* fileLocation, int numValues, int*
values);

int char_to_int(char c);
 

int main()
{

	int values[5];
	int result;
	char* fileLocation = "solution_3_txt.txt";
	int length = sizeof(values) / sizeof(values[0]);
	printf("%d\n", length);
	
	result = read_basic_csv(fileLocation, length, values);
	
	printf("result=%d\n", result);
	
	return 0;
}



int read_basic_csv(char* fileLocation, int numValues, int*
values)
{

	int ii = 0;
	int nextValue;
	FILE* fileLoc = fopen(fileLocation, "r+");

	if (fileLoc == 0)
		return -3;


	while(!feof(fileLoc)) 
	{
		if (ii >= numValues)
		{
			fclose(fileLoc);
			return -2;
		}
		nextValue = char_to_int(fgetc(fileLoc));
		values[ii] = nextValue;
		//printf("next value=%d\n",values[ii]);
		nextValue = char_to_int(fgetc(fileLoc));
		ii++;
		//printf("ii=%d\n", ii);
	}

	if (ii != numValues)
		{
		fclose(fileLoc);
		return -1;
		}
	
	fclose(fileLoc);
		
	return 0;
}



int char_to_int(char c) 
{
	return c - '0'; 
}
