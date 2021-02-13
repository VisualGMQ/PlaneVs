#include "engin/app.hpp"

void quitSDL() {
    IMG_Quit();
    TTF_Quit();
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
}

App::App(Stage* stage) {
    initSystem();
    Logi("App::App", "System inited");
    Director::GetInstance()->SetStage(stage);
    imgui::Init(_render);
    atexit(quitSDL);
}

void App::SetTitle(string title) {
    SDL_SetWindowTitle(_window, title.c_str());
}

void App::initSystem() {
    Assertm(SDL_Init(SDL_INIT_EVERYTHING) == 0, "App::initSystem", "App::initSystem", "SDL init failed");
    SDL_SetHintWithPriority(SDL_HINT_FRAMEBUFFER_ACCELERATION, "1", SDL_HINT_OVERRIDE);
    SDL_SetHintWithPriority(SDL_HINT_RENDER_OPENGL_SHADERS, "1", SDL_HINT_OVERRIDE);
    SDL_SetHintWithPriority(SDL_HINT_RENDER_SCALE_QUALITY, "1", SDL_HINT_OVERRIDE);
    SDL_SetHintWithPriority(SDL_HINT_RENDER_VSYNC, "1", SDL_HINT_OVERRIDE);

    IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);
    TTF_Init();
    Mix_Init(MIX_INIT_OGG|MIX_INIT_MP3|MIX_INIT_FLAC|MIX_INIT_MID|MIX_INIT_MOD);
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
    Logi("App::initSystem", "SDL expansions inited");

    _window = SDL_CreateWindow(
        "",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        _window_size.w, _window_size.h,
        SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE|SDL_WINDOW_OPENGL);
    Assertm(_window != nullptr, "App::initSystem", "window create failed");
    _render = SDL_CreateRenderer(_window, -1, 0);
    Assertm(_render != nullptr, "App::initSystem", "render create failed");
    Director::Init(_window, _render);

    SDL_SetRenderDrawBlendMode(_render, SDL_BLENDMODE_BLEND);

    _canva = SDL_CreateTexture(_render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, CanvaSize.w, CanvaSize.h);

}

void App::Run() {
    Director* director = Director::GetInstance();
    while (!director->ShouldExit()) {
        const int tick = SDL_GetTicks();
        SDL_SetRenderTarget(_render, _canva);
        SDL_SetRenderDrawColor(_render, _clear_color.r, _clear_color.g, _clear_color.b, _clear_color.a);
        SDL_RenderClear(_render);
        imgui::Prepare();
        eventHandle();
        director->Update();
        SDL_SetRenderTarget(_render, nullptr);
        SDL_RenderCopy(_render, _canva, nullptr, nullptr);
        SDL_RenderPresent(_render);
        imgui::Finish();
        const int delay_time = round(1000.0/FPS);
        const int delta_tick= SDL_GetTicks() - tick;
        if (delta_tick <= delay_time) {
            SDL_Delay(delay_time-delta_tick);
        } else {
            SDL_Delay(10);
        }
    }
}

void App::eventHandle() {
    while (SDL_PollEvent(&_event)) {
        if (_event.type == SDL_QUIT)
            Director::GetInstance()->Exit();
        imgui::EventHandle(_event);
        Keyboard::GetInstance()->ReceiveEvent(_event);
        Mouse::GetInstance()->ReceiveEvent(_event);
    }
}

App::~App() {
    Logi("App::~App", "App cleanup");
    Director::GetInstance()->Destroy();
    Logi("App::~App", "Director destroyed");
    Font::DestroyAll();
    Logi("App::~App", "Font destroyed");
    TextureRepo::DestroyAll();
    Logi("App::~App", "TextureRepo destroyed");
    Texture::DestroyAll();
    Logi("App::~App", "Texture destroyed");
    imgui::Quit();
    Logi("App::~App", "imgui quited");
    Bgm::Destroy();
    Logi("App::~App", "Bgm destroyed");
    Music::DestroyAll();
    Logi("App::~App", "Music destroyed");
    SDL_DestroyTexture(_canva);
    SDL_DestroyWindow(_window);
    Logi("App::~App", "Window destroyed");
    SDL_DestroyRenderer(_render);
    Logi("App::~App", "Renderer destroyed");
    Logi("App::~App", "All system quit, App finished");
}
