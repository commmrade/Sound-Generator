#pragma once
#include "generator_base.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <portaudio.h>

class BinauralBeatsGenerator : public GeneratorBase {
    SoundConfig m_config;

    inline static float leftFreq{0.9f};   // Base frequency for left channel (A4)
    inline static float rightFreq{1.1f};
    inline static float DEL = 300.f;

    float sineWaveLeft;
    float sineWaveRight;

    int j{0};
public:
    int sampleCallback(void* outputBuf, unsigned long frameCount) override {
        float* out = (float*) outputBuf;

        for (auto i = 0; i < frameCount; ++i) {
            sineWaveLeft = (float) sin(((float)j / DEL) * leftFreq * M_PI * 2.f);
            sineWaveRight = (float) sin(((float)(j + 3) / DEL) * rightFreq * M_PI * 2.f);

            *out++ = sineWaveLeft * m_config.volume;
            *out++ = sineWaveRight * m_config.volume;
            j++;
        }

        return paContinue;
    }
    virtual void setConfig(const SoundConfig &cfg) override {
        m_config = cfg;
    }

    ~BinauralBeatsGenerator() = default;
};
