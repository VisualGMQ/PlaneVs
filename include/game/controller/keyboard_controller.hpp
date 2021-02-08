#ifndef KEYBOARD_CONTROLLER_HPP
#define KEYBOARD_CONTROLLER_HPP
#include "engin/input/keyboard.hpp"
#include "game/controller/controller_command.hpp"

class KeyboardCommand_Up: public ControllerCommand {
 public:
    KeyboardCommand_Up(SDL_Keycode key):_key(key) {}
    void Execute(Plane* plane) override {
        if (plane &&
            Keyboard::GetInstance()->Query(_key) == KEY_PRESS) {
            plane->MoveBy(0, -plane->GetSpeed());
        }
    }
    virtual ~KeyboardCommand_Up() = default;

 private:
    SDL_Keycode _key = SDLK_UNKNOWN;
};

class KeyboardCommand_Down: public ControllerCommand {
 public:
    KeyboardCommand_Down(SDL_Keycode key):_key(key) {}
    void Execute(Plane* plane) override {
        if (plane &&
            Keyboard::GetInstance()->Query(_key) == KEY_PRESS) {
            plane->MoveBy(0, plane->GetSpeed());
        }
    }
    virtual ~KeyboardCommand_Down() = default;

 private:
    SDL_Keycode _key = SDLK_UNKNOWN;
};

class KeyboardCommand_Left: public ControllerCommand {
 public:
    KeyboardCommand_Left(SDL_Keycode key):_key(key) {}
    void Execute(Plane* plane) override {
        if (plane &&
            Keyboard::GetInstance()->Query(_key) == KEY_PRESS) {
            plane->MoveBy(-plane->GetSpeed(), 0);
        }
    }
    virtual ~KeyboardCommand_Left() = default;

 private:
    SDL_Keycode _key = SDLK_UNKNOWN;
};

class KeyboardCommand_Right: public ControllerCommand {
 public:
    KeyboardCommand_Right(SDL_Keycode key):_key(key) {}
    void Execute(Plane* plane) override {
        if (plane &&
            Keyboard::GetInstance()->Query(_key) == KEY_PRESS) {
            plane->MoveBy(plane->GetSpeed(), 0);
        }
    }
    virtual ~KeyboardCommand_Right() = default;

 private:
    SDL_Keycode _key = SDLK_UNKNOWN;
};

class KeyboardCommand_Fire: public ControllerCommand {
 public:
    KeyboardCommand_Fire(SDL_Keycode key):_key(key) {}
    void Execute(Plane* plane) override {
        if (plane) {
            int key_status = Keyboard::GetInstance()->Query(_key);
            if (key_status == KEY_PRESS) {
                plane->StartShoot();
            } else if (key_status == KEY_RELEASE){
                plane->StopShoot();
            }
        }
    }
    virtual ~KeyboardCommand_Fire() = default;

 private:
    SDL_Keycode _key = SDLK_UNKNOWN;
};

class KeyboardCommand_Bomb: public ControllerCommand {
 public:
    KeyboardCommand_Bomb(SDL_Keycode key):_key(key) {}
    void Execute(Plane* plane) override {
        if (plane) {
            if (Keyboard::GetInstance()->Query(_key) == KEY_PRESS) {
                //TODO not implement bomb
            }
        }
    }
    virtual ~KeyboardCommand_Bomb() = default;

 private:
    SDL_Keycode _key = SDLK_UNKNOWN;
};

class KeyboardCommand_Blast: public ControllerCommand {
 public:
    KeyboardCommand_Blast(SDL_Keycode key):_key(key) {}
    void Execute(Plane* plane) override {
        if (plane) {
            if (Keyboard::GetInstance()->Query(_key) == KEY_PRESS) {
                //TODO not implement blast
            }
        }
    }
    virtual ~KeyboardCommand_Blast() = default;

 private:
    SDL_Keycode _key = SDLK_UNKNOWN;
};


#endif

