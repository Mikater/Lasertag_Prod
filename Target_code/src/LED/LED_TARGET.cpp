#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN 5


int NumPixels = 4;
Adafruit_NeoPixel pixels(NumPixels, LED_PIN, NEO_GRB + NEO_KHZ800);

uint32_t team_color[6] = {pixels.Color(255, 0, 0), pixels.Color(0, 0, 255), pixels.Color(255, 180, 0), pixels.Color(0, 255, 0), pixels.Color(255, 255, 255), pixels.Color(255, 0, 255)};

bool pulsing = false;
int shoot_period = 20;
int pulse_period = 20;
unsigned long shoot_time_1;
unsigned long shoot_time_2;
unsigned long shoot_time_3;
unsigned long shoot_time_4;
unsigned long last_pulse_time;
int pulse_prop = 1;
int max_brightnes;
int pulse_brightnes;
int led_color = pixels.Color(255, 0, 255);

int get_team_color(int team){
    return team_color[team];
}

void leds_shot(int color){
    led_color = color;
    pulsing = false;
    pixels.setBrightness(max_brightnes);
    
    unsigned long current_time = millis();
    
    shoot_time_1 = current_time + shoot_period;
    shoot_time_2 = current_time + shoot_period*2;
    shoot_time_3 = current_time + shoot_period*3;
    shoot_time_4 = current_time + shoot_period*4;
    
    pixels.setPixelColor(0, led_color);
    pixels.show();
}

void leds_pulse(int color){
    pixels.setPixelColor(0, led_color);
    pixels.setPixelColor(1, led_color);
    pixels.setPixelColor(2, led_color);
    pixels.setPixelColor(3, led_color);
    pixels.show();
    led_color = color;
    pulsing = true;
    pixels.setBrightness(max_brightnes);
    pulse_brightnes = max_brightnes;
    pulse_prop = 1;
}

void leds_tick(){
    unsigned long current_time = millis();

    if(pulsing){

        if(current_time >= last_pulse_time){
            if(pulse_brightnes <= 0 || pulse_brightnes >= max_brightnes){
                pulse_prop = pulse_prop * (-1);
            }
            pulse_brightnes = pulse_brightnes + pulse_prop * 5;
            pixels.setBrightness(pulse_brightnes);
            
            pixels.setPixelColor(0, led_color);
            pixels.setPixelColor(1, led_color);
            pixels.setPixelColor(2, led_color);
            pixels.setPixelColor(3, led_color);
            
            pixels.show();
            // Serial.println(pulse_brightnes);
            last_pulse_time = current_time + pulse_period;
        }
    } else {
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
    max_brightnes = strenght;
    pixels.setBrightness(max_brightnes);
    pixels.clear();
    pixels.show();
}