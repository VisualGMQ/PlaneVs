#include "game/bullet.hpp"

Bullet::Bullet(ISprite* sprite, BulletProperty property):_property(property), _oldposition(ivec2(0, 0)) {
    _property.direction = glm::normalize(_property.direction);
    _sprite = sprite->CopyISprite();
    _sprite->Show();
}

void Bullet::Show() {
    if (_sprite)
        _sprite->Show();
}

void Bullet::Hide() {
    if (_sprite)
        _sprite->Hide();
}

bool Bullet::IsShow() {
    if (_sprite)
        return _sprite->IsShow();
    return false;
}

void Bullet::MoveTo(int x, int y) {
    _oldposition = GetPosition();
    Movable::MoveTo(x, y);
    if (_sprite)
        _sprite->MoveTo(x, y);
}

void Bullet::MoveTo(ivec2 pos) {
    MoveTo(pos.x, pos.y);
}

void Bullet::MoveBy(int offset_x, int offset_y) {
    _oldposition = GetPosition();
    Movable::MoveBy(offset_x, offset_y);
    if (_sprite)
        _sprite->MoveBy(offset_x, offset_y);
}

void Bullet::MoveBy(ivec2 offset) {
    MoveBy(offset.x, offset.y);
}

void Bullet::update() {
    _sprite->Update();
    MoveBy(round(_property.speed*_property.direction.x), round(_property.speed*_property.direction.y));
}

void Bullet::draw() {
    _sprite->Draw();
}
