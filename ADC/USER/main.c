#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_usart.h"
#include "misc.h"
#include <stdio.h>
#include <string.h>

#define VREF 3300  

void USART1_Init(void);
void USART1_SendString(const char *str);
void GPIO_Config(void);
void ADC1_Init_Config(void);
uint16_t ADC1_Read(void);

char buffer[64];

int main(void) {
    GPIO_Config();        // LED PC13
    USART1_Init();        // UART1
    ADC1_Init_Config();   // ADC1 channel 0 (PA0)

    USART1_SendString("ADC to UART demo start!\r\n");

    while (1) {
        uint16_t adc_value = ADC1_Read();  
        uint32_t voltage = (adc_value * VREF) / 4095;  

        sprintf(buffer, "ADC = %u, Voltage = %lu mV\r\n", adc_value, voltage);
        USART1_SendString(buffer);

        for (volatile int i = 0; i < 800000; i++); 
    }
}

/* ---------------- Cau hinh ADC ---------------- */
void ADC1_Init_Config(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef gpio;
    gpio.GPIO_Pin = GPIO_Pin_0;          // PA0 = ADC channel 0
    gpio.GPIO_Mode = GPIO_Mode_AIN;      // analog input
    GPIO_Init(GPIOA, &gpio);

    ADC_InitTypeDef adc;
    adc.ADC_Mode = ADC_Mode_Independent;
    adc.ADC_ScanConvMode = DISABLE;
    adc.ADC_ContinuousConvMode = DISABLE;
    adc.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    adc.ADC_DataAlign = ADC_DataAlign_Right;
    adc.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &adc);

    ADC_Cmd(ADC1, ENABLE);

    // Calibration
    ADC_ResetCalibration(ADC1);
    while (ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1));
}

uint16_t ADC1_Read(void) {
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
    return ADC_GetConversionValue(ADC1);
}

/* ---------------- Cau hinh UART ---------------- */
void USART1_Init(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | 
                           RCC_APB2Periph_GPIOA | 
                           RCC_APB2Periph_AFIO, ENABLE);

    GPIO_InitTypeDef gpio;

    // PA9 = TX
    gpio.GPIO_Pin = GPIO_Pin_9;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    gpio.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &gpio);

    // PA10 = RX
    gpio.GPIO_Pin = GPIO_Pin_10;
    gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &gpio);

    USART_InitTypeDef usart;
    USART_StructInit(&usart);
    usart.USART_BaudRate = 9600;
    usart.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART1, &usart);

    USART_Cmd(USART1, ENABLE);
}

void USART1_SendString(const char *str) {
    while (*str) {
        USART_SendData(USART1, (uint16_t)(*str++));
        while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    }
}

/* ---------------- Cau Hinh LED ---------------- */
void GPIO_Config(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_InitTypeDef gpio;
    gpio.GPIO_Pin = GPIO_Pin_13;
    gpio.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &gpio);

    GPIO_ResetBits(GPIOC, GPIO_Pin_13);  
}
