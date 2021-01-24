#ifndef LOG_HPP
#define LOG_HPP
#include <string>
#include <cassert>
#include <SDL.h>
using std::string;

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
#endif

