#ifndef EXEC_BODY_HPP
#define EXEC_BODY_HPP
#include "SDL.h"
#include "gl_program.hpp"

class ExecBody {
 public:
     virtual void Init() = 0;
     virtual void EventHandle(SDL_Event& event) = 0;
     virtual void Step() = 0;
     virtual void Destroy() = 0;
     virtual ~ExecBody() = default;
     void DepsInject(SDL_Window* window) {
         _window = window;
     }

     bool ShouldExit() const {
         return _should_exit;
     }

     void Exit() {
        _should_exit = true;
     }

 protected:
     SDL_Window* _window = nullptr;

 private:
     bool _should_exit = false;
};

#endif
