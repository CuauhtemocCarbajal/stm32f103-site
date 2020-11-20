#include <stm32f10x.h>

/*
LED verde:					  Connected to PB0
LED amarillo:					Connected to PB1
LED rojo:					    Connected to PB10
*/



void delaybyms(uint32_t j){
	uint32_t k;
	while(j--){
		for (k=4800; k!=0; k--);
		}
}

int main(void){
	enum states {GREEN, YELLOW, RED};
	enum states state = GREEN;
	
	RCC->APB2ENR |= (1<<3); //GPIOB enable clock
	GPIOB->CRL = (GPIOB->CRL & 0xFFFFFF00) | 0x00000033; // Configure pins 0, 1
	GPIOB->CRH = (GPIOB->CRH & 0xFFFFF0FF) | 0x00000300; // Configure pins 10
	
	while(1) {
		switch(state){
			case GREEN:
				GPIOB->ODR = 1; //poner el pin 0 a uno
			  GPIOB->ODR &= ~(1<<1); //poner el pin 1 en cero
				GPIOB->ODR &= ~(1<<10); //poner el pin 10 en cero
				state = YELLOW;
			  delaybyms(100);
				break;
			case YELLOW:
				GPIOB->ODR |= 1<<1; //poner el pin 1 a uno
			  GPIOB->ODR &= ~(1); //poner el pin 0 en cero
				GPIOB->ODR &= ~(1<<10); //poner el pin 10 en cero
				state = RED;
			  delaybyms(100);
				break;
			case RED:
				GPIOB->ODR |= 1<<10; //poner el pin 10 a uno
			  GPIOB->ODR &= ~(1); //poner el pin 0 en cero
				GPIOB->ODR &= ~(1<<1); //poner el pin 1 en cero
				state = GREEN;
			  delaybyms(100);
				break;
		}
	}
}

