#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP
#include <SDL.h>

struct ControllerButtonMap {
    SDL_Keycode up = SDLK_UNKNOWN;
    SDL_Keycode down = SDLK_UNKNOWN;
    SDL_Keycode left = SDLK_UNKNOWN;
    SDL_Keycode right = SDLK_UNKNOWN;
    SDL_Keycode shoot = SDLK_UNKNOWN;
    SDL_Keycode bomb = SDLK_UNKNOWN;
    SDL_Keycode blast = SDLK_UNKNOWN;
    SDL_Keycode esc = SDLK_UNKNOWN;
};

class Controller {
 public:
    bool IsWorking() const { return _is_working; }
    void TrunOn() { _is_working = true; }
    void TrunOff() { _is_working = false; }

    virtual void OnLeft() = 0;
    virtual void OnRight()  = 0;
    virtual void OnUp() = 0;
    virtual void OnDown() = 0;
    virtual void OnShoot() = 0;
    virtual void OnBomb() = 0;
    virtual void OnBlast() = 0;
    virtual void OnEsc() = 0;

    void Update() {
        if (IsWorking()) {
            OnRight();
            OnUp();
            OnDown();
            OnLeft();
            OnShoot();
            OnBomb();
            OnBlast();
            OnEsc();
        }
    }

    const ControllerButtonMap& GetButtonMap() const { return _map; }
    void SetButtonMap(ControllerButtonMap button_map) { _map = button_map; }

    virtual ~Controller() = default;

 private:
    ControllerButtonMap _map;
    bool _is_working = false;
};

#endif

