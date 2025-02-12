#include "soundplayer.hpp"
#include <exception>

SoundPlayer::SoundPlayer(std::unique_ptr<GeneratorBase> generator, const PlayerConfig &config /* = {} */) : generator(std::move(generator)), config(config) {
    init();
}
SoundPlayer::~SoundPlayer() {
    try {
        terminate();
    } catch (...) {
        std::cerr << "Could not terminate PA\n";
    }
}

void SoundPlayer::init() {
    PaError err = Pa_Initialize();
    if (err != paNoError) {
        throw std::runtime_error("PA could not be initialized");
    }

    err = Pa_OpenDefaultStream(&stream, 0, 2, paFloat32, config.sampleRate, paFramesPerBufferUnspecified, &SoundPlayer::soundCallback, this);
    if (err != paNoError) {
        throw std::runtime_error("Could not open default stream");
    }
}

void SoundPlayer::terminate() {
    PaError err = Pa_Terminate();
    if (err != paNoError) {
        throw std::runtime_error("Could not terminate PA");
    }
}


void SoundPlayer::start() {
    PaError err = Pa_StartStream(stream);
    if (err != paNoError) {
        throw std::runtime_error("Could not start stream");
    }
}
void SoundPlayer::stop() {
    PaError err = Pa_StopStream(stream);
    if (err != paNoError) {
        std::cerr << Pa_GetErrorText(err);
        throw std::runtime_error("Could not stop stream");
    }
}

int SoundPlayer::soundCallback(const void *inputBuf, void* outputBuf, unsigned long frameCount, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData) {
    auto* soundPlayer =  static_cast<SoundPlayer*>(userData);
    float* out = static_cast<float*>(outputBuf);
    return soundPlayer->generator->sampleCallback(outputBuf, frameCount);
}
