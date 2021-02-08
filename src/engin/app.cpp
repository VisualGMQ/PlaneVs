#include "engin/app.hpp"

App::App(Stage* stage) {
    initSystem();
    Logi("App::App", "System inited");
    CreatePresetPrograms();
    Logi("App::App", "programs inited");
    initGLBuffers();
    Logi("App::App", "gl buffers inited");
    Director::GetInstance()->SetStage(stage);
}

void App::SetTitle(string title) {
    SDL_SetWindowTitle(_window, title.c_str());
}

void App::initSystem() {
    Assertm(SDL_Init(SDL_INIT_EVERYTHING) == 0, "App::initSystem", "App::initSystem", "SDL init failed");
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);
    Logi("App::initSystem", "SDL inited");

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

    SDL_GL_CreateContext(_window);

    glewExperimental = true;
    Assertm(glewInit() == GLEW_OK, "App::initSystem", "glew init failed");
    Logi("App::initSystem", "glew inited");

    glViewport(0, 0, _window_size.w, _window_size.h);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);

    _projection = glm::ortho(0.0f, static_cast<float>(_window_size.w), static_cast<float>(_window_size.h), 0.0f, -1.0f, 1.0f);
}

void App::initGLBuffers() {
    CreatePresetGfxBufs();
    _gfx_buf = GLGfxBufManager::GetById(SYSTEM_GFXBUF_ID);
    Logi("App::initGLBuffers", "system gfx buffer created");
}

void App::Run() {
    Director* director = Director::GetInstance();
    while (!director->ShouldExit()) {
        const int tick = SDL_GetTicks();
        glClearColor(_clear_color.r, _clear_color.g, _clear_color.b, _clear_color.a);
        glClear(GL_COLOR_BUFFER_BIT|GL_STENCIL_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glBindBuffer(GL_ARRAY_BUFFER, _gfx_buf->vbo);
        glBindVertexArray(_gfx_buf->vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _gfx_buf->ebo);
        eventHandle();
        GLProgramManager::GetById(TEXTURE_PROGRAM_ID)->UniformMat4("projection", _projection);
        director->Update();
        SDL_GL_SwapWindow(_window);

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
        if (_event.type == SDL_WINDOWEVENT) {
            if (_event.window.event == SDL_WINDOWEVENT_RESIZED) {
                 glViewport(0, 0, _event.window.data1, _event.window.data2);
            }
        }
        if (_event.type == SDL_QUIT)
            Director::GetInstance()->Exit();
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
    GLGfxBufManager::Destroy();
    Logi("App::~App", "GLGfxBufManager destroyed");
    GLProgramManager::Destroy();
    Logi("App::~App", "GLProgramManager destroyed");
    Bgm::Destroy();
    Logi("App::~App", "Bgm destroyed");
    Music::DestroyAll();
    Logi("App::~App", "Music destroyed");
    SDL_DestroyWindow(_window);
    Logi("App::~App", "Window destroyed");
    IMG_Quit();
    TTF_Quit();
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
    Logi("App::~App", "All system quit, App finished");
}
