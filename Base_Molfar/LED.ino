int delai = 70;

int Line1[5] = {0, 1, 2, 3, 4};
int Line2[6] = {5, 6, 7, 8, 9, 10};
int Line3[7] = {11, 12, 13, 14, 15, 16, 17};
int Line4[8] = {18, 19, 20, 21, 22, 23, 24, 25};
int Line5[9] = {26, 27, 28, 29, 30, 31, 32, 33, 34};
int Line6[8] = {35, 36, 37, 38, 39, 40, 41, 42};
int Line7[7] = {43, 44, 45, 46, 47, 48, 49};
int Line8[6] = {50, 51, 52, 53, 54, 55};
int Line9[5] = {56, 57, 58, 59, 60};

void circ_0(uint32_t color){
  for(int i=0; i<5; i++) {
    pixels.setPixelColor(Line1[i], color);
    pixels.setPixelColor(Line9[i], color);
    pixels.show();
  }
  pixels.setPixelColor(Line2[0], color);
  pixels.setPixelColor(Line2[5], color);
  pixels.setPixelColor(Line3[0], color);
  pixels.setPixelColor(Line3[6], color);
  pixels.setPixelColor(Line4[0], color);
  pixels.setPixelColor(Line4[7], color);
  pixels.setPixelColor(Line5[0], color);
  pixels.setPixelColor(Line5[8], color);
  pixels.setPixelColor(Line6[0], color);
  pixels.setPixelColor(Line6[7], color);
  pixels.setPixelColor(Line7[0], color);
  pixels.setPixelColor(Line7[6], color);
  pixels.setPixelColor(Line8[0], color);
  pixels.setPixelColor(Line8[5], color);
  pixels.show();
}

void circ_1(uint32_t color){
  for(int i=1; i<5; i++) {
    pixels.setPixelColor(Line2[i], color);
    pixels.setPixelColor(Line8[i], color);
    pixels.show();
  }
  pixels.setPixelColor(Line3[1], color);
  pixels.setPixelColor(Line3[5], color);
  pixels.setPixelColor(Line4[1], color);
  pixels.setPixelColor(Line4[6], color);
  pixels.setPixelColor(Line5[1], color);
  pixels.setPixelColor(Line5[7], color);
  pixels.setPixelColor(Line6[1], color);
  pixels.setPixelColor(Line6[6], color);
  pixels.setPixelColor(Line7[1], color);
  pixels.setPixelColor(Line7[5], color);
  pixels.show();
}

void circ_2(uint32_t color){
  for(int i=2; i<5; i++) {
    pixels.setPixelColor(Line3[i], color);
    pixels.setPixelColor(Line7[i], color);
    pixels.show();
  }
  pixels.setPixelColor(Line4[2], color);
  pixels.setPixelColor(Line4[5], color);
  pixels.setPixelColor(Line5[2], color);
  pixels.setPixelColor(Line5[6], color);
  pixels.setPixelColor(Line6[2], color);
  pixels.setPixelColor(Line6[5], color);
  pixels.show();
}

void circ_3(uint32_t color){
  for(int i=3; i<5; i++) {
    pixels.setPixelColor(Line4[i], color);
    pixels.setPixelColor(Line6[i], color);
    pixels.show();
  }
  pixels.setPixelColor(Line5[3], color);
  pixels.setPixelColor(Line5[5], color);
  pixels.show();
}

void circ_4(uint32_t color){
  pixels.setPixelColor(30, color);
  pixels.show();
}

void circ_outToIn(uint32_t color){
  pixels.clear();
  circ_0(color);
  
  delay(delai);
  pixels.clear();
  circ_1(color);

  delay(delai);
  pixels.clear();
  circ_2(color);

  delay(delai);
  pixels.clear();
  circ_3(color);

  delay(delai);
  pixels.clear();
  circ_4(color);
}

void circ_inToOut(int color){
  pixels.clear();
  circ_4(color);
  
  delay(delai);
  pixels.clear();
  circ_3(color);

  delay(delai);
  pixels.clear();
  circ_2(color);

  delay(delai);
  pixels.clear();
  circ_1(color);

  delay(delai);
  pixels.clear();
  circ_0(color);

  delay(delai);
  pixels.clear();
}

void pizza_0(int color){
  pixels.setPixelColor(1, color);
  pixels.setPixelColor(2, color);
  pixels.setPixelColor(3, color);
  pixels.setPixelColor(7, color);
  pixels.setPixelColor(8, color);
  pixels.setPixelColor(14, color);
  pixels.show();
}

void pizza_1(int color){
  pixels.setPixelColor(5, color);
  pixels.setPixelColor(16, color);
  pixels.setPixelColor(17, color);
  pixels.setPixelColor(18, color);
  pixels.setPixelColor(19, color);
  pixels.setPixelColor(20, color);
  pixels.show();
}

void pizza_2(int color){
  pixels.setPixelColor(35, color);
  pixels.setPixelColor(36, color);
  pixels.setPixelColor(37, color);
  pixels.setPixelColor(48, color);
  pixels.setPixelColor(49, color);
  pixels.setPixelColor(50, color);
  pixels.show();
}

void pizza_3(int color){
  pixels.setPixelColor(46, color);
  pixels.setPixelColor(52, color);
  pixels.setPixelColor(53, color);
  pixels.setPixelColor(58, color);
  pixels.setPixelColor(59, color);
  pixels.setPixelColor(57, color);
  pixels.show();
}

void pizza_4(int color){
  pixels.setPixelColor(40, color);
  pixels.setPixelColor(41, color);
  pixels.setPixelColor(42, color);
  pixels.setPixelColor(43, color);
  pixels.setPixelColor(44, color);
  pixels.setPixelColor(55, color);
  pixels.show();
}

void pizza_5(int color){
  pixels.setPixelColor(10, color);
  pixels.setPixelColor(11, color);
  pixels.setPixelColor(12, color);
  pixels.setPixelColor(23, color);
  pixels.setPixelColor(24, color);
  pixels.setPixelColor(25, color);
  pixels.show();
}

void frozen_disp(){
  int color_froz = pixels.Color(0, 255, 255);

  pixels.clear();
  pixels.setPixelColor(30, color_froz);
    
  pixels.setPixelColor(21, color_froz);
  pixels.setPixelColor(22, color_froz);
  pixels.setPixelColor(29, color_froz);
  pixels.setPixelColor(31, color_froz);
  pixels.setPixelColor(38, color_froz);
  pixels.setPixelColor(39, color_froz);

  pixels.setPixelColor(13, color_froz);
  pixels.setPixelColor(15, color_froz);
  pixels.setPixelColor(28, color_froz);
  pixels.setPixelColor(32, color_froz);
  pixels.setPixelColor(45, color_froz);
  pixels.setPixelColor(47, color_froz);

  pixels.setPixelColor(6, color_froz);
  pixels.setPixelColor(9, color_froz);
  pixels.setPixelColor(27, color_froz);
  pixels.setPixelColor(33, color_froz);
  pixels.setPixelColor(51, color_froz);
  pixels.setPixelColor(54, color_froz);

  pixels.setPixelColor(0, color_froz);
  pixels.setPixelColor(4, color_froz);
  pixels.setPixelColor(26, color_froz);
  pixels.setPixelColor(34, color_froz);
  pixels.setPixelColor(56, color_froz);
  pixels.setPixelColor(60, color_froz);

  pixels.setPixelColor(1, color_froz);
  pixels.setPixelColor(3, color_froz);
  pixels.setPixelColor(5, color_froz);
  pixels.setPixelColor(10, color_froz);
  pixels.setPixelColor(18, color_froz);
  pixels.setPixelColor(25, color_froz);
  pixels.setPixelColor(35, color_froz);
  pixels.setPixelColor(42, color_froz);
  pixels.setPixelColor(50, color_froz);
  pixels.setPixelColor(55, color_froz);
  pixels.setPixelColor(57, color_froz);
  pixels.setPixelColor(59, color_froz);
  pixels.show();
}

void ico_respawn(int color){
  pixels.setPixelColor(32, color);
  pixels.setPixelColor(28, color);
  
  circ_1(color);
  circ_3(color);

  pixels.show();

}

void ico_base(int color){
  pixels.setPixelColor(57, color);
  pixels.setPixelColor(58, color);
  pixels.setPixelColor(59, color);
  pixels.setPixelColor(45, color);
  pixels.setPixelColor(47, color);
  pixels.setPixelColor(29, color);
  pixels.setPixelColor(31, color);
  pixels.setPixelColor(13, color);
  pixels.setPixelColor(15, color);
  
  pixels.setPixelColor(6, color);
  pixels.setPixelColor(7, color);
  pixels.setPixelColor(8, color);
  pixels.setPixelColor(9, color);

  pixels.setPixelColor(1, color);
  pixels.setPixelColor(3, color);

  pixels.show();
}

void ico_target(){
  pixels.clear();
  uint32_t mono_color = pixels.Color(200, 0, 255);
  circ_1(mono_color);
  pixels.setPixelColor(30, mono_color);
  pixels.show();
}

void ico_checkPoint(int color){
  pixels.setPixelColor(57, color);
  pixels.setPixelColor(58, color);
  pixels.setPixelColor(59, color);
  pixels.setPixelColor(46, color);
  pixels.setPixelColor(30, color);
  pixels.setPixelColor(2, color);
  pixels.setPixelColor(14, color);
  
  pixels.setPixelColor(6, color);
  pixels.setPixelColor(7, color);
  pixels.setPixelColor(15, color);
  pixels.setPixelColor(16, color);

  pixels.setPixelColor(17, color);
  pixels.setPixelColor(19, color);

  pixels.show();
}

void ico_bonus(){
  uint32_t mono_color = pixels.Color(160, 0, 255);
  pixels.setPixelColor(39, mono_color);
  pixels.setPixelColor(38, mono_color);
  pixels.setPixelColor(30, mono_color);
  pixels.setPixelColor(31, mono_color);
  pixels.setPixelColor(20, mono_color);
  pixels.setPixelColor(21, mono_color);
  pixels.setPixelColor(15, mono_color);
  pixels.setPixelColor(16, mono_color);
  pixels.setPixelColor(1, mono_color);
  pixels.setPixelColor(2, mono_color);
  pixels.setPixelColor(3, mono_color);
  pixels.setPixelColor(6, mono_color);
  pixels.setPixelColor(7, mono_color);
  pixels.setPixelColor(8, mono_color);
  pixels.setPixelColor(9, mono_color);
  pixels.setPixelColor(12, mono_color);
  pixels.setPixelColor(13, mono_color);

  pixels.setPixelColor(58, mono_color);
  pixels.setPixelColor(52, mono_color);
  pixels.setPixelColor(53, mono_color);

  pixels.show();
}

void ico_lamp(){
  circ_2(pixels.Color(255, 130, 0));
  pixels.setPixelColor(52, pixels.Color(180, 180, 255));
  pixels.setPixelColor(53, pixels.Color(180, 180, 255));
  pixels.setPixelColor(58, pixels.Color(180, 180, 255));

  pixels.show();
}

void rainbow(){
  int red = 250;
  int green = 0;
  int blue = 0;
  int step = 25;

  while (green < 250){
    circ_outToIn(pixels.Color(red, green, blue));
    green += step;
  }
  sendcommand(0x8305E8);
  while (red > 0){
    circ_outToIn(pixels.Color(red, green, blue));
    red -= step;
  }
  sendcommand(0x8305E8);
  while (blue < 250){
    circ_outToIn(pixels.Color(red, green, blue));
    blue += step*2;
  }
  sendcommand(0x8305E8);
  while (green > 0){
    circ_outToIn(pixels.Color(red, green, blue));
    green -= step*2;
  }
  sendcommand(0x8305E8);
  while (red < 250){
    circ_outToIn(pixels.Color(red, green, blue));
    red += step;
  }
  sendcommand(0x8305E8);
  while (blue > 0){
    circ_outToIn(pixels.Color(red, green, blue));
    blue -= step;
  }
  sendcommand(0x8305E8); 
  while (green < 250){
    circ_inToOut(pixels.Color(red, green, blue));
    green += step;
  }
  sendcommand(0x8305E8);
  while (red > 0){
    circ_inToOut(pixels.Color(red, green, blue));
    red -= step;
  }
  sendcommand(0x8305E8);
  while (blue < 250){
    circ_inToOut(pixels.Color(red, green, blue));
    blue += step*2;
  }
  sendcommand(0x8305E8);
  while (green > 0){
    circ_inToOut(pixels.Color(red, green, blue));
    green -= step*2;
  }
  sendcommand(0x8305E8);
  while (red < 250){
    circ_inToOut(pixels.Color(red, green, blue));
    red += step;
  }
  sendcommand(0x8305E8);
  while (blue > 0){
    circ_inToOut(pixels.Color(red, green, blue));
    blue -= step;
  }
  sendcommand(0x8305E8);
}
