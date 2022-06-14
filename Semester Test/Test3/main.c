#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define LED_DDR DDRE
#define LED_PORT PORTE

#define BUZZ_DDR DDRD
#define BUZZ_PORT PORTD

#define BAUD_RATE 51
volatile unsigned char rxData;

char command[3];
int count;

void USART_Init() {
	UBRR1H = (unsigned char) BAUD_RATE >> 8;	// - 전송 속도 설정
	UBRR1L = (unsigned char) BAUD_RATE;
	
	UCSR1B = (1<<RXCIE1) | (1<<TXEN1) | (1<<RXEN1);		// - 수신, 송신, 수신인터럽트 기능 설정
	UCSR1C = (1<<UCSZ11) | (1<<UCSZ10);					// - No Parity, 1 Stop Bit, 8 bit Data
}


void USART_Transmitter(unsigned char txData) {
	while(!(UCSR1A & (1 << UDRE1)));	// - 송신 버퍼가 빌 때까지 대기
	UDR1 = txData;						// - 버퍼에 데이터를 채우기
}

void buzzCommand(char str[]) {
	if (str[1] - '0' == 1) {
		BUZZ_PORT = 0x00;
		} else if (str[1] - '0' == 0) {
		BUZZ_PORT = 0xff;
	}
}

void ledCommand(char str[]) {
	int one = str[1] - '0';
	int two = str[2] - '0';
	if (two == 1) {
		LED_PORT |= 1 << one;
		} else if (two == 0) {
		LED_PORT &= ~(1<<one);
	}
}


ISR(USART1_RX_vect) {
	// - 수신 버퍼에서 읽어 온 데이터를 다시 송신
	if (UCSR1A & (1<<RXC1)) {
		rxData = UDR1;
		USART_Transmitter(rxData);
		if (rxData == '\n')
		{
			return;
		}
		
		command[count] = rxData;

		
		if (count == 1 && command[0] == 'B') {
			buzzCommand(command);
			count = 0;
			return;
		}
		
		if (count == 2 && command[0] == 'L') {
			ledCommand(command);
			count = 0;
			return;
		}
		
		if (count == 2 && command[0] != 'L') {
			count = 0;
			return;
		}
		count++;
	}
}

int main() {
	
	LED_DDR = 0xff;
	LED_PORT = 0x00;
	
	BUZZ_DDR = 0xff;
	BUZZ_PORT = 0xff;
	
	USART_Init();
	sei();
	USART_Transmitter('S');
	
	count = 0;
	while (1) {
		;
	}
	return 0;
}