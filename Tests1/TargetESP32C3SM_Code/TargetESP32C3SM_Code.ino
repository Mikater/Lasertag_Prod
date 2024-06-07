//Ir Read
const uint8_t MAX_COUNT      = 39; // max розмір масиву
const int16_t lnk_lvl_0       = 600; // 0
const int16_t lnk_lvl_1       = 1200; // 1
const int16_t lnk_timeout     = 3500;
//IR Send
const uint8_t CLONE_COUNT    = 36;
const int16_t lvl_0           = 600;
const int16_t lvl_1           = lvl_0<<1;
const uint8_t irfrequency    = 36;
const int16_t irt             = (int) ((500/irfrequency) - 4);
const uint8_t irpulses       = (int) (lvl_0 / (1000/irfrequency));

// Pin List
uint8_t receiverPin = 5;    // ІЧ датчик
uint8_t irtransmitpin = 2;  // ІЧ діод
uint8_t butIn = 4;          // кнопка
uint8_t blueLed = 3;        // лямпочка
//modes
int mode = 0;               // Режими 0=Приціл, 1=бонус, 2=тир
int mode_max = 2;           // максимум режимів

int reflex_time_max = 5000; // Максимум час на реакційний режим

uint16_t commands[6] = {0x8305, 0x8300, 0x8310, 0x8310, 0x8310, 0x8310};  // Команди на рандом
int com_max = 6;                                                          // Кількість команд

uint8_t data_recieved[MAX_COUNT]; // Масив принятого коду

// wifi
#include <WiFi.h>
const char* ssid     = "netis";
const char* password = "Cntgfy40";
WiFiServer server(80);


void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));

  pinMode(irtransmitpin, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(receiverPin, INPUT);
  pinMode(butIn, INPUT_PULLUP);
  digitalWrite(blueLed, HIGH);
  
  // Wifi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}}

void loop() {
  WiFiClient client = server.available();
  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/H\">here</a> to turn the LED on pin 5 on.<br>");
            client.print("Click <a href=\"/L\">here</a> to turn the LED on pin 5 off.<br>");
            client.print(millis());
            // The HTTP response ends with another blank line:
            client.println();
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
        if (currentLine.endsWith("GET /ledon")) {
          digitalWrite(3, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /ledoff")) {
          digitalWrite(3, LOW);                // GET /L turns the LED off
        }}}
        client.stop();
        Serial.println("Client Disconnected.");
        }                    // print it out the serial monitor


  if (mode == 0){
    receive_command();}
  else if (mode == 1){
    //bonus();
    sendcommand(commands[0]);
    delay(200);
  } else {
    reflex();
  }
  triggers();   
  
}

void web_page(){
  
}

void triggers(){
    static uint8_t tr  = 0;
    static uint8_t ltr = 0;
        ltr = tr;
        tr = digitalRead(butIn);
        if ( tr != ltr && tr == LOW){
          Serial.print("Button clicked");
          blym_blym(3, 500);
          if(mode<mode_max){mode++;}
          else{mode=0;}}}

void bonus(){
  static int16_t recieved_pulse   = 0;
    static uint8_t recieved_bit   = 0;
    recieved_pulse = pulseIn(receiverPin, LOW);
    if (recieved_pulse > 1800){
      blym_blym(2, 1000);
      blym_blym(5, 500);
      blym_blym(10, 250);
      int rand = random(0,com_max-1);
      sendcommand(commands[rand]);
    }
}

void reflex(){
  static int16_t recieved_pulse   = 0;
    static uint8_t recieved_bit   = 0;
    recieved_pulse = pulseIn(receiverPin, LOW);
    if (recieved_pulse > 1800){
      int rand = random(100, reflex_time_max);
      blym_blym(1, rand);
    }
}

void receive_command(){
    static int16_t recieved_pulse  = 0;
    static uint8_t recieved_bit    = 0;
    int16_t index = 0;
    recieved_pulse = pulseIn(receiverPin, LOW);
    if (recieved_pulse > 1800){
      while (recieved_pulse != 0){
        recieved_pulse = pulseIn(receiverPin, LOW,lnk_timeout);
        if ((recieved_pulse > lnk_lvl_0 - 200) && (recieved_pulse < lnk_lvl_0 + 200)) {recieved_bit = 0;}
        else if ((recieved_pulse > lnk_lvl_1 - 200) && (recieved_pulse < lnk_lvl_1 + 200)) {recieved_bit = 1;}
        else if (recieved_pulse == 0){
          Serial.println("Data Received:");
          for (int i = 0; i < MAX_COUNT; i++) {
            Serial.print(data_recieved[i]);}
          Serial.println();
          blym_blym(1, 2000);
          break;
        }
          if (index < MAX_COUNT) { // Перевірте, чи індекс ще в межах масиву
        data_recieved[index] = recieved_bit; // Додайте нове значення до масиву
        index++;
}}}}

void blym_blym(int hm, int time){
  for (int16_t i = 0; i < hm; i++){
    digitalWrite(blueLed, LOW);
    delay(time);
    digitalWrite(blueLed, HIGH);
    if (hm == 1){return;}
    delay(time);
  }
}

void sendcommand(uint16_t comm){
    uint8_t parity = 0; uint8_t cl_game_mode_on    = 1;
    sendPulse(irtransmitpin,2);
    delayMicroseconds(lvl_0);
    for (int16_t i = 15; i >= 0; i--){
        if (((comm >> i) & B1) == 0){sendPulse(irtransmitpin,0);}
        else {
            sendPulse(irtransmitpin,1);
            parity = parity + 1;
        }
        delayMicroseconds(lvl_0);        
    }
    for (int16_t i = 7; i >= 0; i--){
        if (((0xE8 >> i) & B1) == 0){sendPulse(irtransmitpin,0);}
        else {sendPulse(irtransmitpin,1);}
        delayMicroseconds(lvl_0);        
    }
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
