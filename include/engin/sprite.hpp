#ifndef SPRITE_HPP
#define SPRITE_HPP
#include "base/drawable.hpp"
#include "base/geomentry.hpp"
#include "base/texture.hpp"
#include <glm/glm.hpp>

#include <string>
using glm::vec2;

class SpriteSheetCache;

class Sprite {
 public:
    friend SpriteSheetCache;

    static Sprite* Create(string filename, irect* area = nullptr);
    static vector<Sprite> _instances;

    void SetClipArea(irect area) { _clip_area = area; }
    irect GetClipArea() const { return _clip_area; }
    void SetRotation(float degree) { _degree = degree; }
    float GetRotation() const { return _degree; }
    void SetKeyColor(float r, float g, float b) {
        _key_color.r = r;
        _key_color.g = g;
        _key_color.b = b;
    }
    color GetKeyColor() const { return _key_color; }
    void SetColor(float r, float g, float b) {
        _color.r = r;
        _color.g = g;
        _color.b = b;
    }
    color GetColor() const { return _color; }
    void Move(int offset_x, int offset_y) {
        _position.x += offset_x;
        _position.y += offset_y;
    }
    void MoveTo(int x, int y) {
        _position.x = x;
        _position.y = y;
    }
    void Show() { _is_show = true; }
    void Hide() { _is_show = false; }
    bool IsShow() { return _is_show; }
    vec2 GetPosition() const { return _position; }
    void SetSize(int w, int h) { _size.w = w; _size.h = h; }
    isize GetSize() const { return _size; }
    void SetFlip(FlipEnum flip) { _flip = flip; }
    FlipEnum GetFlip() const { return _flip; }
    void Draw();
    virtual void Update() {}
    virtual ~Sprite() = default;

 private:
    vec2 _position;
    isize _size;
    color _color = {1, 1, 1, 1};
    color _key_color = {-1, -1, -1, 1};
    ITexture* _texture = nullptr;
    FlipEnum _flip = FLIP_NONE;
    irect _clip_area;
    bool _is_show = false;
    float _degree = 0;

    static Sprite* create();
    Sprite() = default;
    void init(ITexture* texture, irect* area);
};

#endif

