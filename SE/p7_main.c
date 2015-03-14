/**
* Following includes:
*	- avr/io.h includes the port and pin definitions (i.e. DDRB, PORTB, PB1, etc)
*	- util/delay.h provides the _delay_ms function which is very useful
*	- LCD.h includes the LCD.c functions
*	- Graphics.h includes the Graphics.c functions
*/
#include <avr/io.h>
#include <util/delay.h> 
#include "LCD.h" 
#include "Graphics.h"

/**
* Function declarations
*/
void init();

/**
* Main function where code operations with the libraries should be performed
*/
int main() {
	init(); 
	
	return 0;
}

/**
* Function to initialise the Teensy environment. It should do the following:
*	- Correctly initialise the LCD screen
*	- Configure any required pins to inputs and outputs
* Segmenting common pieces of code like this into functions is good practice!
*/
void init() {
	
}