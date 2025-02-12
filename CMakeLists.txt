cmake_minimum_required(VERSION 3.15)
project(proj VERSION 1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

find_library(PORTAUDIO_LIBRARY NAMES portaudio)
include_directories(/usr/local/include)

# Add executable
add_executable(proj src/main.cpp src/core/soundplayer.cpp src/config/arguments.cpp)

# Link PortAudio library to the project
target_link_libraries(proj /usr/local/lib/libportaudio.so)
