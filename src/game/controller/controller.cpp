#include "game/controller/controller.hpp"

#define SetXXCommandImplement(var, param) \
    if (var) \
        destroyCommand(var); \
    var = param;


void Controller::SetUpCommand(ControllerCommand* cmd) {
    SetXXCommandImplement(_on_up, cmd)
}

void Controller::SetDownCommand(ControllerCommand* cmd) {
    SetXXCommandImplement(_on_down, cmd)

}

void Controller::SetLeftCommand(ControllerCommand* cmd) {
    SetXXCommandImplement(_on_left, cmd)
}

void Controller::SetRightCommand(ControllerCommand* cmd) {
    SetXXCommandImplement(_on_right, cmd)
}

void Controller::SetFireCommand(ControllerCommand* cmd) {
    SetXXCommandImplement(_on_fire, cmd)
}

void Controller::SetBombCommand(ControllerCommand* cmd) {
    SetXXCommandImplement(_on_bomb, cmd)
}

void Controller::SetBlastCommand(ControllerCommand* cmd) {
    SetXXCommandImplement(_on_blast, cmd)
}

#undef SetXXCommandImplement

void Controller::Control() {
    if (!IsWorking())
        return;
    if (_on_up)
        _on_up->Execute();
    if (_on_down)
        _on_down->Execute();
    if (_on_left)
        _on_left->Execute();
    if (_on_right)
        _on_right->Execute();
    if (_on_fire)
        _on_fire->Execute();
    if (_on_bomb)
        _on_bomb->Execute();
    if (_on_blast)
        _on_blast->Execute();
}
