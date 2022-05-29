#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

// SENSOR PIN 선언---------------------
#define LED_DDR DDRE	// 입력 & 출력 모드 설정 레지스터
#define LED_PORT PORTE	// 출력 데이터 저장 레지스터

#define BUZZ_DDR DDRB
#define BUZZ_PORT PORTB

void allLED();
void sequential();
void buzz();

// 엔트로포인트 함수
int main(void)
{
	//allLED();
	//sequential();
	buzz();
	
}

// LED 10번 반복
void allLED() {
	// LED 초기화
	LED_DDR = 0xFF;		// 0b1111 1111 => 0번 포트를 출력모드 설정
	LED_PORT = 0x00;	// 0b1111 1111 => 0번 포드에 HIGH 출력
	
	// LED 10번 반복
	int i = 0;
	while (i < 10)
	{
		// LED ON
		LED_PORT = 0xFF;
		_delay_ms(500);
		
		// LED OFF
		LED_PORT = 0x00;
		_delay_ms(500);
		i++;
	}
}

void sequential() {
	LED_DDR= 0xFF;
	LED_PORT = 0x00;
	
	_delay_ms(500);
	LED_PORT = 0x01;
	
	for (int i = 1; i <= 8; i++) {
		_delay_ms(500);
		LED_PORT <<= 1;
		LED_PORT += 1;
	}
	for (int i = 1; i <= 8; i++) {
		LED_PORT >>= 1;
		_delay_ms(500);
	}
}

void buzz() {
	LED_DDR = 0xFF;
	LED_PORT = 0x01;
	BUZZ_DDR = 0x01;
	BUZZ_PORT = 0x00;
	
	for (int i = 1; i <= 8; i++) {
		_delay_ms(500);
		LED_PORT <<= 1;
		//if (LED_PORT % 2 == 0) {
			//BUZZ_PORT = 0x01;
		//}
		BUZZ_PORT = !BUZZ_PORT;
	}
	BUZZ_PORT=0x01;
	
}

