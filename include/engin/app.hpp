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
#include "base/texture_repo.hpp"
#include "engin/stage.hpp"
#include "engin/sprite.hpp"
#include "engin/bgm.hpp"
#include "engin/music.hpp"
#include "engin/text.hpp"
#include "engin/director.hpp"
#include "engin/input/input.hpp"
using std::to_string;

class App final{
 public:
     App(Stage* stage);
     void SetTitle(string title);
     void Run();
     ~App();
 private:
     SDL_Window* _window = nullptr;
     color _clear_color = {0.5f, 0.5f, 0.5f, 1.0f};
     const isize _window_size = WindowInitSize;
     const isize _canva_size = CanvaSize;
     SDL_Event _event;
     GLGfxBuf* _gfx_buf = nullptr;
     glm::mat4 _projection;

     void initSystem();
     void initGLBuffers();
     void eventHandle();
};

#endif
