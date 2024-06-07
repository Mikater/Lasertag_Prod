#include <IRremote.h>

int IRpin = 11; // Пін, на якому підключено "OUT" інфрачервоного приймача
int ledPin = 13; // Пін, на якому підключено світлодіод


IRrecv irrecv(IRpin);
decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); // Включаємо прийом IR-сигналів
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (irrecv.decode(&results)) {
    unsigned long receivedCode = results.value;
    Serial.println(receivedCode, HEX); // Виводимо код сигналу в шістнадцятковому форматі

    // Перевіряємо, чи отриманий код відповідає вашій команді
    if (receivedCode == 0xA90) {
      // Вмикаємо світлодіод
      digitalWrite(ledPin, HIGH);
      delay(1000); // Пауза 1 секунда
      // Вимикаємо світлодіод
      digitalWrite(ledPin, LOW);
    }

    irrecv.resume(); // Продовжуємо приймати IR-сигнали
  }
}