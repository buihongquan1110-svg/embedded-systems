# BÀI TẬP VỀ MUTEX VÀ IRQ MÔN HỆ THỐNG NHÚNG CỦA PTIT.
# - Bài 3: Viết chương trình có 2 Task cùng in dữ liệu qua UART có sử dụng Mutex để chia sẻ tài nguyên.A1"

# CÁC BƯỚC THỰC HIỆN.
# 1. Khởi tạo các hệ thống và thư viện.
<img width="809" height="151" alt="image" src="https://github.com/user-attachments/assets/c66d5559-9b3e-449c-9985-c3e80c90ffad" />

<img width="967" height="159" alt="image" src="https://github.com/user-attachments/assets/10434a9e-c5a5-4da5-8620-55b5382b297e" />

Giải thích:

- Import các thư viện cần thiết.

- Khai báo huart1 để cấu hình UART1.

- Các hàm SystemClock_Config, MX_GPIO_Init, MX_USART1_UART_Init dùng để thiết lập hệ thống cơ bản.

# 2. Khai báo Task và Mutex.
<img width="875" height="93" alt="image" src="https://github.com/user-attachments/assets/2c92f807-48e1-4fa3-a0e5-3b0de96323d6" />

Giải thích:

- Tạo 3 handle cho các task.

- `"uartMutexHandle"` là biến lưu handle của mutex dùng để bảo vệ UART.

# 3. Hàm main() - Khởi tạo và tạo task.
<img width="930" height="207" alt="image" src="https://github.com/user-attachments/assets/20be8f7f-cfd0-4f36-a936-1f2ea1bab696" />

- Khởi tạo hệ thống và gửi dòng giới thiệu qua UART.

# Tạo mutex.
<img width="884" height="145" alt="image" src="https://github.com/user-attachments/assets/bbafb488-e870-4fd3-a57a-da99ccc31983" />

- Tạo mutex dùng để đảm bảo chỉ 1 task được phép gửi UART tại 1 thời điểm.

- Nếu tạo mutex thất bại thì gọi Error_Handler().

# Tạo các task.
<img width="852" height="289" alt="image" src="https://github.com/user-attachments/assets/09e1e8e3-4f8e-46b1-9695-3ff9edcf4b96" />

Giải thích:

- `"defaultTask"`: task mặc định (rảnh rỗi).

- `"Task02"`, `"Task03"`: 2 task chính sẽ gửi dữ liệu UART.

- `"osKernelStart()"` khởi chạy hệ điều hành FreeRTOS.

# 4. Viết các hàm khởi tạo.
<img width="774" height="258" alt="image" src="https://github.com/user-attachments/assets/e5117b05-593e-4251-b394-a55213b6480a" />

# 5. Viết các task.
# Default Task (nhàn rỗi).
<img width="740" height="137" alt="image" src="https://github.com/user-attachments/assets/e9b4b590-79f3-453f-9c84-75b957412905" />

# Task 02 - Gửi `"aaaa"`.
<img width="1031" height="289" alt="image" src="https://github.com/user-attachments/assets/f1f25c40-fad8-4236-aae1-67ea106f0424" />

Giải thích:

- `"osMutexWait()"` → Task02 sẽ chờ nếu UART đang bị chiếm.

- Sau khi được quyền, task gửi chuỗi `"aaaaa"`.

- Sau đó `"osMutexRelease()"` trả mutex cho task khác.

# Task 03 - Gửi `"bbbb"`.
<img width="1006" height="327" alt="image" src="https://github.com/user-attachments/assets/c9fc7fd4-b0a1-4c1d-88f7-4951efc795e8" />
Giải thích:

- Task03 hoạt động tương tự Task02 nhưng gửi chuỗi khác (bbbbb).

# 6. Error Handler.
<img width="828" height="124" alt="image" src="https://github.com/user-attachments/assets/cc65aba0-a440-43b3-8b85-051bb1a556a5" />

# 7. Kết quả.


`"=== UART WITH MUTEX Demo ==="`


`"aaaaa"`


`"bbbbb"`


`"aaaaa"`


`"bbbbb"`


`"..."`

- Không bị lỗi xen ký tự (do mutex bảo vệ UART).
- Các task xen kẽ nhịp nhàng nhờ delay 100ms.


Link demo: https://drive.google.com/drive/folders/1hZ4lKnKttU1os_HSbFJYsOGZ5DkHneAC







