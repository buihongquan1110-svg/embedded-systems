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
