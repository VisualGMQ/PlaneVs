#include "base/font.hpp"

int FontStyle2TTFStyle(FontStyle style) {
    switch (style) {
        case FONT_STYLE_NORMAL:
            return TTF_STYLE_NORMAL;
        case FONT_STYLE_BOLD:
            return TTF_STYLE_BOLD;
        case FONT_STYLE_ITALIC:
            return TTF_STYLE_ITALIC;
        case FONT_STYLE_OUTLINE:
            return TTF_STYLE_OUTLINE;
        case FONT_STYLE_UNDERLINE:
            return TTF_STYLE_OUTLINE;
        case FONT_STYLE_STRIKETHROUGH:
            return TTF_STYLE_STRIKETHROUGH;
        default:
            return TTF_STYLE_NORMAL;
    }
}

vector<Font*> Font::_instances;

Font* Font::Create(SDL_Renderer* render, string font_filename, int pt, FontStyle style) {
    _instances.push_back(new Font(render, font_filename, pt, style));
    return _instances.back();
}

void Font::DestroyAll() {
    for (Font* font : _instances)
        delete font;
    _instances.clear();
}

Font::Font(SDL_Renderer* render, string font_filename, int pt, FontStyle style):_pt(pt) {
    _font = FC_CreateFont();
    FC_LoadFont(_font, render, font_filename.c_str(), pt, FC_MakeColor(0, 0, 0, 255), FontStyle2TTFStyle(style));
}

isize Font::GetSizeByText(string text) {
    isize s;
    s.w = FC_GetWidth(_font, text.c_str());
    s.h = FC_GetHeight(_font, text.c_str());
    return s;
}

void Font::Draw(SDL_Renderer* render, int x, int y, icolor color, scale s, const char* format, ...) {
    FC_Effect effect;
    effect.color.r = color.r;
    effect.color.g = color.g;
    effect.color.b = color.b;
    effect.color.a = color.a;
    effect.alignment = FC_ALIGN_CENTER;
    effect.scale.x = s.x;
    effect.scale.y = s.y;

    char buf[1024];
    VARARGS2BUF(buf, sizeof(buf)-1, format);
    FC_DrawEffect(_font, render, x, y-GetSizeByText(buf).h/2, effect, buf);
}

void Font::DrawBox(SDL_Renderer* render, FontAlignment align, irect box, icolor color, scale s, const char* format, ...) {
    FC_Effect effect;
    effect.color.r = color.r;
    effect.color.g = color.g;
    effect.color.b = color.b;
    effect.color.a = color.a;
    if (align == FONT_ALIGN_LEFT)
        effect.alignment = FC_ALIGN_LEFT;
    else if (align == FONT_ALIGN_CENTER)
        effect.alignment = FC_ALIGN_CENTER;
    else if (align == FONT_ALIGN_RIGHT)
        effect.alignment = FC_ALIGN_RIGHT;
    effect.scale.x = s.x;
    effect.scale.y = s.y;

    char buf[1024];
    VARARGS2BUF(buf, sizeof(buf)-1, format);

    SDL_Rect rect = IRect2SDL_Rect(box);
    FC_DrawBoxEffect(_font, render, rect, effect, buf);
}

Font::~Font() {
    if (_font)
        FC_FreeFont(_font);
}
