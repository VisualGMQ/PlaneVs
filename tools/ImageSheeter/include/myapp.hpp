#ifndef MYAPP_HPP
#define MYAPP_HPP
#include "canva.hpp"
#include "label.hpp"

class MyApp {
 public:
     MyApp();
     void Exit();
     bool ShouldQuit() const;
     void MainLoop();
 private:
     SDL_Window* _window = nullptr;
     SDL_Renderer* _render = nullptr;
     SDL_Event _event;
     bool _should_quit = false;

     Canva _canva;

     void onInit();
     void onDestroy();
     void eventHandle();
     void step();

     // event handlers
     void onExit(SDL_Event&);
     void onDropFile(SDL_Event&);
};

#endif
