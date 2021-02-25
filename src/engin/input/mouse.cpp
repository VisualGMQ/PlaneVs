#include "engin/input/mouse.hpp"

using input::Mouse;
using input::Button;
using input::ButtonState;

Mouse Mouse::_instance;

Mouse* Mouse::GetInstance() {
    return &_instance;
}

void Mouse::ReceiveEvent(SDL_Event& event) {
    if (event.type == SDL_MOUSEMOTION) {
        _motion.x = event.motion.xrel;
        _motion.y = event.motion.yrel;
        _position.x = event.motion.x;
        _position.y = event.motion.y;
    }
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            _lbutton_state = BUTTON_PRESSED;
        } else if (event.button.button == SDL_BUTTON_RIGHT) {
            _rbutton_state = BUTTON_PRESSED;
        }
    }
    if (event.type == SDL_MOUSEBUTTONUP) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            _lbutton_state = BUTTON_RELEASED;
        } else if (event.button.button == SDL_BUTTON_RIGHT) {
            _rbutton_state = BUTTON_RELEASED;
        }
    }
}

void Mouse::Update() {
    if (_lbutton_state == BUTTON_RELEASED) {
        _lbutton_state = BUTTON_RELEASING;
    } else if (_lbutton_state == BUTTON_PRESSED) {
        _lbutton_state = BUTTON_PRESSING;
    }
    if (_rbutton_state == BUTTON_RELEASED) {
        _rbutton_state = BUTTON_RELEASING;
    } else if (_rbutton_state == BUTTON_PRESSED) {
        _rbutton_state = BUTTON_PRESSING;
    }
}

Button Mouse::GetLeftButtonState() {
    return Button(_lbutton_state);
}

Button Mouse::GetRightButtonState() {
    return Button(_rbutton_state);
}
