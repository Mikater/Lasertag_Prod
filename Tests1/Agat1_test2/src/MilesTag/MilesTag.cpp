#include <Arduino.h>
#include "LED/LED.h"
#include "Sound/Buzzer.h"

const int16_t lvl_0           = 600;
const int16_t lvl_1           = lvl_0<<1;
const uint8_t irfrequency    = 36;
const int16_t irt            = (int) (1000/irfrequency);
const uint8_t irpulses       = (int) (lvl_0 / (2000/irfrequency));
const int16_t lnk_timeout     = 2000; // для зчитування команд

int mt_burst = 3;
bool shooting = false;
int time_before_shoot = 160;
int mt_ammo = 30;
int ammo_left;
int mt_magazines = 9;
int mt_color_code;

int invert_data(int data){
  int newData = 0;
  for(int i = 0; i<24; i++){
    if(bitRead(data, i) == 1){bitSet(newData, 23-i);}
    else{bitClear(newData, 23-i);}}
  return newData;
}

int mt_take_comm(int ir_receive_pin){
    static int16_t recieved_pulse  = 0;
    int supdata = 0;
    int datar = 0;
    int16_t index = 0;
    recieved_pulse = pulseIn(ir_receive_pin, LOW);
    if (recieved_pulse > 1800){
      while (recieved_pulse != 0){
        recieved_pulse = pulseIn(ir_receive_pin, LOW, lnk_timeout);
        if ((recieved_pulse > lvl_0 - 200) && (recieved_pulse < lvl_0 + 200)) {bitClear(supdata, index);}
        else if ((recieved_pulse > lvl_1 - 200) && (recieved_pulse < lvl_1 + 200)) {bitSet(supdata, index);}
        else if (recieved_pulse == 0){
          break;
        }
        index++;}
      Serial.println(supdata, BIN);
      datar = invert_data(supdata);
      Serial.println(datar, HEX);
      Serial.println(" = = = = = = = = = = ");
      return datar;
    }
    else {
        return 0;
    }
}

void sendPulse(int16_t pin, int length){
  int16_t i = 0;
  while(i < irpulses<<length){
    i++;
    digitalWrite(pin, HIGH);
    delayMicroseconds(irt);
    digitalWrite(pin, LOW);
    delayMicroseconds(irt);
  }
  delayMicroseconds(lvl_0);
}

void mt_start(int burst, int color_code){
  mt_burst = burst;
  ammo_left = mt_ammo;
  mt_color_code = color_code;
}

unsigned long lastSingleShot;

void mt_single_shoot(int IR_LED_PIN, int data){
  if(lastSingleShot <= millis()-100){
    return;
  } else {
    lastSingleShot = millis();
  }
  if (ammo_left > 0){
    sendPulse(IR_LED_PIN, 2); // start
    for(int i = 23; i>=0; i--){
        sendPulse(IR_LED_PIN, bitRead(data, i) == 0 ? 0 : 1);
    }
    leds_shot(mt_color_code);
    //shoot_bip(26);
    ammo_left--;
  }
}

void mt_burst_shoot(int IR_LED_PIN, int data){
  static long next_shoot;
  static int shoots_left;
  long current_time = millis();

  if (ammo_left > 0){
    if (!shooting){
      shooting = true;
      shoots_left = mt_burst - 1;
      next_shoot = current_time + time_before_shoot;
      mt_single_shoot(IR_LED_PIN, data);
      return;
    } else {
      if (next_shoot<=current_time && shoots_left > 0){
        next_shoot = current_time + time_before_shoot;
        shoots_left--;
        mt_single_shoot(IR_LED_PIN, data);
      }
    }
  }
}

void mt_auto_shoot(int IR_LED_PIN, int data){
  static long next_shoot;
  long current_time = millis();

  if (ammo_left > 0){
    if (!shooting){
      shooting = true;
      next_shoot = current_time + time_before_shoot;
      mt_single_shoot(IR_LED_PIN, data);
      return;
    } else {
      if (next_shoot<=current_time){
        next_shoot = current_time + time_before_shoot;
        mt_single_shoot(IR_LED_PIN, data);
      }
    }
  }
}

void mt_exit_shooting(){
  shooting = false;
}

void mt_reload(){
  ammo_left = mt_ammo;
  reload_bup(26);
}

int mt_create_shoot(int ID, int team, int damage){
    int shootData = 0;
    shootData = ID << 16;
    shootData = shootData | (team << 14);
    shootData = shootData | (damage << 10);
    return shootData;
}