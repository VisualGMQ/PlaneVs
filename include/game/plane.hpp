#ifndef PLANE_HPP
#define PLANE_HPP
#include <vector>

#include "engin/animation.hpp"
#include "engin/sprite.hpp"
#include "engin/isprite.hpp"
#include "game/charger.hpp"
#include "game/objectable.hpp"
using std::vector;

struct PlaneProperty {
    int hp;
    int speed;
};

class Plane;

using PlaneDrawCb = void(*)(Plane*);
using UpdateDrawCb = void(*)(Plane*);

void DefaultPlaneDrawCb(Plane* plane);
void DefaultPlaneUpdateCb(Plane* plane);

/*
 * @brief This class present all planes(include player plane)
 */
class Plane: public Objectable {
 public:
    explicit Plane(ISprite* sprite, PlaneProperty prop);
    /*
     * @brief Plane will delete charge automatically, it means
     * you can pass a charger by `new`
     */
    void AddCharger(Charger* charge);
    int GetHp() const { return _property.hp; }
    void SetHp(int hp) { _property.hp = hp; }
    int GetSpeed() const { return _property.speed; }
    void SetSpeed(int speed) { _property.speed = speed; }
    void StartShoot();
    void StopShoot();

    /* net two function's area prepare for update()
     * the _sprites and _animations allow you to restore some sprite and use them in update */

    /* @brief add sprite to this plane */
    void AddSprite(Sprite* sprite) { _sprites.push_back(sprite); }
    /* @brief add animation to this plane */
    void AddAnimation(Animation* animation) { _animations.push_back(animation); }

    /* @brief set the isprite which will be draw */
    void SetDrawingSprite(ISprite* sprite) { _sprite = sprite; }
    ISprite* GetSprite() const { return _sprite; }

    virtual ~Plane();

 protected:
    void draw() override;
    void update() override;

 private:
    vector<Charger*> _chargers;
    vector<Sprite*> _sprites;
    vector<Animation*> _animations;
    PlaneDrawCb _draw_cb = DefaultPlaneDrawCb;
    UpdateDrawCb _update_cb = DefaultPlaneUpdateCb;

    PlaneProperty _property;
    ISprite* _sprite = nullptr;
};
#endif
