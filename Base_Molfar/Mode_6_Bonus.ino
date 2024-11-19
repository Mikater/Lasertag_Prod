int rain[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
unsigned long time_to_led = 0;
unsigned long time_to_off = 0;

void bonus_mode(){
  // Serial.println("1");  
  static int n_elem = 0;
  static int n_elem_to_off = 5;
  static int rain[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


  unsigned long current_time = millis();
  if (time_to_led <= current_time){
    int n = random(0, 62);
    // Serial.println("2");  

    pixels.setPixelColor(n, pixels.Color(random(0, 256), random(0, 256), random(0, 256)));
    pixels.show();
    time_to_led = current_time + bonus_rain_period;
    rain[n_elem] = n;
    
    if (n_elem < 9){
    n_elem += 1;
    } else {n_elem = 0;}
  }
  if (time_to_off <= current_time){
    pixels.setPixelColor(rain[n_elem_to_off], pixels.Color(0, 0, 0));
    pixels.show();
    time_to_off = current_time + bonus_rain_period + random(-50, 50);
    if (n_elem_to_off < 9){
    n_elem_to_off += 1;
    } else {n_elem_to_off = 0;}
  }
}

void bonus_hit(){
  int comands[5] = {0xB400E8, 0xB401E8, 0xB402E8, 0xB403E8, 0x8300E8};
  int n = random(0, 5);

  circ_inToOut(pixels.Color(random(0, 256), random(0, 256), random(0, 256)));
  circ_inToOut(pixels.Color(random(0, 256), random(0, 256), random(0, 256)));
  circ_inToOut(pixels.Color(random(0, 256), random(0, 256), random(0, 256)));
  circ_inToOut(pixels.Color(random(0, 256), random(0, 256), random(0, 256)));
  circ_inToOut(pixels.Color(random(0, 256), random(0, 256), random(0, 256)));
  
  sendcommand(comands[n]);
  
  pixels.clear();
}