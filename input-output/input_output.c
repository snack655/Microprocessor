#include <avr/io.h>
#include <util/delay.h>

#define DC_DDR DDRF
#define DC_PORT PORTF

#define BT_DDR DDRC
#define BT_PIN PINC

#define FND_DDR DDRB
#define FND_PORT PORTB

void prob1(){
	DC_DDR=0xff;
	BT_DDR=0x00;
	char onf=0;
	char dir=0x01;
	char f1=0;
	char f2=0;
	while (1)
	{
		if((BT_PIN&0x01)==0 && f1==0){
			if(onf){
				onf=0;
				DC_PORT=0x00;
			}
			else{
				onf=1;
				DC_PORT=dir;
			}
			f1=1;
		}
		if((BT_PIN&0x02)==0&&f2==0){
			if(dir==0x01){
				dir=0x02;
			}
			else if(dir==0x02){
				dir=0x01;
			}
			if(onf)
			DC_PORT=dir;
			f2=1;
		}
		if((BT_PIN&0x01)!=0){
			f1=0;
		}
		if((BT_PIN&0x02)!=0){
			f2=0;
		}
		_delay_ms(10);
	}
}

void prob2(){
	DC_DDR=0xff;
	FND_DDR=0xff;
	int number[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x27,0x7f,0x6f};
	int abc[6]={0x77,0x7f,0x39,0x3f,0x79,0x71};
	while (1)
	{
		DC_PORT=0x01;
		for (int i=0;i<10;i++)
		{
			FND_PORT=number[i];
			_delay_ms(5000);
		}
		DC_PORT=0x00;
		for (int i=0;i<6;i++)
		{
			FND_PORT=abc[i];
			_delay_ms(5000);
		}
	}
}

int main(void)
{
	prob1();
	//prob2();
}