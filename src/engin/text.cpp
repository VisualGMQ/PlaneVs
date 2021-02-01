#include "engin/text.hpp"

vector<Font*> Font::_instances;

Font* Font::Create(string font_filename, int pt) {
    _instances.push_back(new Font(font_filename, pt));
    return _instances.back();
}

void Font::DestroyAll() {
    for (Font* font : _instances)
        delete font;
    _instances.clear();
}

Font::Font(string font_filename, int pt) {
    _font = TTF_OpenFont(font_filename.c_str(), pt);
}

SDL_Surface* Font::RenderSurface(string text) {
    SDL_Color c = {255, 255, 255, 255};
    return TTF_RenderUTF8_Blended(_font, text.c_str(), c);
}

Font::~Font() {
    if (_font)
        TTF_CloseFont(_font); 
}

forward_list<Text> Text::_instances;

Text* Text::Create(Font* font, string text, icolor color) {
    Text instance(font, text, color);
    _instances.push_front(instance);
    return &_instances.front();
}

Text::Text(Font* font, string text, icolor color) {
    _font = font;
    _texture = Texture::CreateIndependent(nullptr);
    SetText(text);
    SetColor(color.r, color.g, color.b);
    initGLBuffer();
}

void Text::initGLBuffer() {
}

void Text::SetText(string text) {
    _text = text;
    SDL_Surface* surface = _font->RenderSurface(_text);
    if (_texture) {
        _texture->Load(surface);
        _size.w = surface->w;
        _size.h = surface->h;
    }
    SDL_FreeSurface(surface);
}

string Text::GetText() const {
    return _text;
}

void Text::SetColor(int r, int g, int b) {
    _color.r = r;
    _color.g = g;
    _color.b = b;
    _color.a = 255;
}

void Text::Draw(int x, int y) {
    if (_texture) {
        irect dst_rect = {x, y, _size.w, _size.h};
        _texture->Draw(nullptr, &dst_rect, &_color, nullptr);
    }
}

void Text::Destroy() {
    _instances.remove_if([&](Text& text){ return &text == this; });
}
