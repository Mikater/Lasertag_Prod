
void settings_comm(int data){
  static int set_team = 0;
  static int set_mode = 1;
  
  if (data == 0x8305E8){          // Start game
    mode = set_mode;
    if(mode == 1){
      HP = base_max_HP;
      base_team = set_team;
    } else if (mode == 2){
      res_team = set_team;
    } else if(mode == 4){
      cp_HP = cp_max_HP;
      cp_team = set_team;
    }
    pixels.clear();
    return;
  }else if (data == 0xA900E8){    // Team Red
    set_team = 0;
  }else if (data == 0xA901E8){    // Team Blue
    set_team = 1;
  }else if (data == 0xA902E8){    // Team Yellow
    set_team = 2;
  }else if (data == 0xA903E8){    // Team Green
    set_team = 3;
  }else if (data == 0xA800E8){    // Mode Base
    set_mode = 1;
  }else if (data == 0xA803E8){    // Mode Restart
    set_mode = 2;
  }else if (data == 0xA805E8){    // Mode Target
    set_mode = 3;
  }else if (data == 0xA807E8){    // Mode CheckPoint
    set_mode = 4;
  }else if (data == 0x830EE8){    // Mode Lamp
    set_mode = 5;
  }else if (data == 0xA801E8){    // Mode Bonus
    set_mode = 6;
  }
  //  830EE8 lamp
  //  bonus A801E8
  //  Apteka A806C0
  //  Arsenal 811EE8

  if(set_mode == 1){
    pixels.clear();
    ico_base(team_color[set_team]);
  }else if(set_mode == 2){
    pixels.clear();
    ico_respawn(team_color[set_team]);
  }else if(set_mode == 3){
    pixels.clear();
    ico_target();
  }else if(set_mode == 4){
    pixels.clear();
    ico_checkPoint(team_color[set_team]);
  }else if(set_mode == 5){
    pixels.clear();
    ico_lamp();
  }else if(set_mode == 6){
    pixels.clear();
    ico_bonus();
  }
}