#include "engin/director.hpp"

Director* Director::director = nullptr;

void Director::Init(SDL_Window* window, SDL_Renderer* render) {
    if (director)
        delete director;
    director = new Director;
    director->_window = window;
    director->_render = render;
}

void Director::Update() {
    if (_stage) {
        _stage->Step();
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
