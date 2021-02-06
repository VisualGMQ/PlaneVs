#ifndef ENGIN_SPRITE_HPP
#define ENGIN_SPRITE_HPP

#include <string>
#include <forward_list>

#include <glm/glm.hpp>

#include "base/tools.hpp"
#include "base/texture.hpp"
#include "base/geomentry.hpp"
#include "engin/movable.hpp"
#include "engin/rotatable.hpp"
#include "engin/resizable.hpp"
#include "engin/flipable.hpp"
#include "engin/isprite.hpp"
using std::string;
using std::forward_list;
using glm::vec2;

class SpriteSheetCache;

class Sprite: virtual public Resizable, public Rotatable, public ISprite {
 public:
    friend SpriteSheetCache;

    static Sprite* Create(string filename, irect* area = nullptr);

    void SetClipArea(irect area) { _clip_area = area; }
    irect GetClipArea() const { return _clip_area; }
    void SetKeyColor(int r, int g, int b) {
        _key_color.r = Clamp(0, 255, r);
        _key_color.g = Clamp(0, 255, g);
        _key_color.b = Clamp(0, 255, b);
    }
    icolor GetKeyColor() const { return _key_color; }
    void SetColor(int r, int g, int b) {
        _color.r = Clamp(0, 255, r);
        _color.g = Clamp(0, 255, g);
        _color.b = Clamp(0, 255, b);
    }
    void SetOpacity(int value) {
        _color.a = Clamp(0, 255, value);
    }
    int GetOpacity()  const { return _color.a; }
    isize GetOriginSize() {
        if (_texture)
            return _texture->GetSize();
        return isize();
    }
    icolor GetColor() const { return _color; }
    Sprite* Copy();
    ISprite* CopyISprite() override;
    virtual ~Sprite() = default;

 protected:
    void update() override {}
    void draw() override;

 private:
    icolor _color = {255, 255, 255, 255};
    icolor _key_color = {-255, -255, -255, 0};
    ITexture* _texture = nullptr;
    irect _clip_area;

    static forward_list<Sprite> _instances;

    Sprite() = default;
    void init(ITexture* texture, irect* area);
    static Sprite* create();
};

#endif

