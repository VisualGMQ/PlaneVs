#ifndef FLIPABLE_HPP
#define FLIPABLE_HPP
#include "base/flip.hpp"

class Flipable {
 public:
    virtual void Flip(FlipEnum flip);
    virtual void SetFlip(FlipEnum flip) { _flip = flip; }
    virtual FlipEnum GetFlip() { return _flip; }

 private:
    FlipEnum _flip = FLIP_NONE;
};

#endif

