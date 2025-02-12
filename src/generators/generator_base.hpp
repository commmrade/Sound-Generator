#pragma once

#include <portaudio.h>
#include "../config/types.hpp"


class GeneratorBase {
public:
    virtual float generateSamples() = 0;
    virtual void setConfig(const SoundConfig &cfg) = 0;

    virtual ~GeneratorBase() = default;
};
