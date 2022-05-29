#include <stdio.h>
#include <avr/io.h>

// LED PIN 선언
#define LED_DDR DDRE
#define LED_PORT PORTE

// SWICH PIN 선언
#define SW_DDR DDRC
#define SW_PIN PINC

#define BUZZ_DDR DDRB
#define BUZZ_PORT PORTB

void pushSwitch();
void buzzSwitch();

int main(void)
{
	
	//pushSwitch();
	buzzSwitch();

}

void pushSwitch() {
	// LED 초기화
	LED_DDR = 0xFF;
	LED_PORT = 0x00;
	
	

	while (1)
	{
		LED_PORT = ~SW_PIN;
	}
}

void buzzSwitch() {
	SW_DDR = 0x00;
	SW_PIN = 0xFF;
	
	BUZZ_DDR = 0x01;
	BUZZ_PORT = 0x01;
	
	while (1)
	{
		int value = ~SW_PIN;
		if (value & 1 == 1) {
			BUZZ_PORT = 0x00;
		}
		if ((value>> 1) & 1 == 1) {
			BUZZ_PORT = 0x01;
		}
		
	}
			
}


