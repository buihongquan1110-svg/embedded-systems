# BÀI TẬP VỀ RTOS MÔN HỆ THỐNG NHÚNG CỦA PTIT.
# Tạo một project FreeRTOS.
# Viết 1 chương trình sử dụng FreeRTOS thực hiện:
# Nhấp nháy 3 LED ở 3 tần số khác nhau: 3Hz, 10Hz và 25Hz.
# 1,Sử dụng 3 hàm độc lập cho 3 tác vụ.
# 2,Nâng cao (Không bắt buộc): Viết 1 hàm tác vụ duy nhất và truyền vào tham số để thay đổi chân nháy LED, tần số nháy.
# Lưu ý sử dụng: vTaskDelay hoặc vTaskUntil.
## Mô tả
Dự án này sử dụng FreeRTOS để điều khiển 3 LED nhấp nháy ở 3 tần số khác nhau:

LED1: 3 Hz → nhấp nháy mỗi ~166 ms

LED2: 10 Hz → nhấp nháy mỗi ~50 ms

LED3: 25 Hz → nhấp nháy mỗi ~20 ms

Vi điều khiển: STM32F103C8T6
IDE: Keil uVision
Thư viện: HAL + CMSIS-RTOS v1 (FreeRTOS)

## Thông tin phần cứng
- MCU: STM32F103C8T6
- Clock: HSE 8 MHz, PLL x9 → 72 MHz
- LED1: PA0
- LED2: PA1
- LED3: PA2

## Các bước thực hiện 
# Bước 1 : Khai báo các Task-handle và prototype 
<img width="940" height="113" alt="image" src="https://github.com/user-attachments/assets/31241ca0-fb13-4f66-9f6a-42fce6db2bbe" />
<img width="930" height="165" alt="image" src="https://github.com/user-attachments/assets/6eea241e-be43-4f30-834e-e1ca12dc6a84" />

Mỗi biến kiểu osThreadId lưu lại địa chỉ của một task trong FreeRTOS.  
Dùng để theo dõi hoặc điều khiển task (xóa, tạm dừng, v.v.).
# Bước 2 : Tạo các task 
<img width="818" height="280" alt="image" src="https://github.com/user-attachments/assets/4a06f7d6-7317-44be-8bf3-e159625154e4" />
osThreadDef(): định nghĩa một task, gồm tên, hàm, độ ưu tiên, stack size.  
osThreadCreate(): tạo và đưa task vào trạng thái sẵn sàng .
<img width="380" height="75" alt="image" src="https://github.com/user-attachments/assets/61216279-92cd-4cab-9cb8-e2f9c88d37a9" />
Khởi động FreeRTOS Scheduler, chuyển quyền điều khiển cho các task.




## Lưu ý
- FreeRTOSConfig.h KHÔNG được include trong package theo yêu cầu. Bạn cần thêm file FreeRTOSConfig.h phù hợp (với config for STM32F1) vào MDK/ trước khi build.
- Thay thế startup & system file bằng file chính thức từ CubeMX/Keil để build chuẩn.
