#include "FastLED.h"
#include <SD.h>
#include <SPI.h>

#define NUM_LEDS 220  // Tổng số đèn LED
#define DATA_PIN 7    // Chân dữ liệu LED
#define CHIP_SELECT 10 // Chân Chip Select cho thẻ SD

CRGB leds[NUM_LEDS];

File file;

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);  // Khởi tạo LED WS2812B với thứ tự màu GRB
  Serial.begin(9600); // Khởi tạo Serial Monitor để theo dõi hoạt động
  while (!Serial) {
    ; // Chờ cho đến khi Serial Monitor sẵn sàng
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(CHIP_SELECT)) {
    Serial.println("Initialization failed!");
    return;
  }
  Serial.println("Initialization done.");
}

void loop() {
  // Mở tệp trên thẻ SD
  file = SD.open("filename.dat");
  if (!file) {
    Serial.println("Error opening file");
    return;
  }

  for (int i = 0; i < 200; i++) { // 200 khung hình
    // Đọc dữ liệu cho mỗi khung hình
    for (int j = 0; j < NUM_LEDS; j++) {
      // Đọc 3 byte cho mỗi LED (R, G, B)
      leds[j].r = file.read();
      leds[j].g = file.read();
      leds[j].b = file.read();
    }

    reduceBrightness(0.1); // Giảm sáng 
    FastLED.show();
    delay(40); // Độ trễ giữa các khung hình
  }

  file.close(); // Đóng tệp
}

// Hàm giảm độ sáng
void reduceBrightness(float factor) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].r = leds[i].r * factor;
    leds[i].g = leds[i].g * factor;
    leds[i].b = leds[i].b * factor;
  }
}
