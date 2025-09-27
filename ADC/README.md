# BÀI TẬP VỀ ADC MÔN HỆ THỐNG NHÚNG CỦA PTIT.
# "- Cấu hình một kênh ADC để đọc giá trị từ một biến trở hoặc cảm biến nhiệt độ.
# - Chuyển đổi giá trị này thành điện áp (mV) và hiển thị lên terminal."

# Giới thiệu & mục tiêu.
Giới thiệu: 
- Đọc giá trị điện áp analog từ chân PA0 thông qua bộ ADC1.

- Chuyển đổi giá trị ADC sang điện áp (mV) dựa trên VREF = 3.3V.

- Gửi dữ liệu ADC và điện áp đo được tới máy tính qua UART1 (PA9 - TX, PA10 - RX).

- Kết quả có thể quan sát bằng phần mềm terminal như PuTTY hoặc TeraTerm.


Mục tiêu:
- Hiểu cách cấu hình và sử dụng ADC để đọc tín hiệu analog.

- Hiểu cách cấu hình UART để truyền dữ liệu tới máy tính.

- Kết hợp ADC và UART trong một chương trình thực tế.

- Ứng dụng làm nền tảng cho các dự án như đo cảm biến ánh sáng, nhiệt độ, độ ẩm,... rồi hiển thị trên PC.


Yêu cầu:
Phần cứng

- STM32F103C8T6 (Blue Pill).

- USB to TTL 3.3V (kết nối TX, RX, GND).

- Biến trở hoặc cảm biến analog nối vào PA0.

- LED tích hợp sẵn ở PC13.

Phần mềm

- Keil uVision / STM32CubeIDE / PlatformIO.

- STM32 StdPeriph Library.
