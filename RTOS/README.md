# BÀI TẬP VỀ RTOS MÔN HỆ THỐNG NHÚNG CỦA PTIT.
# Tạo một project FreeRTOS.
# Viết 1 chương trình sử dụng FreeRTOS thực hiện:
# Nhấp nháy 3 LED ở 3 tần số khác nhau: 3Hz, 10Hz và 25Hz.
# Sử dụng 3 hàm độc lập cho 3 tác vụ.
# Nâng cao (Không bắt buộc): Viết 1 hàm tác vụ duy nhất và truyền vào tham số để thay đổi chân nháy LED, tần số nháy.
# Lưu ý sử dụng: vTaskDelay hoặc vTaskUntil.
## Mô tả
Dự án này sử dụng FreeRTOS để điều khiển 3 LED nhấp nháy ở 3 tần số khác nhau:

LED1: 3 Hz → nhấp nháy mỗi ~166 ms

LED2: 10 Hz → nhấp nháy mỗi ~50 ms

LED3: 25 Hz → nhấp nháy mỗi ~20 ms

Vi điều khiển: STM32F103C8T6
IDE: Keil uVision
Thư viện: HAL + CMSIS-RTOS v1 (FreeRTOS)

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
