# BÀI TẬP VỀ UART MÔN HỆ THỐNG NHÚNG TẠI PTIT.
# "- Cấu hình UART trên STM32F1.
# - Viết chương trình gửi chuỗi ""Hello from STM32!"" tới máy tính. 
# - Sử dụng phần mềm terminal để hiển thị chuỗi này.
# - Khi gửi một ký tự từ máy tính, STM32 sẽ phản hồi lại ký tự đó.
# - Khi gửi chuỗi ""ON"" thì bật đèn, ""OFF"" thì tắt đèn.
# - Sử dụng ngắt để nhận chuỗi dữ liệu."


# Giới thiệu & mục tiêu.
Mục tiêu chính:
+ Giúp người mới làm quen với STM32 hiểu rõ quy trình cấu hình UART từ đầu đến cuối.

+ Minh hoạ cách kết hợp USART1 (PA9/PA10) với LED trên PC13 để tạo ví dụ thực tế.

+ Giải thích ý nghĩa từng dòng lệnh cấu hình để dễ dàng chỉnh sửa và tái sử dụng.

+ Cung cấp nền tảng để phát triển các ứng dụng giao tiếp UART phức tạp hơn (ví dụ: giao tiếp module GPS, ESP8266, máy tính...).

Yêu cầu:
- Board phát triển chứa MCU STM32F103 (F103C8 / F103RB...).

- Thư viện STM32 Standard Peripheral Library (StdPeriphLib) đã được thêm vào project.

- Trình biên dịch / IDE: Keil uVision / STM32CubeIDE / TrueSTUDIO (hướng dẫn chung, không cụ thể IDE).

- Bộ USB‑TTL (3.3V!) để nối với UART (hoặc module phù hợp). Không dùng 5V TTL.

- Kết nối dây: chung GND giữa board và USB‑TTL.


# CÁC BƯỚC THỰC HIỆN.
# Bước 1 — Tạo project & thêm StdPeriphLib.
- Tạo project mới cho STM32F103.

- Thêm file startup (startup_stm32f10x.s) và các file thư viện StdPeriphLib vào project.

- Đảm bảo include path trỏ đến thư mục headers của StdPeriphLib.

# Bước 2 — Bật clock cho ngoại vi cần dùng.
<img width="608" height="127" alt="image" src="https://github.com/user-attachments/assets/afc4e52c-1371-4629-a11e-63407f9acc61" />


Giải thích:

- USART1 nằm trên APB2, cần bật.

- GPIOA để cấu hình PA9/PA10.

- AFIO để cho phép chế độ alternate function.

# Bước 3 — Cấu hình GPIO cho TX/RX.
- PA9: TX → GPIO_Mode_AF_PP (Alternate Function Push-Pull).

- PA10: RX → GPIO_Mode_IN_FLOATING (Input floating).
<img width="476" height="235" alt="image" src="https://github.com/user-attachments/assets/e6e12f44-0627-400f-b906-245f91fe9d5d" />

# Bước 4 — Cấu hình chân LED (PC13).
<img width="670" height="252" alt="image" src="https://github.com/user-attachments/assets/d48aa07c-5b5a-4671-911a-ff2b39d5e76b" />

# Bước 5 — Khởi tạo USART1.
- Chọn baudrate, kích hoạt TX & RX.
<img width="539" height="117" alt="image" src="https://github.com/user-attachments/assets/f2b872d0-1c02-4eb0-9b26-1c13c54a1976" />

# Bước 6 — Bật ngắt khi có dữ liệu (RXNE).
<img width="532" height="51" alt="image" src="https://github.com/user-attachments/assets/fa48d425-ff56-4b51-ad29-577209b478b5" />
- Giải thích: Khi có byte nhận xong, cờ RXNE sẽ set và gây ngắt vào USART1_IRQHandler.

# Bước 7 — Cấu hình NVIC cho USART1.
<img width="498" height="144" alt="image" src="https://github.com/user-attachments/assets/768357ea-eb7c-41d2-aa45-e638a390e2d1" />

# Bước 8 — Viết hàm truyền chuỗi.
<img width="786" height="155" alt="image" src="https://github.com/user-attachments/assets/3b386852-c8a6-470a-b8cc-3a2bf524306a" />
- Hàm này gửi từng ký tự và đợi cờ TXE.

# Bước 9 — Viết USART1_IRQHandler (ví dụ xử lý lệnh ON/OFF).
- Ý tưởng: đọc từng ký tự, lưu vào buffer rx_data. Khi gặp \r hoặc \n xử lý lệnh.

- Kiểm tra overflow buffer, so sánh chuỗi.
<img width="745" height="666" alt="image" src="https://github.com/user-attachments/assets/4d1358f5-3685-40b4-a509-ae6c005bbaeb" />

# Bước 10 — Hàm main() để khởi động và test.
<img width="668" height="219" alt="image" src="https://github.com/user-attachments/assets/868800fc-69aa-484a-bcf5-f42e52b45302" />


# KẾT QUẢ.
- Khi STM32 khởi động, terminal hiển thị:

Hello from STM32!

- Gõ ON → LED PC13 sáng (GPIO_ResetBits).

- Gõ OFF → LED PC13 tắt (GPIO_SetBits).

- Nếu nhập sai lệnh → terminal phản hồi:

Unknown command

- LED hoạt động đúng theo lệnh từ người dùng qua UART.
- Link demo: https://drive.google.com/drive/folders/128JQ7NboFaNV9Mmz9hb6a1gLwqTgti3s










