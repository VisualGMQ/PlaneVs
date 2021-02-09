#include "base/geo_math.hpp"

void IRect2SDL_Rect(irect& irect, SDL_Rect& sdl_rect) {
    sdl_rect.x = irect.x;
    sdl_rect.y = irect.y;
    sdl_rect.w = irect.w;
    sdl_rect.h = irect.h;
}

void IColor2SDL_Color(icolor& color, SDL_Color& sdl_color) {
    sdl_color.r = color.r;
    sdl_color.g = color.g;
    sdl_color.b = color.b;
    sdl_color.a = color.a;
}

void IVec22SDL_Point(glm::ivec2& vec, SDL_Point& point) {
    point.x = vec.x;
    point.y = vec.y;
}
