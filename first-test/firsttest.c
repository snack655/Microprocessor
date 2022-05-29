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
	 Push Switch �Է����� FND ���� ����
	 - 1��° Push Switch ������  => FND 1 ~ 9 ���� 1�� ���� ���
	 - 2��° Push Switch ������  => FND 2, 4, 6, 8, ���� 1�� ����  ���
	 - 3��° Push Switch ������  => FND 3, 6, 9 ���� 1�� ���� ���
	 - 4��° Push Switch ������  => FND a ~ f ���� 1�� ���� ���
	 - 5��° Push Switch ������  => ��� ���̴� FND ��� ����
	 */
	
	int number[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
	int abc[6] = {0x77, 0x7c, 0x39, 0x5E,0x79, 0x71};
	
	// �ʱ�ȭ
	SW_DDR = 0x00;
	SGMENT_DDR = 0xFF;
	SGMENT_PORT = 0x00;
	
	while (1)
	{
		// 1��
		if ((SW_PIN^0xFF) >> 0 == 1)
		{
			for (int i = 0; i < 9; i++)
			{
				// 5��
				if ((SW_PIN^0xFF) >> 4 == 1)
					break;
				SGMENT_PORT = number[i+1];
				_delay_ms(1000);
			}
			SGMENT_PORT = 0x00;
		}
		
		// 2��
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
		
		// 3��
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
		
		// 4��
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
	Buzzer�� LED  ���� ����
	- LED 8���� 1�� �������� ���ʷ� On �ϰ� ���� ������ LED ON�Ǹ� Buzzer ON-OFF(1��)
	- On�� LED ���ʷ� (8��LED > 1��LED)Off�ϰ� ���� ������ LED OFF�Ǹ� Buzzer ON-OFF(1��)
	*/
	
	// �ʱ�ȭ
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
	 LED�� FND ��������
	 - FND�� LED ��� ������ 1�� ����
	 - 1 - 3 - 5 - 7 - a - f �������  3���� ���� �� ���� ����
	 
	 - FND�� 1 - 3 - 5 - 7 - a - f ������� ����ϸ� LED ������ 1��, 3��, 5��, 7�� ���
	 - FND�� a ��� �� ��� LED ON
	 - FND�� f ��� �� ��� LED OFF
	 */
	
	SGMENT_DDR = 0xFF;
	SGMENT_PORT = 0x00;
	LED_DDR = 0xFF;
	LED_PORT = 0x00;
	
	// 1 3 5 7 a f
	int arr[6] = {0x06, 0x4F, 0x6D, 0x07, 0x77, 0x71};
	int numberArr[6] = {0x01, 0x07, 0x1F, 0x7F, 0xFF, 0x00};
		
	// FND 3�� �ݺ�
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

