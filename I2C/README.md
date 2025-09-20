# BÀI TẬP VỀ I2C MÔN HỆ THỐNG NHÚNG TẠI PTIT.
# "- Cấu hình STM32 là Master I2C. 
# - Giao tiếp với một EEPROM hoặc cảm biến I2C để đọc/ghi dữ liệu. Hiển thị dữ liệu đọc được lên màn hình terminal qua UART."

# Giới thiệu & mục tiêu.
Mục tiêu chính: 
- Hiểu cách cấu hình I2C1 trên STM32F103 để giao tiếp với cảm biến AHT10.

- Thực hành gửi và nhận dữ liệu qua bus I2C (SCL, SDA).

- Đọc và hiển thị nhiệt độ và độ ẩm từ cảm biến.

- Kết hợp với USART1 để gửi kết quả ra terminal.

Yêu cầu: 



Phần cứng: 

- STM32F103C8T6 (Blue Pill hoặc board tương tự).

- Cảm biến AHT10 (I2C interface).

- Kết nối dây:

- PB6 → SCL

- PB7 → SDA

- 3.3V → VCC

- GND → GND

- USB-UART để quan sát dữ liệu trên PC.

Phần mềm:

- IDE: Keil uVision / STM32CubeIDE / PlatformIO.

- STM32 Standard Peripheral Library (STM32F10x_StdPeriph_Driver).

- Serial Monitor (Hercules, Tera Term, PuTTY, …).
