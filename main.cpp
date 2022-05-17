#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

#define LED_DDR DDRB
#define LED_PORT PORTB

void init_EINT() {
	EICRB |= ((1<<ISC41)|(1<<ISC40)|(1<<ISC50)|(1<<ISC51));
	EIMSK |= ((1<<INT4)|(1<<INT5));
}

ISR(INT4_vect) {
	// 인터럽트 처리코드
	LED_PORT = 0x00;
}

ISR(INT5_vect) {
	LED_PORT = 0xFF;
}

int main(void)
{
	
	// 초기화
	LED_DDR = 0xFF;
	LED_PORT = 0xFF;
	init_EINT();
	
	// Global Interrupt 활성화
	sei();

    while (1) {
		;
    }
	
	return 0;
}

