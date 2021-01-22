#ifndef APP_HPP
#define APP_HPP
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#define GL_STATIC
#include <GL/glew.h>

#include "base/exec_body.hpp"
#include "base/header.hpp"
#include "engin/gl_gfxbuf.hpp"
using std::to_string;

class App final{
 public:
     App();
     void SetExecBody(ExecBody* body);
     void SetTitle(string title);
     void Run();
     ~App();
 private:
     SDL_Window* _window = nullptr;
     Color _clear_color = {0.5, 0.5, 0.5, 1};
     const Size _window_size = {1024, 720};
     const Size _canva_size = {1024, 720};
     const int _delay_time = 30;
     SDL_Event _event;
     ExecBody* _exec_body = nullptr;
     GLGfxBufManager::GLGfxBuf* _gfx_buf = nullptr;

     void initSystem();
     void initGLBuffers();
     void eventHandle();
     void prepDataForDraw();
     ExecBody* getExecBody();
};

#endif
