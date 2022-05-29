#include <avr/io.h>
#include <util/delay.h>

/* == USART 제어를 위한 정의 == */
#define BAUD_RATE 51		// - ATmega128 데이터 시트 51(192000bps)값

void USART_Init() {
	UBRR1H = (unsigned char) BAUD_RATE >> 8;	// - 전송 속도 설정
	UBRR1L = (unsigned char) BAUD_RATE;
	
	UCSR1B = (1<<TXEN1);						// - 송신 기능 설정
	UCSR1C = (1<<UCSZ11) | (1<<UCSZ10);			// - No Parity, 1 Stop Bit, 8 bit Data
}

/* == USART Transmitter 함수 == */
void USART_Transmitter(unsigned char txData) {
	while(!(UCSR1A & (1 << UDRE1)));	// - 송신 버퍼가 빌 때까지 대기
	UDR1 = txData;						// - 버퍼에 데이터를 채우기
}

/* == main 함수 == */
int main(void) {
	unsigned char buffer[] = "Hello ATmega128!\r\n";
	int i;
	
	USART_Init();
	while(1) {
		for (i = 0; i < sizeof(buffer); i++) {
			if (!buffer[i]) break;
			
			USART_Transmitter(buffer[i]);
		}
		_delay_ms(1000);
	}
	return 0;
}