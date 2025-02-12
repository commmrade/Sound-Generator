#include "generator_base.hpp"
#include <algorithm>
#include <cstdlib>
#include <random>
#include "../config/consts.hpp"
#include <iostream>

class BrownNoiseGenerator: public GeneratorBase {
private:
    SoundConfig m_config{};
    inline static float GAIN = 0.015f;
    inline static float LOW_PASS = 0.985f;

    std::random_device device;
    std::normal_distribution<> dist{0.0f, 1.0f}; // Standard deviation for normal distribution
    std::mt19937_64 engine{device()};
public:


    int generateSamples(void *outputBuf, unsigned long frameCount, void* userData) override
    {
        float* out = (float*)outputBuf;
        float brownNoise = 0.0f;
        for (auto i = 0; i < frameCount; ++i) {
            float randomSample = dist(engine);

            brownNoise += randomSample * GAIN;  // Adjust gain for smoother transitions
            brownNoise = brownNoise * LOW_PASS;

            *out++ = brownNoise * m_config.volume;
        }
        return 0;
    }

    void setConfig(SoundConfig &cfg) override {
        m_config = cfg;
    }
};
