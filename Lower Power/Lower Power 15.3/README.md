# BÀI TẬP VỀ LOWER POWER MÔN HỆ THỐNG NHÚNG CỦA PTIT.
# " Bài tập 3: Viết chương trình cho STM32 định kỳ thức dậy gửi dữ liệu UART lên máy tính sau đó chuyển sang chế độ Standby. 
# " Đo điện năng tiêu thụ khi gửi và khi Standby."

# CÁC BƯỚC THỰC HIỆN.
# Bước 1: Khởi tạo hệ thống và ngoại vi.
- Mục tiêu: Chuẩn bị môi trường hoạt động của MCU gồm CLock, GPIO, và UART.
<img width="569" height="113" alt="image" src="https://github.com/user-attachments/assets/61889292-8a64-4970-8f31-223632706ac6" />

- Giải thích: 
- `"HAL_Init()"` thiết lập SysTick và các chức năng cơ bản.

- `"SystemClock_Config()"` dùng PLL nhân 9, từ HSE (8 MHz) → 72 MHz.

- `"MX_GPIO_Init()"` cấu hình PA0 là output, PA1 là input có ngắt ngoài.

- `"MX_USART1_UART_Init()" thiết lập UART1 Baudrate 115200, truyền/nhận 8-bit.
