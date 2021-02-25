#include "engin/text.hpp"
forward_list<Text> Text::_instances;

Text* Text::Create(Font* font, string text, icolor color) {
    Text instance(font, text, color);
    _instances.push_front(instance);
    return &_instances.front();
}

Text::Text(Font* font, string text, icolor color) {
    _font = font;
    SetText(text.c_str());
    SetColor(color.r, color.g, color.b, color.a);
}

isize Text::GetSize() {
    if (_should_gen_texture) {
        regenerateTexture();
        _should_gen_texture = false;
    }
    if (_texture)
        return _texture->GetSize();
    return {0, 0};
}

void Text::SetText(const char* format, ...) {
    if (strcmp(format, _text.c_str()) != 0) {
        char buf[1024] = {0};
        VARARGS2BUF(buf, sizeof(buf)-1, format);
        _text = buf;
        _should_gen_texture = true;
    }
}

string Text::GetText() const {
    return _text;
}

void Text::SetColor(int r, int g, int b, int a) {
    if (_color.r != r || _color.g != g || _color.b != b || _color.a != a) {
        _color.r = r;
        _color.g = g;
        _color.b = b;
        _color.a = a;
        _should_gen_texture = true;
    }
}

void Text::Draw(int x, int y) {
    auto render = Director::GetInstance()->GetRender();
    if (_should_gen_texture || !_texture) {
        regenerateTexture();
        if (_should_gen_texture) {
            _should_gen_texture = false;
        }
    }
    if (_texture) {
        irect dst_rect;
        isize size = GetSize();
        dst_rect.w = size.w;
        dst_rect.h = size.h;
        dst_rect.x = x-size.w/2;
        dst_rect.y = y-size.h/2;
        _texture->Draw(render, nullptr, &dst_rect, &_color);
    }
}

void Text::regenerateTexture() {
    if (!_texture) {
        delete _texture;
    }
    _texture = _font->BlendSurface(Director::GetInstance()->GetRender(), _color, _text.c_str());
}

Text::~Text() {
    delete _texture;
}

void Text::Destroy() {
    _instances.remove_if([&](Text& text){ return &text == this; });
}
