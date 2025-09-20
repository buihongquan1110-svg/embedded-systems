#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_i2c.h"
#include "stm32f10x_usart.h"
#include <stdio.h>
#include <string.h>

#define AHT10_ADDR         0x38 << 1   


void USART1_Init(void);
void USART1_SendChar(char c);
void USART1_SendString(char *s);


void I2C1_Init(void);
void I2C_Write(uint8_t addr, uint8_t *data, uint8_t len);
void I2C_Read(uint8_t addr, uint8_t *data, uint8_t len);


void AHT10_Init(void);
uint8_t AHT10_Read(float *temp, float *humi);

volatile uint32_t msTicks = 0;


void TIM2_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    TIM_TimeBaseInitTypeDef TIM_InitStruct;
    TIM_InitStruct.TIM_Prescaler = 7200 - 1;    // 72MHz / 7200 = 10kHz
    TIM_InitStruct.TIM_Period = 10 - 1;         // 10kHz / 10 = 1kHz (1ms)
    TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM2, &TIM_InitStruct);

    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM2, ENABLE);

    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
}


void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
        msTicks++;
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}


void DelayMs(uint32_t ms)
{
    uint32_t start = msTicks;
    while ((msTicks - start) < ms);
}


int main(void)
{
    float temperature, humidity;
    char buffer[64];

    SystemInit();
    USART1_Init();
    I2C1_Init();
    TIM2_Init();  

    USART1_SendString("Init AHT10...\r\n");
    AHT10_Init();

    while (1)
    {
        if (AHT10_Read(&temperature, &humidity) == 0)
        {
            sprintf(buffer, "Temp: %.2f C, Humi: %.2f %%\r\n", temperature, humidity);
            USART1_SendString(buffer);
        }
        else
        {
            USART1_SendString("Read error!\r\n");
        }

        DelayMs(1000);   
    }
}



void USART1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    USART_InitTypeDef USART_InitStruct;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);

    // PA9 = TX
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // PA10 = RX
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    USART_InitStruct.USART_BaudRate = 115200;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

    USART_Init(USART1, &USART_InitStruct);
    USART_Cmd(USART1, ENABLE);
}

void USART1_SendChar(char c)
{
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    USART_SendData(USART1, c);
}

void USART1_SendString(char *s)
{
    while (*s) USART1_SendChar(*s++);
}


void I2C1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    I2C_InitTypeDef I2C_InitStruct;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

    // PB6 = SCL, PB7 = SDA
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    I2C_InitStruct.I2C_ClockSpeed = 100000;
    I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStruct.I2C_OwnAddress1 = 0x00;
    I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;

    I2C_Init(I2C1, &I2C_InitStruct);
    I2C_Cmd(I2C1, ENABLE);
}

void I2C_Write(uint8_t addr, uint8_t *data, uint8_t len)
{
    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

    I2C_GenerateSTART(I2C1, ENABLE);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

    I2C_Send7bitAddress(I2C1, addr, I2C_Direction_Transmitter);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

    for (uint8_t i = 0; i < len; i++)
    {
        I2C_SendData(I2C1, data[i]);
        while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    }

    I2C_GenerateSTOP(I2C1, ENABLE);
}

void I2C_Read(uint8_t addr, uint8_t *data, uint8_t len)
{
    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

    I2C_AcknowledgeConfig(I2C1, ENABLE);
    I2C_GenerateSTART(I2C1, ENABLE);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

    I2C_Send7bitAddress(I2C1, addr, I2C_Direction_Receiver);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

    for (uint8_t i = 0; i < len; i++)
    {
        if (i == (len - 1))
        {
            I2C_AcknowledgeConfig(I2C1, DISABLE);
            I2C_GenerateSTOP(I2C1, ENABLE);
        }
        while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
        data[i] = I2C_ReceiveData(I2C1);
    }
    I2C_AcknowledgeConfig(I2C1, ENABLE);
}


void AHT10_Init(void)
{
    uint8_t cmd[3] = {0xE1, 0x08, 0x00};
    I2C_Write(AHT10_ADDR, cmd, 3);
    DelayMs(500);   
}

uint8_t AHT10_Read(float *temp, float *humi)
{
    uint8_t cmd[3] = {0xAC, 0x33, 0x00};
    uint8_t data[6];

    I2C_Write(AHT10_ADDR, cmd, 3);
    DelayMs(80); 

    I2C_Read(AHT10_ADDR, data, 6);

    if (data[0] & 0x80) return 1; 

    uint32_t raw_humi = ((uint32_t)data[1] << 12) | ((uint32_t)data[2] << 4) | (data[3] >> 4);
    uint32_t raw_temp = ((uint32_t)(data[3] & 0x0F) << 16) | ((uint32_t)data[4] << 8) | data[5];

    *humi = ((float)raw_humi / 1048576.0f) * 100.0f;
    *temp = ((float)raw_temp / 1048576.0f) * 200.0f - 50.0f;

    return 0;
}