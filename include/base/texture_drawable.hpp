#ifndef TEXTURE_DRAWABLE_HPP
#define TEXTURE_DRAWABLE_HPP
#include <glm/glm.hpp>

#include "base/geo_math.hpp"
#include "base/flip.hpp"

class TextureDrawable {
 public:
    virtual void Draw(SDL_Renderer*, irect* src_rect, irect* dst_rect, icolor* tex_color) const = 0;
    virtual void Draw(SDL_Renderer*, irect* src_rect, irect* dst_rect, float degree, FlipEnum flip, icolor* tex_color) const = 0;
    virtual ~TextureDrawable() = default;
};

#endif

