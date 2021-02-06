#ifndef KEYBOARD_CONTROLLER_HPP
#define KEYBOARD_CONTROLLER_HPP
#include <forward_list>

#include "engin/input/input.hpp"
#include "engin/controller.hpp"
#include "game/plane.hpp"
using std::forward_list;

class KeyboardController: public Controller {
 public:
    static KeyboardController* Create(Plane* plane, ControllerButtonMap key_map);

    KeyboardController(Plane* plane, ControllerButtonMap button_map):_plane(plane) {
        SetButtonMap(button_map);
    }

    void OnLeft() override;
    void OnRight() override;
    void OnUp() override;
    void OnDown() override;
    void OnShoot() override;
    void OnBomb() override {}
    void OnBlast() override {}
    void OnEsc() override {}

    virtual ~KeyboardController() = default;

 private:
    Plane* _plane = nullptr;

    static forward_list<KeyboardController> _instances;
};

#endif

