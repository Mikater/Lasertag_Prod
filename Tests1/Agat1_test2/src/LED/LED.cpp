#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN 26


int NumPixels = 4;
Adafruit_NeoPixel pixels(NumPixels, LED_PIN, NEO_GRB + NEO_KHZ800);

uint32_t team_color[6] = {pixels.Color(255, 0, 0), pixels.Color(0, 0, 255), pixels.Color(255, 180, 0), pixels.Color(0, 255, 0), pixels.Color(255, 255, 255), pixels.Color(255, 0, 255)};

bool pulsing = false;
int shoot_period = 20;
int pulse_period = 1000;
unsigned long shoot_time_1;
unsigned long shoot_time_2;
unsigned long shoot_time_3;
unsigned long shoot_time_4;
int led_color = pixels.Color(255, 0, 255);

int get_team_color(int team){
    return team_color[team];
}

void leds_shot(int color){
    led_color = color;
    pulsing = false;
    
    unsigned long current_time = millis();
    
    shoot_time_1 = current_time + shoot_period;
    shoot_time_2 = current_time + shoot_period*2;
    shoot_time_3 = current_time + shoot_period*3;
    shoot_time_4 = current_time + shoot_period*4;
    
    pixels.setPixelColor(0, led_color);
    pixels.show();
}

void leds_pulse(int color){
    led_color = color;
    pulsing = true;
}

void leds_tick(){
    if(pulsing){

    } else {
        unsigned long current_time = millis();
        if(current_time>shoot_time_4){
            pixels.clear();
            pixels.show();
        } else if(current_time>shoot_time_3){
            pixels.clear();
            pixels.setPixelColor(3, led_color);
            pixels.show();
        } else if(current_time>shoot_time_2){
            pixels.clear();
            pixels.setPixelColor(2, led_color);
            pixels.show();
        } else if(current_time>shoot_time_1){
            pixels.clear();
            pixels.setPixelColor(1, led_color);
            pixels.show();
        } 
    }
}

void leds_start(int strenght){
    pixels.begin();
    pixels.setBrightness(strenght);
    pixels.clear();
    pixels.show();
}