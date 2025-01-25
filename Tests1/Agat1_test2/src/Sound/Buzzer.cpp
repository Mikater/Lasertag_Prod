#include <Arduino.h>

void shoot_bip(int BUZZER_PIN){
    tone(BUZZER_PIN, 800, 50);
}

void reload_bup(int BUZZER_PIN){
    tone(BUZZER_PIN, 400, 500);
}