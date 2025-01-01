// void WiFi_start(){
//   WiFi.begin(ssid, password);
//   // Serial.println("Connected to WiFi");
//   Serial.println(WiFi.localIP());
// }

// void server_start(){
//   server.on("/setMode", handleSetMode);

//   // server.on("/callBipStart", handleCallBipStart);

//   // server.on("/Base", handleBase);

//   // server.on("/info", handleDeviceDynamicInfo);

//   server.on("/", handleDeviceStaticInfo);

//   server.begin();
//   server_on = true;
// }

// void handleSetMode() {
//   if (server.hasArg("value")) {
//     gameMode = server.arg("value").toInt();
//     server.send(200, "text/plain", "Mode set to " + String(gameMode));
//   } else {
//     server.send(400, "text/plain", "Value not provided");
//   }
// }

// void handleDeviceStaticInfo() {
//   String json = "{";
//   json += "\"ID\": " + String(ID) + ",";
//   json += "\"serial_nomer\": " + String(SerialNomber);
//   json += "}";

//   server.send(200, "application/json", json);
// }