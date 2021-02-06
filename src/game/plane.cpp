#include "game/plane.hpp"

void DefaultPlaneDrawCb(Plane* plane) {
    plane->GetSprite()->Draw();
}

void DefaultPlaneUpdateCb(Plane* plane) {
    plane->GetSprite()->Update();
}

Plane::Plane(ISprite* sprite, PlaneProperty prop):_property(prop) {
    _sprite = sprite->CopyISprite();
    _sprite->Show();
}

void Plane::AddCharger(Charger* charger) {
    _chargers.push_back(charger);
}

void Plane::StartShoot() {
    for (Charger* charger : _chargers)
        charger->StartShoot();
}

void Plane::StopShoot() {
    for (Charger* charger : _chargers)
        charger->StopShoot();
}

void Plane::draw() {
    if (_sprite)
        _sprite->Draw();
    if (_draw_cb)
        _draw_cb(this);
}

void Plane::update() {
    for (auto charger : _chargers) {
        charger->SetPosition(GetPosition().x, GetPosition().y);
        charger->Update();
    }
    if (_sprite)
        _sprite->MoveTo(GetPosition().x, GetPosition().y);
    if (_update_cb)
        _update_cb(this);
}

Plane::~Plane() {
    for (Charger* charger : _chargers)
        delete charger;
}
