#ifndef EXEC_BODY_HPP
#define EXEC_BODY_HPP
#include <SDL.h>

#include "engin/gl_program.hpp"

class ExecBody {
 public:
     virtual void Init() = 0;
     virtual void EventHandle(SDL_Event& event) = 0;
     virtual void Step() = 0;
     virtual void Destroy() = 0;
     virtual ~ExecBody() = default;
     Size GetWindowSize() const {
         int w, h;
         SDL_GetWindowSize(_window, &w, &h);
         return {static_cast<float>(w), static_cast<float>(h)};
     }

     Size GetCanvaSize() const {
         return _canva_size;
     }

     void DepsInject(SDL_Window* window, Size canva_size) {
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
     Size _canva_size;
};

#endif
