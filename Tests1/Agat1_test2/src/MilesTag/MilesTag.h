int mt_take_comm(int ir_receive_pin);

void mt_start(int burst, int color_code);

int invert_data(int data);

void mt_single_shoot(int IR_LED_PIN, int data);
void mt_burst_shoot(int IR_LED_PIN, int data);
void mt_auto_shoot(int IR_LED_PIN, int data);

void mt_exit_shooting();

void mt_reload();

int mt_create_shoot(int ID, int team, int damage);