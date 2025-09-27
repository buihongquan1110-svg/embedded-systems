#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_tim.h"
#include <stdio.h>

#define BUF_SIZE 16
uint16_t ADC_Buffer[BUF_SIZE];   // Bo nho dem de DMA ghi du lieu vao ADC

//================= USART1 INIT =================//
void USART1_Init(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef thanh;
    // PA9 = TX
    thanh.GPIO_Pin = GPIO_Pin_9;
    thanh.GPIO_Speed = GPIO_Speed_50MHz;
    thanh.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &thanh);

    // PA10 = RX
    thanh.GPIO_Pin = GPIO_Pin_10;
    thanh.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &thanh);

		//UART Config
    USART_InitTypeDef usart;
    usart.USART_BaudRate = 9600;
    usart.USART_WordLength = USART_WordLength_8b;
    usart.USART_StopBits = USART_StopBits_1;
    usart.USART_Parity = USART_Parity_No;
    usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    usart.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART1, &usart);

    USART_Cmd(USART1, ENABLE);
}

void USART1_SendChar(char c) {
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    USART_SendData(USART1, c);
}

void USART1_SendString(char *s) {
    while(*s) {
        USART1_SendChar(*s++);
    }
}

//================= TIMER2 Delay =================//
void Timer2_Init(void) {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    TIM_TimeBaseInitTypeDef tim;
    tim.TIM_Prescaler = 7200 - 1; // 72MHz/7200 = 10kHz (moi tick = 0.1ms)
    tim.TIM_CounterMode = TIM_CounterMode_Up;
    tim.TIM_Period = 0xFFFF; 
    tim.TIM_ClockDivision = TIM_CKD_DIV1;
    tim.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &tim);

    TIM_Cmd(TIM2, ENABLE);
}

void Timer2_DelayMs(uint16_t ms) {
    TIM_SetCounter(TIM2, 0);
    while (TIM_GetCounter(TIM2) < (ms * 10)); // vì 1ms = 10 tick (0.1ms moi tick)
}

//================= ADC + DMA =================//
void ADC1_DMA_Config(void) {
    // Bat clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    // PA0 = Analog input
    GPIO_InitTypeDef gpio;
    gpio.GPIO_Pin = GPIO_Pin_0;
    gpio.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &gpio);

    // ADC config
    ADC_InitTypeDef adc;
    adc.ADC_Mode = ADC_Mode_Independent;
    adc.ADC_ScanConvMode = DISABLE;
    adc.ADC_ContinuousConvMode = ENABLE;
    adc.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    adc.ADC_DataAlign = ADC_DataAlign_Right;
    adc.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &adc);

    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);

    // DMA config
    DMA_InitTypeDef dma;
    dma.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
    dma.DMA_MemoryBaseAddr = (uint32_t)ADC_Buffer;
    dma.DMA_DIR = DMA_DIR_PeripheralSRC;
    dma.DMA_BufferSize = BUF_SIZE;
    dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    dma.DMA_MemoryInc = DMA_MemoryInc_Enable;
    dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    dma.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    dma.DMA_Mode = DMA_Mode_Circular;
    dma.DMA_Priority = DMA_Priority_High;
    dma.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel1, &dma);

    // Bat DMA cho ADC
    DMA_Cmd(DMA1_Channel1, ENABLE);
    ADC_DMACmd(ADC1, ENABLE);

    // Bat ngat DMA
    DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);

    // Enable ADC
    ADC_Cmd(ADC1, ENABLE);
    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));

    // Start ADC
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

//================= NVIC =================//
void NVIC_Config(void) {
    NVIC_InitTypeDef nvic;
    nvic.NVIC_IRQChannel = DMA1_Channel1_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 0;
    nvic.NVIC_IRQChannelSubPriority = 0;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);
}

//================= DMA IRQ Handler =================//
void DMA1_Channel1_IRQHandler(void) {
    if(DMA_GetITStatus(DMA1_IT_TC1)) {
        // In du lieu ra UART
        char buf[32];
        for(int i=0; i<BUF_SIZE; i++) {
            sprintf(buf, "ADC[%d] = %d\r\n", i, ADC_Buffer[i]);
            USART1_SendString(buf);
            Timer2_DelayMs(200); // Delay 200ms 
        }
        USART1_SendString("==== DMA Transfer Done ====\r\n");

        DMA_ClearITPendingBit(DMA1_IT_TC1);
    }
}

//================= MAIN =================//
int main(void) {
    USART1_Init();
    Timer2_Init();
    NVIC_Config();
    ADC1_DMA_Config();

    USART1_SendString("DMA ADC Test Start...\r\n");

    while(1) {
    }
}