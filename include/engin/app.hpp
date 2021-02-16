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
     SDL_Event _event;

     void initSystem();
     void eventHandle();
};

#endif
