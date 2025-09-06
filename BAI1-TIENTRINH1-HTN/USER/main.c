#include "stm32f10x.h"                  
#include "stm32f10x_gpio.h"                       
#include "stm32f10x_rcc.h"
#include "stdio.h"



void delay_ms(uint32_t time) {
    uint32_t i, j;
    for (i = 0; i < time; i++)
        for (j = 0; j < 7200; j++);
}

void GPIO_Config()
{
	GPIO_InitTypeDef denLed;
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOB , ENABLE);
	
	
	//Cum Led A
	denLed.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
	denLed.GPIO_Speed = GPIO_Speed_50MHz;
	denLed.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &denLed);
	
	//Cum Led B
	denLed.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_Init(GPIOB, &denLed);
}

int main()
{
	GPIO_Config();
	while(1){
		GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2);
		GPIO_SetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1);
		delay_ms(500);
		GPIO_ResetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2);
		GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1 );
		delay_ms(500);
	}
		
}