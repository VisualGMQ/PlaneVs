#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP
#include <glm/glm.hpp>

#include "base/geomentry.hpp"

enum FlipEnum {
    FLIP_NONE,
    FLIP_HORIZENTAL,
    FLIP_VERTICAL,
    FLIP_BOTH
};

class TextureDrawable {
 public:
    virtual void Draw(irect* src_rect, irect* dst_rect, color* tex_color, color* key_color) const = 0;
    virtual void Draw(irect* src_rect, irect* dst_rect, float degree, FlipEnum flip, color* tex_color, color* key_color) const = 0;
};

#endif

