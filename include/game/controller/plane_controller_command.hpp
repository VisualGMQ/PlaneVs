#ifndef PLANE_CONTROLLER_COMMAND_HPP
#define PLANE_CONTROLLER_COMMAND_HPP
#include "engin/input/keyboard.hpp"
#include "game/controller/controller_command.hpp"

class PlaneControllerCommand: public ControllerCommand {
 public:
    void Execute() override {
        if (_plane) {
            execute(_key, _plane);
        }
    }
    SDL_Keycode GetKey() { return _key; }
    void SetPlane(Plane* plane) {
        _plane = plane;
    }
    virtual ~PlaneControllerCommand() = default;

 protected:
    virtual bool isTrigged() = 0;   /* if return true, the command will be execute */
    virtual void execute(SDL_Keycode, Plane*) = 0;

 private:
    SDL_Keycode _key = SDLK_UNKNOWN;
    Plane* _plane = nullptr;
};

#endif
