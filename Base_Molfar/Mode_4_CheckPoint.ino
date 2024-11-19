unsigned long cp_time0 = 0; // поява піца 0
unsigned long cp_time1 = 0; // поява піца 1
unsigned long cp_time2 = 0; // поява піца 2
unsigned long cp_time3 = 0; // поява піца 3
unsigned long cp_time4 = 0; // поява піца 4
unsigned long cp_time5 = 0; // поява піца 5
unsigned long cp_time6 = 0; // постріл команд та рестарт

unsigned long cp_timer_regen = 0; // таймер регенерації
unsigned long cp_time_last_shot = 0; // таймер регенерації




void checkPoint_mode(){
  unsigned long current_time = millis();
  cp_froz_check();                            // якщо база жива
    if(current_time >= cp_time6){
      pixels.clear();
      circ_inToOut(pixels.Color(255,0,255));
      sendcommand(team_respawn[cp_team]); // відродження
      circ_inToOut(pixels.Color(255,0,255));
      // sendcommand(0x8305E8); // радіація

      current_time = millis();
      int a = cp_period*1000/7;
      cp_time0 = current_time + a;
      cp_time1 = current_time + a * 2;
      cp_time2 = current_time + a * 3;
      cp_time3 = current_time + a * 4;
      cp_time4 = current_time + a * 5;
      cp_time5 = current_time + a * 6;
      cp_time6 = current_time + a * 7;
    } else {
      if (current_time >= cp_time5){
        pizza_5(team_color[cp_team]);
      } 
      if (current_time >= cp_time4){
        pizza_4(team_color[cp_team]);
      }
      if (current_time >= cp_time3){
        pizza_3(team_color[cp_team]);
      } 
      if (current_time >= cp_time2){
        pizza_2(team_color[cp_team]);
      } 
      if (current_time >= cp_time1){
        pizza_1(team_color[cp_team]);
      }
      if (current_time >= cp_time0){
        pizza_0(team_color[cp_team]);
      }
    }
  
}

void cp_take_damage(int data){
  int damage_in_shot[16] = {1, 2, 4, 5, 7, 10, 15, 17, 20, 25, 30, 35, 40, 50, 75, 100};
  int ero = (data >> 10) & 0xF;
  int damage = damage_in_shot[ero];
  int e_team = (data >> 14) & 0x3;
  if (e_team != cp_team){
    if (cp_HP-damage <= 0){
      cp_HP = cp_max_HP;
      cp_team = e_team;
    } else {
      cp_HP-=damage;
    }
    cp_time_last_shot = millis();
  } else cp_take_heal(damage);
}

void cp_take_heal(int hp){
  if (cp_HP + hp >= cp_max_HP){
    cp_HP = cp_max_HP;
  } else {
    cp_HP+=hp;
  }
  cp_time_last_shot = millis();
}

void cp_froz_check(){
  unsigned long current_time = millis();
  int i = cp_max_HP / 5;
  int color_froz = pixels.Color(0, 255, 255);
  int color_defroz = pixels.Color(0, 0, 0);
  if (cp_HP != cp_max_HP){
    if(current_time >= cp_time_last_shot + cp_regen_period * 1000){
      cp_take_heal(10); // regeneration
    }
  }
  if(cp_HP == cp_max_HP){ // 100
    pixels.setPixelColor(30, color_defroz);
    
    pixels.setPixelColor(21, color_defroz);
    pixels.setPixelColor(22, color_defroz);
    pixels.setPixelColor(29, color_defroz);
    pixels.setPixelColor(31, color_defroz);
    pixels.setPixelColor(38, color_defroz);
    pixels.setPixelColor(39, color_defroz);

    pixels.setPixelColor(13, color_defroz);
    pixels.setPixelColor(15, color_defroz);
    pixels.setPixelColor(28, color_defroz);
    pixels.setPixelColor(32, color_defroz);
    pixels.setPixelColor(45, color_defroz);
    pixels.setPixelColor(47, color_defroz);

    pixels.setPixelColor(6, color_defroz);
    pixels.setPixelColor(9, color_defroz);
    pixels.setPixelColor(27, color_defroz);
    pixels.setPixelColor(33, color_defroz);
    pixels.setPixelColor(51, color_defroz);
    pixels.setPixelColor(54, color_defroz);

    pixels.setPixelColor(0, color_defroz);
    pixels.setPixelColor(4, color_defroz);
    pixels.setPixelColor(26, color_defroz);
    pixels.setPixelColor(34, color_defroz);
    pixels.setPixelColor(56, color_defroz);
    pixels.setPixelColor(60, color_defroz);    
  }else if(cp_HP >= i*4){ // 80
    pixels.setPixelColor(30, color_froz);
    
    pixels.setPixelColor(21, color_defroz);
    pixels.setPixelColor(22, color_defroz);
    pixels.setPixelColor(29, color_defroz);
    pixels.setPixelColor(31, color_defroz);
    pixels.setPixelColor(38, color_defroz);
    pixels.setPixelColor(39, color_defroz);

    pixels.setPixelColor(13, color_defroz);
    pixels.setPixelColor(15, color_defroz);
    pixels.setPixelColor(28, color_defroz);
    pixels.setPixelColor(32, color_defroz);
    pixels.setPixelColor(45, color_defroz);
    pixels.setPixelColor(47, color_defroz);

    pixels.setPixelColor(6, color_defroz);
    pixels.setPixelColor(9, color_defroz);
    pixels.setPixelColor(27, color_defroz);
    pixels.setPixelColor(33, color_defroz);
    pixels.setPixelColor(51, color_defroz);
    pixels.setPixelColor(54, color_defroz);

    pixels.setPixelColor(0, color_defroz);
    pixels.setPixelColor(4, color_defroz);
    pixels.setPixelColor(26, color_defroz);
    pixels.setPixelColor(34, color_defroz);
    pixels.setPixelColor(56, color_defroz);
    pixels.setPixelColor(60, color_defroz);  
  }else if(cp_HP >= i*3){ // 60
    pixels.setPixelColor(30, color_froz);
    
    pixels.setPixelColor(21, color_froz);
    pixels.setPixelColor(22, color_froz);
    pixels.setPixelColor(29, color_froz);
    pixels.setPixelColor(31, color_froz);
    pixels.setPixelColor(38, color_froz);
    pixels.setPixelColor(39, color_froz);

    pixels.setPixelColor(13, color_defroz);
    pixels.setPixelColor(15, color_defroz);
    pixels.setPixelColor(28, color_defroz);
    pixels.setPixelColor(32, color_defroz);
    pixels.setPixelColor(45, color_defroz);
    pixels.setPixelColor(47, color_defroz);

    pixels.setPixelColor(6, color_defroz);
    pixels.setPixelColor(9, color_defroz);
    pixels.setPixelColor(27, color_defroz);
    pixels.setPixelColor(33, color_defroz);
    pixels.setPixelColor(51, color_defroz);
    pixels.setPixelColor(54, color_defroz);

    pixels.setPixelColor(0, color_defroz);
    pixels.setPixelColor(4, color_defroz);
    pixels.setPixelColor(26, color_defroz);
    pixels.setPixelColor(34, color_defroz);
    pixels.setPixelColor(56, color_defroz);
    pixels.setPixelColor(60, color_defroz);  
  }else if(cp_HP >= i*2){
    pixels.setPixelColor(30, color_froz);
    
    pixels.setPixelColor(21, color_froz);
    pixels.setPixelColor(22, color_froz);
    pixels.setPixelColor(29, color_froz);
    pixels.setPixelColor(31, color_froz);
    pixels.setPixelColor(38, color_froz);
    pixels.setPixelColor(39, color_froz);

    pixels.setPixelColor(13, color_froz);
    pixels.setPixelColor(15, color_froz);
    pixels.setPixelColor(28, color_froz);
    pixels.setPixelColor(32, color_froz);
    pixels.setPixelColor(45, color_froz);
    pixels.setPixelColor(47, color_froz);

    pixels.setPixelColor(6, color_defroz);
    pixels.setPixelColor(9, color_defroz);
    pixels.setPixelColor(27, color_defroz);
    pixels.setPixelColor(33, color_defroz);
    pixels.setPixelColor(51, color_defroz);
    pixels.setPixelColor(54, color_defroz);

    pixels.setPixelColor(0, color_defroz);
    pixels.setPixelColor(4, color_defroz);
    pixels.setPixelColor(26, color_defroz);
    pixels.setPixelColor(34, color_defroz);
    pixels.setPixelColor(56, color_defroz);
    pixels.setPixelColor(60, color_defroz);  
  }else if(cp_HP >= i){
    pixels.setPixelColor(30, color_froz);
    
    pixels.setPixelColor(21, color_froz);
    pixels.setPixelColor(22, color_froz);
    pixels.setPixelColor(29, color_froz);
    pixels.setPixelColor(31, color_froz);
    pixels.setPixelColor(38, color_froz);
    pixels.setPixelColor(39, color_froz);

    pixels.setPixelColor(13, color_froz);
    pixels.setPixelColor(15, color_froz);
    pixels.setPixelColor(28, color_froz);
    pixels.setPixelColor(32, color_froz);
    pixels.setPixelColor(45, color_froz);
    pixels.setPixelColor(47, color_froz);

    pixels.setPixelColor(6, color_froz);
    pixels.setPixelColor(9, color_froz);
    pixels.setPixelColor(27, color_froz);
    pixels.setPixelColor(33, color_froz);
    pixels.setPixelColor(51, color_froz);
    pixels.setPixelColor(54, color_froz);

    pixels.setPixelColor(0, color_defroz);
    pixels.setPixelColor(4, color_defroz);
    pixels.setPixelColor(26, color_defroz);
    pixels.setPixelColor(34, color_defroz);
    pixels.setPixelColor(56, color_defroz);
    pixels.setPixelColor(60, color_defroz);  
  } else if(cp_HP >= 0){
    pixels.setPixelColor(30, color_froz);
    
    pixels.setPixelColor(21, color_froz);
    pixels.setPixelColor(22, color_froz);
    pixels.setPixelColor(29, color_froz);
    pixels.setPixelColor(31, color_froz);
    pixels.setPixelColor(38, color_froz);
    pixels.setPixelColor(39, color_froz);

    pixels.setPixelColor(13, color_froz);
    pixels.setPixelColor(15, color_froz);
    pixels.setPixelColor(28, color_froz);
    pixels.setPixelColor(32, color_froz);
    pixels.setPixelColor(45, color_froz);
    pixels.setPixelColor(47, color_froz);

    pixels.setPixelColor(6, color_froz);
    pixels.setPixelColor(9, color_froz);
    pixels.setPixelColor(27, color_froz);
    pixels.setPixelColor(33, color_froz);
    pixels.setPixelColor(51, color_froz);
    pixels.setPixelColor(54, color_froz);

    pixels.setPixelColor(0, color_froz);
    pixels.setPixelColor(4, color_froz);
    pixels.setPixelColor(26, color_froz);
    pixels.setPixelColor(34, color_froz);
    pixels.setPixelColor(56, color_froz);
    pixels.setPixelColor(60, color_froz);  
  }
  pixels.show();
}