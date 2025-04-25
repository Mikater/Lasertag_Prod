#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

// WiFi
const char* ssid = "DesireTag";
const char* password = "DesTag2025";
WebServer server(80);
bool server_on = false;
int ID = 2;
const char* SerialNomber = "TAR00002";

int SetFilter = -1;
const int bufer = 1000;

int pause_value = 0;

int Last10Logs[bufer][4];

unsigned long timer_to_wifi;

bool addShotToLogs(int id, int team, int damage){
  for (size_t i = 0; i < bufer; i++)
  {
    if (Last10Logs[i][3] == 0){
      Last10Logs[i][0] = id;
      Last10Logs[i][1] = team;
      Last10Logs[i][2] = damage;
      Last10Logs[i][3] = 1;
      return true;
    }
  }
  return false;
}

void clearLogs() {
  for (size_t i = 0; i < bufer; i++) {
      for (size_t j = 0; j < 4; j++) {
          Last10Logs[i][j] = 0;
      }
  }
}

void WiFi_connect(){
  WiFi.begin(ssid, password);
  // Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());
}

void handleSetFilter() {
  if (server.hasArg("value")) {
    SetFilter = server.arg("value").toInt();
    server.send(200, "text/plain", "Filter set to " + String(SetFilter));
  } else {
    server.send(400, "text/plain", "Value not provided");
  }
}

int GetFilter(){
  return SetFilter;
}

void handlePause() {
  if (server.hasArg("value")) {
    pause_value = server.arg("value").toInt();
    server.send(200, "text/plain", "Pause set to " + String(pause_value));
  } else {
    server.send(400, "text/plain", "Value not provided");
  }
}

int GetPause(){
  return pause_value;
}

void handleDeviceStaticInfo() {
  String json = "{";
  json += "\"ID\": " + String(ID) + ",";
  json += "\"serial_nomer\": \"" + String(SerialNomber) + "\",";
  json += "\"Time\": " + String(millis());
  json += "}";

  server.send(200, "application/json", json);
}

void handleDeviceDynamicInfo() {
  String json = "{\"count\": 0, \"logs\": []}";  // За замовчуванням

  int logCount = 0;
  for (size_t i = 0; i < bufer; i++) {
    if (Last10Logs[i][3] != 0) {
      logCount++;
    }
  }

  if (logCount > 0) {
    json = "{\"count\": " + String(logCount) + ", \"logs\": [";
    bool firstLog = true;
    for (size_t i = 0; i < bufer; i++) {
      if (Last10Logs[i][3] != 0) {
        if (!firstLog) {
          json += ",";
        }
        json += "{";
        json += "\"Log_ID\": " + String(i) + ",";
        json += "\"ID\": " + String(Last10Logs[i][0]) + ",";
        json += "\"Team\": " + String(Last10Logs[i][1]) + ",";
        json += "\"Damage\": " + String(Last10Logs[i][2]) + ",";
        json += "\"Time\": " + String(Last10Logs[i][3]);
        json += "}";
        firstLog = false;
      }
    }
    json += "]}";
  }

  server.send(200, "application/json", json);
  clearLogs();
}

void server_start(){
  server.on("/setFilter", handleSetFilter);

  server.on("/pause", handlePause);

  server.on("/info", handleDeviceDynamicInfo);

  server.on("/", handleDeviceStaticInfo);

  server.begin();
  server_on = true;
}

void web_server_tick(){
  if (WiFi.status() == WL_CONNECTED){
    if (!server_on){
      Serial.println(WiFi.localIP());
      server_start();
    } else {
      server.handleClient();
    }
  } else {
    if(millis()>timer_to_wifi){
      if (server_on){
      server_on = false;
      }
      WiFi_connect();
      timer_to_wifi = millis() + 5000;
    }
  }
}