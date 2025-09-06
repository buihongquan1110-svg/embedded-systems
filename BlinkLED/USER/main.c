#include "stm32f10x.h"                  // Device header

void delay(unsigned int time){
		unsigned int count;
		while(time--){
				for(count = 0; count < 1000; count++);
		}
}

int main(void){
		/* Cap Clock cho bo GPIOC */
		/* | OR ; & AND */
		// RCC->APB2ENR |= (Ox1<<4);
		// RCC->APB2ENR = RCC->APB2ENR | (0X1<<4);
		RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
		GPIOC->CRH = 0x00000000;
		// Cau hinh C13 la Output (CNF:00) Max 50MHz (MODE: 11)
		//GPIOC->CRH = GPIO_CRH_CNF13_1;
		//GPIOC->CRH = 0x00300000;
		GPIOC->CRH = GPIO_CRH_MODE13_0 | GPIO_CRH_MODE13_1;

		while(1){
		//Xuat muc 1 ra chan C13
		GPIOC->ODR |= (0X1<<13);
		delay(1000);
		//GPIOC->ODR |= GPIO_ODR_ODR13;
		//Xuat muc 0 ra chan C13
		GPIOC->ODR |= ~(0x1<<13);
		delay(1000);
			
		}
}

