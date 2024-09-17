void sendcommand(int comm){
  sendPulse(irDiode, 2); // start
  for(int i = 23; i>=0; i--){
    sendPulse(irDiode, bitRead(comm, i) == 0 ? 0 : 1);
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