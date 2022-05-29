#include <avr/io.h>
#include <util/delay.h>

#define SW_DDR DDRC
#define SW_PIN PINC

#define SGMENT_DDR DDRB
#define SGMENT_PORT PORTB

#define LED_DDR DDRE
#define LED_PORT PORTE

#define BUZZ_DDR DDRD
#define BUZZ_PORT PORTD
	
void number1();
void number2();
void number3();


int main(void) {
	//number1();
	//number2();
	number3();
}

void number1() {
	/*
	 Push Switch 입력으로 FND 동작 제어
	 - 1번째 Push Switch 누르기  => FND 1 ~ 9 숫자 1초 간격 출력
	 - 2번째 Push Switch 누르기  => FND 2, 4, 6, 8, 숫자 1초 간격  출력
	 - 3번째 Push Switch 누르기  => FND 3, 6, 9 숫자 1초 간격 출력
	 - 4번째 Push Switch 누르기  => FND a ~ f 숫자 1초 간격 출력
	 - 5번째 Push Switch 누르기  => 출력 중이던 FND 출력 끄기
	 */
	
	int number[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
	int abc[6] = {0x77, 0x7c, 0x39, 0x5E,0x79, 0x71};
	
	// 초기화
	SW_DDR = 0x00;
	SGMENT_DDR = 0xFF;
	SGMENT_PORT = 0x00;
	
	while (1)
	{
		// 1번
		if ((SW_PIN^0xFF) >> 0 == 1)
		{
			for (int i = 0; i < 9; i++)
			{
				// 5번
				if ((SW_PIN^0xFF) >> 4 == 1)
					break;
				SGMENT_PORT = number[i+1];
				_delay_ms(1000);
			}
			SGMENT_PORT = 0x00;
		}
		
		// 2번
		if ((SW_PIN^0xFF) >> 1 == 1)
		{
			for (int i = 0; i < 8; i+=2)
			{
				if ((SW_PIN^0xFF) >> 4 == 1)
					break;
				SGMENT_PORT = number[i+2];
				_delay_ms(1000);
			}
			SGMENT_PORT = 0x00;
		}
		
		// 3번
		if ((SW_PIN^0xFF) >> 2 == 1)
		{
			for (int i = 3; i < 10; i+=3)
			{
				if ((SW_PIN^0xFF) >> 4 == 1)
					break;
				SGMENT_PORT = number[i];
				_delay_ms(1000);
			}
			SGMENT_PORT = 0x00;
		}
		
		// 4번
		if ((SW_PIN^0xFF) >> 3 == 1)
		{
			for (int i = 0; i < 6; i++)
			{
				if ((SW_PIN^0xFF) >> 4 == 1)
					break;
				SGMENT_PORT = abc[i];
				_delay_ms(1000);

			}
			SGMENT_PORT = 0x00;
		}
	}
	
}

void number2() {
	/*
	Buzzer와 LED  동작 제어
	- LED 8개를 1초 간격으로 차례로 On 하고 제일 마지막 LED ON되면 Buzzer ON-OFF(1초)
	- On한 LED 차례로 (8번LED > 1번LED)Off하고 제일 마지막 LED OFF되면 Buzzer ON-OFF(1초)
	*/
	
	// 초기화
	LED_DDR = 0xFF;
	LED_PORT = 0x00;
	BUZZ_DDR = 0x01;
	BUZZ_PORT = 0x01;
	
	LED_PORT = 0x01;
	
	// ON
	for (int i = 1; i < 8; i++) {
		_delay_ms(1000);
		LED_PORT <<= 1;
		LED_PORT += 1;
	}
	BUZZ_PORT = 0x00;
	_delay_ms(1000);
	BUZZ_PORT = 0x01;
	// OFF
	for (int i = 1; i <= 8; i++) {
		LED_PORT >>= 1;
		if (i == 8)
		{
			BUZZ_PORT = 0x00;
		}
		_delay_ms(1000);
	}
	BUZZ_PORT = 0x01;
	
}

void number3() {
	/*
	 LED와 FND 동작제어
	 - FND와 LED 출력 간격은 1초 간격
	 - 1 - 3 - 5 - 7 - a - f 순서대로  3번만 진행 후 동작 정지
	 
	 - FND에 1 - 3 - 5 - 7 - a - f 순서대로 출력하며 LED 갯수도 1개, 3개, 5개, 7개 출력
	 - FND에 a 출력 시 모든 LED ON
	 - FND에 f 출력 시 모든 LED OFF
	 */
	
	SGMENT_DDR = 0xFF;
	SGMENT_PORT = 0x00;
	LED_DDR = 0xFF;
	LED_PORT = 0x00;
	
	// 1 3 5 7 a f
	int arr[6] = {0x06, 0x4F, 0x6D, 0x07, 0x77, 0x71};
	int numberArr[6] = {0x01, 0x07, 0x1F, 0x7F, 0xFF, 0x00};
		
	// FND 3번 반복
	for (int i=0; i < 3; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			SGMENT_PORT = arr[j];
			LED_PORT = numberArr[j];
			_delay_ms(1000);
		}
	}
	SGMENT_PORT = 0x00;
}

