#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP
#include <map>

#include "engin/input/device.hpp"
using std::map;

enum KeyStatus {
    KEY_RELEASE = 0,
    KEY_PRESS = 1
};

class Keyboard final: public Device {
 public:
    static Keyboard* GetInstance();

    void ReceiveEvent(SDL_Event& event) override;
    KeyStatus Query(SDL_Keycode sym) const;

 private:
    static Keyboard _instance;

    map<SDL_Keycode, KeyStatus> _status;

    Keyboard() = default;
};

#endif

