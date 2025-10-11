# RTOS

FreeRTOS LED Blinking Example (STM32F103C8T6)

## Mô tả
Project này sử dụng FreeRTOS để quản lý 3 task chạy song song, mỗi task điều khiển 1 LED nhấp nháy ở tần số khác nhau.

## Thông tin phần cứng
- MCU: STM32F103C8T6
- Clock: HSE 8 MHz, PLL x9 → 72 MHz
- LED1: PA0
- LED2: PA1
- LED3: PA2

## Cấu trúc thư mục
```
RTOS/
├── MDK/              # Project Keil uVision (.uvprojx, .uvoptx, startup,…)
├── USER/             # main.c, main.h
└── README.md
```

## Lưu ý
- FreeRTOSConfig.h KHÔNG được include trong package theo yêu cầu. Bạn cần thêm file FreeRTOSConfig.h phù hợp (với config for STM32F1) vào MDK/ trước khi build.
- Thay thế startup & system file bằng file chính thức từ CubeMX/Keil để build chuẩn.
