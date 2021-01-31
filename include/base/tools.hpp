#ifndef TOOLS_HPP
#define TOOLS_HPP
#include <string>
#include <filesystem>
using std::string;
namespace fs = std::filesystem;

template <typename T>
T Clamp(T a, T b, T value) {
    if (value > b)
        return b;
    else if (value < a)
        return a;
    return value;
}

inline string Filename2Name(string filename) {
    return fs::path(filename).filename().string().substr(0, filename.rfind('.'));
}

#endif

