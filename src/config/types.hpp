#pragma once

#include <string_view>
enum class SoundTypes {
    PINK_NOISE,
    WHITE_NOISE,
    BROWN_NOISE,
    WAVES,
};
inline SoundTypes toSoundType(const std::string_view typeStr) {
    if (typeStr == "pink_noise") {
        return SoundTypes::PINK_NOISE;
    } else if (typeStr == "white_noise") {
        return SoundTypes::WHITE_NOISE;
    } else if (typeStr == "brown_noise") {
        return SoundTypes::BROWN_NOISE;
    } else {
        return SoundTypes::WAVES;
    }
}

struct GeneralConfig {
    float volume;
    int playTime;
    SoundTypes type;
    int sampleRate;
};
struct SoundConfig {
    float volume{0.1};
};
struct PlayerConfig {
    int sampleRate{44100};
};
