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

# BƯỚC 3: Task 1 - Blink LED.
<img width="584" height="202" alt="image" src="https://github.com/user-attachments/assets/9d7e8bda-0daa-4bb5-8263-84a45ab27c2d" />

- LED PA5 bật/tắt mỗi 500ms → giúp ta biết hệ thống vẫn đang chạy.

- Task này không phụ thuộc ngắt, luôn chạy nền.

# BƯỚC 4: Task 2 - Xử lý ngắt.
<img width="859" height="430" alt="image" src="https://github.com/user-attachments/assets/12d63eb2-a4ce-4a43-8f95-2b2431f9341b" />

- Task 2 chỉ hoạt động sau khi nhận semaphore từ ISR.

- Sau khi xử lý xong (LED nháy 5 lần), Task 2 quay lại chờ tín hiệu tiếp theo.

# BƯỚC 5: Ngắt ngoài(ISR).
<img width="851" height="289" alt="image" src="https://github.com/user-attachments/assets/79ed2225-8d77-45e7-bb29-393d18f35e35" />

- ISR không nên thao tác trực tiếp với LED → chỉ give semaphore.

- Task 2 mới thực hiện nháy LED.

- `"portYIELD_FROM_ISR()"` đảm bảo nếu Task 2 có ưu tiên cao, nó chạy ngay sau khi ISR kết thúc.

# BƯỚC 6: Cấu hình GPIO & NVIC.
<img width="791" height="642" alt="image" src="https://github.com/user-attachments/assets/4fffcd9e-968b-4c61-b499-8ae3ffd183a4" />

| Chân | Chức năng     | Cấu hình                       | Ghi chú           |
| PA0  | LED Warning   | Output                         | Dùng trong Task 2 |
| PA1  | Button        | Input (Interrupt Falling Edge) | Gây ngắt ngoài    |
| PA5  | LED Heartbeat | Output                         | Dùng trong Task 1 |






