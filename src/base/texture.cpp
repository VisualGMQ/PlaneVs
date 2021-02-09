#include "base/texture.hpp"

vector<Texture*> Texture::_instances;

Texture* Texture::Create(SDL_Texture* texture) {
    Texture* t = new Texture(texture);
    _instances.push_back(t);
    return t;
}

Texture* Texture::CreateIndependent(SDL_Texture* texture) {
    return new Texture(texture);
}

Texture::Texture(SDL_Texture* texture) {
    Load(texture);
}

void Texture::Load(SDL_Texture* texture) {
    if (!texture) {
        invalid();
    } else {
        _texture = texture;
        SDL_QueryTexture(_texture, nullptr, nullptr, &_size.w, &_size.h);
        valid();
    }
}

isize Texture::GetSize() const {
    return _size;
}

void Texture::Draw(SDL_Renderer* render, irect* src_rect, irect* dst_rect, icolor* tex_color) const {
    Draw(render, src_rect, dst_rect, 0, FLIP_NONE, tex_color);
}

void Texture::Draw(SDL_Renderer* render, irect* src_rect, irect* dst_rect, float degree, FlipEnum flip, icolor* tex_color) const {
    SDL_Rect src_rect_;
    SDL_Rect dst_rect_;
#define IRECT2SDLRECT(sdl_rect, x_, y_, w_, h_) \
    sdl_rect.x = (x_); \
    sdl_rect.y = (y_); \
    sdl_rect.w = (w_); \
    sdl_rect.h = (h_);

    if (src_rect) {
        IRECT2SDLRECT(src_rect_, src_rect->x, src_rect->y, src_rect->w, src_rect->h)
    } else {
        IRECT2SDLRECT(src_rect_, 0, 0, GetSize().w, GetSize().h)
    }
    if (dst_rect) {
        IRECT2SDLRECT(dst_rect_, dst_rect->x, dst_rect->y, dst_rect->w, dst_rect->h)
    } else {
        IRECT2SDLRECT(dst_rect_, 0, 0, CanvaSize.w, CanvaSize.h)
    }
#undef IRECT2SDLRECT
    SDL_RendererFlip f = SDL_FLIP_NONE;
    if (flip == FLIP_VERTICAL)
        f = SDL_FLIP_VERTICAL;
    if (flip == FLIP_HORIZENTAL)
        f = SDL_FLIP_HORIZONTAL;
    if (flip == FLIP_BOTH)
        f = static_cast<SDL_RendererFlip>(SDL_FLIP_VERTICAL|SDL_FLIP_HORIZONTAL);
    if (tex_color) {
        SDL_SetTextureColorMod(_texture, tex_color->r, tex_color->g, tex_color->b);
        SDL_SetTextureAlphaMod(_texture, tex_color->a);
    }
    SDL_RenderCopyEx(render, _texture, &src_rect_, &dst_rect_, degree, nullptr, f);
}

Texture::~Texture() {
    SDL_DestroyTexture(_texture);
}

void Texture::Destroy() {
    auto it = std::find(_instances.begin(), _instances.end(), this);
    if (it != _instances.end()) {
        Texture* tmp = *it;
        _instances.erase(it);
        delete tmp;
    }
}
