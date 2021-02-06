#ifndef STAGE_HPP
#define STAGE_HPP
#include <SDL.h>

#include "base/log.hpp"
#include "base/geomentry.hpp"

/*
 * @brief stage , can send to App and run
 * @warn suggest put `clean up` phase into Destroy rather than deconstructor.And **Never** call Destroy() in deconstructor.
 *       Due to the auto deconstruction by main, your Destroy function will be call twice(by class App, and function main).
 */
class Stage {
 public:
    virtual void Init() = 0;
    virtual void EventHandle(SDL_Event& event) = 0;
    virtual void Step() = 0;
    virtual void Destroy() = 0;
    virtual ~Stage() = default;

    bool ShouldExit() const {
        return _should_exit;
    }

    void Exit() {
       _should_exit = true;
       Logi("Stage::Exit()", "Game Exited");
    }

 private:
    bool _should_exit = false;
};

#endif
