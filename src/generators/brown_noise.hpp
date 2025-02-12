#pragma once
#include "generator_base.hpp"
#include <cstdlib>
#include <portaudio.h>
#include <random>

class BrownNoiseGenerator: public GeneratorBase {
private:
    SoundConfig m_config{};
    inline static float GAIN = 0.015f;
    inline static float LOW_PASS = 0.992f;

    std::random_device device;
    std::normal_distribution<> dist{0.0f, 1.0f}; // Standard deviation for normal distribution
    std::mt19937_64 engine{device()};

    float brownNoise{0.0f};
public:
    BrownNoiseGenerator() = default;
    ~BrownNoiseGenerator() = default;

    int sampleCallback(void* outputBuf, unsigned long frameCount) override
    {
        float* out = (float*)outputBuf;
        for (auto i = 0; i < frameCount; ++i) {
            float randomSample = dist(engine);
            brownNoise += randomSample * GAIN;
            brownNoise = brownNoise * LOW_PASS;
            *out++ = brownNoise * m_config.volume;
        }
        return paContinue;
    }


    void setConfig(const SoundConfig &cfg) override {
        m_config = cfg;
    }
};
