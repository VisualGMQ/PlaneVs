#include "game/controller/controller.hpp"

void Controller::Control() {
    if (IsWorking()) {
        Up();
        Down();
        Left();
        Right();
        Fire();
        Bomb();
        Blast();
    }
}
