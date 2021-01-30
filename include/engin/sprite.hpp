#ifndef ENGIN_SPRITE_HPP
#define ENGIN_SPRITE_HPP

#include <string>
#include <forward_list>

#include <glm/glm.hpp>

#include "base/flip.hpp"
#include "base/texture.hpp"
#include "base/geomentry.hpp"
#include "engin/object.hpp"
#include "engin/drawable.hpp"
#include "engin/updatable.hpp"
#include "engin/visiable.hpp"
using std::string;
using std::forward_list;
using glm::vec2;

class SpriteSheetCache;

class Sprite: virtual public Object, public Drawable, public Updatable, public Visiable {
 public:
    friend SpriteSheetCache;

    static Sprite* Create(string filename, irect* area = nullptr);

    void Flip(FlipEnum flip);
    void SetFlip(FlipEnum flip) { _flip = flip; }
    FlipEnum GetFlip() const { return _flip; }
    void SetClipArea(irect area) { _clip_area = area; }
    irect GetClipArea() const { return _clip_area; }
    void SetKeyColor(int r, int g, int b) {
        _key_color.r = r;
        _key_color.g = g;
        _key_color.b = b;
    }
    icolor GetKeyColor() const { return _key_color; }
    void SetColor(int r, int g, int b) {
        _color.r = r;
        _color.g = g;
        _color.b = b;
    }
    void SetOpacity(int value) {
        _color.a = value;
    }
    int GetOpacity()  const { return _color.a; }
    isize GetOriginSize() {
        if (_texture)
            return _texture->GetSize();
        return isize();
    }
    icolor GetColor() const { return _color; }
    void Draw() override;
    void Update() override {}
    virtual ~Sprite() = default;

 private:
    icolor _color = {255, 255, 255, 255};
    icolor _key_color = {-255, -255, -255, 255};
    ITexture* _texture = nullptr;
    irect _clip_area;
    FlipEnum _flip = FLIP_NONE;

    static forward_list<Sprite> _instances;

    Sprite() = default;
    void init(ITexture* texture, irect* area);
    static Sprite* create();
};

#endif

