#ifndef EXEC_BODY_HPP
#define EXEC_BODY_HPP
#include <SDL.h>

#include "base/log.hpp"
#include "base/geomentry.hpp"

/*
 * @brief execute body, can send to App and run
 * @warn suggest put `clean up` phase into Destroy rather than deconstructor.And **Never** call Destroy() in deconstructor.
 *       Due to the auto deconstruction by main, your Destroy function will be call twice(by class App, and function main).
 */
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

     void DepsInject(SDL_Window* window) {
         _window = window;
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
};

#endif
