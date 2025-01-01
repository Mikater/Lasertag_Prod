#include <esp_now.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Adafruit_NeoPixel.h>

// pinout
int vibro_pin = 0;
int LED_pin = 4;

int HP = 100;
int team = 0; // 0 - red | 1 - blue | 2 - yellow | 3 - green
int mode = 1;


void setup() {
  // put your setup code here, to run once:
  pinMode(0, OUTPUT);

  set_vibro(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  check_vibro();
}
