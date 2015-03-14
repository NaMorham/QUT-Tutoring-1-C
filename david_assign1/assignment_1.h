/**
 * Assignment 1 header file
 */
 
 
#ifndef __DS__ASSIGNMENT_1_H__ 
#define __DS__ASSIGNMENT_1_H__  
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>



// File IO Functions

/**
 * This function is responsible for reading an image file and placing the pixel data from the file into the array image_data
 * The function automatically determines whether the image data is gray scale or rgb and sizes image_data accordingly
 *
 * @param char* file_name   - The name of the file to be opened
 * @param char** image_data - A pointer to an array of pixel data
 * @param int* width        - The width of the read image in pixels
 * @param int* height       - The height of the read image in pixels
 *
 * @return int - The size of the allocated image_data array, otherwise, -1
 */
 
 
int read_image(char* file_name, char** image_data, int* width, int* height);


/**
 * This function is responsible for writing image data to a file
 * The function automatically determines whether the image data is gray scale or rgb
 * 
 * @param char* file_name   - The name of the file to be created
 * @param int width         - The width of the image in pixels
 * @param int height        - The height of the image in pixels
 * @param char* image_data  - The image data array to be written to file
 * @param int data_length   - The length of the image data array
 *
 * @return int - the numeric value 0 on success, -1 if the image file could not be opened for writing
 */
int write_image(char* file_name, int width, int height, char* image_data, int data_length);


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
int embed(char* image_data, int data_length, char* message, char** encoded);

/**
 * This function is responsible for extracting the potential message from the supplied image data
 * 
 * @param char* image_data  - The image data array from which we extract the message
 * @param int data_length   - The length of the image data array
 * @param char** message    - The extracted message array
 *
 * @return int - the numeric value 0 on success
 */
int extract(char* image_data, int data_length, char** message);














// Message Obscuring Functions
/**
 * This function is responsible for rotating each alphabetic character in the message k times to hide the meaning of the message
 * 
 * @param char* message     - The message which the rotation will be applied to
 * @param int k             - The number of rotations to be applied
 *
 * @return int - A count of the number of characters modified
 */
int rot_k(char* message, int k);
















// Message Cracking Functions
/**
 * This function attempts to look for a rotated message by brute-force until a known word is found or the word could not be detected
 * 
 * @param char* encoded     - The potentially rotated message
 * @param char* known_word  - The word that will be searched for while rotating the encoded message
 * @param char** message    - A new array containing the detected message
 *
 * @return int - the k value needed to remove the rotation on success, -1 if no message was detected
 */
int crack(char* encoded, char* known_word, char** message);

/*=======================================================/*

PUT IN LITTLE FUNCTIONS HERE */





#endif // __ DS__ASSIGNMENT_1_H__ 
