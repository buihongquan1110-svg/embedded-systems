# BÀI TẬP MÔN VỀ LOWER POWER MÔN HỆ THỐNG NHÚNG TẠI PTIT.
# Bài tập 2: Viết 2 chương trình cho STM32 có chung tính năng, 1 chương trình sử dụng Delay, 1 chương trình sử dụng cơ chế Sleep
# Sử dụng đồng hồ đo so sánh dòng tiêu thụ của 2 chế độ.

# CƠ CHẾ DELAY.
# CÁC HÀM INIT (CUBEMX sinh sẵn).
<img width="985" height="537" alt="image" src="https://github.com/user-attachments/assets/b1ed30e7-986c-4d8e-925b-59dffbd09c59" />
- Cấu hình ở cube sẽ sinh ra các hàm: `"SystemClock_Config()"`, `"MX_GPIO_Init()"`.
- Giải thích: bật clock cho port, cấu hình PA0 ổn định; gọi hàm này trong main() lúc init.

# Viết vòng lặp điều khiển LED.
<img width="1058" height="294" alt="image" src="https://github.com/user-attachments/assets/eee111cb-dca7-4481-bf9a-6a4c0c58f225" />
# Giải thích từng lệnh:

- HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET) — đặt PA0 = HIGH → LED sáng.

- HAL_Delay(5000) — dừng chương trình 5000ms. HAL_Delay dùng SysTick.

- Lặp lại hành động để nhấp nháy.

# Cấu hình Clock.
<img width="850" height="576" alt="image" src="https://github.com/user-attachments/assets/58b6a6fb-be93-4c43-b50e-9827bbd89ccd" />

Link demo: https://drive.google.com/drive/folders/11_z9zW8yyQCuuiFB0QfpeN9DwNaxghNv
