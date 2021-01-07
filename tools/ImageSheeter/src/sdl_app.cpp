#include "sdl_app.hpp"

SDLApp::SDLApp() {
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_TIF);
    TTF_Init();
    onInit();
}

void SDLApp::onInit() {}
void SDLApp::onDestroy() {}
void SDLApp::onStep() {}

void SDLApp::initWindowAndRender(string title, int w, int h) {
    _window = SDL_CreateWindow(
            title.c_str(),
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            w, h, SDL_WINDOW_SHOWN);
    if (!_window) {
        SDL_Log("window can't create");
        exit(1);
    }

    _render = SDL_CreateRenderer(_window, -1, 0);
    if (!_render) {
        SDL_Log("render can't create");
        exit(2);
    }
}

void SDLApp::MainLoop() {
    while (!ShouldQuit()) {
        auto render = GetRender();
        SDL_SetRenderDrawColor(render, 100, 100, 100, 255);
        SDL_RenderClear(render);
        eventHandleWithPoll();
        onStep();
        SDL_RenderPresent(render);
        SDL_Delay(30);
    }
}

void SDLApp::eventHandleWithPoll() {
    while (SDL_PollEvent(&_event)) {
        if (_event.type == SDL_QUIT)
            Exit();
        eventHandle();
    }
}

void SDLApp::eventHandle() {}

bool SDLApp::ShouldQuit() const {
    return _should_quit;
}

SDL_Renderer* SDLApp::GetRender() {
    if (!_render)
        SDL_Log("render is nullptr, there something wrong");
    return _render;
}

SDL_Window* SDLApp::GetWindow() {
    if (!_window)
        SDL_Log("window is nullptr, there something wrong");
    return _window;
}

void SDLApp::Exit() {
    _should_quit = true;
}

SDLApp::~SDLApp() {
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_render);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}
