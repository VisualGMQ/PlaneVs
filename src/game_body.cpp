#include "game_body.hpp"

void GameBody::Init() {
    _projection = glm::ortho(0.0f, 1024.0f, 720.0f, 0.0f, -1.0f, 1.0f);
    GLShader vertex_shader(GL_VERTEX_SHADER, "shader/shader.vs");
    GLShader frag_shader(GL_FRAGMENT_SHADER, "shader/shader.fs");
    _program.ApplyShaders(vertex_shader, frag_shader);

    _texture.Load("resources/container.png");
}

void GameBody::Step() {
    _program.Use();
    _program.UniformMat4("projection", _projection);
    _texture.Draw(_program, 512, 360, 1, 1, 30); 
}

void GameBody::Destroy() {
    _program.Destroy();
}

GameBody::~GameBody() {
    Destroy();
}
