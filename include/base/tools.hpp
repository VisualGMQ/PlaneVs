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

/*
 * @brief return the length of coverage of [a1, b1] and [a2, b2]
 */
template <typename T>
T GetCoverLen(T a1, T b1, T a2, T b2) {
    if (a1 >= b2 || b1 <= a2)
        return 0;
    if (b1 > a2) {
        if (b1 <= b2) {
            return b1 - a2;
        } else {
            return b2 - a2;
        }
    } else if (b2 > a1) {
        if (b2 <= b1) {
            return b2 - a1;
        } else {
            return b1 - a1;
        }
    }
    return 0;
}

#endif

