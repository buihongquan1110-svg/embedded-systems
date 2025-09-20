#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "misc.h"     
#include "string.h"

volatile char rx_data[50];
volatile uint8_t rx_pos = 0;


void USART1_SendString(const char *str);

void USART1_IRQHandler(void) {
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
        uint16_t data = USART_ReceiveData(USART1);   
        char c = (char)(data & 0xFF);              

       
        USART_SendData(USART1, (uint16_t)c);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);

        if (c == '\n' || c == '\r') {
            if (rx_pos == 0) {
                
            } else {
                rx_data[rx_pos] = '\0'; 
               
                if (strcmp((char*)rx_data, "ON") == 0) {
                    GPIO_ResetBits(GPIOC, GPIO_Pin_13);  
                    USART1_SendString("\r\nLED ON\r\n");
                } else if (strcmp((char*)rx_data, "OFF") == 0) {
                    GPIO_SetBits(GPIOC, GPIO_Pin_13);    
                    USART1_SendString("\r\nLED OFF\r\n");
                } else {
                    USART1_SendString("\r\nUnknown command\r\n");
                }
                rx_pos = 0;
            }
        } else {
            if (rx_pos < (sizeof(rx_data) - 1)) {
                rx_data[rx_pos++] = c;
            } else {
                rx_pos = 0;
            }
        }
        USART_ClearITPendingBit(USART1, USART_IT_RXNE); 
    }
}

void USART1_Init(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

    GPIO_InitTypeDef gpio;
    /* PA9 = TX */
    gpio.GPIO_Pin = GPIO_Pin_9;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    gpio.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &gpio);

    /* PA10 = RX */
    gpio.GPIO_Pin = GPIO_Pin_10;
    gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &gpio);

    USART_InitTypeDef usart;
    USART_StructInit(&usart);
    usart.USART_BaudRate = 9600;
    usart.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART1, &usart);

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    NVIC_InitTypeDef nvic;
    nvic.NVIC_IRQChannel = USART1_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 0;
    nvic.NVIC_IRQChannelSubPriority = 0;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);

    USART_Cmd(USART1, ENABLE);
}

void GPIO_Config(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_InitTypeDef gpio;
    gpio.GPIO_Pin = GPIO_Pin_13;
    gpio.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &gpio);

    GPIO_SetBits(GPIOC, GPIO_Pin_13); 
}

void USART1_SendString(const char *str) {
    while (*str) {
        USART_SendData(USART1, (uint16_t)(*str++));
        while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    }
}

int main(void) {
    GPIO_Config();
    USART1_Init();

    USART1_SendString("Hello from STM32!\r\n");

    while (1) {
    }
}
