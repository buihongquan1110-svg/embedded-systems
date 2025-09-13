
# BÀI TẬP VỀ SỬ DỤNG TIMER ĐỂ LẬP TRÌNH - MÔN HỆ THỐNG NHÚNG PTIT.
- Cấu hình một Timer ở chế độ cơ bản, sử dụng Timer để tạo hàm Delay đạt độ chính xác cao.
- Cấu hình một timer cơ bản để tạo ngắt mỗi 500ms. Trong ISR của timer, đảo trạng thái của LED LD2. Kết quả là LED nhấp nháy với chu kỳ 1000ms.
- Có thể dùng máy hiện sóng, Logic Analyzer để đánh giá tính chính xác của Timer.

# 1. GIỚI THIỆU.
- Chương trình minh họa:
- TIM2: Cấu hình ngắt định kỳ → LED tại PA1 nhấp nháy tự động.
- TIM3: Sử dụng làm bộ đếm để tạo hàm Delay_ms() chính xác (thay vì dùng vòng lặp for).
- Main loop: LED tại PA2 sáng/tắt mỗi 1 giây (sử dụng hàm Delay).

# 2. CÁC BƯỚC CHÍNH.

# 2.1 CẤU HÌNH GPIO.
- PA1: Output → LED điều khiển bởi ngắt Timer2.
- PA2: Output → LED điều khiển bằng hàm Delay_ms().

<img width="686" height="398" alt="image" src="https://github.com/user-attachments/assets/655b1c46-6f1e-40a8-8998-28e821d954ce" />

# 2.2 CẤU HÌNH TIM2 - TẠO NGẮT ĐỊNH KỲ.
- Prescaler = 7200 - 1 → mỗi 0.1 ms tăng 1 lần.
- Period = 5000 - 1 → tràn sau 500 ms.
- Bật ngắt Update và cấu hình NVIC cho TIM2.
- Mỗi lần tràn → LED PA1 đổi trạng thái.

<img width="829" height="492" alt="image" src="https://github.com/user-attachments/assets/7f52b7a6-ae29-49fc-85e4-4611bbc77ff9" />

- HÀM ISR CHO TIM2.

<img width="659" height="193" alt="image" src="https://github.com/user-attachments/assets/e51e3c42-0886-49e3-8178-72a3248aef6f" />

# 2.3 CẤU HÌNH TIM3 - TẠO HÀM Delay_ms().
- TIM3 chạy với:
- Prescaler = 7200 - 1 → 0.1 ms mỗi tick.
- Period = 10 - 1 → 1 ms tràn.
- Dùng TIM3 làm bộ đếm để tạo delay chính xác theo mili giây.

<img width="784" height="311" alt="image" src="https://github.com/user-attachments/assets/24c82f3a-5059-474b-9323-609bb822f695" />

- HÀM Delay_ms().

<img width="519" height="211" alt="image" src="https://github.com/user-attachments/assets/84c94bec-f4db-4f17-84ef-19870f94b721" />

# 2.4 VÒNG LẶP CHÍNH.
- LED PA2: Sáng 1s – Tắt 1s (nhờ Delay_ms()).
- LED PA1: Tự động nhấp nháy theo ngắt TIM2.

<img width="564" height="205" alt="image" src="https://github.com/user-attachments/assets/1adb5424-c190-4874-bb02-a5ad1fdb501e" />

# 3. KẾT QUẢ.
- Đã cấu hình một Timer cơ bản (TIM3) để xây dựng hàm Delay_ms() → tạo độ trễ với độ chính xác cao.
- Đã cấu hình một Timer cơ bản (TIM2) để phát sinh ngắt mỗi 500 ms.
- Trong hàm ngắt (ISR) của TIM2, LED LD2 (PA1) được đảo trạng thái → LED nhấp nháy với chu kỳ 1000 ms (1 giây).

- Link video demo: https://drive.google.com/drive/folders/1cf8YeYu8BAEyeznQ5B0CXOEakjldg1q8






