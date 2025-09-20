# BÀI TẬP VỀ SPI MÔN HỆ THỐNG NHÚNG TẠI PTIT.
# "- Cấu hình STM32 là Master SPI. 
# - Kết nối với một module SPI đơn giản (Cảm biến, Màn hình, SD-Card).
# - Gửi một byte dữ liệu và nhận phản hồi, hiển thị dữ liệu nhận được lên terminal."

# Giới thiệu & mục tiêu.
- Dự án này sử dụng STM32F103C8T6 (Blue Pill) để giao tiếp với OLED SSD1306 (128x64) qua chuẩn SPI.
- Ngoài ra, UART1 được dùng để debug dữ liệu và Timer2 tạo ngắt định kỳ.


Mục tiêu:

- Hiểu cách cấu hình SPI1 trên STM32.

- Truyền nhận dữ liệu SPI.

- Hiển thị chuỗi ký tự trên OLED SSD1306.

- Debug dữ liệu qua UART.


Yêu cầu phần cứng: 

- STM32F103C8T6 (hoặc STM32F103xx tương đương).

- Màn hình OLED SSD1306 giao tiếp SPI (128x64).

- USB-UART để debug (nếu cần).

- Dây nối, breadboard.
