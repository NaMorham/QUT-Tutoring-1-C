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

//Game State
#define STATE_TITLE 		0
#define STATE_COUNT 		1
#define STATE_GENTERRAIN 	2
#define STATE_P1ANG 		3
#define STATE_P1POWER 		4
#define STATE_P1SHOOT 		5
#define STATE_P1BULLET		6
#define STATE_AISHOOT		7
#define STATE_AIBULLET		8
#define STATE_FINISHED		9




void init();

void Handle_Input();

void Update_Objects();

void Draw_Screen();




static int gamestate = 0;
int Button0 = 0x00;
int Button1 = 0x00;
int LED0 = 0x00;
int LED1 = 0x00;


int main() {
CPU_PRESCALE(CPU_16MHz);
	init(); 

	while(1){	
		Button0 = (PINB & (1<<0));			// Checks button state
		Button1 = (PINB & (1<<1));			// Checks button state
	
		Handle_Input();
			if(LED0){
			PORTB |= (1 << 2);		// LED ON
		}
		else{PORTB &= ~(1 << 2);
			
			}
			
			if (LED1) {PORTB |= (1 << 3);
			//_delay_ms(1000);
			}
			else{PORTB &= ~(1 << 3);
			}			
						
		Update_Objects();
		
		Draw_Screen();
		
		
		
	}
		
}
	
	void init() {
	LCDInitialise(0x2f);		// set contrast of the screen
	DDRB |= (1<<2);	// for output of LED
	DDRB |= (1<<3);	// for output of LED2
	
	DDRB &= ~(1<<0);	// input for button
	DDRB &= ~(1<<1);	// input for button 2
	
	}
	
	void Draw_Screen(){
	
	switch(gamestate){
	case	STATE_TITLE:{
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
		break;
	}
	case	STATE_COUNT:{
			
			LCDClear();	
			LCDString("3") ;
			_delay_ms(1000);
			LCDClear();
			LCDString("2") ;
			_delay_ms(1000);
			LCDClear();
			LCDString("1") ;
			_delay_ms(5000);
			break;
	}
	case	STATE_GENTERRAIN:
	case	STATE_P1ANG:
	case	STATE_P1POWER:
	case	STATE_P1SHOOT: 
	case	STATE_P1BULLET:
	case	STATE_AISHOOT:
	case	STATE_AIBULLET:	
	case	STATE_FINISHED:
	
	default:
	LCDClear();
	gamestate = STATE_TITLE;	//If Bad State Return to TiTLE
	
		return;	
	}
	
	
	
	
	
	}
		
	void Update_Objects(){		//generate terrain and update shot in flight   updating maths function
		switch(gamestate){
			case	STATE_TITLE:
			case	STATE_COUNT:
			case	STATE_GENTERRAIN:
			case	STATE_P1ANG:
			case	STATE_P1POWER:
			case	STATE_P1SHOOT: 
			case	STATE_P1BULLET:
			case	STATE_AISHOOT:
			case	STATE_AIBULLET:	
			case	STATE_FINISHED:
			
			default:
			gamestate = STATE_TITLE;	//If Bad State Return to TiTLE
			
				return;	
	}
}
	
	void Handle_Input(){
	switch(gamestate){
	case	STATE_TITLE:{
		if(Button0){			// button is presses
			_delay_ms(10);	// delay for dbounce
			LED0 = 1;
			gamestate = STATE_COUNT;
			LCDClear();
		}	
		else{LED0 =0;}
		
		if(Button1){
			_delay_ms(10);	// delay for dbounce
			LED1 = 1;
			gamestate = STATE_COUNT;
			LCDClear();
		}
		else{LED1 = 0;}
		
	break;
	}
	case	STATE_COUNT:{
			
	
			break;		
			}
	case	STATE_GENTERRAIN:{
	}
	case	STATE_P1ANG:{
	}
	case	STATE_P1POWER:
	case	STATE_P1SHOOT: 
	case	STATE_P1BULLET:
	case	STATE_AISHOOT:
	case	STATE_AIBULLET:	
	case	STATE_FINISHED:
	
	default:
	gamestate = STATE_TITLE;	//If Bad State Return to TiTLE
	
		return;	
	}
	
	_delay_ms(500);
	}
	
	
	
	
	
	
	
	
	
	
	/* 
	if(PINB & (1<<0)){			// button is presses
		_delay_ms(10);	// delay for dbounce
		PORTB |= (1 << 2);
		_delay_ms(1000);
		PORTB &= ~(1 << 2);
		LCDClear(); 		
		}			
		else if(PINB & (1<<1)){
		_delay_ms(10);	// delay for dbounce
		PORTB |= (1 << 3);
		_delay_ms(1000);
		PORTB &= ~(1 << 3);
		LCDClear();
		}
		
		*/
	
	
	
	
	