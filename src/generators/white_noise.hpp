#pragma once
#include "generator_base.hpp"
#include <cstdlib>
#include <portaudio.h>
#include <random>



class WhiteNoiseGenerator: public GeneratorBase {
private:
    SoundConfig m_config{};

    std::random_device device;
    std::normal_distribution<> dist{-.2f, 0.4f};
public:
    WhiteNoiseGenerator() = default;
    ~WhiteNoiseGenerator() = default;

    int sampleCallback(void* outputBuf, unsigned long frameCount)
    {
        float* out = (float*)outputBuf;
        for (auto i = 0; i < frameCount; ++i) {
            auto val = dist(device);
            *out++ = val * m_config.volume;
        }
        return paContinue;
    }
    void setConfig(const SoundConfig &cfg) override {
        m_config = cfg;
    }
};
