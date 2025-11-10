#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();  // Створюємо об’єкт дисплея

void setup() {
  Serial.begin(115200);
  Serial.println("Ініціалізація дисплея...");

  tft.init();               // Ініціалізуємо GC9A01
  tft.setRotation(0);       // Поворот 0–3
  tft.fillScreen(TFT_BLACK);
  Serial.println("Дисплей запущено!");

  // Прості тести:
  tft.fillScreen(TFT_RED);
  delay(5000);
  tft.fillScreen(TFT_GREEN);
  delay(5000);
  tft.fillScreen(TFT_BLUE);
  delay(5000);
  tft.fillScreen(TFT_BLACK);

  // Текст у центрі
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawCentreString("Hello!", 120, 110, 4);

  // Малюємо коло, якщо кольори працюють — дисплей робочий
  tft.drawCircle(120, 120, 100, TFT_YELLOW);
}

void loop() {
  // Міняємо кольори по колу, щоб бачити оновлення
  static uint16_t colors[] = {TFT_RED, TFT_GREEN, TFT_BLUE, TFT_CYAN, TFT_MAGENTA, TFT_YELLOW};
  static int i = 0;
  tft.fillCircle(120, 120, 40, colors[i]);
  i = (i + 1) % 6;
  delay(300);
}
