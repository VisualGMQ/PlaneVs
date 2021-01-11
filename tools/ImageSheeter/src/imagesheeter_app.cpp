#include "imagesheeter_app.hpp"

ImageSheeterApp::ImageSheeterApp() {
    onInit();
    _canva.SetRender(GetRender());
    _canva.InitResources(GetWindow());
}

void ImageSheeterApp::onInit() {
    initWindowAndRender("ImageSheeter", 800, 600);
}

void ImageSheeterApp::eventHandle() {
    if (_event.type == SDL_KEYDOWN) {
        if (_event.key.keysym.sym == SDLK_ESCAPE)
            onExit(_event);
    }
    _canva.EventHandle(_event);
}

void ImageSheeterApp::onExit(SDL_Event&) {
    _canva.Exit();
    Exit();
}

void ImageSheeterApp::onStep() {
    _canva.Paint();
}
