#include <Arduino.h>
#include "Wifi/Web_server.h"
#include "LED/LED_TARGET.h"

// Pins on plate
// IO5 - RGB
// IO4 - Button
// IO2 - IR Recv
// IO15 - Batery
// IO13 - Vibro

#define IR_RECV 2

const int16_t lvl_0           = 600;
const int16_t lvl_1           = lvl_0<<1;
const uint8_t irfrequency    = 36;
const int16_t irt            = (int) (1000/irfrequency);
const uint8_t irpulses       = (int) (lvl_0 / (2000/irfrequency));
const int16_t lnk_timeout     = 2000; // для зчитування команд

int filter = -1; // -1 = all 

void setup() {
  pinMode(IR_RECV, INPUT);
  
  leds_start(255);
  leds_shot(get_team_color(5));

  analogReadResolution(12);
  
  Serial.begin(115200);
  Serial.println("Started sucsesfully!");
}




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
  int data = 0;
  int index = 0;
  recieved_pulse = pulseIn(ir_receive_pin, LOW, 10000);
  if (recieved_pulse > 1800){
    while (recieved_pulse != 0){
      recieved_pulse = pulseIn(ir_receive_pin, LOW, lnk_timeout);
      if ((recieved_pulse > lvl_0 - 200) && (recieved_pulse < lvl_0 + 200)) {bitClear(supdata, index);}
      else if ((recieved_pulse > lvl_1 - 200) && (recieved_pulse < lvl_1 + 200)) {bitSet(supdata, index);}
      else if (recieved_pulse == 0){
        break;
      }
      index++;}
    data = invert_data(supdata);
    Serial.println(data, BIN);
    Serial.println("= = = = = = = = = = -");
    return data;
  }
  else {
    return 0;
  }
}

void loop() {
  int ir_recieved_data = mt_take_comm(IR_RECV);
  if(ir_recieved_data != 0) {
    uint32_t id = (ir_recieved_data >> 16) & 0x7F;       // 7 біт (1-7)
    uint32_t team = (ir_recieved_data >> 14) & 0x3;      // 2 біти (8-9)
    uint32_t damage = (ir_recieved_data >> 10) & 0xF;    // 4 біти (10-13)
    if (filter == -1){
      if(addShotToLogs(id, team, damage)){
        leds_shot(get_team_color(team));
      } else {
        leds_shot(get_team_color(5));
      }
      Serial.println(ir_recieved_data);
      Serial.println("= = = = = = = = = = -");
    } else {
      if (team == filter){
        if(addShotToLogs(id, team, damage)){
          leds_shot(get_team_color(team));
        } else {
          leds_shot(get_team_color(5));
        }
      }
    }
  }

  leds_tick();
  web_server_tick();
  filter = GetFilter();
}