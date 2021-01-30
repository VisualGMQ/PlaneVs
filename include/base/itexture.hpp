#ifndef ITEXTURE_HPP
#define ITEXTURE_HPP
#include "base/texture_drawable.hpp"

class ITexture: public TextureDrawable {
 public:
    virtual isize GetSize() const = 0;
    virtual ~ITexture() = default;
};

#endif

