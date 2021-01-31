#ifndef GAME_BODY_HPP
#define GAME_BODY_HPP
#include "engin/sprite.hpp"
#include "engin/exec_body.hpp"
#include "engin/bgm.hpp"
using glm::mat4;
using std::to_string;

class GameBody final: public ExecBody {
 public:
     GameBody() = default;
     void Init() override;
     void Step() override;
     void Destroy() override;
     void EventHandle(SDL_Event&) override;
     virtual ~GameBody() = default;

 private:
     Sprite* _sprite = nullptr;
};

#endif

