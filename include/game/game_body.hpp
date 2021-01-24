#ifndef GAME_BODY_HPP
#define GAME_BODY_HPP
#include "base/exec_body.hpp"
#include "engin/texture.hpp"
using glm::mat4;
using std::to_string;

class GameBody final: public ExecBody {
 public:
     GameBody() = default;
     void Init() override;
     void Step() override;
     void Destroy() override;
     void EventHandle(SDL_Event&) override;
     virtual ~GameBody();
 private:
     Texture _texture;
};

#endif

