#include <Arduino.h>

#define BUTTON_SHOOT 13
#define BUTTON_RELOAD 16

void checkButtonShoot(void *pvParameters){
  bool isTriggered = false;
  while (true) {
    if(!isTriggered && digitalRead(BUTTON_SHOOT) == LOW){
      isTriggered = true;
      Serial.println("Shoot");
    } else if(isTriggered && digitalRead(BUTTON_SHOOT) == HIGH){
      isTriggered = false;
      Serial.println("No Shoot");
    }

    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}

void checkButtonReload(void *pvParameters){
  bool isTriggered = false;
  while (true) {
    if(!isTriggered && digitalRead(BUTTON_RELOAD) == LOW){
      isTriggered = true;
      Serial.println("Reload");
    } else if(isTriggered && digitalRead(BUTTON_RELOAD) == HIGH){
      isTriggered = false;
    }

    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(BUTTON_SHOOT, INPUT_PULLUP);
  pinMode(BUTTON_RELOAD, INPUT_PULLUP);

  xTaskCreate(
    checkButtonShoot,
    "checkButtonShoot",
    1000,
    NULL,
    1,
    NULL
  );

  xTaskCreate(
    checkButtonReload,
    "checkButtonReload",
    1000,
    NULL,
    1,
    NULL
  );
}

void loop() {}
