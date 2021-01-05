#ifndef UIOBJECT_HPP
#define UIOBJECT_HPP
#include <filesystem>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
namespace fs = std::filesystem;

class UIObject {
 public:
     void SetRender(SDL_Renderer* render);
     SDL_Renderer* GetRender();

     // NOTE delever event at here
     void EventHandle(SDL_Event&);

     virtual void Paint() = 0;

     virtual ~UIObject() = default;

 protected:
     // NOTE add event at here
     virtual void onMouseMotion(SDL_Event&) {}
     virtual void onMouseLeftDown(SDL_Event&) {}
     virtual void onMouseLeftUp(SDL_Event&) {}
     virtual void onMouseRightDown(SDL_Event&) {}
     virtual void onMouseRightUp(SDL_Event&) {}
     virtual void onDrag(SDL_Event&) {}
     virtual void onKeyDown(SDL_Event&) {}
     virtual void onKeyUp(SDL_Event&) {}
     virtual void onDropFile(SDL_Event&, fs::path file_path) {}

 private:
     SDL_Renderer* _render;
     bool _mouse_left_pressing = false;
     bool _mouse_right_pressing = false;
};


#endif
