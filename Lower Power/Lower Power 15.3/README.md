# BÀI TẬP VỀ LOWER POWER MÔN HỆ THỐNG NHÚNG CỦA PTIT.
# " Bài tập 3: Viết chương trình cho STM32 định kỳ thức dậy gửi dữ liệu UART lên máy tính sau đó chuyển sang chế độ Standby. 
# " Đo điện năng tiêu thụ khi gửi và khi Standby."

# CÁC BƯỚC THỰC HIỆN.
# Bước 1: Khởi tạo hệ thống và ngoại vi.
- Mục tiêu: Chuẩn bị môi trường hoạt động của MCU gồm CLock, GPIO, và UART.
<img width="569" height="113" alt="image" src="https://github.com/user-attachments/assets/61889292-8a64-4970-8f31-223632706ac6" />

# Giải thích: 
- `"HAL_Init()"` thiết lập SysTick và các chức năng cơ bản.

- `"SystemClock_Config()"` dùng PLL nhân 9, từ HSE (8 MHz) → 72 MHz.

- `"MX_GPIO_Init()"` cấu hình PA0 là output, PA1 là input có ngắt ngoài.

- `"MX_USART1_UART_Init()"` thiết lập UART1 Baudrate 115200, truyền/nhận 8-bit.

# Bước 2: Gửi dữ liệu UART nhiều lần.
- Mục tiêu: Gửi chuỗi dữ liệu qua UART trước khi MCU đi ngủ.
<img width="808" height="124" alt="image" src="https://github.com/user-attachments/assets/de8cb231-a19f-4ad5-b408-29b1cd5a1775" />

# Giải thích:
- Vòng for chạy 50 lần, mỗi lần gửi 1 chuỗi.

- `"HAL_UART_Transmit()"` truyền dữ liệu qua UART1.

- `"HAL_Delay(100)"` giúp quan sát rõ dữ liệu gửi trên Terminal.

# Bước 3: Chuẩn bị vào chế độ Standby.
- Mục tiêu: Dọn dẹp cờ và bật pin đánh thức trước khi vào Standby.
<img width="871" height="103" alt="image" src="https://github.com/user-attachments/assets/e5a93ee0-0f27-47fa-ae3f-41a0f0fbdfe4" />

# Giải thích:
- MCU cần xóa cờ WU cũ để tránh tự đánh thức lại.

- `"PWR_WAKEUP_PIN1"` tương ứng chân PA1 trên STM32F1.

# Bước 4: Vào chế độ Standby.
<img width="916" height="62" alt="image" src="https://github.com/user-attachments/assets/98d414c9-a019-4484-87af-947811cd15b6" />

# Giải thích:
- Khi thực hiện lệnh, CPU ngừng hoạt động, RAM bị xóa, chỉ RTC và pin wakeup còn duy trì.
- MCU sẽ reset lại từ đầu chương trình khi được đánh thức.

# Bước 5: Cấu hình GPIO và ngắt ngoài.
- Mục tiêu: Cấu hình PA1 làm ngõ vào, kích hoạt ngắt cạnh lên.
<img width="885" height="169" alt="image" src="https://github.com/user-attachments/assets/1a908c4e-bb36-4c94-ba0f-bd28040bb247" />

# Giải thích:
- Khi PA1 từ mức HIGH -> LOW -> HIGH, ngắt được kích hoạt.
- `"EXTI1_IRQn"` xử lý ngắt cho chân PA1.

# Bước 6: Sau khi đánh thức.
- Mục tiêu: Khi nhấn PA1, MCU reset và chạy lại từ main().

- Do Standby làm mất RAM, MCU reset lại hoàn toàn.

- Quá trình khởi động lại giống như sau khi cấp nguồn.

- UART tiếp tục gửi chuỗi `"STM32 wakeup and send UART"` như ban đầu.

Link demo: https://drive.google.com/drive/folders/1qY_uUcnnjZzl0eb7vgiRicecC6W90-sx


