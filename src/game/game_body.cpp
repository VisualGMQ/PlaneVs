#include "game/game_body.hpp"

void GameBody::Init() {
    _sprite = Sprite::Create("resources/container.png");
    _sprite->MoveTo(CanvaSize.w/2, CanvaSize.h/2);
    _sprite->ResizeTo(500, 300);
    _sprite->RotateTo(20);
    _sprite->Show();
    _sprite->SetColor(80, 80, 255);

    Bgm::Load("./test/test_resources/Mind Control.ogg");
    Bgm::FadeIn(-1, 3000);
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
