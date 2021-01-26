#include "game/game_body.hpp"

void GameBody::Init() {
    _sprite = Sprite::Create("resources/container.png");
    _sprite->MoveTo(CanvaSize.w/2, CanvaSize.h/2);
    _sprite->SetSize(500, 300);
    _sprite->SetRotation(20);
    _sprite->Show();
    _sprite->SetColor(0.3, 0.3, 1);
}

void GameBody::EventHandle(SDL_Event& event) {
}

void GameBody::Step() {
    _sprite->Draw();
    _sprite->Update();
}

void GameBody::Destroy() {
    Log("GameBody Destoryed");
}
