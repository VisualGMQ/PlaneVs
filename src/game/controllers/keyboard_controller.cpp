#include "game/controller/keyboard_controller.hpp"

forward_list<KeyboardController> KeyboardController::_instances;

KeyboardController* KeyboardController::Create(Plane* plane, ControllerButtonMap button_map) {
    _instances.emplace_front(plane, button_map);
    return &_instances.front();
}

void KeyboardController::OnLeft() {
    auto keyboard = Keyboard::GetInstance();
    if (keyboard->Query(SDLK_a) == KEY_PRESS) {
        if (_plane) {
            int speed = _plane->GetSpeed();
            _plane->MoveBy(-speed, 0);
        }
    }
}

void KeyboardController::OnRight() {
    auto keyboard = Keyboard::GetInstance();
    if (keyboard->Query(SDLK_d) == KEY_PRESS) {
        if (_plane) {
            int speed = _plane->GetSpeed();
            _plane->MoveBy(speed, 0);
        }
    }
}

void KeyboardController::OnUp() {
    auto keyboard = Keyboard::GetInstance();
    if (keyboard->Query(SDLK_w) == KEY_PRESS) {
        if (_plane) {
            int speed = _plane->GetSpeed();
            _plane->MoveBy(0, -speed);
        }
    }
}

void KeyboardController::OnDown() {
    auto keyboard = Keyboard::GetInstance();
    if (keyboard->Query(SDLK_s) == KEY_PRESS) {
        if (_plane) {
            int speed = _plane->GetSpeed();
            _plane->MoveBy(0, speed);
        }
    }
}

void KeyboardController::OnShoot() {
    if (!_plane)
        return;
    auto keyboard = Keyboard::GetInstance();
    if (keyboard->Query(SDLK_j) == KEY_PRESS) {
        _plane->StartShoot();
    } else if (keyboard->Query(SDLK_j) == KEY_RELEASE) {
        _plane->StopShoot();
    }
}

void KeyboardController::OnBomb() {

}

void KeyboardController::OnBlast() {

}

void KeyboardController::OnEsc() {

}
