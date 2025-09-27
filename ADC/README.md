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

# CÁC BƯỚC THỰC HIỆN.
# Bước 1 - Cấu hình LED(PC13).
- Bật clock cho GPIOC.

- Đặt chân PC13 ở chế độ Output Push-Pull.
<img width="714" height="258" alt="image" src="https://github.com/user-attachments/assets/cbbed0e8-d3d6-4bef-8631-ac163d96a63e" />

# Bước 2 - Cấu hình USART(PA9-TX, PA10-RX).
- PA9 = TX → AF_PP.

- PA10 = RX → IN_FLOATING.

- Baudrate = 9600.
<img width="736" height="530" alt="image" src="https://github.com/user-attachments/assets/1a85e78b-fcf6-4f94-bf96-b9c9c7f1ce80" />

# Bước 3 - Hàm gửi chuỗi UART.
- Gửi từng ký tự cho đến khi hết chuỗi.
<img width="846" height="145" alt="image" src="https://github.com/user-attachments/assets/e1a91f82-85e8-479d-a1ff-6003b7c28be1" />

# Bước 4 - Cấu hình ADC1(PA0).
- PA0 = Analog input.

- ADC mode = Independent.

- Calibration trước khi dùng.
<img width="866" height="512" alt="image" src="https://github.com/user-attachments/assets/0e37792e-44f4-404b-80c1-9d0125e93207" />

# Bước 5 - Hàm đọc ADC.
- Chọn kênh ADC_Channel_0.

- Bắt đầu chuyển đổi bằng phần mềm.

- Chờ cờ EOC rồi trả về giá trị.
<img width="828" height="145" alt="image" src="https://github.com/user-attachments/assets/b9e82dfa-c7b9-4501-be31-aaaf58b050a3" />

# Bước 6 - Hàm main().
- Khởi tạo LED, UART, ADC

- Gửi thông báo chào mừng

- Trong vòng lặp:

Đọc giá trị ADC

Tính điện áp theo công thức

Gửi dữ liệu qua UART
<img width="835" height="369" alt="image" src="https://github.com/user-attachments/assets/de1ae6dc-0c60-464a-8fb3-cbe734aacc10" />

# KẾT QUẢ.
Trong main() mình viết vòng lặp while(1), mỗi lần sẽ:

Đọc giá trị ADC từ PA0

Tính toán ra điện áp (mV)

Gửi chuỗi "ADC = ..., Voltage = ... mV" qua UART

Delay một chút rồi lặp lại
Vì thế trên PuTTY (hoặc TeraTerm) bạn sẽ thấy dữ liệu chạy liên tục, kiểu:

  `"ADC = 512, Voltage = 412 mV"`
  `"ADC = 1024, Voltage = 825 mV"`
  `"ADC = 1536, Voltage = 1237 mV"`
  `"ADC = 2048, Voltage = 1650 mV"`
  ...
  
  
  
  
  
