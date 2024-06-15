#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pinout
int16_t button1 = 4;
int16_t IR_Diode = 2;
int16_t diods = 5;

// IR
const int16_t lvl_0           = 600;
const int16_t lvl_1           = lvl_0<<1;
const uint8_t irfrequency     = 36;
const int16_t irt             = (int) ((500/irfrequency) - 4);
const uint8_t irpulses       = (int) (lvl_0 / (1000/irfrequency));

int HP = 100;
int Ammo = 30;

void setup() {
  pinMode(button1, INPUT_PULLUP); // Налаштуйте штифт як вхідний
  pinMode(diods, OUTPUT);
  pinMode(IR_Diode, OUTPUT);
  Serial.begin(115200);
  Serial.println("start");
  // put your setup code here, to run once:
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  i2cDisp();
}

void loop() {
  triggers();
  // i2cDisp();
  delay(200);
}

void triggers(){
    static uint8_t tr  = 0;
    static uint8_t ltr = 0;
    ltr = tr;
    tr = digitalRead(button1);
    if ( tr != ltr && tr == LOW){
      // Serial.print("ButShot");
      digitalWrite(diods, HIGH);
      sendcommand(0x8302);
            //sendclonedata();
            //sendcommand(commands[x_to_mass]);
      delay(1000);
      digitalWrite(diods, LOW);
}}

void sendcommand(uint16_t comm){
    sendPulse(IR_Diode, 3); // start
    for(int i = 15; i>=0; i--){
      sendPulse(IR_Diode, bitRead(comm, i) == 0 ? 0 : 1);
    }
    for(int i = 7; i>=0; i--){
      //sendPulse(IR_Diode,(((byte*)&comm)[i])==0 ? 0 : 1);
      //binaryString += bitRead(0xE8, i) == 0 ? "0" : "1";
      sendPulse(IR_Diode, bitRead(0xE8, i) == 0 ? 0 : 1);
    }
}

void sendPulse(int16_t pin, int length){
  int sig_l = 580; // крок сигналу
  digitalWrite(pin, HIGH);
  delayMicroseconds(sig_l+(sig_l*length));
  digitalWrite(pin, LOW);
  delayMicroseconds(sig_l);
}

void i2cDisp() {
  display.clearDisplay();
  dispTopLine();
  display.display();
}

void dispTopLine() {
  const unsigned char icoNet [] PROGMEM = {
	0x03, 0xf0, 0x0f, 0xf8, 0x1e, 0x00, 0x38, 0x00, 0x70, 0x00, 0x60, 0xf0, 0xe1, 0xf8, 0xc3, 0x80, 
	0xc7, 0x00, 0xc6, 0x30, 0xc6, 0x78, 0xc6, 0x78, 0x42, 0x30};
  const unsigned char Battery10 [] PROGMEM = {
	0x7f, 0xf8, 0x40, 0x08, 0xc0, 0x08, 0x80, 0x08, 0xc0, 0x08, 0x40, 0x08, 0x7f, 0xf8};
  const unsigned char Battery50 [] PROGMEM = {
	0x7f, 0xf8, 0x42, 0xf8, 0xc1, 0xf8, 0x82, 0xf8, 0xc1, 0xf8, 0x42, 0xf8, 0x7f, 0xf8};
  const unsigned char Battery100 [] PROGMEM = {
	0x7f, 0xf8, 0x7f, 0xf8, 0xff, 0xf8, 0xff, 0xf8, 0xff, 0xf8, 0x7f, 0xf8, 0x7f, 0xf8};
  int netX = 0;
  int netY = 19;
  int battTagX = 0;
  int battTagY = 0;
  int battHeadX = 0;
  int battHeadY = 10;

  bool net = true;
  int battTag = 9;
  int battHead = 30;

  if(net){
    display.drawBitmap(netX, netY, icoNet, 13, 13, 1);
  }

  if(battTag > 70){
    display.drawBitmap(battTagX, battTagY, Battery100, 13, 7, 1);
  } else if(battTag > 10){
    display.drawBitmap(battTagX, battTagY, Battery50, 13, 7, 1);
  } else {
    display.drawBitmap(battTagX, battTagY, Battery10, 13, 7, 1);
  }
  if(battHead > 70){
    display.drawBitmap(battHeadX, battHeadY, Battery100, 13, 7, 1);
  } else if(battHead > 10){
    display.drawBitmap(battHeadX, battHeadY, Battery50, 13, 7, 1);
  } else if(battHead > -1){
    display.drawBitmap(battHeadX, battHeadY, Battery10, 13, 7, 1);
  }
}
