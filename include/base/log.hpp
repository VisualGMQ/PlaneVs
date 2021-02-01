#ifndef LOG_HPP
#define LOG_HPP
#include <string>
#include <cassert>
#include <cstdio>

#include <SDL.h>
using std::string;
using std::printf;

inline void Log(const char* format, ...) {
    va_list l;
    va_start(l, format);
    SDL_Log(format, l);
    va_end(l);
}

inline void Assertm(string msg, bool condition) {
    if (!condition) {
        printf("[Assert]: %s", msg.c_str());
        fflush(stdout);
        assert(false);
    }
}
#endif

