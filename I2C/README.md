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


# CÁC BƯỚC THỰC HIỆN.
# Bước 1 — Bật clock cho GPIOB và I2C1.
- Để GPIOB (PB6, PB7) và ngoại vi I2C1 hoạt động, cần bật clock:
<img width="619" height="77" alt="image" src="https://github.com/user-attachments/assets/b3d5ff75-f135-41ff-8bcd-a89972dfc8b8" />

# Bước 2 — Cấu hình chân PB6 (SCL) và PB7 (SDA).
- Cả 2 chân cần để chế độ Alternate Function Open-Drain.

- Open-drain cho phép nhiều thiết bị chia sẻ bus I2C.
<img width="564" height="118" alt="image" src="https://github.com/user-attachments/assets/9fd356c5-8445-4932-99aa-27836eaffe00" />

# Bước 3 — Khởi tạo I2C1 ở chế độ master.
- Tốc độ: 100 kHz (chuẩn I2C).

- Địa chỉ master có thể đặt 0x00 vì không dùng.
<img width="743" height="193" alt="image" src="https://github.com/user-attachments/assets/90cb415b-a44c-4c69-876f-aedda82dd9db" />

# Bước 4 — Hàm ghi dữ liệu qua I2C (Master → Slave).
* Các bước con:
- Kiểm tra bus rảnh.

- Gửi tín hiệu START.

- Gửi địa chỉ slave + chế độ ghi.

- Gửi từng byte dữ liệu.

- Kết thúc bằng STOP.



