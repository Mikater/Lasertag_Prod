#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h> // Світлодіодна лента

// I2C Display 
#define SCREEN_WIDTH  128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// pinout
int16_t irDiode = 0;
int16_t buzzer = 1;
int16_t rgbLine = 2;
int16_t irReceiver = 3;
// int16_t battery = 4;
int16_t Button1 = 7;
int16_t Button2 = 8;
int16_t Button3 = 9;
int16_t Button4 = 10;
int16_t Button5 = 20;
int16_t Button6 = 21;

// IR Properties
const int16_t lvl_0           = 600;
const int16_t lvl_1           = lvl_0<<1;
const uint8_t irfrequency    = 36;
const int16_t irt            = (int) (1000/irfrequency);
const uint8_t irpulses       = (int) (lvl_0 / (2000/irfrequency));
const int16_t lnk_timeout     = 2000; // для зчитування команд

int mode = 0;
/* MODES:
0 - home
1 - menu
*/
int iInMainMenu = 0;
int iInMenu2 = 0;
const char* text_menu[] = {"mode1", "mode2", "mode3", "mode4", "mode5"};
const char* menu_texts[4][5] = {
  {"Teams", "Red", "Blue", "Yellow", "Green"},
  {"Roles", "Sniper", "Medic", "Soldier", "Vampire"},
  {"Sirius and CP", "Next", "Before", "Add", "Remove"},
  {"Commands", "Create command", "Check comm", "Check shoot", "clone"}
};
bool menu2 = false;
int numEl = 3;
int numEl2 = 5;

int mainCommandB2 = 0;
int standartMainCommandB2 = 0x8305E8;

// Led Strip
#define NUM_LEDS    3       // Кількість світлодіодів у стрічці
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, rgbLine, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(irDiode, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(irReceiver, INPUT);

  pinMode(Button1, INPUT_PULLUP);
  pinMode(Button2, INPUT_PULLUP);
  pinMode(Button3, INPUT_PULLUP);
  pinMode(Button4, INPUT_PULLUP);
  pinMode(Button5, INPUT_PULLUP);
  pinMode(Button6, INPUT_PULLUP);
  strip.begin();           // Ініціалізація стрічки
  strip.show(); 
  strip.setBrightness(50); // Встановлення яскравості
  Serial.begin(115200);
  Serial.println("start");
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  i2cDisp();

  mainCommandB2 = standartMainCommandB2;

  tone(buzzer, 800, 500);
}

void loop() {
  //buttons_checker();
  buttonTriggers();
  take_command();
}

void setColorString(int Red, int Green, int Blue){
  for(int i; i < NUM_LEDS; i++){
          strip.setPixelColor(i, strip.Color(Red, Green, Blue));}
  strip.show();
}





