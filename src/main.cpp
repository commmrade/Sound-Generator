#include <iostream>
#include "config/arguments.hpp"
#include <memory>
#include <portaudio.h>
#include <stdexcept>
#include <thread>
#include <cmath>
#include "config/types.hpp"
#include "core/soundplayer.hpp"
#include "generators/binaural_beats.hpp"
#include "generators/generator_base.hpp"
#include "generators/white_noise.hpp"
#include "generators/brown_noise.hpp"
#include "portaudio.h"

int main(int argc, char** argv) {
    GeneralConfig config;
    try {
        config = ArgumentParser::parseArgs(argc, argv);
    } catch (...) {
        return 1;
    }

    std::unique_ptr<GeneratorBase> gen;
    switch (config.type) {
        case SoundTypes::BROWN_NOISE: {
            gen = std::make_unique<BrownNoiseGenerator>();
            break;
        }
        case SoundTypes::BINAURAL: {
            gen = std::make_unique<BinauralBeatsGenerator>();
            // config.channels = 2;
            break;
        }
        case SoundTypes::WHITE_NOISE: {
        }
        default: {
            gen = std::make_unique<WhiteNoiseGenerator>();
            break;
        }
    }

    SoundConfig soundCfg;
    soundCfg.volume = config.volume;
    gen->setConfig(soundCfg);
    std::cout << soundCfg.volume << std::endl;

    PlayerConfig playerCfg;
    playerCfg.sampleRate = config.sampleRate;


    SoundPlayer player(std::move(gen), playerCfg);
    player.start();
    Pa_Sleep(1000 * config.playTime);
    player.stop();
    return 0;
}
