/*
 * Graphics.c
 *
 * Created: 20/12/2012 11:59:59 PM
 *  Author: Michael a.k.a Not that there's anything wrong with that
 */ 

#include "Graphics.h"
#include "LCD.h"

unsigned char screenBuffer[LCD_BUFFER_SIZE]; // Our screen buffer array

void SetPixel(unsigned char x, unsigned char y, unsigned char value){

}

void DrawLine(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2) {

}

void PresentBuffer(void) {
	// (Hint: writes every byte of the buffer to the LCD)
}

void ClearBuffer(void) {

}

void DrawBall(unsigned char x, unsigned char y){

}

/**
* Extend this file with whatever other graphical functions you may need
*	Remember to include the declaration of any new functions in "Graphics.h"
*/