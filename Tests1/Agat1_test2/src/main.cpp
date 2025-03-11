#include <Arduino.h>
#include "MilesTag/MilesTag.h"

#define BUTTON_SHOOT 13
#define BUTTON_RELOAD 16
#define IR_RECEIVE_PIN 14
#define lnk_timeout 2000
#define lvl_0 600
#define lvl_1 1200


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
    } else if(isTriggered && digitalRead(BUTTON_SHOOT) == HIGH){
      isTriggered = false;
      Serial.println("No Shoot");
      Serial.print("Executed on core: ");
      Serial.println(xPortGetCoreID());
      Serial.println("= = = = = = = = = =");
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

void checkIrReceive(void *pvParameters) {
  // while (true) {
    
  // }
}

void setup() {
  Serial.begin(115200);

  pinMode(IR_RECEIVE_PIN, INPUT);
  pinMode(BUTTON_SHOOT, INPUT_PULLUP);
  pinMode(BUTTON_RELOAD, INPUT_PULLUP);

  xTaskCreate(
    checkButtonShoot,
    "checkButtonShoot",
    1000,
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

  // xTaskCreatePinnedToCore(
  //   checkIrReceive,   
  //   "checkIrReceive", 
  //   10000,            
  //   NULL,             
  //   1,                
  //   NULL,             
  //   1                 
  // );
}

void loop() {
  take_comm(IR_RECEIVE_PIN);
  // delay(100);
}
