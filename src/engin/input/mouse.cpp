#include "engin/input/mouse.hpp"

Mouse* Mouse::_instance = nullptr;

Mouse* Mouse::GetInstance() {
    if (!_instance)
        _instance = new Mouse;
    return _instance;
}

void Mouse::Destroy() {
    delete _instance;
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
            _lbutton_status = MOUSE_BUTTON_PRESS;
        } else if (event.button.button == SDL_BUTTON_RIGHT) {
            _rbutton_status = MOUSE_BUTTON_PRESS;
        }
    }
    if (event.type == SDL_MOUSEBUTTONUP) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            _lbutton_status = MOUSE_BUTTON_RELEASE;
        } else if (event.button.button == SDL_BUTTON_RIGHT) {
            _rbutton_status = MOUSE_BUTTON_RELEASE;
        }
    }
}

MouseButtonStatue Mouse::GetButtonStatue(Uint8 button) {
    if (button == SDL_BUTTON_LEFT)
        return _lbutton_status;
    if (button == SDL_BUTTON_RIGHT)
        return _rbutton_status;
    return MOUSE_BUTTON_RELEASE;
}
