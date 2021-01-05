#include "label.hpp"

void Label::SetPosition(SDL_Point position) {
    _position = position;
}

void Label::Show() {
    _show = true;
}

void Label::Hide() {
    _show = false;
}

string Label::GetText() {
    return _text;
}

SDL_Size Label::GetSize() const {
    return _size;
}

void Label::SetText(string text) {
    _text = text;
    updateTextureByText(text);
}

void Label::updateTextureByText(string text) {
    SDL_Surface* surface = TTF_RenderUTF8_Blended(_font, _text.c_str(), {0, 0, 0, 255});
    SDL_Rect rect = {_position.x-5, _position.y-5, surface->w+10, surface->h+10};
    if (_texture) {
        SDL_DestroyTexture(_texture);
    }
    _texture = SDL_CreateTextureFromSurface(GetRender(), surface);
    _size.w = surface->w;
    _size.h = surface->h;
    SDL_FreeSurface(surface);
}

void Label::Paint() {
    if (_show) {
        paint();
    }
}

void Label::paint() {
    auto render = GetRender();
    const int padding_w = 3, padding_h = 3;
    SDL_Rect texture_rect = {_position.x - _size.w/2, _position.y - _size.h/2, _size.w, _size.h},
             frame_rect = {texture_rect.x - padding_w, texture_rect.y - padding_h,
                           texture_rect.w + padding_w*2, texture_rect.h + padding_h*2};
    SDL_SetRenderDrawColor(render, 240, 240, 0, 255);
    SDL_RenderFillRect(render, &frame_rect);

    SDL_RenderCopy(render, _texture, nullptr, &texture_rect);


    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
    SDL_RenderDrawRect(render, &frame_rect);
}

void Label::InitFont() {
    _font = TTF_OpenFont("resources/SimHei.ttf", 13);
    if (!_font) {
        SDL_Log("font load failed");
    }
}

Label::~Label() {
    TTF_CloseFont(_font);
}
