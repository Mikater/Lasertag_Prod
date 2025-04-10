#include <Arduino.h>
#include "MilesTag/MilesTag.h"
#include "Display/Display.h"
#include "LED/LED.h"

#define BUTTON_SHOOT 13
#define BUTTON_RELOAD 16
#define IR_LED_PIN 12
#define IR_RECEIVE_PIN 14
#define lnk_timeout 2000
#define lvl_0 600
#define lvl_1 1200

int shoot_data = 0;


void take_comm(int ir_receive_pin) {
  static int16_t recieved_pulse = 0;
  int supdata = 0;
  int datar = 0;
  int16_t index = 0;
  recieved_pulse = pulseIn(ir_receive_pin, LOW);
  if (recieved_pulse > 1800) {
    while (recieved_pulse != 0) {
      recieved_pulse = pulseIn(ir_receive_pin, LOW, lnk_timeout);
      if ((recieved_pulse > lvl_0 - 200) && (recieved_pulse < lvl_0 + 200)) {
        bitClear(supdata, index);
      } else if ((recieved_pulse > lvl_1 - 200) && (recieved_pulse < lvl_1 + 200)) {
        bitSet(supdata, index);
      } else if (recieved_pulse == 0) {
        break;
      }
      index++;
    }
    Serial.println(supdata, BIN);
    datar = invert_data(supdata);
    Serial.println(datar, HEX);
    Serial.print("Executed on core: ");
    Serial.println(xPortGetCoreID());
    Serial.println(" = = = = = = = = = = ");
  }
}

void checkButtonShoot(void *pvParameters){
  bool isTriggered = false;
  while (true) {
    if(!isTriggered && digitalRead(BUTTON_SHOOT) == LOW){
      isTriggered = true;
      Serial.println("Shoot");
      mt_single_shoot(IR_LED_PIN, shoot_data);
    } else if(isTriggered && digitalRead(BUTTON_SHOOT) == HIGH){
      isTriggered = false;
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

void displayReload(void *pvParameters) {
  while (true) {
    i2cDisp();

    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void LED_reload(void *pvParameters) {
  while (true) {
    leds_tick();

    vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(IR_RECEIVE_PIN, INPUT);
  pinMode(IR_LED_PIN, OUTPUT);
  pinMode(BUTTON_SHOOT, INPUT_PULLUP);
  pinMode(BUTTON_RELOAD, INPUT_PULLUP);

  shoot_data = mt_create_shoot(1, 1, 1);

  displayStart();

  xTaskCreate(
    checkButtonShoot,
    "checkButtonShoot",
    2048,
    NULL,
    2,
    NULL
  );

  xTaskCreate(
    checkButtonReload,
    "checkButtonReload",
    1000,
    NULL,
    2,
    NULL
  );
  
  xTaskCreate(
    displayReload,
    "displayReload",
    2048,
    NULL,
    3,
    NULL
  );

  xTaskCreate(
    LED_reload,
    "LED_reload",
    2048,
    NULL,
    3,
    NULL
  );
}

void loop() {
  take_comm(IR_RECEIVE_PIN);
  // delay(100);
}
