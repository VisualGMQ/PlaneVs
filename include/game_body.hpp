#ifndef GAME_BODY_HPP
#define GAME_BODY_HPP
#include "default_body.hpp"
#include "texture.hpp"
using glm::mat4;

class GameBody final: public DefaultBody{
 public:
     GameBody() = default;
     void Init() override;
     void Step() override;
     void Destroy() override;
     virtual ~GameBody();
 private:
    GLProgram _program;
    mat4 _projection;
    Texture _texture;
};

#endif

