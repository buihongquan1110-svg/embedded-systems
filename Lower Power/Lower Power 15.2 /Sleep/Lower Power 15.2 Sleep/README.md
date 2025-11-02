# BÀI TẬP MÔN VỀ LOWER POWER MÔN HỆ THỐNG NHÚNG TẠI PTIT.
# Bài tập 2: Viết 2 chương trình cho STM32 có chung tính năng, 1 chương trình sử dụng Delay, 1 chương trình sử dụng cơ chế Sleep
# Sử dụng đồng hồ đo so sánh dòng tiêu thụ của 2 chế độ.

# CƠ CHẾ SLEEP.

# CÁC BƯỚC THỰC HIỆN.
# Bước 1: Khởi tạo HAL và hệ thống clock.
<img width="965" height="106" alt="image" src="https://github.com/user-attachments/assets/066a2b32-6da2-43d1-b0d4-d2183c1d232b" />
# Giải thích:
- `"HAL_Init()"` cấu hình timer hệ thống, ngắt SysTick và chuẩn bị các driver HAL.

- `"SystemClock_Config()"` thiết lập xung HSE (8MHz) và PLL (nhân 9 → 72MHz).

# Bước 2: Khởi tạo GPIO.
<img width="711" height="374" alt="image" src="https://github.com/user-attachments/assets/3cabac63-fab5-4840-aa52-6a088d62cebe" />

# Giải thích:
- `"GPIO_MODE_IT_RISING"` → ngắt khi nhấn nút (mức LOW → HIGH).

- `"GPIO_PULLUP"` → đảm bảo PA1 mặc định ở mức HIGH (tránh nhiễu).

- Khi nhấn nút, ngắt EXTI1 được kích hoạt → đánh thức MCU.

# Bước 3: Vòng lặp chính.
<img width="1091" height="268" alt="image" src="https://github.com/user-attachments/assets/a29d411e-5e4a-4f9f-87ac-621917071ddf" />

# Giải thích:
- LED sáng 3s → báo hiệu trước khi MCU ngủ.

- `"HAL_SuspendTick()"` → tắt SysTick để không bị đánh thức bởi timer.

- `"HAL_PWR_EnterSLEEPMode()"` → CPU dừng, chờ ngắt để thức dậy.

- Khi nhấn nút PA1, EXTI1 được kích hoạt → MCU tỉnh dậy.

- `"HAL_ResumeTick()"` bật lại SysTick để chương trình chạy bình thường.

# Bước 4: Xử lý ngắt ngoài (EXTI) từ nút nhấn.
<img width="882" height="169" alt="image" src="https://github.com/user-attachments/assets/5e4f0a2e-8742-4b60-b84a-62fd896861fb" />

# Giải thích:
- Khi nút PA1 được nhấn, ngắt EXTI1 gọi hàm callback này.

- MCU tự động thoát khỏi Sleep Mode → quay lại vòng lặp chính.

# Bước 5: Xử lý lỗi (nếu có).
<img width="1125" height="179" alt="image" src="https://github.com/user-attachments/assets/93abb85b-3ad4-451d-9556-336951ec0137" />

Link demo: https://drive.google.com/drive/folders/11_z9zW8yyQCuuiFB0QfpeN9DwNaxghNv




