#include "engin/sprite.hpp"

forward_list<Sprite> Sprite::_instances;

Sprite* Sprite::Create(string filename, irect* area) {
    Sprite* sprite;
    sprite = Sprite::create();
    SDL_Surface* surface = IMG_Load(filename.c_str());
    sprite->init(Texture::Create(surface), area);
    SDL_FreeSurface(surface);
    return sprite;
}

Sprite* Sprite::create() {
    Sprite sprite;
    _instances.push_front(sprite);
    return &_instances.front();
}

void Sprite::draw() {
    if (_texture) {
        irect dst;
        dst.x = GetPosition().x;
        dst.y = GetPosition().y;
        dst.w = GetSize().w;
        dst.h = GetSize().h;
        _texture->Draw(&_clip_area, &dst, GetRotation(), GetFlip(), &_color, &_key_color);
    } else {
        Logw("Sprite::Draw", "Sprite:Draw texture is nullptr");
    }
}

void Sprite::init(ITexture* texture, irect* area) {
    if (!texture) {
        return;
    }
    _texture = texture;
    if (area) {
        _clip_area = *area;
    } else {
        _clip_area = {0, 0, _texture->GetSize().w, _texture->GetSize().h};
    }
    ResizeTo(_clip_area.w, _clip_area.h);
}

Sprite* Sprite::Copy() {
    Sprite* sprite = Sprite::create();
    *sprite = *this;
    return sprite;
}

ISprite* Sprite::CopyISprite() {
    return Copy();
}
