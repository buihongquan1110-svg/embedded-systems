# VIẾT CHƯƠNG TRÌNH SỬ DỤNG CƠ CHẾ EVENT GROUPs . 
# Có 1 Task chính điều phối 3 Task còn lại hoạt động theo tiến trình qui định .
# Sử dụng cả điều khiển kích hoạt đơn và kích hoạt đồng thời .

# CẤU TRÚC CHƯƠNG TRÌNH 
# 1.Khai báo thư viện 
 
 - main.h: Tệp header chính của dự án , chứa cấu hình chân (pin) và các hàm riêng .
 - cmsis_os.h: Lớp API chung (wrapper) của ARM. Cung cấp các hàm os... (như osDelay) để gọi FreeRTOS, giúp dễ thay đổi RTOS.
- FreeRTOS.h: Tệp lõi (core) của FreeRTOS. Định nghĩa các kiểu dữ liệu và cấu hình cơ bản nhất.
- task.h: Dùng để quản lý tác vụ (task). Chứa các hàm tạo (xTaskCreate), trì hoãn (vTaskDelay), xóa tác vụ...
- event_groups.h: Dùng để đồng bộ hóa. Cho phép các tác vụ chờ một hoặc nhiều sự kiện ("cờ" - flag) xảy ra cùng lúc.

# 2.Định nghĩa các bit Event Group
 
- Bit	Giá trị	Chức năng
- EVENT_LED1	0b001	Điều khiển LED1
- EVENT_LED2	0b010	Điều khiển LED2
- EVENT_LED3	0b100	Điều khiển LED3

# 3. Khai báo Handle cho Task và Event Group
- Biến	Chức năng	Vai trò
- defaultTaskHandle	Handle cho task chính (StartDefaultTask)	Task gửi Event để điều khiển LED
- myTask02Handle	Handle cho Task02	Nhận EVENT_LED1 → điều khiển LED1
- myTask03Handle	Handle cho Task03	Nhận EVENT_LED2 → điều khiển LED2
- myTask05Handle	Handle cho Task05	Nhận EVENT_LED3 → điều khiển LED3
# 4. Cấu hình hệ thống xung nhịp (Clock) cho vi điều khiển STM32.
- Bật và dùng HSE (External crystal – thạch anh ngoài)
- Bật PLL để nhân xung → tạo xung hệ thống cao hơn
- Thiết lập clock cho CPU, AHB, APB1, APB2
- Cài đặt độ trễ Flash phù hợp tốc độ CPU
# 5. Cấu hình GPIO cho vi điều khiển STM32
 
- Hàm MX_GPIO_Init() cấu hình GPIO cho vi điều khiển STM32:
•	Bật clock cho port GPIO
•	Cấu hình các chân GPIO làm ngõ ra điều khiển LED
•	Đưa các chân GPIO về trạng thái ban đầu (LOW)
# 6. Task chính (Default Task) chạy nền trong FreeRTOS.
 
# Nhiệm vụ của task:


•	Gửi sự kiện EventGroup để điều khiển LED thông qua các task khác


•	Tạo hiệu ứng LED bật tuần tự rồi bật đồng loạt


•	Tạm dừng (delay) giữa các lần phát sự kiện
 # Lưu ý: Task này không trực tiếp bật LED, mà gửi tín hiệu cho các task LED khác xử lý.

# 7. Task điều khiển các Led
# 7.1. Task điều khiển LED1 (GPIO PA0)
- Lệnh	Chức năng
- xEventGroupWaitBits()	Chờ nhận tín hiệu từ Event Group
- EVENT_LED1	Bit sự kiện cần chờ → điều khiển LED1
- pdTRUE	Xóa bit sự kiện sau khi nhận (clear on exit)
- pdFALSE	Không yêu cầu chờ tất cả bit (chỉ cần một bit)
- portMAX_DELAY	Chờ vô thời hạn đến khi có event
- Task này đợi sự kiện EVENT_LED1 từ task chính.
- Khi nhận được sự kiện → lật (toggle) chân PA0, làm LED1 đổi trạng thái (sáng → tắt hoặc ngược lại).
# 7.2. Task điều khiển LED2 (GPIO PA1)
- Khi nhận tín hiệu EVENT_LED2, LED2 sẽ đổi trạng thái.
- Hoạt động giống Task02 nhưng dành cho:
- Chức năng	Giá trị
- Sự kiện nhận	EVENT_LED2
- GPIO điều khiển	GPIO_PIN_1 (PA1)
- Hành động	Toggle LED2
# 7.3. Task điều khiển LED3 (GPIO PA2)
- Thông tin	Giá trị
- Sự kiện chờ	EVENT_LED3
- GPIO điều khiển	GPIO_PIN_2 (PA2)
- Hành động	Toggle LED3


Link demo : https://drive.google.com/drive/folders/1FsrdNDsagYTNyAJ12m25YvEVQLWHFLRt

