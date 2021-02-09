#ifndef RESIZABLE_HPP
#define RESIZABLE_HPP
#include "base/geo_math.hpp"

class Resizable {
 public:
    virtual void ResizeTo(int w, int h) { _size.w = w; _size.h = h; }
    virtual void ResizeTo(isize size) { ResizeTo(size.w, size.h); }
    virtual void ResizeBy(int offset_w, int offset_h) { _size.w += offset_w; _size.h += offset_h; }
    virtual void ResizeBy(irect offset) { ResizeBy(offset.w, offset.h); }
    virtual isize GetSize() const { return _size; }
    ~Resizable() = default;

 private:
    isize _size;
};

#endif

