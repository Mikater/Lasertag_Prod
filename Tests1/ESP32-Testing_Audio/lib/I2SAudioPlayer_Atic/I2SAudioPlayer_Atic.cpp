#include "I2SAudioPlayer_Atic.h"
#include <FS.h>

I2SAudioPlayer::I2SAudioPlayer(i2s_port_t port) : _port(port) {}

void I2SAudioPlayer::begin(uint32_t sampleRate, uint8_t bitsPerSample, uint8_t channels) {
    i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
        .sample_rate = sampleRate,
        .bits_per_sample = (i2s_bits_per_sample_t)(bitsPerSample),
        .channel_format = (channels == 2) ? I2S_CHANNEL_FMT_RIGHT_LEFT : I2S_CHANNEL_FMT_ONLY_LEFT,
        .communication_format = I2S_COMM_FORMAT_I2S_MSB,
        .intr_alloc_flags = 0,
        .dma_buf_count = 8,
        .dma_buf_len = 1024,
        .use_apll = false
    };

    i2s_pin_config_t pin_config = {
        .bck_io_num = 27,
        .ws_io_num = 14,
        .data_out_num = 26,
        .data_in_num = I2S_PIN_NO_CHANGE
    };

    i2s_driver_install(_port, &i2s_config, 0, NULL);
    i2s_set_pin(_port, &pin_config);
}

void I2SAudioPlayer::playRawFile(File& file, size_t bufferSize) {
    if (!file || file.isDirectory()) return;

    uint8_t* buffer = (uint8_t*)malloc(bufferSize);
    if (!buffer) return;

    _isPlaying = true;

    while (file.available() && _isPlaying) {
        size_t bytesRead = file.read(buffer, bufferSize);
        size_t bytesWritten;
        i2s_write(_port, buffer, bytesRead, &bytesWritten, portMAX_DELAY);
    }

    free(buffer);
}

void I2SAudioPlayer::stop() {
    _isPlaying = false;
    i2s_zero_dma_buffer(_port);
}