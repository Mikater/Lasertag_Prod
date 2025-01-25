#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "netis";
const char* password = "Cntgfy40";
WebServer server(80);
bool server_on = false;


// Pin List
int IR_Input = 2;
int Buzzer = 3;
int IR_Led = 4;
int Leds = 5;

// LED
int NumPixels = 61;
Adafruit_NeoPixel pixels(NumPixels, Leds, NEO_GRB + NEO_KHZ800);

// mods data
int mode = 0;                  // 1-Base 2-Restart 3-target 4-CheckPoint 5-Lamp 6-Bonus
int team_color[5] = {pixels.Color(255, 0, 0), pixels.Color(0, 0, 255), pixels.Color(255, 180, 0), pixels.Color(0, 255, 0), pixels.Color(255, 255, 255)};
int team_respawn[5] = {0xB400E8, 0xB401E8, 0xB402E8, 0xB403E8, 0x8305E8};
int base_period = 5;          // Період таймера
int base_regen_period = 5;    // Період регенерації
int base_froz_period = 15;    // Період заморозки
int base_team = 0;            // 0-Red, 1-Blue, 2-Yellow, 3-Green;
int base_max_HP = 100;
int HP = 100;
bool base_froz = false;       //=====================================
int res_period = 10;
int res_team = 0;             //=====================================
int cp_period = 5;          // Період таймера
int cp_regen_period = 5;    // Період регенерації
int cp_froz_period = 15;    // Період заморозки
int cp_team = 0;            // 0-Red, 1-Blue, 2-Yellow, 3-Green;
int cp_max_HP = 100;
int cp_HP = 100;
int lamp_color = pixels.Color(255, 255, 255);
int bonus_rain_period = 100;

// IR Properties
const int16_t lvl_0           = 600;
const int16_t lvl_1           = lvl_0<<1;
const uint8_t irfrequency    = 36;
const int16_t irt            = (int) (1000/irfrequency);
const uint8_t irpulses       = (int) (lvl_0 / (2000/irfrequency));
const int16_t lnk_timeout     = 2000; // для зчитування команд

// Device data
int SerialNomber = 0;
int ID = 1;


void setup() {
  Serial.begin(115200);

  pinMode(IR_Input, INPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(IR_Led, OUTPUT);

  WiFi_start(); // Web server

  pixels.begin();
  pixels.setBrightness(255);
  pixels.clear();
  circ_2(pixels.Color(255, 130, 0));
  // ico_bonus();

  bip_start();  
}

void loop() {
  take_command();
  if(mode == 1){
    base_mode();
  } else if (mode == 2){
    restart_mode();
  } else if (mode == 4){
    checkPoint_mode();
  } else if(mode == 5){
    lamp_mode();
  } else if(mode == 6){
    bonus_mode();
  }

  if (WiFi.status() != WL_CONNECTED && !server_on){
    server_start();
  }

  server.handleClient();
}


