/* Write to LCD */

#include <avr/io.h>
#include <util/delay.h> 
#include "LCD.h" 
#include "Graphics.h"
#include "ASCIIFont.h"


#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define CPU_16MHz       0x00
#define CPU_8MHz        0x01
#define CPU_4MHz        0x02
#define CPU_2MHz        0x03
#define CPU_1MHz        0x04
#define CPU_500kHz      0x05
#define CPU_250kHz      0x06
#define CPU_125kHz      0x07
#define CPU_62kHz       0x08

/**
* Function declarations
*/
void init();

/**
* Main function where code operations with the libraries should be performed
*/
int main() {
CPU_PRESCALE(CPU_16MHz);

	// SET_OUTPUT(DDRD, 6);
	// OUTPUT_HIGH(PORTD, 6);
	init(); 
	// while(1){						// need infinite loop for micro controllers
		// if(PINB & (1<<0)){			// button is presses
		// _delay_ms(10);				// delay for dbounce
		// PORTB ^=(1<<2);			// turn on/of
		// }
	//LCDCharacter('H');
	LCDClear();
	

	LCDString("  SCORCHED     EARTH      LACHlAN     N8801656  Press Button")  ;
	
	LCDWrite(LCD_D, 0xf0);
	LCDWrite(LCD_D, 0xc0);
	LCDWrite(LCD_D, 0xa0);
	LCDWrite(LCD_D, 0x90);
	LCDWrite(LCD_D, 0x08);
	LCDString(" To Start " );
	LCDWrite(LCD_D, 0x08);
	LCDWrite(LCD_D, 0x90);
	LCDWrite(LCD_D, 0xa0);
	LCDWrite(LCD_D, 0xc0);
	LCDWrite(LCD_D, 0xf0);
	
	
	while(1){						// need infinite loop for micro controllers
		if(PINB & (1<<0)){			// button is presses
		_delay_ms(100);			// delay for dbounce
		else(PINB & (1<<0))
		}
	}
	
	
		
		//PORTB ^=(1<<2);			// turn on/of
		 }
		 
		 }
	
}

	
	//LCDString("");
	//while (1) {
	//LCDClear();
	//}






/**
* Function to initialise the Teensy environment. It should do the following:
*	- Correctly initialise the LCD screen
*	- Configure any required pins to inputs and outputs
* Segmenting common pieces of code like this into functions is good practice!
*/
void init() {
	LCDInitialise(0x2f);		// set contrast of the screen
	DDRB |= (1<<2);	// for output of LED
	DDRB |= (1<<3);	// for output of LED2
	DDRB &= ~(1<<0);	// input for button
	DDRB &= ~(1<<1);	// input for button 2
	
	
	
	// Turn everything off to start with
	//PORTB = 0x00;
	}
	
	