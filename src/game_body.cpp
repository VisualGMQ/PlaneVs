#include "game_body.hpp"

void GameBody::Init() {
    Size size = GetWindowSize();
    _projection = glm::ortho(0.0f, size.w, size.h, 0.0f, -1.0f, 1.0f);
    GLShader vertex_shader(GL_VERTEX_SHADER, "shader/shader.vert");
    GLShader frag_shader(GL_FRAGMENT_SHADER, "shader/shader.frag");
    _program.ApplyShaders(vertex_shader, frag_shader);

    _texture.Load("resources/container.png");
}

void GameBody::EventHandle(SDL_Event& event) {
}

void GameBody::Step() {
    _program.Use();
    _program.UniformMat4("projection", _projection);
    Size size = GetCanvaSize();
    _texture.Draw(_program, {.position = {size.w/2, size.h/2}, .scale = {1, 1}, .degree = 30},
            {.color = {1, 0, 0, 1}});
}

void GameBody::Destroy() {
    _program.Destroy();
}

GameBody::~GameBody() {
    Destroy();
}
