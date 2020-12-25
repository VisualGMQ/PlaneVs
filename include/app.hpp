#ifndef APP_HPP
#define APP_HPP
#include "SDL.h"
#include "SDL_image.h"
#define GLEW_STATIC
#include "GL/glew.h"
#include "exec_body.hpp"
#include "header.hpp"

class App final{
 public:
     App();
     void SetExecBody(ExecBody* body);
     void Run();
     ~App();
 private:
     SDL_Window* _window = nullptr;
     Color _clear_color = {0.5, 0.5, 0.5, 1};
     const int _window_width = 1024;
     const int _window_height = 720;
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
};

#endif
