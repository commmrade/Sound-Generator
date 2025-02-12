#include "generator_base.hpp"
#include <cstdlib>
#include <random>



class WhiteNoiseGenerator: public GeneratorBase {
private:
    SoundConfig m_config{};

    std::random_device device;
    std::normal_distribution<> dist{-.2f, 0.4f};
public:
    WhiteNoiseGenerator() = default;
    ~WhiteNoiseGenerator() = default;

    float generateSamples() override
    {
        auto val = dist(device);
        return val * m_config.volume;
    }
    void setConfig(const SoundConfig &cfg) override {
        m_config = cfg;
    }
};
