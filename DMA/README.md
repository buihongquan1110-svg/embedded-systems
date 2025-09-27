# BÀI TẬP VỀ DMA MÔN HỆ THỐNG NHÚNG TẠI PTIT.
# "- Cấu hình DMA để truyền dữ liệu từ ADC vào bộ nhớ RAM. 
# - Khi quá trình truyền hoàn tất, một ngắt được kích hoạt để xử lý dữ liệu.
# - Hiển thị dữ liệu đã được truyền thành công lên terminal."

# Giới thiệu & mục tiêu.
Giới thiệu:
- Đọc giá trị ADC từ chân PA0 bằng ADC1.

- Sử dụng DMA1 Channel1 để tự động ghi dữ liệu vào bộ đệm ADC_Buffer.

- Sau khi DMA truyền xong, dữ liệu được gửi ra máy tính qua UART1.

- Kết quả hiển thị trên terminal như PuTTY / TeraTerm.

Mục tiêu: 
- Thực hành cấu hình UART1 để truyền dữ liệu.

- Thực hành cấu hình Timer2 để tạo hàm delay.

- Sử dụng ADC + DMA để đọc tín hiệu analog mà không chiếm CPU.

- Hiển thị dữ liệu ADC qua UART.

Yêu cầu:
Phần cứng: 

- STM32F103C8T6 (Blue Pill).

- Chân PA0 nối với biến trở (hoặc tín hiệu analog).

- Module USB–UART (PA9 = TX, PA10 = RX).

- Máy tính với phần mềm terminal (PuTTY, TeraTerm).

Phần mềm:

- Keil uVision / STM32CubeIDE.

- STM32 Standard Peripheral Library.


# CÁC BƯỚC THỰC HIỆN.
# BƯỚC 1 - CẤU HÌNH USART.
- Bật clock cho GPIOA và USART1.

- PA9 = TX (AF_PP), PA10 = RX (IN_FLOATING).

- Baudrate = 9600, 8N1.
<img width="884" height="552" alt="image" src="https://github.com/user-attachments/assets/84d751b8-4014-4794-94bd-a98c4100e333" />
- Hàm gửi dữ liệu qua USART:
<img width="688" height="223" alt="image" src="https://github.com/user-attachments/assets/fe35295c-d7df-4b0c-9fce-29db5f52ff5f" />

# BƯỚC 2 - CẤU HÌNH TIMER2 HÀM DELAY.
- Timer2 clock = 72 MHz.

- Prescaler = 7200 → 1 tick = 0.1ms.

- Dùng while để tạo delay theo mili giây.
<img width="887" height="384" alt="image" src="https://github.com/user-attachments/assets/554fe0f1-b512-4f7e-a61c-82a7a2eeb8c9" />

# BƯỚC 3 - CẤU HÌNH ADC1 VÀ DMA CHANNEL1.
- PA0 = analog input.

- ADC1: chế độ Continuous Conversion.

- DMA1: chế độ Circular, buffer size = 16 (ADC_Buffer[16]).
<img width="1014" height="451" alt="image" src="https://github.com/user-attachments/assets/f00e6119-7427-42be-966e-4bb95cc536c0" />

<img width="893" height="648" alt="image" src="https://github.com/user-attachments/assets/6307a813-7c1a-4642-bf36-245248fc7da5" />




