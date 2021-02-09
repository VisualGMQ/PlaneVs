#ifndef CHARGER_HPP
#define CHARGER_HPP
#include <vector>

#include "base/log.hpp"
#include "base/config.hpp"
#include "base/geo_math.hpp"
#include "game/bullet.hpp"
using std::vector;

struct ChargerProperty {
    ivec2 position;
    int delay;  /* the time between two bullet shoot */
};

class Charger {
 public:
    Charger(ISprite* bullet_sprite, BulletProperty bullet_prop, int delay_time);
    void StartShoot() { _is_shooting = true; }
    void StopShoot() { _is_shooting = false; }
    void SetPosition(int x, int y) {
        _property.position.x = x;
        _property.position.y = y;
    }
    ivec2 GetPosition() const { return _property.position; }
    void Update();
    ~Charger();

 private:
    struct BulletWrap {
        bool alive = false;
        Bullet* bullet = nullptr;
    };
    vector<BulletWrap> _bullets;
    ChargerProperty _property;
    int _time_count = 0;
    bool _is_shooting = false;
};

#endif

