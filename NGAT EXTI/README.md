# BÀI TẬP VỀ EXTI MÔN HỆ THỐNG NHÚNG PTIT: 
# "- Cấu hình ngắt ngoài cho 1 nút nhấn. Khi nhấn nút, trạng thái của LED sẽ đảo ngược.
# - Trong quá trình đó 1 LED khác vẫn nhấp nháy với chu kỳ 1Hz"

# Giới thiệu & mục tiêu
- Học cách cấu hình EXTI (ngắt ngoài) và NVIC trên STM32.
- Học cách cấu hình timer (TIM2) và bắt ngắt cập nhật (update interrupt).
- Thực hành viết ISR để xử lý ngắt nhanh, tắt/bật/ngắt hành vi IO.
# Yêu cầu
Phần cứng
Board STM32F103C8T6 (BluePill) hoặc tương đương
2 × LED + 2 × resistor 330Ω (hoặc dùng LED onboard nếu phù hợp)
1 × Push-button
ST-LINK V2 (hoặc công cụ nạp tương đương)
# Phần mềm
Keil uVision (MDK-ARM) hoặc IDE tương thích
STM32F10x Standard Peripheral Library (SPL)
File startup_stm32f10x.s, system_stm32f10x.c (SystemCoreClock phải chính xác)

# # CÁC BƯỚC THỰC HIỆN.
# 1. CẤU HÌNH GPIO.
PA0: Input (Pull-up) làm nút nhấn.
PB0: Output → LED nhấp nháy theo Timer2.
PB1: Output → LED điều khiển bằng nút nhấn (EXTI0).
<img width="1032" height="393" alt="image" src="https://github.com/user-attachments/assets/811812e6-cecf-46ef-9625-3161e5f78f09" />
# 2. CẤU HÌNH EXTI.
Chọn PA0 làm chân ngắt ngoài.
Kích hoạt ngắt cạnh Falling Edge (nhấn nút kéo xuống GND).
Bật NVIC cho EXTI0.
<img width="1066" height="524" alt="image" src="https://github.com/user-attachments/assets/2fc7fae2-4003-4416-b4fe-870efa3ac80b" />
Hàm ISR.
<img width="565" height="225" alt="image" src="https://github.com/user-attachments/assets/36da4697-487b-4d12-8b3a-9923a8126ff0" />
# 3. CẤU HÌNH TIMER2.
Prescaler: 7199 → mỗi 1 ms đếm tăng 1.
Period: 5000 → tràn sau 5000 ms (≈ 1 Hz).
Kích hoạt ngắt Timer2 trong NVIC.
<img width="570" height="258" alt="image" src="https://github.com/user-attachments/assets/6c3c3b67-cb3e-4a16-ac5b-b4bd06b5ac73" />
Hàm ISR.
<img width="646" height="256" alt="image" src="https://github.com/user-attachments/assets/6109830b-0399-4ce9-9065-c539b786d89b" />

# 4. KẾT QUẢ.
LED PB0: Nhấp nháy tự động 1 Hz (nhờ Timer2).
LED PB1: Đảo trạng thái mỗi khi nhấn nút (nhờ ngắt ngoài EXTI0).




