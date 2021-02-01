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

void Sprite::Draw() {
    if (IsShow() && _texture) {
        irect dst;
        dst.x = GetPosition().x;
        dst.y = GetPosition().y;
        dst.w = GetSize().w;
        dst.h = GetSize().h;
        _texture->Draw(&_clip_area, &dst, GetRotation(), _flip, &_color, &_key_color);
    } else {
        Log("Sprite:Draw texture is nullptr");
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

void Sprite::Flip(FlipEnum flip) {
    if (GetFlip() == FLIP_NONE) {
        SetFlip(flip);
    } else if (GetFlip() == FLIP_VERTICAL) {
        if (flip == FLIP_VERTICAL)
            SetFlip(FLIP_NONE);
        else if (flip == FLIP_HORIZENTAL)
            SetFlip(FLIP_BOTH);
        else if (flip == FLIP_BOTH)
            SetFlip(FLIP_HORIZENTAL);
    } else if (GetFlip() == FLIP_HORIZENTAL) {
        if (flip == FLIP_VERTICAL)
            SetFlip(FLIP_BOTH);
        else if (flip == FLIP_HORIZENTAL)
            SetFlip(FLIP_NONE);
        else if (flip == FLIP_BOTH)
            SetFlip(FLIP_VERTICAL);
    } else if (GetFlip() == FLIP_BOTH) {
        if (flip == FLIP_VERTICAL)
            SetFlip(FLIP_HORIZENTAL);
        else if (flip == FLIP_HORIZENTAL)
            SetFlip(FLIP_VERTICAL);
        else if (flip == FLIP_BOTH)
            SetFlip(FLIP_NONE);
    }
}
