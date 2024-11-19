unsigned long base_time0 = 0; // поява піца 0
unsigned long base_time1 = 0; // поява піца 1
unsigned long base_time2 = 0; // поява піца 2
unsigned long base_time3 = 0; // поява піца 3
unsigned long base_time4 = 0; // поява піца 4
unsigned long base_time5 = 0; // поява піца 5
unsigned long base_time6 = 0; // постріл команд та рестарт

unsigned long base_timer_regen = 0; // таймер регенерації
unsigned long time_last_shot = 0; // таймер регенерації
unsigned long base_timer_froz = 0; // таймер регенерації




void base_mode(){
  unsigned long current_time = millis();
  base_froz_check();
  if(HP > 0){                             // якщо база жива
    if(current_time >= base_time6){
      pixels.clear();
      circ_inToOut(pixels.Color(255,0,255));
      sendcommand(team_respawn[base_team]); // відродження
      circ_inToOut(pixels.Color(255,0,255));
      // sendcommand(0x8305E8); // радіація

      current_time = millis();
      int a = base_period*1000/7;
      base_time0 = current_time + a;
      base_time1 = current_time + a * 2;
      base_time2 = current_time + a * 3;
      base_time3 = current_time + a * 4;
      base_time4 = current_time + a * 5;
      base_time5 = current_time + a * 6;
      base_time6 = current_time + a * 7;
    } else if (current_time >= base_time5){
      pizza_5(team_color[base_team]);
    } else if (current_time >= base_time4){
      pizza_4(team_color[base_team]);
    } else if (current_time >= base_time3){
      pizza_3(team_color[base_team]);
    } else if (current_time >= base_time2){
      pizza_2(team_color[base_team]);
    } else if (current_time >= base_time1){
      pizza_1(team_color[base_team]);
    } else if (current_time >= base_time0){
      pizza_0(team_color[base_team]);
    }
  }
}

void base_take_damage(int data){
  int damage_in_shot[16] = {1, 2, 4, 5, 7, 10, 15, 17, 20, 25, 30, 35, 40, 50, 75, 100};
  int ero = (data >> 10) & 0xF;
  int damage = damage_in_shot[ero];
  int e_team = (data >> 14) & 0x3;
  if (e_team != base_team){
    if (HP-damage <= 0){
      HP = 0;
    } else {
      HP-=damage;
    }
    time_last_shot = millis();
  }
}

void base_take_heal(int hp){
  if (HP + hp >= base_max_HP){
    HP = base_max_HP;
  } else {
    HP+=hp;
  }
  time_last_shot = millis();
}

void base_froz_check(){
  unsigned long current_time = millis();
  int i = base_max_HP / 5;
  int color_froz = pixels.Color(0, 255, 255);
  int color_defroz = pixels.Color(0, 0, 0);
  if (HP == 0){
    if(base_froz){
      if(current_time >= base_timer_froz){
        base_froz = false;
        HP = base_max_HP;
        pixels.clear();
      }
      frozen_disp();
    }
    else{
      base_froz = true;
      base_timer_froz = millis() + base_froz_period * 1000;
      frozen_disp();
    }
  }else if (HP != base_max_HP){
    if(current_time >= time_last_shot + base_regen_period * 1000){
      base_take_heal(10); // regeneration
    }
  }
  if(HP == base_max_HP){ // 100
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
  }else if(HP >= i*4){ // 80
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
  }else if(HP >= i*3){ // 60
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
  }else if(HP >= i*2){
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
  }else if(HP >= i){
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
  } else if(HP >= 0){
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