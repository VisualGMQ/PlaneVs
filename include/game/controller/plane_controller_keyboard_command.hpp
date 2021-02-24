#ifndef PLANE_CONTROLLER_KEYBOARD_COMMAND_HPP
#define PLANE_CONTROLLER_KEYBOARD_COMMAND_HPP
#include "game/controller/plane_controller_command.hpp"

class PlaneControllerCommand_Up final: public PlaneControllerCommand{
 protected:
    void execute(SDL_Keycode key, Plane* plane) override {
        if (Keyboard::GetInstance()->Query(key) == KEY_PRESS) {
            plane->MoveBy(0, -plane->GetSpeed());
        }
    }
    virtual ~PlaneControllerCommand_Up() = default;
};

class PlaneControllerCommand_Down final: public PlaneControllerCommand {
 public:
    void execute(SDL_Keycode key, Plane* plane) override {
        if (Keyboard::GetInstance()->Query(key) == KEY_PRESS) {
            plane->MoveBy(0, plane->GetSpeed());
        }
    }
    virtual ~PlaneControllerCommand_Down() = default;
};

class PlaneControllerCommand_Left: public PlaneControllerCommand {
 public:
    void execute(SDL_Keycode key, Plane* plane) override {
        if (Keyboard::GetInstance()->Query(key) == KEY_PRESS) {
            plane->MoveBy(-plane->GetSpeed(), 0);
        }
    }
    virtual ~PlaneControllerCommand_Left() = default;
};

class PlaneControllerCommand_Right: public PlaneControllerCommand {
 public:
    void execute(SDL_Keycode key, Plane* plane) override {
        if (Keyboard::GetInstance()->Query(key) == KEY_PRESS) {
            plane->MoveBy(plane->GetSpeed(), 0);
        }
    }
    virtual ~PlaneControllerCommand_Right() = default;
};

class PlaneControllerCommand_Fire: public PlaneControllerCommand {
 public:
    void execute(SDL_Keycode key, Plane* plane) override {
        int key_status = Keyboard::GetInstance()->Query(key);
        if (key_status == KEY_PRESS) {
            plane->StartShoot();
        } else if (key_status == KEY_RELEASE) {
            plane->StopShoot();
        }
    }
    virtual ~PlaneControllerCommand_Fire() = default;
};

class PlaneControllerCommand_Bomb: public PlaneControllerCommand {
 public:
    void execute(SDL_Keycode key, Plane* plane) override {
        if (Keyboard::GetInstance()->Query(key) == KEY_PRESS) {
            // TODO not implement bomb
        }
    }
    virtual ~PlaneControllerCommand_Bomb() = default;
};

class PlaneControllerCommand_Blast: public PlaneControllerCommand {
 public:
    void execute(SDL_Keycode key, Plane* plane) override {
        if (Keyboard::GetInstance()->Query(key) == KEY_PRESS) {
            // TODO not implement blast
        }
    }
    virtual ~PlaneControllerCommand_Blast() = default;
};

#endif
