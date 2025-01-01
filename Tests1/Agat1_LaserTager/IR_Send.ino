void createShootData(){
  shootData = 0;
  shootData = ID << 16;
  shootData = shootData | (team << 14);
  shootData = shootData | (damage << 10);
}



void sendcommand(uint16_t comm){
  sendPulse(IR_Diode, 2); // start
  for(int i = 15; i>=0; i--){
    sendPulse(IR_Diode, bitRead(comm, i) == 0 ? 0 : 1);
  }
  for(int i = 7; i>=0; i--){
    sendPulse(IR_Diode, bitRead(0xE8, i) == 0 ? 0 : 1);
  }
}

void sendPulse(int16_t pin, int length){
  int16_t i = 0;
  while(i < irpulses<<length){
    i++;
    digitalWrite(pin, HIGH);
    delayMicroseconds(irt);
    digitalWrite(pin, LOW);
    delayMicroseconds(irt);
  }
  delayMicroseconds(lvl_0);
}