#ifndef APP_HPP
#define APP_HPP
#include "exec_body.hpp"
#include "header.hpp"
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#define GL_STATIC
#include "GL/glew.h"
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
     GLuint _vbo = 0;
     GLuint _vao = 0;
     GLuint _ebo = 0;

     void initSystem();
     void initGLBuffers();
     void eventHandle();
     void prepDataForDraw();
     ExecBody* getExecBody();
};

#endif
