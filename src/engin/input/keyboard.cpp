#include "engin/input/keyboard.hpp"

Keyboard* Keyboard::_instance = nullptr;

Keyboard* Keyboard::GetInstance() {
    if (!_instance)
        _instance = new Keyboard;
    return _instance;
}

void Keyboard::Destroy() {
    delete _instance;
}

void Keyboard::ReceiveEvent(SDL_Event& event) {
    SDL_Keycode key = event.key.keysym.sym;
    if (event.type == SDL_KEYDOWN) {
        _status[key] = KEY_PRESS;
    }
    if (event.type == SDL_KEYUP) {
        _status[key] = KEY_RELEASE;
    }
}

KeyStatus Keyboard::Query(SDL_Keycode sym) const {
    if (_status.find(sym) == _status.end())
        return KEY_RELEASE;
    return _status.at(sym);
}

