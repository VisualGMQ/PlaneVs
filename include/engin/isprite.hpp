#ifndef ISPRITE_HPP
#define ISPRITE_HPP
#include "engin/updatable.hpp"
#include "engin/drawable.hpp"
#include "engin/visiable.hpp"
#include "engin/movable.hpp"
#include "engin/flipable.hpp"

class ISprite: virtual public Flipable, public Movable, public Updatable, public Drawable, public Visiable {
 public:
    void Update() override {
        if (IsShow())
            update();
    }
    void Draw() override {
        if (IsShow())
            draw();
    }
    
    virtual ISprite* CopyISprite() = 0;

    ~ISprite() = default;

 protected:
    virtual void update() = 0;
    virtual void draw() = 0;
};

#endif

