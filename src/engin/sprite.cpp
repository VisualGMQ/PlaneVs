#include "engin/sprite.hpp"

vector<Sprite> Sprite::_instances;

Sprite* Sprite::Create(string filename, irect* area) {
    Sprite* sprite = Sprite::create();
    sprite->init(Texture::Create(filename), area);
    return sprite;
}

Sprite* Sprite::create() {
    Sprite sprite;
    _instances.push_back(std::move(sprite));
    return &_instances.back();
}
    
void Sprite::Draw() {
    if (IsShow() && _texture) {
        irect dst;
        dst.x = _position.x;
        dst.y = _position.y;
        dst.w = _size.w;
        dst.h = _size.h;
        _texture->Draw(&_clip_area, &dst, _degree, _flip, &_color, &_key_color);
    } else {
        Log("Sprite:Draw texture is nullptr");
    }
}

void Sprite::init(ITexture* texture, irect* area) {
    if (!texture)
        return;
    _texture = texture;
    if (area) {
        _clip_area = *area;
        _size = {area->w, area->h};
    } else {
        _clip_area = {0, 0, _texture->GetSize().w, _texture->GetSize().h};
        _size = _texture->GetSize();
    }
}
