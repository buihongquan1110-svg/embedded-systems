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


# CÁC BƯỚC THỰC HIỆN.
# Bước 1 — Bật clock cho SPI1 và GPIO.
<img width="794" height="35" alt="image" src="https://github.com/user-attachments/assets/ea2f7997-10dd-4200-8fe9-f401c4e68971" />

# Bước 2 — Cấu hình chân SPI1.
- PA5 (SCK): Alternate Function Push-Pull.

- PA7 (MOSI): Alternate Function Push-Pull.

- PA6 (MISO): Input Floating.

- PA4 (CS): Output Push-Pull (dùng làm Chip Select cho OLED).
<img width="462" height="323" alt="image" src="https://github.com/user-attachments/assets/f7a1fad4-a639-4a48-b80e-da933f4835db" />

# Bước 3 — Cấu hình SPI1 ở chế độ Master.
- Full Duplex.

- 8-bit data.

- CPOL = Low, CPHA = 1Edge.

- NSS = Soft.

- BaudRatePrescaler = 16.

- FirstBit = MSB.
<img width="647" height="254" alt="image" src="https://github.com/user-attachments/assets/ee075296-6372-4b75-a87d-838193d157f3" />

# Bước 4 — Hàm truyền nhận SPI.
<img width="521" height="140" alt="image" src="https://github.com/user-attachments/assets/9d6507dd-83d6-4861-b483-58e1bbdc3122" />

# Bước 5 — Viết hàm main().
- Trong hàm main(), chương trình được thực hiện theo các bước sau:

# 1. Khởi tạo hệ thống.

- Gọi SystemInit() để thiết lập clock cho STM32.

- Thực hiện các hàm cấu hình: GPIO_Config(), SPI1_Init(), USART1_Init(), OLED_Init().

- Mục tiêu: đảm bảo GPIO, SPI, UART và OLED đã sẵn sàng.

# 2. In thông báo qua UART.

- Gửi chuỗi "STM32 SPI + OLED demo\r\n" để báo cho người dùng rằng hệ thống đã khởi tạo thành công.

# 3. Hiển thị nội dung trên OLED.

- Gọi OLED_Clear() để xóa màn hình.

- Dùng OLED_DrawString() để hiển thị dòng chữ `"HELLO STM32 SPI"` ở dòng đầu tiên và "JUST FOR FUN" ở dòng thứ hai.

# 4. Vòng lặp chính.

- Trong vòng while(1), chương trình thực hiện:

- Truyền thử 1 byte dữ liệu 0x55 qua SPI bằng SPI1_Transfer(0x55).

- Nhận lại giá trị phản hồi từ slave, lưu vào biến rx.

- Gửi chuỗi debug qua UART với thông tin: "TX=0x55, RX=0xXX".

- Chờ 1 giây (Delay_ms(1000)) rồi lặp lại.
<img width="927" height="567" alt="image" src="https://github.com/user-attachments/assets/2bda5ecd-891e-4904-a699-bd4f8a7ace8d" />


# KẾT QUẢ.
- OLED SSD1306 khởi động thành công, hiển thị chuỗi ký tự.

- Dữ liệu truyền SPI được gửi/nhận (TX/RX) và in qua UART.

- Timer2 tạo ngắt mỗi giây để gửi dữ liệu mới.
- Khi chạy, UART sẽ in:
  `"STM32 SPI + UART + OLED demo
  TX=0x55, RX=0xXX
  TX=0x56, RX=0xXX
  ..."`
- Màn hình OLED sẽ hiển thị:
  `"JUST FOR FUN"`
- Link demo: https://drive.google.com/drive/folders/1WQcWl2md6d8chsdR09YDq3CeYabEDcp3



