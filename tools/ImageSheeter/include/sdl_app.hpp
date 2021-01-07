#ifndef SDL_APP_HPP
#define SDL_APP_HPP
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
using std::string;

class SDLApp {
 public:
     SDLApp();
     bool ShouldQuit() const;
     void Exit();
     virtual void MainLoop();
     SDL_Renderer* GetRender();
     SDL_Window* GetWindow();
     virtual ~SDLApp();
 protected:
     SDL_Event _event;

     virtual void onInit();
     virtual void eventHandleWithPoll();
     virtual void eventHandle();
     virtual void onDestroy();
     virtual void onStep();
     void initWindowAndRender(string title, int w, int h);
 private:
     SDL_Window* _window = nullptr;
     SDL_Renderer* _render = nullptr;
     bool _should_quit = false;
};

#endif

