#include "engin/input/keyboard.hpp"
using input::Keyboard;
using input::Button;

Keyboard Keyboard::_instance;

Keyboard* Keyboard::GetInstance() {
    return &_instance;
}

void Keyboard::ReceiveEvent(SDL_Event& event) {
    SDL_Keycode key = event.key.keysym.sym;
    if (_states.find(key) == _states.end()) {
        _states[key] = BUTTON_RELEASING;
    }
    if (event.type == SDL_KEYDOWN) {
        _states[key] = input::UpdateButtonState(true, _states[key]);
    }
    if (event.type == SDL_KEYUP) {
        _states[key] = input::UpdateButtonState(false, _states[key]);
    }
}

void Keyboard::Update() {
    for (auto& [key, value] : _states) {
        if (value == input::BUTTON_PRESSED) {
            value = input::BUTTON_PRESSING;
        } else if (value == input::BUTTON_RELEASED) {
            value = input::BUTTON_RELEASING;
        }
    }
}

Button Keyboard::Query(SDL_Keycode sym) const {
    if (_states.find(sym) == _states.end())
        return Button(BUTTON_RELEASING);
    return Button(_states.at(sym));
}

