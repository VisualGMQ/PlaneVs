#ifndef COLLIDE_HPP
#define COLLIDE_HPP
#include <glm/glm.hpp>

#include "base/geo_math.hpp"
#include "base/tools.hpp"
using glm::vec2;

template <typename T>
bool CollideRects(rect_base<T>& rect1, rect_base<T>& rect2) {
    if ((rect1.w <= 0 && rect1.h <= 0) ||
        (rect2.w <= 0 && rect2.h <= 0))
        return false;
    return !(rect1.x+rect1.w < rect2.x ||
             rect1.y+rect1.h < rect2.y ||
             rect1.x > rect2.x+rect2.w ||
             rect1.y > rect2.y+rect2.h);
}

template <typename T>
T SatRects(rect_base<T>& rect1, rect_base<T>& rect2) {
    T depth = 0;
    T depth_x = GetCoverLen(rect1.x, rect1.x + rect1.w, rect2.x, rect2.x + rect2.w),
      depth_y = GetCoverLen(rect1.y, rect1.y + rect1.h, rect2.y, rect2.y + rect2.h);
    if (depth_x < depth_y)
        return depth_x;
    else
        return depth_y;
};

#endif
