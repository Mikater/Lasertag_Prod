#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <WebServer.h>
#include <esp_now.h>
#include "GyverButton.h"


#define BTN_PIN 14				// кнопка подключена сюда (BTN_PIN --- КНОПКА --- GND)
GButton butt1(BTN_PIN);

// WiFi
const char* ssid = "netis";
const char* password = "Cntgfy40";
WebServer server(80);
bool server_on = false;


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pinout
int16_t button1 = 14;
int16_t button2 = 23;
int16_t IR_Diode = 4;
int16_t IR_Diode_Force = 19;
int16_t Leds = 5;
int16_t Buzzer = 2;

// LED
int NumPixels = 4;
Adafruit_NeoPixel pixels(NumPixels, Leds, NEO_GRB + NEO_KHZ800);

// IR Properties
const int16_t lvl_0           = 600;
const uint8_t irfrequency    = 36;
const int16_t irt            = (int) (1000/irfrequency);
const uint8_t irpulses       = (int) (lvl_0 / (2000/irfrequency));

// Player Details
int team = 0; // 0 - red | 1 - blue | 2 - yellow | 3 - green
int damage = 9;
// Device data
int SerialNomber = 0;
int ID = 20;  // айді тагера

// Game Proporties
int M_Damage[16] = {1, 2, 4, 5, 7, 10, 15, 17, 20, 25, 30, 35, 40, 50, 75, 100};
int HP = 100;
int mode = 1;
int Ammo = 30;
int M_Ammo = 9;
int shootMode = 0;
int gameMode = 1; // 0 - WaitMod | 1 - InGame | 2 - Game Over
int shootData = 0;

void setup() {
  Serial.begin(115200);
  //pinMode(button1, INPUT_PULLUP);
  pinMode(Buzzer, OUTPUT);
  pinMode(button2, INPUT_PULLUP);
  pinMode(IR_Diode, OUTPUT);
  pinMode(IR_Diode_Force, OUTPUT);
  Serial.begin(115200);
  Serial.println("start");
  tone(Buzzer, 500, 500);
  // put your setup code here, to run once:
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  WiFi_start(); // Web server

  pixels.begin(); // LED
  pixels.setBrightness(100);
  pixels.clear();
}

void loop() {
  butt1.tick();
  if (butt1.isPress()) Serial.println("Press"); 
  i2cDisp();
  delay(200);
  if (WiFi.status() != WL_CONNECTED && !server_on){
    server_start();
  }
  server.handleClient();
  // if(digitalRead(button2) == LOW){
  //    dacWrite(25, 128);
  // } else {dacWrite(25, 255);}
  
}


