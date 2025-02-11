#pragma once
#include <args.hpp>
#include "types.hpp"




class ArgumentParser {
public:
    static GeneralConfig parseArgs(int argc, char** argv) {
        args::ArgumentParser parser("Sound generator");
        args::HelpFlag help(parser, "help", "Display the help menu", {'h', "help"});
        args::ValueFlag<std::string> type(parser, "sound", "Type of the sound you wanna play", {'t', "type"}, "white_noise");
        args::ValueFlag<float> volume(parser, "volume", "Volume of the sound", {'v', "volume"}, 0.5f);
        args::ValueFlag<int> playTime(parser, "playtime", "Number of seconds it shall play", {"pt", "play-time"}, 600);
        args::ValueFlag<int> sampleRate(parser, "sampleRate", "Sample Rate", {"sr", "sample-rate"}, 44100);
        // Todo parse more args
        try {
            parser.ParseCLI(argc, argv);
        } catch (args::Help) {
            std::cout << parser;
        } catch (...) {
            std::cerr << "Some error\n";
        }

        GeneralConfig configGeneral;
        configGeneral.volume = args::get(volume);

        std::string value = args::get(type);
        SoundTypes typeS = toSoundType(value);
        configGeneral.type = typeS;

        configGeneral.playTime = args::get(playTime);

        configGeneral.sampleRate = args::get(sampleRate);

        return configGeneral;
    }
};
