#include "game/welcome_stage.hpp"

void WelcomeStage::Init() {
    SetLogLevel(LOG_ALL);

    PlaneProperty plane_prop;
    plane_prop.hp = 20;
    plane_prop.speed = 5;
    Sprite* sp = Sprite::Create("resources/enemy1.png");
    sp->SetKeyColor(32, 32, 32);
    _enemy = new Plane(sp, plane_prop);

    BulletProperty prop;
    prop.damage = 10;
    prop.speed = 8;
    prop.direction.x = 0;
    prop.direction.y = 1;
    Sprite* sprite = Sprite::Create("resources/enemy_bullet1.png");
    sprite->SetKeyColor(32, 32, 32);
    Charger* charger = new Charger(sprite, prop, 10);
    _enemy->AddCharger(charger);
    _enemy->MoveTo(100, 100);
    _enemy->Show();

    _cache = SpriteSheetCache::Create("resources/player_plane.json");
    sprite = _cache->CreateSprite("player_plane");
    sprite->SetKeyColor(32, 32, 32);
    _plane = new Plane(sprite, plane_prop);
    _plane->Show();
    _plane->MoveTo(400, 400);
    prop.direction.y = -1;
    sprite = _cache->CreateSprite("player_bullet");
    sprite->SetKeyColor(32, 32, 32);
    _plane->AddCharger(new Charger(sprite, prop, 10));

    Logt("WelcomeStage::Init", "will new controller");
    _controller = new Controller;
    _controller->TrunOn();
    Logt("WelcomeStage::Init", "will new commands");
    _controller->SetUpCommand(new KeyboardCommand_Up(SDLK_w));
    _controller->SetDownCommand(new KeyboardCommand_Down(SDLK_s));
    _controller->SetLeftCommand(new KeyboardCommand_Left(SDLK_a));
    _controller->SetRightCommand(new KeyboardCommand_Right(SDLK_d));
    _controller->SetFireCommand(new KeyboardCommand_Fire(SDLK_j));
    _controller->SetBombCommand(new KeyboardCommand_Bomb(SDLK_k));
    _controller->SetBlastCommand(new KeyboardCommand_Blast(SDLK_o));
    Logt("WelcomeStage::Init", "end");
}

void WelcomeStage::Step() {
    _controller->Control(_plane);
    _enemy->Update();
    _plane->Update();
    _enemy->Draw();
    _plane->Draw();
}

void WelcomeStage::Destroy() {
    delete _controller;
    delete _enemy;
    delete _plane;
    Logi("WelcomStage::Destroy", "WelcomeStage Destoryed");
}
