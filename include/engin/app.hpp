#ifndef APP_HPP
#define APP_HPP
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#define GL_STATIC
#include <GL/glew.h>

#include "base/log.hpp"
#include "base/exec_body.hpp"
#include "base/id_generator.hpp"
#include "engin/gl_gfxbuf.hpp"
using std::to_string;

constexpr isize WindowInitSize = {1024, 720};
constexpr isize CanvaInitSize = {1024, 720};

class App final{
 public:
     App();
     void SetExecBody(ExecBody* body);
     void SetTitle(string title);
     void Run();
     ~App();
 private:
     SDL_Window* _window = nullptr;
     color _clear_color = {0.5f, 0.5f, 0.5f, 1.0f};
     const isize _window_size = WindowInitSize;
     const isize _canva_size = CanvaInitSize;
     const int _delay_time = 30;
     SDL_Event _event;
     ExecBody* _exec_body = nullptr;
     GLGfxBuf* _gfx_buf = nullptr;
     glm::mat4 _projection;

     void initSystem();
     void initGLBuffers();
     void eventHandle();
     ExecBody* getExecBody();
};

#endif
