#include "app.hpp"

App::App() {
    initSystem();
    Log("System Inited");
    initGLBuffers();
    Log("gl buffers inited");
    prepDataForDraw();
}

void App::SetTitle(string title) {
    SDL_SetWindowTitle(_window, title.c_str());
}

void App::initSystem() {
    Assertm("SDL init failed", SDL_Init(SDL_INIT_EVERYTHING) == 0);
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
    Log("SDL inited");

    IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);
    TTF_Init();
    Log("SDL expansions inited");

    _window = SDL_CreateWindow(
        "",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        _window_size.w, _window_size.h,
        SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE|SDL_WINDOW_OPENGL);
    Assertm("window create failed", _window != nullptr);

    SDL_GL_CreateContext(_window);

    glewExperimental = true;
    Assertm("glew init failed", glewInit() == GLEW_OK);
    Log("glew inited");

    glViewport(0, 0, _window_size.w, _window_size.h);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
}

void App::initGLBuffers() {
    glGenBuffers(1, &_vbo);
    Assertm("VBO create failed", _vbo != 0);
    glGenBuffers(1, &_ebo);
    Assertm("EBO create failed", _ebo != 0);
    glGenVertexArrays(1, &_vao);
    Assertm("VAO create failed", _vao != 0);
}

void App::prepDataForDraw() {
    GLfloat dataes[] = {
    //  image_x image_y tex_x tex_y
        -0.5,   -0.5,   0,    0,
         0.5,   -0.5,   1,    0,
        -0.5,    0.5,   0,    1,
         0.5,    0.5,   1,    1
    };

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBindVertexArray(_vao);

    glBufferData(GL_ARRAY_BUFFER, sizeof(dataes), dataes, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), static_cast<void*>(0));
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);

    GLuint indices[] = {
        0, 1, 2,
        1, 2, 3
    };

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void App::SetExecBody(ExecBody* body) {
    _exec_body = body;
    _exec_body->DepsInject(_window, _canva_size);
    _exec_body->Init();
    Log("executable body inited");
}

ExecBody* App::getExecBody() {
    if (!_exec_body)
        SDL_Log("exec body empty");
    return _exec_body;
}

void App::Run() {
    ExecBody* exec_body = getExecBody();
    Assertm("Don't have any executable body", exec_body != nullptr);
    while (!exec_body->ShouldExit()) {
        glClearColor(_clear_color.r, _clear_color.g, _clear_color.b, _clear_color.a);
        glClear(GL_COLOR_BUFFER_BIT|GL_STENCIL_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBindVertexArray(_vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
        eventHandle();
        exec_body->Step();
        SDL_GL_SwapWindow(_window);
        SDL_Delay(_delay_time);
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
            _exec_body->Exit();
        _exec_body->EventHandle(_event);
    }
}

App::~App() {
    _exec_body->Destroy();
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(1, &_vbo);
    glDeleteBuffers(1, &_ebo);
    SDL_DestroyWindow(_window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}
