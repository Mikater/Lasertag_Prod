void shoot(){
  sendPulse(IR_Diode, 2);
  for(int i = 23; i>=0; i--){
    sendPulse(IR_Diode, bitRead(shootData, i) == 0 ? 0 : 1);
  }
}