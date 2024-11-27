#include <Adafruit_NeoPixel.h>

#define PIN 6          // Chân điều khiển LED
#define NUMPIXELS 380  // Tổng số LED (20 x 19 = 380)

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin();  // Khởi tạo dải LED
  setAllPixelsRed();
  pixels.show();   // Hiển thị màu trên tất cả các LED
}

void loop() {
  // Không cần làm gì trong vòng lặp vì đã thiết lập màu đỏ cho tất cả LED
}

void setAllPixelsRed() {
  for(int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(255, 0, 0));  // Thiết lập màu đỏ (RGB: 255, 0, 0)
  }
}