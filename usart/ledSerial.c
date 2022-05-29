#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LED_DDR DDRB
#define LED_PORT PORTB

/* == USART 제어를 위한 정의 == */
#define BAUD_RATE 51		// - ATmega128 데이터 시트 51(192000bps)값

volatile unsigned char rxData;			// - 송수신 데이터 저장 변수

void USART_Init() {
	UBRR1H = (unsigned char) BAUD_RATE >> 8;	// - 전송 속도 설정
	UBRR1L = (unsigned char) BAUD_RATE;
	
	UCSR1B = (1<<RXCIE1) | (1<<TXEN1) | (1<<RXEN1);		// - 수신, 송신, 수신인터럽트 기능 설정
	UCSR1C = (1<<UCSZ11) | (1<<UCSZ10);					// - No Parity, 1 Stop Bit, 8 bit Data
}

/* == USART Transmitter 함수 == */
void USART_Transmitter(unsigned char txData) {
	while(!(UCSR1A & (1 << UDRE1)));	// - 송신 버퍼가 빌 때까지 대기
	UDR1 = txData;						// - 버퍼에 데이터를 채우기
}

ISR(USART1_RX_vect) {
	// - 수신 버퍼에서 읽어 온 데이터를 다시 송신
	if (UCSR1A & (1<<RXC1)) {
		rxData = UDR1;					// 수신 버퍼 데이터를 변수에 저장
		USART_Transmitter(rxData);		// PC로 전송해서 확인
		
		// 뒤에 들어오는 enter 처리
		if (rxData != '\n') {
			LED_PORT = 0x00;
		}
		
		// 값 만큼 더하기
		for (int i=0; i<rxData-'0'; i++){
			LED_PORT <<= 1;
			LED_PORT |= 1;
		}
		
	}
}

/* == main 함수 == */
int main(void) {
	USART_Init();	// - USART1 초기화
	sei();			// - 글로벌 인터럽트를 활성화
	USART_Transmitter('S');
	LED_DDR = 0xFF;
	LED_PORT = 0x00;
	
	while (1) {
		;
	}
	return 0;
}

