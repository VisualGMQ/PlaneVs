#include "game/controller/plane/plane_keyboard_controller.hpp"

list<PlaneKeyboardController> PlaneKeyboardController::_controllers;

void PlaneKeyboardController::Up() {
    Plane* plane = GetPlane();
    if (plane &&
        Keyboard::GetInstance()->Query(_up) == KEY_PRESS) {
        plane->MoveBy(0, -plane->GetSpeed());
    }
}

void PlaneKeyboardController::Down() {
    Plane* plane = GetPlane();
    if (plane &&
        Keyboard::GetInstance()->Query(_down) == KEY_PRESS) {
        plane->MoveBy(0, plane->GetSpeed());
    }
}

void PlaneKeyboardController::Left() {
    Plane* plane = GetPlane();
    if (plane &&
        Keyboard::GetInstance()->Query(_left) == KEY_PRESS) {
        plane->MoveBy(-plane->GetSpeed(), 0);
    }
}

void PlaneKeyboardController::Right() {
    Plane* plane = GetPlane();
    if (plane &&
        Keyboard::GetInstance()->Query(_right) == KEY_PRESS) {
        plane->MoveBy(plane->GetSpeed(), 0);
    }
}

void PlaneKeyboardController::Fire() {
    Plane* plane = GetPlane();
    if (plane) {
        int key_status = Keyboard::GetInstance()->Query(_fire);
        if (key_status == KEY_PRESS) {
            plane->StartShoot();
        } else if (key_status == KEY_RELEASE) {
            plane->StopShoot();
        }
    }
}

void PlaneKeyboardController::Bomb() {
    Plane* plane = GetPlane();
    if (plane) {
        if (Keyboard::GetInstance()->Query(_bomb) == KEY_PRESS) {
            // TODO not implement bomb
        }
    }
}

void PlaneKeyboardController::Blast() {
    Plane* plane = GetPlane();
    if (plane) {
        if (Keyboard::GetInstance()->Query(_blast) == KEY_PRESS) {
            // TODO not implement blast
        }
    }
}

