//IR Send
const uint8_t CLONE_COUNT    = 36;
const int16_t lvl_0           = 600;
const int16_t lvl_1           = lvl_0<<1;
const uint8_t irfrequency    = 36;
const int16_t irt             = (int) ((500/irfrequency) - 1);
const uint8_t irpulses       = (int) (lvl_0 / (1000/irfrequency));
const int16_t lnk_timeout     = 3500; // для зчитування команд

uint8_t receiverPin = 1;    // ІЧ датчик
uint8_t irtransmitpin = 3;  // ІЧ діод
uint8_t butIn = 0;          // кнопка
uint8_t blueLed = 4;        // лямпочка
uint8_t buzzerPin = 2;       // пищалка
//modes
int mode = 2;               // Режими 0=Граната, 1=пошук гранати, 2=команда, 3=тир
int mode_max = 3;           // максимум режимів

int reflex_time_max = 5000; // Максимум час на реакційний режим

int GranData = 0;
bool granReady = false;
bool granThrow = false;

void setup() {
  Serial.begin(9600);
  
  pinMode(irtransmitpin, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(receiverPin, INPUT);
  pinMode(butIn, INPUT_PULLUP);
  // digitalWrite(blueLed, HIGH);
  // digitalWrite(irtransmitpin, HIGH);
  bip(400, 300);
  bip(500, 300);
  bip(700, 300);
  bip(400, 300);
  bip(500, 300);
  bip(700, 300);
}

void loop() {
  if (mode == 0){
    if(digitalRead(butIn) == LOW){ // Кнопка нажата
      if(!granReady){
      copy_command();}
      else{
        blym_blym(2, 300);
      }
    }else if(granReady){
      bip(300, 300);
      blym_blym(25, 100);
      bip(500, 1500);
      sendcommand(GranData);
      GranData = 0;
      granReady = false;
      digitalWrite(blueLed, LOW);
      bip(700, 500);
      delay(50000);
      mode = 1;
    }
  }
  else if (mode == 1){
    bip(500, 1000);
    blym_blym(5, 100);
    triggers();
  }
  else if (mode == 2){
    print_command();
    triggers();
  } else {
    reflex();
    triggers();
  }
}

void triggers(){
    static uint8_t tr  = 0;
    static uint8_t ltr = 0;
        ltr = tr;
        tr = digitalRead(butIn);
        if ( tr != ltr && tr == LOW){
          // Serial.print("Button clicked");
          blym_blym(3, 500);
          if(mode<mode_max){mode++;}
          else{mode=0;}
          }}

void reflex(){
  static int16_t recieved_pulse   = 0;
    static uint8_t recieved_bit   = 0;
    recieved_pulse = pulseIn(receiverPin, LOW);
    if (recieved_pulse > 1800){
      int rand = random(100, reflex_time_max);
      blym_blym(1, rand);
    }
}

void print_command(){
    static int16_t recieved_pulse  = 0;
    int supdata = 0;
    int data = 0;
    int16_t index = 0;
    recieved_pulse = pulseIn(receiverPin, LOW);
    if (recieved_pulse > 1800){
      while (recieved_pulse != 0){
        recieved_pulse = pulseIn(receiverPin, LOW,lnk_timeout);
        if ((recieved_pulse > lvl_0 - 200) && (recieved_pulse < lvl_0 + 200)) {bitClear(supdata, index);}
        else if ((recieved_pulse > lvl_1 - 200) && (recieved_pulse < lvl_1 + 200)) {bitSet(supdata, index);}
        else if (recieved_pulse == 0){
          break;
        }
        index++;}
      data = invert_data(supdata);
      Serial.println("Data Received:");
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
      bip(300,100);
  }
}

void copy_command(){
    static int16_t recieved_pulse  = 0;
    int supdata = 0;
    int data = 0;
    int16_t index = 0;
    recieved_pulse = pulseIn(receiverPin, LOW);
    if (recieved_pulse > 1800){
      while (recieved_pulse != 0){
        recieved_pulse = pulseIn(receiverPin, LOW,lnk_timeout);
        if ((recieved_pulse > lvl_0 - 200) && (recieved_pulse < lvl_0 + 200)) {bitClear(supdata, index);}
        else if ((recieved_pulse > lvl_1 - 200) && (recieved_pulse < lvl_1 + 200)) {bitSet(supdata, index);}
        else if (recieved_pulse == 0){
          
          break;
        }
        index++;}
      bitSet(supdata, 10);
      bitSet(supdata, 11);
      bitSet(supdata, 12);
      bitSet(supdata, 13);
      data = invert_data(supdata);

      GranData = data;
      

      Serial.println("Data Received:");
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
      bip(300,100);
      granReady = true;
  }
}

int invert_data(int data){
  int newData = 0;
  for(int i = 0; i<24; i++){
    if(bitRead(data, i) == 1){bitSet(newData, 23-i);}
    else{bitClear(newData, 23-i);}}
  return newData;
}

void blym_blym(int hm, int time){
  for (int16_t i = 0; i < hm; i++){
    digitalWrite(blueLed, LOW);
    delay(time);
    digitalWrite(blueLed, HIGH);
    if (hm == 1){return;}
    delay(time);
  }
}

void bip(int toner, int time){
  tone(buzzerPin, toner);
  delay(time);
  noTone(buzzerPin);
}

void sendcommand(int comm){
    uint8_t byte1 = (comm >> 16) & 0xFF; // Перший байт (старший)
    uint8_t byte2 = (comm >> 8) & 0xFF;  // Другий байт (середній)
    uint8_t byte3 = comm & 0xFF; 

    uint8_t parity = 0; uint8_t cl_game_mode_on    = 1;
    sendPulse(irtransmitpin,2);
    delayMicroseconds(lvl_0);
    for (int16_t i = 23; i >= 0; i--){
        if (((comm >> i) & B1) == 0){sendPulse(irtransmitpin,0);}
        else {
            sendPulse(irtransmitpin,1);
            parity = parity + 1;
        }
        delayMicroseconds(lvl_0);        
    }
    /*
    for (int16_t i = 7; i >= 0; i--){
        if (((0x83 >> i) & B1) == 0){sendPulse(irtransmitpin,0);}
        else {sendPulse(irtransmitpin,1);}
        delayMicroseconds(lvl_0);        
    }
    for (int16_t i = 7; i >= 0; i--){
        if (((byte2 >> i) & B1) == 0){sendPulse(irtransmitpin,0);}
        else {sendPulse(irtransmitpin,1);}
        delayMicroseconds(lvl_0);        
    }
    for (int16_t i = 7; i >= 0; i--){
        if (((byte3 >> i) & B1) == 0){sendPulse(irtransmitpin,0);}
        else {sendPulse(irtransmitpin,1);}
        delayMicroseconds(lvl_0);        
    }*/
    parity += 4;
    if (cl_game_mode_on == 0){parity = 24 - parity;}
    if (parity%2 == 0){sendPulse(irtransmitpin,0);}
    else {sendPulse(irtransmitpin,1);}
    delayMicroseconds(lvl_0); 
}

void sendPulse(int16_t pin, uint8_t length){
  int16_t i = 0;
    while(i < irpulses<<length){
      i++;
      digitalWrite(pin, HIGH);
      delayMicroseconds(irt);
      digitalWrite(pin, LOW);
      delayMicroseconds(irt);
    }
}
