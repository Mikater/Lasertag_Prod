void lamp_mode(){
  pixels.clear();
  for (int i = 0; i < NumPixels; i++) {
    pixels.setPixelColor(i, lamp_color); // Встановлення кольору для кожного світлодіода
  }
  pixels.show();
}