#include <stm32f4xx.h>
#define GPIOAEN (1U<<0)
#define GPIOCEN (1U<<2)
#define lcd_rs  (1U<<0)
#define lcd_rw  (1U<<1)
#define lcd_e   (1U<<2)

void lcd_data(unsigned char data)
{
	GPIOC -> ODR = data;
	GPIOA -> ODR |=  lcd_rs;
	GPIOA -> ODR &= ~lcd_rw;
	GPIOA -> ODR |= lcd_e;
	for(int i=0;i<20000;i++)
	{}
	GPIOA -> ODR &= ~lcd_e;
}

void lcd_command(unsigned char cmd)
{
	GPIOC -> ODR = cmd;
	GPIOA -> ODR &=  ~lcd_rs;
	GPIOA -> ODR &= ~lcd_rw;
	GPIOA -> ODR |= lcd_e;
	for(int i=0;i<20000;i++)
	{}
	GPIOA -> ODR &= ~lcd_e;
}

void lcd_string(const char *str,char length)
{
	for(int i=0;i<length;i++)
	{
		lcd_data(str[i]);
	}
}

void lcd_intialise()
{
	lcd_command(0x38);
	lcd_command(0x06);
	lcd_command(0x0C);
	lcd_command(0x01);
}

int main()
{

	RCC -> AHB1ENR |= GPIOAEN|GPIOCEN;
	GPIOA -> MODER |= (1U<<0)|(1U<<2)|(1U<<4);
	GPIOC -> MODER |= (1U<<0)|(1U<<2)|(1U<<4)|(1U<<6)|(1U<<8)|(1U<<10)|(1U<<12)|(1U<<14);

	lcd_intialise();
	while(1)
	{
		lcd_command(0x80);
		lcd_string("GOVIND LEARNING",15);
		lcd_command(0xC0);
		lcd_string("STM32 WORK",10);
	}
	return 0;
}
