#pragma once

#include <Arduino.h>
#include <driver/i2s.h>
#include <Audio.h>

class I2SAudioPlayer {
public:
    I2SAudioPlayer(i2s_port_t port = I2S_NUM_0);

    void begin(uint32_t sampleRate = 22050, uint8_t bitsPerSample = 16, uint8_t channels = 1);
    void playRawFile(File& file, size_t bufferSize = 1024);
    void stop();

private:
    i2s_port_t _port;
    bool _isPlaying = false;
};