#pragma once
#include <args.hpp>
#include "types.hpp"




class ArgumentParser {
public:
    static GeneralConfig parseArgs(int argc, char** argv);
};
