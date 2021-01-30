#ifndef OBJECT_HPP
#define OBJECT_HPP
#include "base/flip.hpp"
#include "base/geomentry.hpp"

#include <glm/glm.hpp>
using glm::ivec2;

class Object {
 public:
    void MoveBy(int offset_x, int offset_y) { _position.x += offset_x; _position.y += offset_y; }
    void MoveBy(ivec2 offset) { MoveBy(offset.x, offset.y); }
    void MoveTo(int x, int y) { _position.x = x, _position.y = y; }
    void MoveTo(ivec2 pos) { MoveTo(pos.x, pos.y); }
    ivec2 GetPosition() const { return _position; }

    void ResizeTo(int w, int h) { _size.w = w; _size.h = h; }
    void ResizeTo(isize size) { ResizeTo(size.w, size.h); }
    void ResizeBy(int offset_w, int offset_h) { _size.w += offset_w; _size.h += offset_h; }
    void ResizeBy(irect offset) { ResizeBy(offset.w, offset.h); }
    isize GetSize() const { return _size; }

    void RotateTo(float degree) { _degree = degree; }
    void RotateBy(float delta) { _degree += delta; }
    float GetRotation() const { return _degree; }
    virtual ~Object() = default;

 private:
    glm::ivec2 _position;
    float _degree = 0;
    isize _size;
};

#endif

