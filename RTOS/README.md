# 🧩 FreeRTOS LED Blinking – STM32F103C8T6

## 🎯 Mục tiêu
Tạo chương trình sử dụng **FreeRTOS** để điều khiển **3 LED** nhấp nháy ở **3 tần số khác nhau**:
- LED1 → 3 Hz  
- LED2 → 10 Hz  
- LED3 → 25 Hz  

Dự án chạy trên **vi điều khiển STM32F103C8T6** (board Blue Pill), dùng **Keil uVision** và **HAL + FreeRTOS (CMSIS-RTOS)**.

---

## ⚙️ Cấu trúc chương trình
### 1️⃣ File chính: `main.c`
```c
#include "main.h"
#include "cmsis_os.h"
```
- `main.h`: khai báo hàm, chân LED, hàm khởi tạo.  
- `cmsis_os.h`: cung cấp API FreeRTOS (osThreadDef, osDelay, vTaskDelay...).

---

### 2️⃣ Khai báo các task
```c
osThreadId defaultTaskHandle;
osThreadId myTask02Handle;
osThreadId myTask03Handle;
osThreadId myTask04Handle;
```
- Mỗi `osThreadId` lưu thông tin của một task đang chạy.  

---

### 3️⃣ Hàm `main()`
```c
int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
```
- Khởi tạo HAL, clock hệ thống, và GPIO cho LED.  

#### ➤ Tạo các task:
```c
  osThreadDef(myTask02, StartTask02, osPriorityBelowNormal, 0, 128);
  myTask02Handle = osThreadCreate(osThread(myTask02), NULL);

  osThreadDef(myTask03, StartTask03, osPriorityNormal, 0, 128);
  myTask03Handle = osThreadCreate(osThread(myTask03), NULL);

  osThreadDef(myTask04, StartTask04, osPriorityAboveNormal, 0, 128);
  myTask04Handle = osThreadCreate(osThread(myTask04), NULL);
```
- Mỗi task điều khiển một LED riêng biệt.  
- Độ ưu tiên tăng dần: Task02 < Task03 < Task04.  

#### ➤ Bắt đầu Scheduler:
```c
  osKernelStart();
```
- Kích hoạt bộ lập lịch FreeRTOS, CPU bắt đầu quản lý task song song.  

---

### 4️⃣ Cấu hình Clock
```c
PLL Source: HSE (8MHz) × 9 = 72 MHz
```
- Cấu hình chuẩn cho STM32F103C8T6.  
- Đảm bảo FreeRTOS tick chạy chính xác.  

---

### 5️⃣ Cấu hình GPIO
```c
__HAL_RCC_GPIOA_CLK_ENABLE();
GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2;
GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
```
- 3 chân LED: **PA0**, **PA1**, **PA2**.  
- Output Push-Pull, tốc độ thấp, không kéo lên/xuống.

---

## 🧠 Các Task LED

| Task | GPIO | Tần số nháy | Chu kỳ (ms) | Delay (ms) | Ưu tiên |
|------|------|--------------|--------------|-------------|----------|
| Task02 | PA0 | 3 Hz | 333 | 166 | Below Normal |
| Task03 | PA1 | 10 Hz | 100 | 50 | Normal |
| Task04 | PA2 | 25 Hz | 40 | 20 | Above Normal |

### 🔹 Task 1 – LED1 (3 Hz)
```c
void StartTask02(void const * argument)
{
  for(;;)
  {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_0);
    vTaskDelay(pdMS_TO_TICKS(166));
  }
}
```

### 🔹 Task 2 – LED2 (10 Hz)
```c
void StartTask03(void const * argument)
{
  for(;;)
  {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1);
    vTaskDelay(pdMS_TO_TICKS(50));
  }
}
```

### 🔹 Task 3 – LED3 (25 Hz)
```c
void StartTask04(void const * argument)
{
  for(;;)
  {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_2);
    vTaskDelay(pdMS_TO_TICKS(20));
  }
}
```

---

## 🚨 Error Handler
```c
void Error_Handler(void)
{
  __disable_irq();
  while (1) {}
}
```
- Nếu có lỗi clock hoặc khởi tạo, MCU sẽ dừng tại đây để debug.

---

## 💬 Gợi ý mở rộng
- Tạo **1 task duy nhất** và truyền tham số (GPIO, tần số) để giảm trùng code.  
- Dùng **vTaskDelayUntil()** để điều khiển nháy chính xác hơn.  
- Thêm UART hoặc LCD để hiển thị trạng thái từng task.  

---

## 🧾 Tóm tắt
Dự án này minh họa cách tạo **nhiều task FreeRTOS song song**, điều khiển LED với tần số khác nhau bằng **vTaskDelay()**.  
Mỗi LED là một task độc lập, giúp làm quen với cơ chế **lập lịch ưu tiên và đa nhiệm** của FreeRTOS.

---

✍️ *Tác giả: ManhLong*  
📅 *Ngày tạo: Tháng 10 / 2025*  
💡 *Môi trường: Keil uVision + STM32CubeMX + FreeRTOS*
