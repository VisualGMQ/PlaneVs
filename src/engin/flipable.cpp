#include "engin/flipable.hpp"

void Flipable::Flip(FlipEnum flip) {
    if (GetFlip() == FLIP_NONE) {
        SetFlip(flip);
    } else if (GetFlip() == FLIP_VERTICAL) {
        if (flip == FLIP_VERTICAL)
            SetFlip(FLIP_NONE);
        else if (flip == FLIP_HORIZENTAL)
            SetFlip(FLIP_BOTH);
        else if (flip == FLIP_BOTH)
            SetFlip(FLIP_HORIZENTAL);
    } else if (GetFlip() == FLIP_HORIZENTAL) {
        if (flip == FLIP_VERTICAL)
            SetFlip(FLIP_BOTH);
        else if (flip == FLIP_HORIZENTAL)
            SetFlip(FLIP_NONE);
        else if (flip == FLIP_BOTH)
            SetFlip(FLIP_VERTICAL);
    } else if (GetFlip() == FLIP_BOTH) {
        if (flip == FLIP_VERTICAL)
            SetFlip(FLIP_HORIZENTAL);
        else if (flip == FLIP_HORIZENTAL)
            SetFlip(FLIP_VERTICAL);
        else if (flip == FLIP_BOTH)
            SetFlip(FLIP_NONE);
    }
}

