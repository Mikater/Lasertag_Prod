#include <Arduino.h>
#include <driver/i2s.h>
#include <LittleFS.h>

#define I2S_BCK     27  // BCLK
#define I2S_WS      14  // LRC (WS)
#define I2S_DATA    26  // DATA out

#define FILE_NAME   "blaster_shot.raw"
#define BUTTON_PIN  22
#define BUFFER_SIZE 2048

File audioFile;
bool playing = false;

void setup_i2s() {
  const i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
    .sample_rate = 22050,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,  // моно
    .communication_format = I2S_COMM_FORMAT_I2S,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 4,
    .dma_buf_len = 512,
    .use_apll = false,
    .tx_desc_auto_clear = true,
    .fixed_mclk = 0
  };

  const i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_BCK,
    .ws_io_num = I2S_WS,
    .data_out_num = I2S_DATA,
    .data_in_num = I2S_PIN_NO_CHANGE
  };

  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_NUM_0, &pin_config);
  i2s_zero_dma_buffer(I2S_NUM_0);
}

void setup() {
  Serial.begin(115200);
  delay(500);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  if (!LittleFS.begin()) {
    Serial.println("LittleFS не ініціалізовано!");
    while (true);
  }

  setup_i2s();

  audioFile = LittleFS.open(FILE_NAME, "r");
  if (!audioFile || audioFile.isDirectory()) {
    Serial.println("Файл не знайдено або це директорія!");
    while (true);
  }

  Serial.println("Готово. Натисни кнопку для відтворення.");
}

void playSound() {
  uint8_t buffer[BUFFER_SIZE];
  audioFile.seek(0, SeekSet);

  while (audioFile.available()) {
    size_t bytesRead = audioFile.read(buffer, BUFFER_SIZE);
    if (bytesRead == 0) break;

    size_t bytesWritten;
    i2s_write(I2S_NUM_0, buffer, bytesRead, &bytesWritten, portMAX_DELAY);
  }

  Serial.println("Звук відтворено.");
}

void loop() {
  static bool prevBtnState = HIGH;
  bool btnState = digitalRead(BUTTON_PIN);

  if (prevBtnState == HIGH && btnState == LOW && !playing) {
    playing = true;
    playSound();
    playing = false;
  }

  prevBtnState = btnState;
}