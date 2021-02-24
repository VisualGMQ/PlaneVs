#include "engin/director.hpp"

Director* Director::director = nullptr;

void Director::Init() {
    if (director)
        delete director;
    director = new Director;
    director->_window = SDL_CreateWindow(
        "",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WindowInitSize.w, WindowInitSize.h,
        SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE|SDL_WINDOW_OPENGL);
    Assertm(director->_window != nullptr, "App::initSystem", "window create failed");
    director->_render = SDL_CreateRenderer(director->GetWindow(), -1, 0);
    Assertm(director->_render != nullptr, "App::initSystem", "render create failed");
    director->_canva = SDL_CreateTexture(director->GetRender(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, CanvaSize.w, CanvaSize.h);
    Assertm(director->_canva, "Director::Init", "canva create failed");
    SDL_SetRenderTarget(director->GetRender(), director->_canva);
    SDL_SetRenderDrawBlendMode(director->GetRender(), SDL_BLENDMODE_BLEND);
    Logi("Director::Init", "director init Ok");
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
        Logi("Director::SetStage", "stage Inited");
    } else {
        Loge("Director::SetStage", "Director::SetStage stage is nullptr");
    }
}

void Director::SetRenderTargetToDefault() {
    SDL_SetRenderTarget(GetRender(), _canva);
}

void Director::RenderClear(const icolor& color) {
    auto render = GetRender();
    SDL_SetRenderTarget(render, _canva);
    SDL_SetRenderDrawColor(render, color.r, color.g, color.b, color.a);
    SDL_RenderClear(render);
}

void Director::RenderPresent() {
    auto render = GetRender();
    Assertm(render, "Director::RenderPresent", "render is nullptr");
    SDL_SetRenderTarget(render, nullptr);
    SDL_RenderCopy(render, _canva, nullptr, nullptr);
    SDL_RenderPresent(render);
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

void Director::StageDestroy() {
    if (_stage) {
        _stage->Destroy();
    }
}

void Director::Destroy() {
    SDL_DestroyTexture(_canva);
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_render);
    // FIXME Is this will cause Segment Failed???
    delete Director::director;
}
