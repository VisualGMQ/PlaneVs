#include "engin/director.hpp"

Director* Director::director = nullptr;

void Director::Update() {
    if (_controller)
        controllerUpdate();
    if (_stage) {
        _stage->Step();
    }
}

void Director::controllerUpdate() {
    if (!_controller->IsWorking())
        return;
    auto keyboard = Keyboard::GetInstance();
    auto button_map = _controller->GetButtonMap();
    if (keyboard->Query(button_map.up) == KEY_PRESS) {
        _controller->OnUp();
    }
    if (keyboard->Query(button_map.down) == KEY_PRESS) {
        _controller->OnDown();
    }
    if (keyboard->Query(button_map.left) == KEY_PRESS) {
        _controller->OnLeft();
    }
    if (keyboard->Query(button_map.right) == KEY_PRESS) {
        _controller->OnRight();
    }
    if (keyboard->Query(button_map.shoot) == KEY_PRESS) {
        _controller->OnShoot();
    }
    if (keyboard->Query(button_map.bomb) == KEY_PRESS) {
        _controller->OnBomb();
    }
    if (keyboard->Query(button_map.blast) == KEY_PRESS) {
        _controller->OnBlast();
    }
    if (keyboard->Query(button_map.esc) == KEY_PRESS) {
        _controller->OnEsc();
    }
}

void Director::SetStage(Stage* stage) {
    if (_stage) {
        _stage->Destroy();
    }
    _stage = stage;
    if (_stage) {
        _stage->Init();
    } else {
        Loge("Director::SetStage", "Director::SetStage stage is nullptr");
    }
}

void Director::Exit() {
    if (_stage) {
        _stage->Exit();
    }
}

bool Director::ShouldExit() const {
    if (!_stage)
        return true;
    return _stage->ShouldExit();
}

void Director::Destroy() {
    if (_stage) {
        _stage->Destroy();
    }
}
