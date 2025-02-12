#include <iostream>
#include <memory>
#include <portaudio.h>
#include "../generators/generator_base.hpp"
class SoundPlayer {
private:
    PlayerConfig config;
    std::unique_ptr<GeneratorBase> generator;
    PaStream* stream;

    void init();
    void terminate();
public:
    SoundPlayer(std::unique_ptr<GeneratorBase> generator, const PlayerConfig &config = {});
    ~SoundPlayer();

    void start();
    void stop();

    static int soundCallback(const void *inputBuf, void* outputBuf, unsigned long frameCount, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData);
};
