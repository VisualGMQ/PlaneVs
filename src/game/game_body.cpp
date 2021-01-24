#include "game/game_body.hpp"

void GameBody::Init() {
    isize size = GetWindowSize();

    _texture.Load("resources/container.png");
}

void GameBody::EventHandle(SDL_Event& event) {
}

void GameBody::Step() {
    GLProgram* program = GLProgramManager::GetById(TEXTURE_PROGRAM_ID);
    if (!program || !program->IsValid()) {
        Log("program invalid");
    }
    isize size = GetCanvaSize();
    auto tex_size = _texture.GetSize();
    _texture.Draw({.src_rect = {0, 0, tex_size.w/2, tex_size.h/2}, .dst_rect = {size.w/2, size.h/2, tex_size.w/2, tex_size.h/2}, .degree = 30},
            {.tex_color = {1.0f, 0.0f, 0.0f, 1.0f}});
}

void GameBody::Destroy() {
}

GameBody::~GameBody() {
    Destroy();
}
