bool vibro_on = false;
unsigned long vibro_to_time;

void set_vibro(long len_vib){
  vibro_to_time = millis() + len_vib;
  vibro_on = true;
  digitalWrite(vibro_pin, 1);
}

void check_vibro(){
  if (vibro_on){
    if(millis() >= vibro_to_time){
      vibro_on = false;
      digitalWrite(vibro_pin, 0);
    }
  }
}