void behavior(int button){
  if(mode == 0){
    if(button == 1){
      setColorString(255, 0, 0);
      i2cBigText("STOP!");
      sendcommand(0x8300E8); // Admin Kill
      delay(1000);
      resetStringAndDisp();
    }
    else if(button == 2){
      setColorString(0, 255, 0);
      i2cBigText("START!");
      sendcommand(0x8305E8); // Admin Kill
      delay(1000);
      resetStringAndDisp();
    }
    else if(button == 3){
      setColorString(255, 0, 0);
      i2cBigText("Red team");
      sendcommand(0xA900E8); // Admin Kill
      delay(1000);
      resetStringAndDisp();
    }
    else if(button == 4){
      setColorString(0, 0, 255);
      i2cBigText("Blue Team");
      sendcommand(0xA901E8); // Admin Kill
      delay(1000);
      resetStringAndDisp();
    }
  }
  
  else if (mode == 1){

  }

  else if (mode == 3){

  }
}

void resetStringAndDisp(){
  setColorString(0, 0, 0);
  i2cDisp();
}