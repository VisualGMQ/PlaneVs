#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP
#include <SDL.h>

#include "game/controller/controller_command.hpp"

class Controller {
 public:
    bool IsWorking() const { return _is_working; }
    void TrunOn() { _is_working = true; }
    void TrunOff() { _is_working = false; }

    void SetUpCommand(ControllerCommand* cmd);
    void SetDownCommand(ControllerCommand* cmd);
    void SetLeftCommand(ControllerCommand* cmd);
    void SetRightCommand(ControllerCommand* cmd);
    void SetFireCommand(ControllerCommand* cmd);
    void SetBombCommand(ControllerCommand* cmd);
    void SetBlastCommand(ControllerCommand* cmd);

    void Control();

    virtual ~Controller() = default;

 private:
    ControllerCommand* _on_up = nullptr;
    ControllerCommand* _on_down = nullptr;
    ControllerCommand* _on_left = nullptr;
    ControllerCommand* _on_right = nullptr;
    ControllerCommand* _on_fire = nullptr;
    ControllerCommand* _on_bomb = nullptr;
    ControllerCommand* _on_blast = nullptr;
    bool _is_working = false;

    void destroyCommand(ControllerCommand* cmd);
};

#endif

