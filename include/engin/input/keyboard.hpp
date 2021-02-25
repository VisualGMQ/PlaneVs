#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP
#include <map>

#include "engin/input/device.hpp"
#include "engin/input/button.hpp"
using std::map;

namespace input {

class Keyboard final: public Device {
 public:
    static Keyboard* GetInstance();

    void ReceiveEvent(SDL_Event& event) override;
    Button Query(SDL_Keycode sym) const;
    void Update();

 private:
    static Keyboard _instance;

    map<SDL_Keycode, input::ButtonState> _states;

    Keyboard() = default;
};

}   // namespace input

#endif

