/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : FreeRTOS - 2 Task: 
  * 1. Blink LED Heartbeat (PA5)
  * 2. EXTI Button (PA1) unblocks Task to blink Warning LED (PA0)
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "task.h"
#include "semphr.h"

/* Private variables ---------------------------------------------------------*/
osThreadId BlinkTaskHandle; // Task 1: Dùng de Blink LED (heartbeat)
osThreadId ExtiTaskHandle;  // Task 2: Dùng de xu ly ngat (Warning)
SemaphoreHandle_t xButtonSemaphore;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
void StartBlinkTask(void const * argument); // Khai bao Task 1
void StartExtiTask(void const * argument);  // Khai bao Task 2
void Error_Handler(void);

/* -------------------- MAIN -------------------- */
int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init(); // Se khoi tao PA0, PA1, và PA5

  // Tao semaphore nhi phân (ban dau không có tín hieu)
  // Task 2 se cho semaphore nay
  xButtonSemaphore = xSemaphoreCreateBinary();

  // Tao Task 1: Blink LED (Heartbeat) - Theo yeu cau "1 Task Blink LED"
  osThreadDef(BlinkTask, StartBlinkTask, osPriorityNormal, 0, 128);
  BlinkTaskHandle = osThreadCreate(osThread(BlinkTask), NULL);

  // Tao Task 2: Xu lý ngat - Theo yeu cau "1 Task xu lý khi có ngat ngoài"
  osThreadDef(ExtiTask, StartExtiTask, osPriorityNormal, 0, 128);
  ExtiTaskHandle = osThreadCreate(osThread(ExtiTask), NULL);

  // Bat dau Scheduler
  osKernelStart();

  while (1) {}
}

/* -------------------- TASK 1: Blink LED (Heartbeat) -------------------- */
/**
  * @brief Day LÀ "Task Blink LED".
  * Task nay chay doc lap, nhap nháy LED PA5 de báo hieu he thong dang hoat dong.
  */
void StartBlinkTask(void const * argument)
{
  for(;;)
  {
    // Nhap nháy LED PA5 moi 500ms
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5); 
    osDelay(500);
  }
}

/* -------------------- TASK 2: Xu lý ngat (Warning) -------------------- */
/**
  * @brief Day la "Task xu lý khi có ngat".
  * Task này o che do Block, cho den khi ISR cap semaphore.
  */
void StartExtiTask(void const * argument)
{
  for(;;)
  {
    // Buoc 1: Task o che do Block, cho tin hieu tu nut nhan (ISR)
		// Dang o che do Block
    if (xSemaphoreTake(xButtonSemaphore, portMAX_DELAY) == pdTRUE)
    {
      // BUOC 2: Da nhan duoc tin hieu (ngat xay ra).
      
      // Bat den canh bao (PA0) nhap nhay 5 lan
      for (int i = 0; i < 5; i++)
      {
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_0);
        osDelay(200); // Delay
      }
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET); // Tat LED 
    }
  }
}

/* -------------------- Callback: Ngat ngoai (PA1) -------------------- */
/**
  * @brief Ham này duoc goi khi có ngat tu PA1.
  * Nhiem vu cua nó là "Give" semaphore de dánh thuc Task 2 (StartExtiTask).
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == GPIO_PIN_1) // Dung la nut PA1
  {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    
    // Cap semaphore tu trong ISR
    xSemaphoreGiveFromISR(xButtonSemaphore, &xHigherPriorityTaskWoken);
    
    // Yeu cau chuyen ngu canh ngay lap tuc neu Task 2 có uu tiên cao hon
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
  }
}

/* -------------------- GPIO Init -------------------- */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOA_CLK_ENABLE();

  // --- Cau hình LED Canh bao (Task 2) ---
  // PA0 - Output
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);

  // --- Cau hình nút nhan (Ngat) ---
  // PA1 - Ngat canh xuong
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP; 
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  // --- Cau hình LED Blink (Task 1) ---
  // PA5 - Output
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

  // --- Cau hình NVIC cho ngat ---
  HAL_NVIC_SetPriority(EXTI1_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);
}

/* -------------------- Clock config -------------------- */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) Error_Handler();

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    Error_Handler();
}

/* -------------------- Error Handler -------------------- */
void Error_Handler(void)
{
  __disable_irq(); // Tat toàn bo ngat
  while (1)
  {
    // Nháy LED PA0 
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_0);
    HAL_Delay(300);
  }
}