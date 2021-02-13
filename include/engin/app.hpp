#ifndef APP_HPP
#define APP_HPP
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <glm/glm.hpp>

#include "base/log.hpp"
#include "base/config.hpp"
#include "base/texture.hpp"
#include "base/texture_repo.hpp"
#include "engin/stage.hpp"
#include "engin/sprite.hpp"
#include "engin/bgm.hpp"
#include "engin/music.hpp"
#include "engin/text.hpp"
#include "engin/director.hpp"
#include "engin/input/input.hpp"
#include "engin/ui/ui.hpp"
using std::to_string;

void quitSDL();

class App final{
 public:
     App(Stage* stage);
     void SetTitle(string title);
     void Run();
     ~App();
 private:
     SDL_Window* _window = nullptr;
     SDL_Renderer* _render = nullptr;
     icolor _clear_color = {120, 120, 120, 255};
     const isize _window_size = WindowInitSize;
     const isize _canva_size = CanvaSize;
     SDL_Texture* _canva = nullptr; 
     SDL_Event _event;

     void initSystem();
     void eventHandle();
};

#endif
