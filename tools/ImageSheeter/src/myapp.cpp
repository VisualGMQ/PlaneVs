#include "myapp.hpp"

MyApp::MyApp() {
    onInit();
    _canva.SetRender(_render);
    _canva.InitResources();
}

void MyApp::Exit() {
    _should_quit = true;
}

bool MyApp::ShouldQuit() const {
    return _should_quit;
}

void MyApp::MainLoop() {
    while (!ShouldQuit()) {
        SDL_SetRenderDrawColor(_render, 100, 100, 100, 255);
        SDL_RenderClear(_render);
        eventHandle();
        step();
        SDL_RenderPresent(_render);
        SDL_Delay(30);
    }
}

void MyApp::onInit() {
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG|IMG_INIT_JPG|IMG_INIT_TIF|IMG_INIT_WEBP);
    TTF_Init();
    _window = SDL_CreateWindow("Image Sheeter",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            800, 600,
            SDL_WINDOW_SHOWN);
    _render = SDL_CreateRenderer(_window, -1, 0);
    SDL_SetRenderDrawBlendMode(_render, SDL_BLENDMODE_BLEND);
}

void MyApp::eventHandle() {
    while (SDL_PollEvent(&_event)) {
        if (_event.type == SDL_QUIT) {
            onExit(_event);
        }
        if (_event.type == SDL_KEYDOWN) {
            if (_event.key.keysym.sym == SDLK_ESCAPE)
                onExit(_event);
        }
        _canva.EventHandle(_event);
    }
}

void MyApp::onExit(SDL_Event&) {
    _canva.Exit();
    Exit();
}

void MyApp::step() {
    _canva.Paint();
}

void MyApp::onDestroy() {
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_render);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}
