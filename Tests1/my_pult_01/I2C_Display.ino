void i2cDisp() {
  display.clearDisplay();
  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 0);
  display.println(F("home, love"));
  display.display();
}

void i2cBigText(const char* text){
  display.clearDisplay();
  display.setTextSize(3); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(text);
  display.display();
}

void i2cMenu(){
  display.clearDisplay();
  if(iInMainMenu == 0){
    display.drawRect(0, 0, 128, 10, SSD1306_WHITE);
  } else if (iInMainMenu < numEl-1){
    display.drawRect(0, 11, 128, 10, SSD1306_WHITE);
  } else{
    display.drawRect(0, 22, 128, 10, SSD1306_WHITE);
  }
  if(iInMainMenu == 0){
    display.setCursor(3, 1);
    display.setTextSize(1);
    display.println(F(menu_texts[0][0]));
    display.setCursor(3, 12);
    display.println(F(menu_texts[1][0]));
    display.setCursor(3, 23);
    display.println(F(menu_texts[2][0]));
  }else if (iInMainMenu < numEl-1){
    display.setCursor(3, 1);
    display.setTextSize(1);
    display.println(F(menu_texts[iInMainMenu-1][0]));
    display.setCursor(3, 12);
    display.println(F(menu_texts[iInMainMenu][0]));
    display.setCursor(3, 23);
    display.println(F(menu_texts[iInMainMenu+1][0]));
  }else{
    display.setCursor(3, 1);
    display.setTextSize(1);
    display.println(F(menu_texts[iInMainMenu-2][0]));
    display.setCursor(3, 12);
    display.println(F(menu_texts[iInMainMenu-1][0]));
    display.setCursor(3, 23);
    display.println(F(menu_texts[iInMainMenu][0]));
  }
  display.display();
}

void i2cMenu2(){
  display.clearDisplay();
  if(iInMenu2 == 0){
    display.drawRect(0, 0, 128, 10, SSD1306_WHITE);
  } else if (iInMenu2 < numEl2-2){
    display.drawRect(0, 11, 128, 10, SSD1306_WHITE);
  } else{
    display.drawRect(0, 22, 128, 10, SSD1306_WHITE);
  }
  if(iInMenu2 == 0){
    display.setCursor(3, 1);
    display.setTextSize(1);
    display.println(F(menu_texts[iInMainMenu][1]));
    display.setCursor(3, 12);
    display.println(F(menu_texts[iInMainMenu][2]));
    display.setCursor(3, 23);
    display.println(F(menu_texts[iInMainMenu][3]));
  }else if (iInMenu2 < numEl2-2){
    display.setCursor(3, 1);
    display.setTextSize(1);
    display.println(F(menu_texts[iInMainMenu][iInMenu2]));
    display.setCursor(3, 12);
    display.println(F(menu_texts[iInMainMenu][iInMenu2+1]));
    display.setCursor(3, 23);
    display.println(F(menu_texts[iInMainMenu][iInMenu2+2]));
  }else{
    display.setCursor(3, 1);
    display.setTextSize(1);
    display.println(F(menu_texts[iInMainMenu][iInMenu2-1]));
    display.setCursor(3, 12);
    display.println(F(menu_texts[iInMainMenu][iInMenu2]));
    display.setCursor(3, 23);
    display.println(F(menu_texts[iInMainMenu][iInMenu2+1]));
  }
  display.display();
}

void i2cCommand(int data){
  display.clearDisplay();
  if(bitRead(data, 23) == 1){
    display.setTextSize(1); 
    display.setCursor(0, 0);
    display.println("command");
    display.setCursor(0, 10);
    display.println(data, HEX);
    //Serial.println("This is command");
    if(((byte*)&data)[1] == 0x00){
      //Serial.println("Admin Kill!");
    } 
    else if(((byte*)&data)[1] == 0x05){
      Serial.println("Start Game");
    } else {Serial.println("Unknown Comm");}
  } else {
    Serial.println("Shooting!!!");
    int shooterID = ((byte*)&data)[2];
    Serial.print("Id shooter: ");
    Serial.println(shooterID);
    if(bitRead(data, 15) == 1){
      if(bitRead(data, 14) == 1){
        Serial.println("Team Green");
      } else {Serial.println("Team Yellow");}
    } else{
      if(bitRead(data, 14) == 1){
        Serial.println("Team Blue");
      } else {Serial.println("Team Red");}
    }
  }
  display.display();
  setColorString(255, 0, 255);    

  Serial.println("= = = = = = = = = = = = = = = = = = = = = = =");
  delay(2000);
  setColorString(0, 0, 0);    
  
}
