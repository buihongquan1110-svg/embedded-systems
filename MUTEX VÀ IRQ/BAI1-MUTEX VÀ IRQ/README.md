# BÀI TẬP VỀ MUTEX VÀ IRQ MÔN HỆ THỐNG NHÚNG CỦA PTIT.
# "Bài 1: Viết chương trình có 2 Task: 1 Task Blink LED, 
# 1 Task xử lý khi có ngắt ngoài thì bật đèn hoặc còi cảnh báo 
# Yêu cầu xử lý Task bật đèn ngay sau khi hàm xử lý ngắt thực thi. Khi chưa nhấn nút Task bật đèn/còi ở chế độ Block."

# CÁC BƯỚC THỰC HIỆN.
# BƯỚC 1: Tạo Semaphore nhị phân.
<img width="575" height="82" alt="image" src="https://github.com/user-attachments/assets/33268250-468f-4784-ab95-5e7fceac8310" />
- Semaphore này khởi tạo ở trạng thái “Empty” (chưa được cấp).

- Khi người dùng nhấn nút (gây ngắt), ISR sẽ “Give” semaphore → Task 2 được “đánh thức”.

# BƯỚC 2: Tạo các Task.
- Tạo 2 task với mức ưu tiên bằng nhau.
<img width="784" height="167" alt="image" src="https://github.com/user-attachments/assets/dd5447be-4b87-45a3-a9b9-4470d28fb319" />

- `"StartBlinkTask()"` chạy LED PA5 liên tục để báo “hệ thống sống”.

- `"StartExtiTask()"` ở trạng thái block cho đến khi nhận semaphore từ ISR.

