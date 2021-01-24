#ifndef EXEC_BODY_HPP
#define EXEC_BODY_HPP
#include <SDL.h>

#include "engin/gl_program.hpp"
#include "base/geomentry.hpp"

class ExecBody {
 public:
     virtual void Init() = 0;
     virtual void EventHandle(SDL_Event& event) = 0;
     virtual void Step() = 0;
     virtual void Destroy() = 0;
     virtual ~ExecBody() = default;
     isize GetWindowSize() const {
         int w, h;
         SDL_GetWindowSize(_window, &w, &h);
         return {w, h};
     }

     isize GetCanvaSize() const {
         return _canva_size;
     }

     void DepsInject(SDL_Window* window, isize canva_size) {
         _window = window;
         _canva_size = canva_size;
     }

     bool ShouldExit() const {
         return _should_exit;
     }

     void Exit() {
        _should_exit = true;
        Log("Game Exited");
     }

 private:
     bool _should_exit = false;
     SDL_Window* _window = nullptr;
     isize _canva_size;
};

#endif
