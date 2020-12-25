#ifndef HEADER_HPP
#define HEADER_HPP
#include <string>
#include <cassert>
#include "SDL.h"
using std::string;

struct Color{
    float r;
    float g;
    float b;
    float a;
};

struct Size{
    int w;
    int h;
};

inline void Log(string msg) {
    SDL_Log("%s", msg.c_str());
}

inline void Assertm(string msg, bool condition) {
    if (!condition) {
        Log("[Assert]:" + msg);
        assert(false);
    }
}

#endif

