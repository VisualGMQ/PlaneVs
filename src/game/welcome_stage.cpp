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

    ControllerButtonMap key_map;
    key_map.left = SDLK_a;
    key_map.right = SDLK_d;
    key_map.up = SDLK_w;
    key_map.down = SDLK_s;
    key_map.shoot = SDLK_j;
    key_map.bomb = SDLK_k;
    key_map.blast = SDLK_o;
    KeyboardController* controller = KeyboardController::Create(_plane, key_map);
    Director::GetInstance()->SetController(controller);
}

void WelcomeStage::Step() {
    _enemy->Update();
    _plane->Update();
    _enemy->Draw();
    _plane->Draw();
}

void WelcomeStage::Destroy() {
    Director::GetInstance()->SetController(nullptr);
    delete _enemy;
    delete _plane;
    Logi("WelcomStage::Destroy", "WelcomeStage Destoryed");
}
