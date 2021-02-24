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
    auto director = Director::GetInstance();
    director->SetStage(stage);
    Logi("App::App", "first stage set");
    imgui::Init(director->GetRender());
    Logi("App::App", "imgui inited");
    atexit(quitSDL);
}

void App::SetTitle(string title) {
    SDL_SetWindowTitle(Director::GetInstance()->GetWindow(), title.c_str());
}

void App::initSystem() {
    Assertm(SDL_Init(SDL_INIT_EVERYTHING) == 0, "App::initSystem", "App::initSystem", "SDL init failed: %s", SDL_GetError());
    SDL_SetHintWithPriority(SDL_HINT_FRAMEBUFFER_ACCELERATION, "1", SDL_HINT_OVERRIDE);
    SDL_SetHintWithPriority(SDL_HINT_RENDER_OPENGL_SHADERS, "1", SDL_HINT_OVERRIDE);
    SDL_SetHintWithPriority(SDL_HINT_RENDER_SCALE_QUALITY, "1", SDL_HINT_OVERRIDE);
    SDL_SetHintWithPriority(SDL_HINT_RENDER_VSYNC, "1", SDL_HINT_OVERRIDE);

    IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);
    TTF_Init();
    Mix_Init(MIX_INIT_OGG|MIX_INIT_MP3|MIX_INIT_FLAC|MIX_INIT_MID|MIX_INIT_MOD);
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
    Logi("App::initSystem", "SDL expansions inited");

    Director::Init();
}

void App::Run() {
    Director* director = Director::GetInstance();
    Logi("App::Run", "app will run");
    while (!director->ShouldExit()) {
        const int tick = SDL_GetTicks();
        director->RenderClear(CanvaBgColor);
        imgui::Prepare();
        eventHandle();
        director->Update();
        imgui::Finish();
        director->RenderPresent();
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
    Director::GetInstance()->StageDestroy();
    Logi("App::~App", "Stage destroyed");
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
    Director::GetInstance()->Destroy();
    Logi("App::~App", "Director destroyed");
    Logi("App::~App", "All system quit, App finished");
}
