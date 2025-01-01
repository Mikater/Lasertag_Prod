uint8_t broadcastAddress[] = {0xB0, 0xA7, 0x32, 0x22, 0x12, 0x20};

typedef struct struct_message {
  // char a[32];
  int shoot_data;
  int HP;
  int mode;
  int team;
  int code;
  // float c;
  // bool d;
} struct_message;

/*
code: 1-shooted, 200-OK, 0-change mode or team
*/

struct_message en_data;

void begin_esp_now(){
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(esp_now_recv_cb_t(esp_now_data_recv));
}

void esp_now_data_recv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&en_data, incomingData, sizeof(en_data));
  if(en_data.code == 0){
    team = en_data.team;
    mode = en_data.mode;
    return;
  }
  if(en_data.code == 1){
    //shooted
    return;
  }
  // Serial.print("Bytes received: ");
  // Serial.println(len);
  // Serial.print("Char: ");
  // Serial.println(myData.a);
  // Serial.print("Int: ");
  // Serial.println(myData.b);
  // Serial.print("Float: ");
  // Serial.println(myData.c);
  // Serial.print("Bool: ");
  // Serial.println(myData.d);
  // Serial.println();
}

void send_esp_now(int code){
  en_data.HP = HP;
  en_data.team = team;
  en_data.mode = mode;
  en_data.code = code;
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &en_data, sizeof(en_data));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
}