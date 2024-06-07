const uint8_t MAX_COUNT      = 39;
const int16_t lnk_lvl_0       = 600;
const int16_t lnk_lvl_1       = 1200;
const int16_t lnk_timeout     = 3500;


// Pin List
uint8_t receiverPin = 5;
uint8_t irLed = 2;
uint8_t butIn = 4;
uint8_t blueLed = 3;

int mode = 0; // Режими 0=Приціл, 1=бонус, 2=тир
int mode_max = 2;
uint8_t data_recieved[MAX_COUNT];

void setup() {
  Serial.begin(9600);
  pinMode(irLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(receiverPin, INPUT);
  pinMode(butIn, INPUT_PULLUP);
  digitalWrite(blueLed, HIGH);
}

void loop() {
  if (mode == 0){
    receive_command();}
  else if (mode == 1){
    blym_blym(3, 500);
  } else {
    blym_blym(3, 150);
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
