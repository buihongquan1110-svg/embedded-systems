# BÀI TẬP VỀ EXTI MÔN HỆ THỐNG NHÚNG PTIT: 
# "- Cấu hình ngắt ngoài cho 1 nút nhấn. Khi nhấn nút, trạng thái của LED sẽ đảo ngược.
# - Trong quá trình đó 1 LED khác vẫn nhấp nháy với chu kỳ 1Hz"

# Giới thiệu & mục tiêu
- Học cách cấu hình EXTI (ngắt ngoài) và NVIC trên STM32.
- Học cách cấu hình timer (TIM2) và bắt ngắt cập nhật (update interrupt).
- Thực hành viết ISR để xử lý ngắt nhanh, tắt/bật/ngắt hành vi IO.
# Yêu cầu
- Phần cứng
Board STM32F103C8T6 (BluePill) hoặc tương đương
2 × LED + 2 × resistor 330Ω (hoặc dùng LED onboard nếu phù hợp)
1 × Push-button
ST-LINK V2 (hoặc công cụ nạp tương đương)
- Phần mềm
Keil uVision (MDK-ARM) hoặc IDE tương thích
STM32F10x Standard Peripheral Library (SPL)
File startup_stm32f10x.s, system_stm32f10x.c (SystemCoreClock phải chính xác)

# # CÁC BƯỚC THỰC HIỆN.
# 1. CẤU HÌNH GPIO.
PA0: Input (Pull-up) làm nút nhấn.
PB0: Output → LED nhấp nháy theo Timer2.
PB1: Output → LED điều khiển bằng nút nhấn (EXTI0).
<img width="973" height="421" alt="image" src="https://github.com/user-attachments/assets/510e1178-0cd3-4aad-be00-a1f768831871" />

# 2. CẤU HÌNH EXTI.
Chọn PA0 làm chân ngắt ngoài.
Kích hoạt ngắt cạnh Falling Edge (nhấn nút kéo xuống GND).
Bật NVIC cho EXTI0.
<img width="786" height="450" alt="image" src="https://github.com/user-attachments/assets/e198670a-584e-40ea-89c8-192826602ae5" />
Hàm ISR.
<img width="663" height="174" alt="image" src="https://github.com/user-attachments/assets/5b5aded9-7657-4122-a864-ad12709e55be" />
# 3. CẤU HÌNH TIMER2.
Prescaler: 7199 → mỗi 1 ms đếm tăng 1.
Period: 5000 → tràn sau 5000 ms (≈ 1 Hz).
Kích hoạt ngắt Timer2 trong NVIC.
<img width="713" height="479" alt="image" src="https://github.com/user-attachments/assets/b9786ea2-83d5-48f0-bbf1-6d71e42537d1" />
Hàm ISR.
<img width="708" height="114" alt="image" src="https://github.com/user-attachments/assets/690e85dc-c52d-48fa-a5b7-4076f25ba16a" />
# 4. KẾT QUẢ.
- LED PB0: Nhấp nháy tự động 1 Hz (nhờ Timer2).
- LED PB1: Đảo trạng thái mỗi khi nhấn nút (nhờ ngắt ngoài EXTI0).




