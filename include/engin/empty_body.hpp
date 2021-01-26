#ifndef DEFAULTBODY_HPP
#define DEFAULTBODY_HPP
#include "engin/exec_body.hpp"

class EmptyBody: public ExecBody {
 public:
     void Init() override {}
     void EventHandle(SDL_Event& event) override {}
     void Step() override {}
     void Destroy() override {}
     virtual ~EmptyBody() = default;
};

#endif
