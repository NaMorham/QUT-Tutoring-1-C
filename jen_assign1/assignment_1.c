#include <string.h>

#include "assignment_1.h"

int convertToAscii(FILE* newFile, int variable, char after);

int write_image(char* file_name, int width, int height, char* image_data, int data_length)
{
    int maxIntensity = -1;
    int format = 5;
    int ii = 0;

    //Verify that image_data isn't NULL
    if (image_data == NULL)
    {
        return -1;
    }

    //Open/create file as binary write - 
    FILE* newFile = fopen(file_name, "wb");
    //Verify that file_name opened,return -1 if not
    if (newFile == NULL)
    {
        return -1;
    }

    //Get array length
    //int arrayLength = sizeof(image_data)/sizeof(image_data[0]);
    //printf("arraylength: %d\n", arrayLength);
    printf("width: %d\n", width);
    printf("height: %d\n", height);
    printf("data_length: %d\n", data_length);

    //Write header into new file
    //Write format letter 'P'
    fputc('P', newFile);
    //Write format integer {2,3,5,6}
    convertToAscii(newFile, (height * width) == data_length ? 5 : 6, ' ');

    //Write width into file
    convertToAscii(newFile, width, ' ');

    //Write height into file
    convertToAscii(newFile, height, ' ');

    //Write max intensity into file, if RGB: 255, if greyscale: find max
    if (width*height != data_length)
    {
        maxIntensity = 255;
    }
    else
    {
        maxIntensity = 127;
    }
    convertToAscii(newFile, maxIntensity, '\n');

    //Write image_data into file using loop through array
    for (ii = 0; ii < data_length; ii++)
    {
        //Copy value[counter] from image_data to file 
        fputc(image_data[ii], newFile);
    }
    fclose(newFile);

    //return 0 on success
    return 0;
}


#define MAXLENGTH 4

int convertToAscii(FILE* newFile, int variable, char after)
{
    char buff[MAXLENGTH];

#ifdef _MSC_VER
    _snprintf_s(buff, MAXLENGTH-1, _TRUNCATE, "%d", variable);
#else
    snprintf(buff, MAXLENGTH, "%d", variable);
#endif

    int ii = 0;
    while (ii < MAXLENGTH && buff[ii] != 0)
    {
        fputc(buff[ii], newFile);
        ii++;
    }
    fputc(after, newFile);
    return 0;
}
