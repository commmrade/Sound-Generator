#include <iostream>
#include <memory>
#include <portaudio.h>
#include "../config/consts.hpp"
#include "../generators/generator_base.hpp"
class SoundPlayer {
private:
    PlayerConfig config;
    std::unique_ptr<GeneratorBase> generator;
    PaStream* stream;

    void init() {
        PaError err = Pa_Initialize();
        if (err != paNoError) {
            throw std::runtime_error("PA could not be initialized");
        }

        err = Pa_OpenDefaultStream(&stream, 0, 1, paFloat32, config.sampleRate, paFramesPerBufferUnspecified, &SoundPlayer::soundCallback, this);
        if (err != paNoError) {
            throw std::runtime_error("Could not open default stream");
        }
    }

    void terminate() {
        PaError err = Pa_Terminate();
        if (err != paNoError) {
            throw std::runtime_error("Could not terminate PA");
        }
    }
public:
    SoundPlayer(std::unique_ptr<GeneratorBase> generator, const PlayerConfig &config = {}) : generator(std::move(generator)), config(config) {
        init();
    }
    ~SoundPlayer() {
        terminate();
    }

    void start() {
        PaError err = Pa_StartStream(stream);
        if (err != paNoError) {
            throw std::runtime_error("Could not start stream");
        }
    }
    void stop() {
        PaError err = Pa_StopStream(stream);
        if (err != paNoError) {
            std::cerr << Pa_GetErrorText(err);
            throw std::runtime_error("Could not stop stream");
        }
    }



    static int soundCallback(const void *inputBuf, void* outputBuf, unsigned long frameCount, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData) {
        return ((SoundPlayer*)userData)->generator->generateSamples(outputBuf, frameCount, nullptr);
    }
};
