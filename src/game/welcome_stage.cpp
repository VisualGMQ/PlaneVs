#include "game/welcome_stage.hpp"

void WelcomeStage::Init() {
    SetLogLevel(LOG_ALL);

    icolor key_color = {32, 32, 32, 255};

    PlaneProperty plane_prop;
    plane_prop.hp = 20;
    plane_prop.speed = 5;
    Sprite* sp = Sprite::Create("resources/enemy1.png", &key_color);
    _enemy = new Plane(sp, plane_prop);

    BulletProperty prop;
    prop.damage = 10;
    prop.speed = 8;
    prop.direction.x = 0;
    prop.direction.y = 1;
    Sprite* sprite = Sprite::Create("resources/enemy_bullet1.png", &key_color);
    Charger* charger = new Charger(sprite, prop, 10);
    _enemy->AddCharger(charger);
    _enemy->MoveTo(100, 100);
    _enemy->Show();

    _cache = SpriteSheetCache::Create("resources/player_plane.json", &key_color);
    sprite = _cache->CreateSprite("player_plane");
    _plane = new Plane(sprite, plane_prop);
    _plane->Show();
    _plane->MoveTo(400, 400);
    prop.direction.y = -1;
    sprite = _cache->CreateSprite("player_bullet");
    _plane->AddCharger(new Charger(sprite, prop, 10));

    _controller = PlaneKeyboardController::CreateController(_plane, SDLK_w, SDLK_s, SDLK_a, SDLK_d, SDLK_j, SDLK_k, SDLK_l);

    Bgm::Load("test/test_resources/Mind Control.ogg");
    Bgm::Play(0);
    Logi("WelcomeStage::WelcomeStage", "welcome stage inited");
}

void WelcomeStage::Step() {
    _controller->Control();
    _enemy->Update();
    _plane->Update();
    _enemy->Draw();
    _plane->Draw();
}

void WelcomeStage::Destroy() {
    delete _enemy;
    delete _plane;
    Logi("WelcomStage::Destroy", "WelcomeStage Destoryed");
}
