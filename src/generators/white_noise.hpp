#include "generator_base.hpp"
#include <cstdlib>
#include <random>
#include "../config/consts.hpp"


class WhiteNoiseGenerator: public GeneratorBase {
private:
    SoundConfig m_config{};
public:
    int generateSamples(void *outputBuf, unsigned long frameCount, void* userData) override
    {
        float* out = (float*)outputBuf;

        std::random_device device;
        std::normal_distribution<> dist(-.2f, 0.4f);

        for (auto i = 0; i < frameCount; ++i) {
            auto val = dist(device);
            *out++ = val * m_config.volume;
        }

        return 0;
    }
    void setConfig(SoundConfig &cfg) override {
        m_config = cfg;
    }
};
