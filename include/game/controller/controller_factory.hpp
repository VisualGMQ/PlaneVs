#ifndef CONTROLLER_FACTORY_HPP
#define CONTROLLER_FACTORY_HPP
#include <vector>

#include "game/controller/controller.hpp"
#include "game/controller/plane_keyboard_controller_command.hpp"

using std::vector;

class ControllerFactory final {
 public:
    static Controller* CreatePlaneKeyboardController(SDL_Keycode up, SDL_Keycode down, SDL_Keycode left, SDL_Keycode right, SDL_Keycode fire, SDL_Keycode bomb, SDL_Keycode blast) {
        ContAndCommands contstruct = {
            new Controller,
            new PlaneKeyboardCommand_Up(up),

        }
        cont->SetUpCommand()
    }

 private:
    struct ContAndCommands {
        Controller* controller;
        PlaneKeyboardCommand_Up* up;
        PlaneKeyboardCommand_Down* down;
        PlaneKeyboardCommand_Left* left;
        PlaneKeyboardCommand_Right* right;
        PlaneKeyboardCommand_Fire* fire;
        PlaneKeyboardCommand_Bomb* bomb;
        PlaneKeyboardCommand_Blast* blast;
    };
    static vector<ContAndCommands> _cont_structs;
};

#endif

