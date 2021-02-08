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

void Controller::destroyCommand(ControllerCommand* cmd) {
    delete cmd;
}

void Controller::Control(Plane* plane) {
    if (!IsWorking())
        return;
    if (_on_up)
        _on_up->Execute(plane);
    if (_on_down)
        _on_down->Execute(plane);
    if (_on_left)
        _on_left->Execute(plane);
    if (_on_right)
        _on_right->Execute(plane);
    if (_on_fire)
        _on_fire->Execute(plane);
    if (_on_bomb)
        _on_bomb->Execute(plane);
    if (_on_blast)
        _on_blast->Execute(plane);
}

#define DeleteControllerCommand(cmd) if (cmd) destroyCommand(cmd);
        
Controller::~Controller() {
    DeleteControllerCommand(_on_up)
    DeleteControllerCommand(_on_down)
    DeleteControllerCommand(_on_left)
    DeleteControllerCommand(_on_right)
    DeleteControllerCommand(_on_fire)
    DeleteControllerCommand(_on_bomb)
    DeleteControllerCommand(_on_blast)
}

#undef DeleteControllerCommand
