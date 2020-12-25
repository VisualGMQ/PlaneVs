#ifndef DEFAULTBODY_HPP
#define DEFAULTBODY_HPP
#include "exec_body.hpp"

class DefaultBody: public ExecBody {
 public:
     void Init() override {}
     void EventHandle(SDL_Event& event) override {
         while (SDL_PollEvent(&event)) {
             if (event.type == SDL_QUIT)
                 Exit();
         }
     }
     void Step() override {}
     void Destroy() override {}
     virtual ~DefaultBody() {}
};

#endif

