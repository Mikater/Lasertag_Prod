#include <Arduino.h>
#include <Audio.h>
#include <LittleFS.h>

#define I2S_LRC   14  // WS
#define I2S_BCLK  27  // BCK
#define I2S_DIN   26  // DATA

Audio audio;

int period = 100;
unsigned long lastMillis = 0;
bool isPlaying = false;  // Змінна для перевірки, чи грає звук

void playSound(const char* path) {
  if (LittleFS.exists(path)) {
    isPlaying = true;  // Встановлюємо, що звук грає
    Serial.println("Playing: " + String(path));
    audio.connecttoFS(LittleFS, path);
  } else {
    Serial.println("File not found: " + String(path));
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(22, INPUT_PULLUP);  // Кнопка на GPIO 0
  
  // Ініціалізація LittleFS
  if (!LittleFS.begin()) {
    Serial.println("LittleFS Mount Failed. Formatting...");
    LittleFS.format();
    LittleFS.begin();
  }

  // Налаштування I2S для MAX98357A
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DIN);
  audio.setVolume(1);  // Гучність 0-21

  // Тестовий звук при старті
  playSound("/power_on.wav");
}

void loop() {
  audio.loop();  // Обов'язковий виклик!
  int current_time = millis();
  // if (audio.isRunning() == false) {
  //   isPlaying = false;  // Звук закінчився
  //   Serial.println("Sound finished playing.");
  // }
  if (digitalRead(22) == LOW && !isPlaying) {  // Якщо кнопка натиснута
    if (current_time - lastMillis >= period) {
      lastMillis = current_time;
      isPlaying = true;  // Встановлюємо, що звук грає
      Serial.println("Button pressed, playing sound.");
      playSound("/shot.wav");
    }
  }
}

