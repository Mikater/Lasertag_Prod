#include <Adafruit_NeoPixel.h>
#include "WiFi.h"

// Pin List
int IR_Input = 1;
int Buzzer = 2;
int IR_Led = 3;
int Leds = 5;

const char* ssid = "netis";
const char* password =  "Cntgfy40";
bool conected = false;


int NumPixels = 61;

Adafruit_NeoPixel pixels(NumPixels, Leds, NEO_GRB + NEO_KHZ800);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  pixels.begin();
  pixels.setBrightness(4);
  bip();

  while (WiFi.status() != WL_CONNECTED ){
    Serial.println("Connecting to Wifi");
    conected = false;
  }
  conected = true;
  Serial.println("Connected to the WiFi network");
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
}

void loop() {
  // put your main code here, to run repeatedly:
  pixels.clear();
  rainbow();
  
}


