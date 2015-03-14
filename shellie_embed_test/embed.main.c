#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define PRINTC(a) (isprint((unsigned char)a) ? a : '.')
#define TORFSTR(a) (a?"true":"false")

const static char BITMASK = 0x01;
const static char PIXMASK = 0xFE;

extern const char *BinString(const unsigned char src, char *buf, const int bufSize);
static void DumpImageData(const char *data, const int sz);
static void DumpImageDataWide(const char *data, const int sz, const int cols);
static void DumpBinString(const char *str);

extern int MaskBit(char Pixel, char Bit, char* Output);
extern int EmbedChar(int arrsize, char eb, char* source, char* dest);
extern int embed(char* image_data, int data_length, char* message, char** encoded);
extern int read_image(char* file_name, char** image_data, int* width, int* height);

static void TestEmbedBit(char c, char* source, int arrsize, int resultf, char* resultem);
static void TestMaskBit(char Pixel, char Bit, char result);
static void TestEmbedChar(char* image_data, int data_length, char* message, int resultf, char* resultem);
static void TestFile(char *fname, char *testStr, char *resultData);

static void DumpDummy();
static void TestMaskBits();
static void TestEmbedChars();
static void TestEmbedString();
static void TestFiles();

int main()
{	
    TestMaskBits();
	printf("\n");

    TestEmbedChars();
    printf("\n");

    TestEmbedString();
    printf("\n");

    TestFiles();
    
	return 0;
}


//Test masking is ok.
static void TestMaskBit(char Pixel, char Bit, char result)
{	
	char c;
    char buf[9];

    memset(buf, 0, 9 * sizeof(char));
    printf("Test: Pixel [0x%02x '%c' %s] mixed with ", (unsigned char)Pixel, (unsigned char)PRINTC(Pixel), BinString(Pixel, buf, 8));
    printf("Bit [0x%02x '%c' %s] == ", (unsigned char)Bit, (unsigned char)PRINTC(Bit), BinString(Bit, buf, 8));
    printf("[0x%02x '%c' %s] == ", (unsigned char)result, (unsigned char)PRINTC(result), BinString(result, buf, 8));

    if (MaskBit(Pixel, Bit, &c)!=0)
	{
		printf("Function Failed!!\n");
		return;
	} 
	if (c==result)
	{
		printf("OK!\n");
	}
	else 
		printf("Failed\n");
}

//Test a char can be embedded in 8 pixels.
static void TestEmbedBit(char c, char* source, int arrsize, int resultf, char* resultem)
{	
	int internal;
	char* dest;
	int idx=0;
    char buf[9];

    memset(buf, 0, 9 * sizeof(char));
    printf("Test: Pixels (0x%p) = {", (source ? source : "NULL"));
    DumpImageDataWide(source, arrsize, 3);
    printf("\n} encoded with character [0x%02x '%c' %s] == {", (unsigned char)c, (unsigned char)PRINTC(c), BinString(c, buf, 8));
    DumpImageDataWide(resultem, arrsize, 3);
    printf("\n}\n");

    dest = NULL;

	if (source!=NULL && arrsize>0)
	{
		dest=malloc(arrsize*sizeof(char));

		if (dest==NULL)
		{
			printf("Out of memory!!! \n\n\n");
			return;
		}
	}
	internal=EmbedChar(arrsize, c, source, dest); 	
	if (internal==resultf)
	{
		printf("The function works!!\n");
	}
	else
	{
		printf("The function is fucked!\n\n\n");
		return;
	}
    printf("Compare arrays:\n");
	for (idx = 0; idx < 8; idx++)
	{
		//This is an inline if where it prints each character from dest and resultem. 
		//"dest[idx]==resultem[idx]?"True":"False"" is essentially an if statement returning true or false text.
        printf("%02x == %02x (%s)\n", (unsigned char)dest[idx], (unsigned char)resultem[idx], ((unsigned char)dest[idx] == (unsigned char)resultem[idx] ? "True" : "False"));
	}
    printf("\n\n");
}


//Test embedding is ok
static void TestEmbedChar(char* image_data, int data_length, char* message, int resultf, char* resultem)
{
    char* encoded = NULL;
    int rcembed;
    int idx;

    rcembed = embed(image_data, data_length, message, &encoded);

    if (rcembed != resultf)
    {
        printf("Test Failed\n");
        if (encoded != NULL)
        {
            free(encoded);
            encoded = NULL;
        }
        return;
    }
    else
    {
        printf("Yay it worked! WoooHoo!!!\n");
    }
    if (image_data != NULL)
    {
        printf("Compare arrays:\n");
        printf("  encode:    result:");
        for (idx = 0; idx < data_length; idx++)
        {
            if ((idx % 8) == 0)
            {
                printf("\n"); // extra blank line
            }
            //This is an inline if where it prints each character from dest and resultem. 
            //"dest[idx]==resultem[idx]?"True":"False"" is essentially an if statement returning true or false text.
            printf("%3d: 0x%02x == 0x%02x (%s)\n", idx, (unsigned char)encoded[idx], (unsigned char)resultem[idx], TORFSTR((unsigned char)encoded[idx] == (unsigned char)resultem[idx]));
        }
    }
    printf("\n\n");

	if (encoded!=NULL)
	{
		free(encoded);
		encoded=NULL;
	}
}

static void TestFile(char *fname, char *testStr, char *resultData)
{
	char* image_data=NULL;
	char* encoded=NULL;
    int arrsize;
	int width;
	int height;
	int idx;
    char buf[9];

    memset(buf, 0, sizeof(char) * 9);

    printf("--------------------------------------\n");
    printf(" Read image \"%s\"\n", fname);
    arrsize = read_image(fname, &image_data, &width, &height);
    if (arrsize <= 0)
	{
		printf("Unable to read image.\n");
		return;
	}
    printf("--------------------------------------\n");
    printf("Embed text in image\n");
    DumpBinString(testStr);
    printf("--------------------------------------\n");
    if (embed(image_data, arrsize, testStr, &encoded) == -1)
    {
        printf("Embed failed.\n");
        if (image_data != NULL)
        {
            free(image_data);
            image_data = NULL;
        }
        return;
    }
    else
    {
        printf("Embed succeeded.\n");
    }
	
    printf("--------------------------------------\n");
    printf("          image:              encoded:           expected:");
	for (idx=0; idx < arrsize; idx++)
	{
        if ((idx % 8) == 0)
        {
            printf("\n");
        }
        printf("%3d: 0x%02x [%s] --> ", idx, (unsigned char)image_data[idx], BinString(image_data[idx], buf, 8));
        printf("0x%02x [%s] == ", (unsigned char)encoded[idx], BinString(encoded[idx], buf, 8));
        printf("0x%02x [%s] : %s\n", (unsigned char)resultData[idx], BinString(resultData[idx], buf, 8), 
            TORFSTR((unsigned char)encoded[idx] == (unsigned char)resultData[idx]));
    }

    printf("--------------------------------------\n\n");

	if (image_data!=NULL)
	{
		free(image_data);
		image_data=NULL;
	}
	if (encoded!=NULL);
	{
		free(encoded);
		encoded=NULL;
	}
	
}

static void DumpBinString(const char *str)
{
    int idx = 0;
    char c = 0;
    char buf[9];
    int len = 0;

    memset(buf, 0, 9 * sizeof(char));
    len = (int)strlen(str);
    for (idx = 0; idx < len; ++idx)
    {
        c = str[idx];
        printf("[%3d] 0x%02x %c %s\n", idx, c, PRINTC(c), BinString(c, buf, 8));
    }
}

static void DumpImageData(const char *data, const int sz)
{
    int idx = 0;
    char c = 0;
    char buf[9];

    if (data == NULL)
    {
        printf("Invalid data\n");
        return;
    }
    if (sz < 1)
    {
        printf("Not enough data.\n");
        return;
    }

    memset(buf, 0, 9 * sizeof(char));

    printf("Dump dummy test\n");
    printf("sz = %d\n", sz);
    printf("--------------------------------\n");
    // loop through the dummy array and dump binaries
    for (idx = 0; idx < sz; ++idx)
    {
        c = data[idx];
        if ((idx % 8) == 0)
        {
            printf("\n");
        }
        printf("[%3d] 0x%02x '%c' %s %d\n", idx, c, PRINTC(c), BinString(c, buf, 8), (c&BITMASK ? 1 : 0));
    }
    printf("--------------------------------\n");
}

static void DumpImageDataWide(const char *data, const int sz, const int cols)
{
    int idx = 0;
    char c = 0;
    char buf[9];

    if (data == NULL)
    {
        printf("Invalid data\n");
        return;
    }
    if (sz < 1)
    {
        printf("Not enough data.\n");
        return;
    }

    memset(buf, 0, 9 * sizeof(char));

    // loop through the array and binaries
    for (idx = 0; idx < sz; ++idx)
    {
        c = data[idx];
        if ((idx % cols) == 0)
        {
            printf("\n");
        }
        printf("\t[%3d] 0x%02x '%c' %s\t", idx, c, PRINTC(c), BinString(c, buf, 8));
    }
}

static void TestMaskBits()
{
    printf("\n");
    printf("------------------------------\n");
    printf("Test Mask Bits functions\n");
    printf("------------------------------\n");

    TestMaskBit(0x00, 0x00, 0x00);		//Expected 00000000
    TestMaskBit(0xFF, 0xFF, 0xFF);		//Expected 11111111
    TestMaskBit(0x00, 0x01, 0x01);		//Expected 00000001
    TestMaskBit(0xFF, 0x00, 0xFE);		//Exoected 11111110

    printf("------------------------------\n");
    printf("Done\n");
    printf("------------------------------\n");
}

static void TestEmbedChars()
{
    char test1[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    char test2[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

    char teststr1[] = { 0, 0 };
    char teststr2[] = { 0xff, 0 };
    char teststr3[] = "I";  // 0x49    01001001

    char result1[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };  //Test1 with 0x00
    char result2[] = { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 };	//Test1 with 0xFF

    char result3[] = { 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE };	//Test2 with 0x00
    char result4[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };	//Test2 with 0xFF

    char result5[] = { 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x01 };	//Test1 with 'I'
    char result6[] = { 0xff, 0xfe, 0xfe, 0xff, 0xfe, 0xfe, 0xff, 0xfe, 0xff };	//Test2 with 'I'

    printf("\n");
    printf("------------------------------\n");
    printf("Test Embed char functions\n");
    printf("------------------------------\n");

    TestEmbedBit(0x00, test1, 9, 0, result1);
    TestEmbedBit(0xFF, test1, 9, 0, result2);
    TestEmbedBit(0x00, test2, 9, 0, result3);
    TestEmbedBit(0xFF, test2, 9, 0, result4);
    TestEmbedBit('I', test1, 9, 0, result5);
    TestEmbedBit('I', test2, 9, 0, result6);

    printf("------------------------------\n");
    printf("Done\n");
    printf("------------------------------\n");
}

static void TestEmbedString()
{
    char test3char[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    char testmsg[] = "HI"; // 0x48 0x49    0100 1000  0100 1001
    char test3result[] = { 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00,
        0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    char *result = NULL;

    char test1[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    char test2[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
                     0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

    char teststr1[] = { 0, 0 };
    char teststr2[] = { 0xff, 0 };
    char teststr3[] = "I";  // 0x49    01001001

    char result1[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };  //Test1 with 0x00
    char result2[] = { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };  //Test1 with 0xFF

    char result3[] = { 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE,
                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };  //Test2 with 0x00
    char result4[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };  //Test2 with 0xFF

    char result5[] = { 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00,
                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };  //Test1 with 'I'
    char result6[] = { 0xff, 0xfe, 0xfe, 0xff, 0xfe, 0xfe, 0xff, 0xfe,
                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };  //Test2 with 'I'

    printf("\n");
    printf("------------------------------\n");
    printf("Test Embed string functions\n");
    printf("------------------------------\n");

    // failure tests
    TestEmbedChar(NULL, 16, teststr1, -1, result1);

    // positive tests
    TestEmbedChar(test1, 16, teststr1, 0, result1);
    TestEmbedChar(test1, 16, teststr2, 0, result2);
    TestEmbedChar(test1, 16, teststr3, 0, result5);
    TestEmbedChar(test2, 16, teststr1, 0, result3);
    TestEmbedChar(test2, 16, teststr2, 0, result4);
    TestEmbedChar(test2, 16, teststr3, 0, result6);

    TestEmbedChar(test3char, 24, testmsg, 0, result6);

    printf("------------------------------\n");
    printf("Done\n");
    printf("------------------------------\n");
}

static void TestFiles()
{
    char small_25_expected[] = {
        0x26, 0x2e, 0x65, 0x30, 0x2c, 0x05, 0x11, 0x30, 0x51, 0x34,
        0x36, 0x6a, 0x5e, 0x21, 0x19, 0x3c, 0x5a, 0x0b, 0x79, 0x2f,
        0x68, 0x61, 0x67, 0x64, 0x4d, 0x61, 0x4f, 0x48, 0x76, 0x4d,
        0x29, 0x10, 0x63, 0x3a, 0x75, 0x28, 0x48, 0x27, 0x59, 0x7a,
        0x62, 0x71, 0x14, 0x54, 0x7d, 0x31, 0x05, 0x5e, 0x61, 0x5b,
        0x1f, 0x43, 0x0e, 0x61, 0x7b, 0x38, 0x23, 0x1e, 0x15, 0x06,
        0x25, 0x51, 0x5b, 0x64, 0x19, 0x4d, 0x22, 0x16, 0x35, 0x7b,
        0x2b, 0x7c, 0x34, 0x78, 0x7c, 0x58, 0x70, 0x1a, 0x5c, 0x72,
        0x22, 0x36, 0x27, 0x24, 0x1b, 0x5b, 0x28, 0x66, 0x6f, 0x2e
    };
    char small_25_str[] = "dangerous";
    char small_25_fname[] = "../inputs/images/small_25.pgm";

    char small_41_expected[] = {
        0x24, 0x60, 0x4f, 0x2f, 0x7a, 0x0f, 0x1f, 0x6a, 0x0f, 0x40,
        0x18, 0x2a, 0x42, 0x5b, 0x59, 0x38, 0x3e, 0x01, 0x04, 0x22,
        0x51, 0x09, 0x63, 0x26, 0x09, 0x7d, 0x5d, 0x54, 0x04, 0x2d,
        0x51, 0x30, 0x51, 0x48, 0x15, 0x4e, 0x74, 0x4f, 0x11, 0x58,
        0x2a, 0x42, 0x6c, 0x26, 0x7c, 0x7a, 0x5e, 0x72, 0x64, 0x30,
        0x48, 0x51, 0x64, 0x21, 0x25, 0x2d, 0x55, 0x47, 0x2b, 0x25,
        0x16, 0x1c, 0x68, 0x34, 0x61, 0x1a, 0x4f, 0x5f, 0x79, 0x12,
        0x03, 0x26, 0x4f, 0x0a, 0x7b, 0x6d, 0x0f, 0x4e, 0x64, 0x2e
    };
    char small_41_str[] = "large";
    char small_41_fname[] = "../inputs/images/small_41.pgm";

    printf("\n");
    printf("------------------------------\n");
    printf("Test Embed string functions\n");
    printf("------------------------------\n");
    printf("\n");

    TestFile(small_25_fname, small_25_str, small_25_expected);
    TestFile(small_41_fname, small_41_str, small_41_expected);

    printf("------------------------------\n");
    printf("Done\n");
    printf("------------------------------\n");
}
