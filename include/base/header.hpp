#ifndef HEADER_HPP
#define HEADER_HPP
#include <string>
#include <cassert>

#include <SDL.h>
using std::string;

struct Color {
    float r;
    float g;
    float b;
    float a;
};

struct Size {
    float w;
    float h;
};

inline void Log(const char* format, ...) {
    va_list l;
    va_start(l, format);
    SDL_Log(format, l);
    va_end(l);
}

inline void Assertm(string msg, bool condition) {
    if (!condition) {
        Log("[Assert]: %s", msg.c_str());
        assert(false);
    }
}

using IdType = unsigned int;
constexpr IdType SystemGfxBufId = 0;

inline IdType GenerateId() {
    static long long _cur_id = SystemGfxBufId;
    return _cur_id++;
}

#endif

