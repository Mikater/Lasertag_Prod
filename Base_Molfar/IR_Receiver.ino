void take_command(){
    static int16_t recieved_pulse  = 0;
    int supdata = 0;
    int data = 0;
    int16_t index = 0;
    recieved_pulse = pulseIn(IR_Input, LOW, 10000);
    if (recieved_pulse > 1800){
      while (recieved_pulse != 0){
        recieved_pulse = pulseIn(IR_Input, LOW,lnk_timeout);
        if ((recieved_pulse > lvl_0 - 200) && (recieved_pulse < lvl_0 + 200)) {bitClear(supdata, index);}
        else if ((recieved_pulse > lvl_1 - 200) && (recieved_pulse < lvl_1 + 200)) {bitSet(supdata, index);}
        else if (recieved_pulse == 0){
          break;
        }
        index++;}
      data = invert_data(supdata);
      if(data == 0x8300E8){
        mode = 0;
        settings_comm(data);
        return;
      }
      if(mode == 0){
        settings_comm(data);
      } else if(mode == 1){
        if(bitRead(data, 23) != 1){
          base_take_damage(data);}
      } else if(mode == 3){
        print_data(data);
        hitting(data);
      } else if(mode == 4){
        if(bitRead(data, 23) != 1){
          cp_take_damage(data);}
      } else if(mode == 6){
        bonus_hit();
      }
      
  } 
}


void print_data(int data){
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
}

void hitting(int data){
  if(bitRead(data, 23) == 1){
    bip();
    // Serial.println("This is command");
    circ_inToOut(pixels.Color(0, 255, 255));
    if(((byte*)&data)[1] == 0x00){              // Admin kill
      circ_outToIn(pixels.Color(255, 0, 0));
    } 
    else if(((byte*)&data)[1] == 0x05){         // Start Game
      circ_outToIn(pixels.Color(0, 255, 0));
    } 
  } 
  else {
    bup();
    if(bitRead(data, 15) == 1){
      if(bitRead(data, 14) == 1){
        circ_inToOut(pixels.Color(0, 255, 0));              //  Team Green
      } else {circ_inToOut(pixels.Color(255, 255, 0));}     //  Team Yellow
    } else{
      if(bitRead(data, 14) == 1){
        circ_inToOut(pixels.Color(0, 0, 255));              //  Team Blue
      } else {circ_inToOut(pixels.Color(255, 0, 0));}       //  Team Red
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