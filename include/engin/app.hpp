#ifndef APP_HPP
#define APP_HPP
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#define GL_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "base/log.hpp"
#include "base/config.hpp"
#include "base/gl_program.hpp"
#include "base/gl_gfxbuf.hpp"
#include "base/texture.hpp"
#include "engin/exec_body.hpp"
#include "engin/sprite.hpp"
#include "engin/bgm.hpp"
#include "engin/music.hpp"
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
     color _clear_color = {0.5f, 0.5f, 0.5f, 1.0f};
     const isize _window_size = WindowInitSize;
     const isize _canva_size = CanvaSize;
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
