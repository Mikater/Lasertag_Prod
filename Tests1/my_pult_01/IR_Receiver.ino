void take_command(){
    static int16_t recieved_pulse  = 0;
    int supdata = 0;
    int data = 0;
    int16_t index = 0;
    recieved_pulse = pulseIn(irReceiver, LOW, 10000);
    if (recieved_pulse > 1400){
      while (recieved_pulse != 0){
        recieved_pulse = pulseIn(irReceiver, LOW,lnk_timeout);
        if ((recieved_pulse > lvl_0 - 200) && (recieved_pulse < lvl_0 + 200)) {bitClear(supdata, index);}
        else if ((recieved_pulse > lvl_1 - 200) && (recieved_pulse < lvl_1 + 200)) {bitSet(supdata, index);}
        else if (recieved_pulse == 0){
          break;
        }
        index++;}
      data = invert_data(supdata);
      Serial.println("Data Received:");           // Serial
      Serial.println(data, BIN);
      Serial.println(data, HEX);
      if(bitRead(data, 23) == 1){
        Serial.println("This is command");
        if(((byte*)&data)[1] == 0x00){
          Serial.println("Admin Kill!");
        } 
        else if(((byte*)&data)[1] == 0x05){
          Serial.println("Start Game");
        } else {Serial.println("Unknown Comm");
        }
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
      Serial.println("= = = = = = = = = = = = = = = = = = = = = = =");
    i2cCommand(data);
    if(digitalRead(Button4) == LOW){
      mainCommandB2 = data;
    } 
  }
}

int invert_data(int data){
  int newData = 0;
  for(int i = 0; i<24; i++){
    if(bitRead(data, i) == 1){bitSet(newData, 23-i);}
    else{bitClear(newData, 23-i);}}
  return newData;
}