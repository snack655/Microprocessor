#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define LED_DDR DDRE
#define LED_PORT PORTE

void Init_ADC()
{
	//- ADC1 채널, AREF 기준 전압 => AVCC로 H/W 설정
	ADMUX  = (1<<REFS0) | (1<<MUX0);
	
	//- 채널, 활성화, 프리스케일 설정
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
}

unsigned int startADConverter()
{
	unsigned int result;

	cli();									//- ADC 변환 중 인터럽트 금지

	ADCSRA |= (1<<ADSC);					//- ADC 변환 시작
	while(!(ADCSRA & (1<<ADIF))) ;			//- ADC 변환 완료 신호 대기

	result = ADCL;		            	 	//- 변환 결과 저장
	result |= ((ADCH & 0x03) << 8);

	sei();									//- 인터럽트 허용

	return result;
}

int main(void)
{
	unsigned int AdcResult;
	Init_ADC();

	LED_DDR = 0xFF;
	LED_PORT = 0x00;
	
	while(1)
	{
		AdcResult = startADConverter();
		if (AdcResult <= 400) {
			LED_PORT = 0x00;
		} else {
			LED_PORT = 0xFF;
		}
	}
	return 0;
}

