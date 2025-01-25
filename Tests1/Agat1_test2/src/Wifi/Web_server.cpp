#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

// WiFi
const char* ssid = "netis";
const char* password = "Cntgfy40";
WebServer server(80);
bool server_on = false;
int ID;
int SerialNomber;

unsigned long timer_to_wifi;

void WiFi_connect(){
  WiFi.begin(ssid, password);
  // Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());
}

void handleSetMode() {
  if (server.hasArg("value")) {
    int gameMode = server.arg("value").toInt();
    server.send(200, "text/plain", "Mode set to " + String(gameMode));
  } else {
    server.send(400, "text/plain", "Value not provided");
  }
}

void handleDeviceStaticInfo() {
  String json = "{";
  json += "\"ID\": " + String(ID) + ",";
  json += "\"serial_nomer\": " + String(SerialNomber);
  json += "}";

  server.send(200, "application/json", json);
}

void server_start(){
  server.on("/setMode", handleSetMode);

  // server.on("/callBipStart", handleCallBipStart);

  // server.on("/Base", handleBase);

  // server.on("/info", handleDeviceDynamicInfo);

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
      timer_to_wifi = millis() + 500;
    }
  }
}