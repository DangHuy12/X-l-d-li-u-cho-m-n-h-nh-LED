#include <SPI.h>               // Thư viện SPI để giao tiếp với thẻ SD
#include <SD.h>                // Thư viện SD để đọc dữ liệu từ thẻ SD
#include <Adafruit_NeoPixel.h> // Thư viện Adafruit_NeoPixel để điều khiển LED

#define NUM_LEDS 220           // Số lượng LED WS2812B
#define DATA_PIN 6             // Chân điều khiển LED
const uint8_t chipSelect = 10; // Chân chọn SD (thường là 10)

// Khởi tạo đối tượng LED strip
Adafruit_NeoPixel strip(NUM_LEDS, DATA_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);  // Khởi động Serial để kiểm tra dữ liệu
  strip.begin();       // Khởi tạo LED strip
  strip.show();        // Đảm bảo tất cả các đèn LED ban đầu đều tắt

  if (!SD.begin(chipSelect)) {
    Serial.println("Không thể khởi động thẻ SD!");
    while (1);  // Dừng nếu thẻ SD không hoạt động
  }
}

void loop() {
  File file = SD.open("Filename.txt");  // Mở file chứa dữ liệu

  if (!file) {
    Serial.println("Không thể mở file!");
    while (1);  // Dừng nếu không thể mở file
  }

  int ledIndex = 0;  // Chỉ số LED hiện tại

  // Đọc từng giá trị RGB cho đến khi hết file hoặc đạt số LED tối đa
  while (file.available() && ledIndex < NUM_LEDS) {
    int r = file.parseInt();  // Đọc giá trị R
    int g = file.parseInt();  // Đọc giá trị G
    int b = file.parseInt();  // Đọc giá trị B

    // Kiểm tra xem các giá trị RGB có hợp lệ không
    if (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255) {
      // Gán giá trị RGB cho LED tương ứng
      strip.setPixelColor(ledIndex, strip.Color(r, g, b));
      ledIndex++;
    }
  }

  file.close();  // Đóng file sau khi đọc xong

  // Hiển thị dữ liệu lên LED
  strip.show();
  delay(40);  // Giãn cách trước khi lặp lại
}
