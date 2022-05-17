#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

#define LED_DDR DDRB
#define LED_PORT PORTB

void init_EINT() {
	EICRB |= ((1<<ISC41)|(1<<ISC40));
	EIMSK |= (1<<INT4);
}

ISR(INT4_vect) {
	// 인터럽트 처리코드
	LED_PORT = 0x00;
	_delay_ms(500L);
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
		LED_PORT = 0xFF;
	}
	
	return 0;
}