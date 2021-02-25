#include "base/geo_math.hpp"

SDL_Rect IRect2SDL_Rect(const irect& irect) {
    return {irect.x, irect.y, irect.w, irect.h};
}

SDL_Color IColor2SDL_Color(const icolor& color) {
    return {Clamp<Uint8>(0, 255, color.r),
            Clamp<Uint8>(0, 255, color.g),
            Clamp<Uint8>(0, 255, color.b),
            Clamp<Uint8>(0, 255, color.a)};
}

SDL_Point IVec2SDL_Point(const glm::ivec2& vec) {
    return {vec.x, vec.y};
}

SDL_Rect CenterRect2SDL_Rect(int x, int y, int w, int h) {
    return {x-w/2, y-h/2, w, h};
}

SDL_Rect CenterRect2SDL_Rect(const irect& rect) {
    return CenterRect2SDL_Rect(rect.x, rect.y, rect.w, rect.h);
}
