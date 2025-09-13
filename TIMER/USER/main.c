#include "stm32f10x.h"

void GPIO_Config(void);
void TIM2_Config(void);
void TIM3_Config(void);
void Delay_ms(uint32_t ms);

int main(void)
{
    GPIO_Config(); 
    TIM2_Config();   
    TIM3_Config();   
    
    while (1)
    {
        
        GPIO_SetBits(GPIOA, GPIO_Pin_2);   
        Delay_ms(1000);
        GPIO_ResetBits(GPIOA, GPIO_Pin_2); 
        Delay_ms(1000);
    }
}

void GPIO_Config(void)
{
    GPIO_InitTypeDef led_Config;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

   
    led_Config.GPIO_Pin = GPIO_Pin_1;
    led_Config.GPIO_Mode = GPIO_Mode_Out_PP;    
    led_Config.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &led_Config);

    
    led_Config.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIOA, &led_Config);

    
    GPIO_ResetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2);
}

void TIM2_Config(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    
    TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 5000 - 1;    
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);

    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIM2, ENABLE);
}

void TIM3_Config(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    
    TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1; 
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 10 - 1;      
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);

    TIM_Cmd(TIM3, ENABLE);
}

void Delay_ms(uint32_t ms)
{
    for(uint32_t i = 0; i < ms; i++)
    {
        TIM_SetCounter(TIM3, 0);          
        while (TIM_GetCounter(TIM3) < 1); 
    }
}


void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

        GPIOA->ODR ^= GPIO_Pin_1;   
    }
}
