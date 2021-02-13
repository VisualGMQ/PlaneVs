#include "base/geo_math.hpp"

SDL_Rect IRect2SDL_Rect(irect& irect) {
    return {irect.x, irect.y, irect.w, irect.h};
}

SDL_Color IColor2SDL_Color(icolor& color) {
    SDL_Color sdl_color;
    sdl_color.r = Clamp(0, 255, color.r);
    sdl_color.g = Clamp(0, 255, color.g);
    sdl_color.b = Clamp(0, 255, color.b);
    sdl_color.a = Clamp(0, 255, color.a);
    return sdl_color;
}

SDL_Point IVec2SDL_Point(glm::ivec2& vec) {
    return {vec.x, vec.y};
}

SDL_Rect CenterRect2SDL_Rect(int x, int y, int w, int h) {
    return {x-w/2, y-h/2, w, h};
}

SDL_Rect CenterRect2SDL_Rect(irect& rect) {
    return CenterRect2SDL_Rect(rect.x, rect.y, rect.w, rect.h);
}
