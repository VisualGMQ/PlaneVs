#include "engin/sprite.hpp"

forward_list<Sprite> Sprite::_instances;

Sprite* Sprite::Create(string filename, icolor* key_color, irect* area) {
    SDL_Renderer* render = Director::GetInstance()->GetRender();
    Sprite* sprite;
    sprite = Sprite::create();
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if (key_color)
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, key_color->r, key_color->g, key_color->b));
    SDL_Texture* texture = SDL_CreateTextureFromSurface(render, surface);
    SDL_FreeSurface(surface);
    sprite->init(Texture::Create(texture), area);
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
        dst.w = GetSize().w;
        dst.h = GetSize().h;
        dst.x = GetPosition().x - dst.w/2;
        dst.y = GetPosition().y - dst.h/2;
        _texture->Draw(Director::GetInstance()->GetRender(), &_clip_area, &dst, GetRotation(), GetFlip(), &_color);
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

void Sprite::SetColor(int r, int g, int b) {
    _color.r = r;
    _color.g = g;
    _color.b = b;
    _color.a = 255;
}

Sprite* Sprite::Copy() {
    Sprite* sprite = Sprite::create();
    *sprite = *this;
    return sprite;
}

ISprite* Sprite::CopyISprite() {
    return Copy();
}
