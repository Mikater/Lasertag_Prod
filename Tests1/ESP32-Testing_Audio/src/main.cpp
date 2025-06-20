#include <Arduino.h>
#include <Audio.h>
#include <LittleFS.h>
#include "I2SAudioPlayer_Atic.h"

I2SAudioPlayer player;

#define I2S_LRC   14  // WS
#define I2S_BCLK  27  // BCK
#define I2S_DIN   26  // DATA

Audio audio;

File shot_audio;

int period = 350;
unsigned long lastMillis = 0;
bool isPlaying = false;  // Змінна для перевірки, чи грає звук

void playSound(const char* path) {
  if (LittleFS.exists(path)) {
    // isPlaying = true;  // Встановлюємо, що звук грає
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

  shot_audio = LittleFS.open("/blaster_shot_2.raw", "r");
  if (!shot_audio) {
    Serial.println("Failed to open audio file.");
    return;
  }

  // Налаштування I2S для MAX98357A
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DIN);
  audio.setVolume(21);  // Гучність 0-21

  player.begin(22050, 16, 1);  // Ініціалізація I2S аудіо плеєра
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
      player.stop();
      lastMillis = current_time;
      Serial.println("Button pressed, playing sound.");
      player.playRawFile(shot_audio);
    }
  }
}

  

