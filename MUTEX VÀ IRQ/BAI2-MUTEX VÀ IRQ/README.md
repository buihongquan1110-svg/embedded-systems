# BÀI TẬP VỀ MUTEX VÀ IRQ MÔN HỆ THỐNG NHÚNG TẠI PTIT.
# - Bài 2: Viết chương trình có 2 Task cùng in dữ liệu qua UART, không sử dụng Mutex. Hiển thị được sự xung đột. "

# CÁC BƯỚC THỰC HIỆN.
# 1. CẤU HÌNH UART.
<img width="654" height="304" alt="image" src="https://github.com/user-attachments/assets/13c9b092-a045-4b1e-969f-a7aecfdb2f24" />

# 2. Task mặc định(không làm gì).
<img width="616" height="174" alt="image" src="https://github.com/user-attachments/assets/bb795668-d866-47c1-83b0-0d96ebcf205e" />
- Giải thích: giữ cấu trúc hệ thống, tránh chiếm CPU quá mức.

# 3. Task gửi `"aaaaa\r\n"` theo từng ký tự.
<img width="946" height="277" alt="image" src="https://github.com/user-attachments/assets/fd88e5b6-2d7c-431c-80d3-1c11777efd4b" 
- Gửi từng byte (không gửi nguyên chuỗi) giúp dễ thấy hiện tượng xen kẽ.

- osDelay(50) làm cho task cho CPU nhường chỗ — tạo cơ hội Task03 xen vào.

- HAL_MAX_DELAY cho hàm UART block tới khi byte được đưa vào HAL driver. Tùy driver/CMSIS, nếu HAL UART dùng interrupt/DMA, byte sẽ được gửi ra buffer và hàm return nhanh; tuy nhiên trong ví dụ này mục tiêu là minh họa chia sẻ tài nguyên không an toàn.

# 4. Task gửi `"bbbb\r\n"` theo từng ký tự.
<img width="918" height="268" alt="image" src="https://github.com/user-attachments/assets/28f1105f-5a45-413d-8238-bb3c2c921219" 

- Giải thích: tương tự Task02 nhưng gửi ký tự b — khi chạy cùng lúc, kết quả trên terminal sẽ bị xen kẽ.

# 5. Cấu hình GPIO.
<img width="725" height="310" alt="image" src="https://github.com/user-attachments/assets/428c2139-3862-44e0-bb9a-c64e0da4e885" />

# 6. Error Handler.
<img width="657" height="160" alt="image" src="https://github.com/user-attachments/assets/93748ad5-8bdb-4cd9-b638-84e5954c189a" />

# 7. Kết quả mong đợi.
- Khi chạy, bạn sẽ thấy chuỗi trên terminal bị xen kẽ — ví dụ:

`"=== UART No Mutex Demo ==="`
`"ababab"`
`"aababb"`
`"aaabbb"~
`"ababb"`
`"..."`
- Giải thích: vì 2 task gọi HAL_UART_Transmit() xen kẽ mà không có khóa (mutex), nên byte từ task này và task khác có thể chen vào buffer/tổ hợp gửi, dẫn tới chuỗi không nguyên vẹn.





