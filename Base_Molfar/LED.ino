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



void circ_pix(int r, int g, int b){
  uint32_t color = pixels.Color(r, g, b);
  pixels.clear();
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

  delay(delai);

  // #########################################################
  pixels.clear();
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

  delay(delai);

  // #########################################################
  pixels.clear();
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

  delay(delai);

  // #########################################################
  pixels.clear();
  for(int i=3; i<5; i++) {
    pixels.setPixelColor(Line4[i], color);
    pixels.setPixelColor(Line6[i], color);
    pixels.show();
  }
  pixels.setPixelColor(Line5[3], color);
  pixels.setPixelColor(Line5[5], color);
  pixels.show();

  delay(delai);

  // #########################################################
  pixels.clear();
  pixels.setPixelColor(30, color);
  pixels.show();

  delay(delai);
}

void rainbow(){
  int red = 250;
  int green = 0;
  int blue = 0;
  int step = 25;

  while (green < 250){
    circ_pix(red, green, blue);
    green += step;
  }
  while (red > 0){
    circ_pix(red, green, blue);
    red -= step;
  }
  while (blue < 250){
    circ_pix(red, green, blue);
    blue += step*2;
  }
  while (green > 0){
    circ_pix(red, green, blue);
    green -= step*2;
  }
  while (red < 250){
    circ_pix(red, green, blue);
    red += step;
  }
  while (blue > 0){
    circ_pix(red, green, blue);
    blue -= step;
  }
}