#ifndef OBJECTABLE_HPP
#define OBJECTABLE_HPP
#include "engin/movable.hpp"
#include "engin/flipable.hpp"
#include "engin/updatable.hpp"
#include "engin/drawable.hpp"
#include "engin/visiable.hpp"

class Objectable: virtual public Flipable, public Movable, public Updatable, public Drawable, public Visiable {
 public:
    void Update() override {
        if (IsShow())
            update();
    }
    void Draw() override {
        if (IsShow())
            draw();
    }
    
    ~Objectable() = default;

 protected:
    virtual void update() = 0;
    virtual void draw() = 0;
};

#endif

