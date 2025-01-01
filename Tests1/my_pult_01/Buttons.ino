void buttons_checker(){
  if (digitalRead(Button2) == LOW){
    if (mode == 0){
      sendcommand(mainCommandB2);
      i2cBigText("Start!");
      while(digitalRead(Button2) == LOW){}   
      i2cDisp();
    }
  }

  if (digitalRead(Button1) == LOW){
    if (mode == 0){
      // send command stop game;
      i2cBigText("STOP!");
      while(digitalRead(Button1) == LOW){}
      i2cDisp();
    } else {
      // exit to home
      mode = 0;
      iInMainMenu = 0;
      iInMenu2 = 0;
      i2cDisp();
      delay(40);
      mainCommandB2 = standartMainCommandB2;
      while(digitalRead(Button1) == LOW){}
    }
  }
  if (digitalRead(Button3) == LOW){
    if(mode == 0){
      sendcommand(0x8B00E8);
      i2cBigText("HealBox");
      while(digitalRead(Button3) == LOW){}  
      i2cDisp();
    }else if(mode == 1){
      i2cMenu2();
      mode++;
      delay(40);
      while(digitalRead(Button3) == LOW){}}
  }
  if (digitalRead(Button4) == LOW){
    if(mode == 1){
      if(iInMainMenu>0){
        iInMainMenu--;
        i2cMenu();
        delay(40);
        while(digitalRead(Button4) == LOW){}}
    } else if(mode == 2){
      if(iInMenu2>0){
        iInMenu2--;
        i2cMenu2();
        delay(40);
        while(digitalRead(Button4) == LOW){}}}
  }
  if (digitalRead(Button5) == LOW){
    if(mode == 0){
      sendcommand(0x830EE8);
      i2cBigText("HealBox");
      while(digitalRead(Button5) == LOW){}    
      i2cDisp();
    }else if(mode == 1){
      mode = 0;
      iInMainMenu = 0;
      i2cDisp();
      delay(40);
      while(digitalRead(Button5) == LOW){}
    }else if(mode == 2){
      i2cMenu();
      iInMenu2 = 0;
      mode--;
      delay(40);
      while(digitalRead(Button5) == LOW){}}
  }
  if (digitalRead(Button6) == LOW){ //Mode
    if(mode == 0){
      mode++;
      i2cMenu();
      delay(40);
      while(digitalRead(Button6) == LOW){}
    }else if(mode == 1 && iInMainMenu < numEl-1){
      iInMainMenu++;
      delay(40);
      i2cMenu();
      while(digitalRead(Button6) == LOW){}
    }else if(mode == 2 && iInMenu2 < numEl2-2){
      iInMenu2++;
      delay(40);
      i2cMenu2();
      while(digitalRead(Button6) == LOW){}
    }
  }
}

void buttonTriggers(){
  static uint8_t bt1  = 0;
  static uint8_t lbt1 = 0;
  lbt1 = bt1;
  bt1 = digitalRead(Button1);
  if ( bt1 != lbt1 && bt1 == LOW){
    // button1 triggered
    behavior(1);
  }
  static uint8_t bt2  = 0;
  static uint8_t lbt2 = 0;
  lbt2 = bt2;
  bt2 = digitalRead(Button2);
  if ( bt2 != lbt2 && bt2 == LOW){
    // button2 triggered
    behavior(2);
  }
  static uint8_t bt3  = 0;
  static uint8_t lbt3 = 0;
  lbt3 = bt3;
  bt3 = digitalRead(Button3);
  if ( bt3 != lbt3 && bt3 == LOW){
    // button3 triggered
    behavior(3);
  }
  static uint8_t bt4  = 0;
  static uint8_t lbt4 = 0;
  lbt4 = bt4;
  bt4 = digitalRead(Button4);
  if ( bt4 != lbt4 && bt4 == LOW){
    // button4 triggered
    behavior(4);
  }
  static uint8_t bt5  = 0;
  static uint8_t lbt5 = 0;
  lbt5 = bt5;
  bt5 = digitalRead(Button5);
  if ( bt5 != lbt5 && bt5 == LOW){
    // button5 triggered
    behavior(5);
  }
  static uint8_t bt6  = 0;
  static uint8_t lbt6 = 0;
  lbt6 = bt6;
  bt6 = digitalRead(Button6);
  if ( bt6 != lbt6 && bt6 == LOW){
    // button6 triggered
    behavior(6);
  }
}