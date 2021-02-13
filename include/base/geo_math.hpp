#ifndef GEO_MATH_HPP
#define GEO_MATH_HPP
#include <glm/glm.hpp>

#include <SDL.h>

#include "base/tools.hpp"

/*
 * @param x     center x in rect
 * @param y     center y in rect
 * @param w     width in rect
 * @param h     height in rect
 */
template <typename T>
struct rect_base {
    T x = T();
    T y = T();
    T w = T();
    T h = T();
};
using irect= rect_base<int>;
using frect = rect_base<float>;
using drect = rect_base<double>;

template <typename T>
inline bool IsRectValid(const rect_base<T>& rect) {
    return rect.w > 0 && rect.h > 0;
}

template <typename T>
struct size_base {
    T w = T();
    T h = T();
};
using isize = size_base<int>;
using size = size_base<float>;

template <typename T>
struct color_base {
    union { T r; T h; };
    union { T g; T s; };
    union { T b; T v; };
    T a;
};
using icolor = color_base<int>;
using color = color_base<float>;

template <typename T>
struct scale_base {
    T x;
    T y;
};
using scale = scale_base<float>;

SDL_Rect IRect2SDL_Rect(irect& irect);
SDL_Color IColor2SDL_Color(icolor& color);
SDL_Point IVec2SDL_Point(glm::ivec2& vec);
SDL_Rect CenterRect2SDL_Rect(int x, int y, int w, int h);
SDL_Rect CenterRect2SDL_Rect(irect& rect);

#endif
