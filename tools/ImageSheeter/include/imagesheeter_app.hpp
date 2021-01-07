#ifndef IMAGESHEETERAPP_HPP
#define IMAGESHEETERAPP_HPP
#include "sdl_app.hpp"
#include "canva.hpp"
#include "label.hpp"

class ImageSheeterApp:public SDLApp{
 public:
     ImageSheeterApp();
     virtual ~ImageSheeterApp() = default;
 private:
     Canva _canva;

     void onInit() override;
     void onDestroy() override;
     void eventHandle() override;
     void onStep() override;

     // event handlers
     void onExit(SDL_Event&);
     void onDropFile(SDL_Event&);
};

#endif
