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
    if (_font) {
        return _font->GetSizeByText(_text);
    }
    return {0, 0};
}

void Text::SetText(const char* format, ...) {
    char buf[1024] = {0};
    VARARGS2BUF(buf, sizeof(buf)-1, format);
    _text = buf;
}

string Text::GetText() const {
    return _text;
}

void Text::SetColor(int r, int g, int b, int a) {
    _color.r = r;
    _color.g = g;
    _color.b = b;
    _color.a = a;
}

void Text::Draw(int x, int y) {
    if (_font) {
        _font->Draw(Director::GetInstance()->GetRender(), x, y, _color, {1, 1}, _text.c_str());
    }
}

void Text::Destroy() {
    _instances.remove_if([&](Text& text){ return &text == this; });
}
