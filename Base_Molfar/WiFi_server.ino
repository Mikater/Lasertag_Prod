void WiFi_start(){
  WiFi.begin(ssid, password);
  // Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());
}

void server_start(){
  server.on("/setMode", handleSetMode);

  server.on("/callBipStart", handleCallBipStart);

  server.on("/Base", handleBase);

  server.on("/info", handleDeviceDynamicInfo);

  server.on("/", handleDeviceStaticInfo);

  server.begin();
  server_on = true;
}

void handleSetMode() {
  if (server.hasArg("value")) {
    mode = server.arg("value").toInt();
    bip();
    server.send(200, "text/plain", "Mode set to " + String(mode));
  } else {
    server.send(400, "text/plain", "Value not provided");
  }
}

void handleBase(){
  if (server.hasArg("team")) {
    int w_team = server.arg("team").toInt();
    if (w_team >= 0 && w_team <= 3){
      base_team = w_team;
      server.send(200, "text/plain", "Team set to " + String(base_team));
    } else {
      server.send(400, "text/plain", "Value not provided team 0-3");
    }
  } else if (server.hasArg("hp")) {
    int w_hp = server.arg("hp").toInt();
    if (w_hp > 0 && w_hp <1000){
      base_max_HP = w_hp;
      HP = w_hp;
      server.send(200, "text/plain", "HP reloaded to" + String(HP));
    } else {server.send(400, "text/plain", "Value not provided. hp 1-999");}
  } else if (server.hasArg("timer_period")) {
    int w_per = server.arg("timer_period").toInt();
    base_period = w_per;
    server.send(200, "text/plain", "period reloaded to" + String(base_period));
  } else if (server.hasArg("regen_period")) {
    int w_reg_per = server.arg("regen_period").toInt();
      base_regen_period = w_reg_per;
      server.send(200, "text/plain", "regen reloaded to" + String(base_regen_period));
  } else if (server.hasArg("froz")) {
    int w_froz = server.arg("froz").toInt();
      base_froz_period = w_froz;
      server.send(200, "text/plain", "froz reloaded to" + String(base_froz_period));
  } else {
    server.send(400, "text/plain", "Value not provided");}
}

void handleDeviceStaticInfo() {
  String json = "{";
  json += "\"ID\": " + String(ID) + ",";
  json += "\"serial_nomer\": " + String(SerialNomber);
  json += "}";

  server.send(200, "application/json", json);
}

void handleDeviceDynamicInfo() {
  String json = "{";
  json += "\"mode\": " + String(mode) + ",";
  json += "\"base_hp\": " + String(HP) + ",";
  json += "\"cp_hp\": " + String(cp_HP) + ",";
  json += "\"base_team\": " + String(base_team) + ",";
  json += "\"res_team\": " + String(res_team) + ",";
  json += "\"cp_team\": " + String(cp_team); 
  json += "}";

  server.send(200, "application/json", json);
}

void handleCallBipStart() {
  bip_start();
  server.send(200, "text/plain", "bip_start called");
}