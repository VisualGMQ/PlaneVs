#include "game/controller/plane/plane_keyboard_controller.hpp"
using input::Keyboard;

list<PlaneKeyboardController> PlaneKeyboardController::_controllers;

void PlaneKeyboardController::Up() {
    Plane* plane = GetPlane();
    if (plane &&
        Keyboard::GetInstance()->Query(_up).IsPress()) {
        plane->MoveBy(0, -plane->GetSpeed());
    }
}

void PlaneKeyboardController::Down() {
    Plane* plane = GetPlane();
    if (plane &&
        Keyboard::GetInstance()->Query(_down).IsPress()) {
        plane->MoveBy(0, plane->GetSpeed());
    }
}

void PlaneKeyboardController::Left() {
    Plane* plane = GetPlane();
    if (plane &&
        Keyboard::GetInstance()->Query(_left).IsPress()) {
        plane->MoveBy(-plane->GetSpeed(), 0);
    }
}

void PlaneKeyboardController::Right() {
    Plane* plane = GetPlane();
    if (plane &&
        Keyboard::GetInstance()->Query(_right).IsPress()) {
        plane->MoveBy(plane->GetSpeed(), 0);
    }
}

void PlaneKeyboardController::Fire() {
    Plane* plane = GetPlane();
    if (plane) {
        input::Button key_button = Keyboard::GetInstance()->Query(_fire);
        if (key_button.IsPress()) {
            plane->StartShoot();
        } else {
            plane->StopShoot();
        }
    }
}

void PlaneKeyboardController::Bomb() {
    Plane* plane = GetPlane();
    if (plane) {
        if (Keyboard::GetInstance()->Query(_bomb).IsPress()) {
            // TODO not implement bomb
        }
    }
}

void PlaneKeyboardController::Blast() {
    Plane* plane = GetPlane();
    if (plane) {
        if (Keyboard::GetInstance()->Query(_blast).IsPress()) {
            // TODO not implement blast
        }
    }
}

