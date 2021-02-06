#ifndef MOVABLE_HPP
#define MOVABLE_HPP
#include <glm/glm.hpp>
using glm::ivec2;

class Movable {
 public:
    virtual void MoveBy(int offset_x, int offset_y) { _position.x += offset_x; _position.y += offset_y; }
    virtual void MoveBy(ivec2 offset) { MoveBy(offset.x, offset.y); }
    virtual void MoveTo(int x, int y) { _position.x = x, _position.y = y; }
    virtual void MoveTo(ivec2 pos) { MoveTo(pos.x, pos.y); }
    virtual ivec2 GetPosition() const { return _position; }
    ~Movable() = default;

 private:
    ivec2 _position;
};

#endif

