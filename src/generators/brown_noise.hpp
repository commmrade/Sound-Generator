#include "generator_base.hpp"
#include <algorithm>
#include <cstdlib>
#include <random>
#include "../config/consts.hpp"
#include <iostream>

class BrownNoiseGenerator: public GeneratorBase {
private:
    SoundConfig m_config{};
    static inline float smoothingFactor = 0.9f;
    static inline float leakyIntegratorCoefficient = 0.995f;
public:
    int generateSamples(void *outputBuf, unsigned long frameCount, void* userData) override
    {
        float* out = (float*)outputBuf;

        std::random_device device;
        std::normal_distribution<> dist(0.0f, 1.0f); // Standard deviation for normal distribution
        std::mt19937_64 engine(device());

        float brownNoise = 0.0f;
        for (auto i = 0; i < frameCount; ++i) {
            float randomSample = dist(engine);

            brownNoise += randomSample * 0.02f;  // Adjust gain for smoother transitions
            brownNoise = brownNoise * 0.98f;

            *out++ = brownNoise * m_config.volume;
        }
        return 0;
    }

    void setConfig(SoundConfig &cfg) override {
        m_config = cfg;
    }
};
