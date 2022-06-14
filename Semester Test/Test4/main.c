#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>     // sprintf 함수가 선언된 헤더 파일

#include "usart_printf.h"
#include "tlcd.h"

volatile unsigned char rxData;

int channel;

void Init_ADC()
{
	//- ADC1 채널, AREF 기준 전압 => AVCC로 H/W 설정
	ADMUX  = (1<<REFS0) | (1<<channel);
	
	//- 채널, 활성화, 프리스케일 설정
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
}

unsigned int startADConverter()
{
	unsigned int result;

	cli();

	ADCSRA |= (1<<ADSC);
	while(!(ADCSRA & (1<<ADIF)));

	result = ADCL;
	result |= ((ADCH & 0x03) << 8);

	sei();

	return result;
}

ISR(USART1_RX_vect)
{
	if(UCSR1A & (1<<RXC1))
	{
		rxData = UDR1;
		USART_Transmitter(rxData);
		if (rxData == 'T') {
			channel = 1;
			Init_ADC();
		}
		if (rxData == 'L') {
			channel = 0;
			Init_ADC();
		}
	}
}

int main(void)
{
	channel = 0;
	unsigned int AdcResult;
	TXT_LCD_Init();

	USART_Init();
	stdout = &device;
	
	printf("온도(T) / 조도(L)");
	
	Init_ADC();
	
	
	while(1)
	{
		char s1[10];
		AdcResult = startADConverter();
		printf("%d\n", AdcResult);
		sprintf(s1, "%d", AdcResult);
		SendText(DDRAM_ADDR|0x00, s1);		
		_delay_ms(1000);
		SendCommand(CMD_CLEAR_DISPLAY);
		_delay_us(2000);
	}
	return 0;
}