#ifndef CONFIG_HPP
#define CONFIG_HPP

#ifdef _MSC_VER
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "SDL2_ttf.lib")
#pragma comment(lib, "SDL2_mixer.lib")
#endif

#include <SDL.h>

#include "base/geo_math.hpp"

constexpr isize WindowInitSize = {1024, 720};
constexpr isize CanvaSize = {1024, 720};
constexpr int FPS = 120;
constexpr icolor CanvaBgColor = {200, 200, 200, 255};

#endif

