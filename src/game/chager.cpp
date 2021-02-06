#include "game/charger.hpp"

Charger::Charger(ISprite* bullet_sprite, BulletProperty bullet_prop, int delay_time) {
    _property.delay = delay_time;
    _property.position.x = 0;
    _property.position.y = 0;

    isize size = {CanvaSize.w+200, CanvaSize.h+200};
    int time = size.h/bullet_prop.speed;

    int bullet_num = time/delay_time;
    for (int i = 0; i < bullet_num; i++) {
        Bullet* bullet = new Bullet(bullet_sprite, bullet_prop);
        _bullets.push_back({false, bullet});
    }
}

void Charger::Update() {
    for (auto& wrap : _bullets) {
        if (wrap.alive) {
            ivec2 pos = wrap.bullet->GetPosition();
            if (pos.x <= -100 || pos.y <= -100 ||
                pos.x >= CanvaSize.w+100 || pos.y >= CanvaSize.h+100) {
                wrap.bullet->Hide();
                wrap.alive = false;
            }
            wrap.bullet->Draw();
            wrap.bullet->Update();
        }
    }
        
    if (_time_count <= _property.delay) {
        _time_count++;
    } else {
        if (_is_shooting) {
            _time_count = 0;
            for (auto& wrap : _bullets) {
                if (!wrap.alive) {
                    wrap.bullet->MoveTo(_property.position.x, _property.position.y);
                    wrap.alive = true;
                    wrap.bullet->Show();
                    break;
                }
            }
        }
    }
}

Charger::~Charger() {
    for (BulletWrap& wrap : _bullets)
        delete wrap.bullet;
    _bullets.clear();
}
