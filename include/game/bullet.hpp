#ifndef BULLET_HPP
#define BULLET_HPP
#include <glm/glm.hpp>

#include "engin/isprite.hpp"
#include "game/objectable.hpp"

struct BulletProperty {
    int damage;
    int speed;
    glm::vec2 direction;
};

class Bullet: public Objectable {
 public:
    explicit Bullet(ISprite* sprite, BulletProperty property);
    int GetDamage() const { return _property.damage; }
    void Show() override;
    void Hide() override;
    bool IsShow() override;
    void MoveTo(int x, int y) override;
    void MoveTo(ivec2 pos) override;
    void MoveBy(int offset_x, int offset_y) override;
    void MoveBy(ivec2 offset) override;

 protected:
    void update() override;
    void draw() override;

 private:
    BulletProperty _property;
    ISprite* _sprite = nullptr; 
    ivec2 _oldposition;
};

#endif
