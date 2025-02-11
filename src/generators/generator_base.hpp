#pragma once

#include <portaudio.h>
#include "../config/types.hpp"


class GeneratorBase {
public:
    virtual int generateSamples(void *outputBuf, unsigned long frameCount, void* userData) = 0;
    virtual void setConfig(SoundConfig &cfg) = 0;

    virtual ~GeneratorBase() = default;
};
