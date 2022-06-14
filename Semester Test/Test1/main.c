#include <avr/io.h>
#include <util/delay.h>

#define SW_DDR DDRC
#define SW_PIN PINC

#define FND_DDR DDRB
#define FND_PORT PORTB

#define LED_DDR DDRE
#define LED_PORT PORTE

int main(void) {
	int number[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
	
	SW_DDR = 0x00;
	FND_DDR = 0xFF;
	FND_PORT = 0x00;
	LED_DDR = 0xFF;
	LED_PORT = 0x00;
	
	while(1) {
		// 1번
		if ((SW_PIN^0xFF) >> 0 == 1)
		{
			FND_PORT = number[1];
			LED_PORT = 0b00000001;
		}
		
		// 2번
		if ((SW_PIN^0xFF) >> 1 == 1)
		{
			FND_PORT = number[2];
			LED_PORT = 0b00000011;
		}
		
		// 3번
		if ((SW_PIN^0xFF) >> 2 == 1)
		{
			FND_PORT = number[3];
			LED_PORT = 0b00000111;
		}
		
		// 4번
		if ((SW_PIN^0xFF) >> 3 == 1)
		{
			FND_PORT = number[4];
			LED_PORT = 0b00001111;
		}
		
		//54번
		if ((SW_PIN^0xFF) >> 4 == 1)
		{
			FND_PORT = number[5];
			LED_PORT = 0b00011111;
		}
		
		// 6번
		if ((SW_PIN^0xFF) >> 5 == 1)
		{
			FND_PORT = number[6];
			LED_PORT = 0b00111111;
		}
		
		// 7번
		if ((SW_PIN^0xFF) >> 6 == 1)
		{
			FND_PORT = number[7];
			LED_PORT = 0b01111111;
		}
		
		// 8번
		if ((SW_PIN^0xFF) >> 7 == 1)
		{
			FND_PORT = number[8];
			LED_PORT = 0b11111111;
		}
	}
}


