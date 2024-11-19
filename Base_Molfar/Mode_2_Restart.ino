unsigned long res_time0 = 0; // поява піца 0
unsigned long res_time1 = 0; // поява піца 1
unsigned long res_time2 = 0; // поява піца 2
unsigned long res_time3 = 0; // поява піца 3
unsigned long res_time4 = 0; // поява піца 4
unsigned long res_time5 = 0; // поява піца 5
unsigned long res_time6 = 0; // постріл команд та рестарт


void restart_mode(){
    unsigned long current_time = millis();                             // якщо база жива
    if(current_time >= res_time6){
      pixels.clear();
      circ_inToOut(pixels.Color(255,0,255));
      sendcommand(team_respawn[res_team]); // відродження

      current_time = millis();
      int a = res_period*1000/7;
      res_time0 = current_time + a;
      res_time1 = current_time + a * 2;
      res_time2 = current_time + a * 3;
      res_time3 = current_time + a * 4;
      res_time4 = current_time + a * 5;
      res_time5 = current_time + a * 6;
      res_time6 = current_time + a * 7;
    } else if (current_time >= res_time5){
      pizza_5(team_color[res_team]);
    } else if (current_time >= res_time4){
      pizza_4(team_color[res_team]);
    } else if (current_time >= res_time3){
      pizza_3(team_color[res_team]);
    } else if (current_time >= res_time2){
      pizza_2(team_color[res_team]);
    } else if (current_time >= res_time1){
      pizza_1(team_color[res_team]);
    } else if (current_time >= res_time0){
      pizza_0(team_color[res_team]);
    }

}