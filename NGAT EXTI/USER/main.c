#include "stm32f10x.h"                  // Device header
#include "stm32f10x_exti.h"             // Keil::Device:StdPeriph Drivers:EXTI
#include "misc.h"                       // Keil::Device:StdPeriph Drivers:Framework
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM


void GPIO_Config(void);
void EXTI_Config(void);
void TIM2_Config(void);

int main(void){
	GPIO_Config();
	EXTI_Config();
	TIM2_Config();
	while(1){
		
	}

}
//cau hinh GPIO
void GPIO_Config(void){
	GPIO_InitTypeDef gpio;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
	
	gpio.GPIO_Pin = GPIO_Pin_0;
	gpio.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &gpio);
	
	gpio.GPIO_Pin = GPIO_Pin_1;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &gpio);
	
//nhap nhay 1hz
	gpio.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOB, &gpio);

}


//cau hinh EXTI
void EXTI_Config(void){
	EXTI_InitTypeDef exti;
	NVIC_InitTypeDef nvic;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
	
	exti.EXTI_Line = EXTI_Line0;
	exti.EXTI_Mode = EXTI_Mode_Interrupt;
	exti.EXTI_Trigger = EXTI_Trigger_Falling;
	exti.EXTI_LineCmd = ENABLE;
	EXTI_Init(&exti);
	
	nvic.NVIC_IRQChannel = EXTI0_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 0;
	nvic.NVIC_IRQChannelSubPriority = 0;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);

}


void TIM2_Config(void){
	TIM_TimeBaseInitTypeDef tim;
	NVIC_InitTypeDef nvic;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	tim.TIM_Prescaler = 7199; //7200-1
	tim.TIM_CounterMode = TIM_CounterMode_Up;
	tim.TIM_Period = 5000-1;
	tim.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM2, &tim);
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	nvic.NVIC_IRQChannel = TIM2_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 1;
	nvic.NVIC_IRQChannelSubPriority = 0;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);
	
	TIM_Cmd(TIM2, ENABLE);
}

//ngat EXTI0(Button)

void EXTI0_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line0) != RESET){
		GPIOB -> ODR ^= GPIO_Pin_1;
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

//Ngat Timer2(LED nhap nhay)

void TIM2_IRQHandler(void){
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET){
		GPIOB -> ODR ^= GPIO_Pin_0;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
