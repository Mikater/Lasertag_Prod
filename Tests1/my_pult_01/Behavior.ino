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
  }
}

void resetStringAndDisp(){
  setColorString(0, 0, 0);
  i2cDisp();
}