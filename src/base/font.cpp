#include "base/font.hpp"

int FontStyle2TTFStyle(FontStyle style) {
    switch (style) {
        case FONT_STYLE_NORMAL:
            return TTF_STYLE_NORMAL;
        case FONT_STYLE_BOLD:
            return TTF_STYLE_BOLD;
        case FONT_STYLE_ITALIC:
            return TTF_STYLE_ITALIC;
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

int Font::GetHeight() const {
    if (_font)
        return TTF_FontHeight(_font);
    return 0;
}

void Font::DestroyAll() {
    for (Font* font : _instances)
        delete font;
    _instances.clear();
}

Font::Font(SDL_Renderer* render, string font_filename, int pt, FontStyle style):_pt(pt) {
    _font = TTF_OpenFont(font_filename.c_str(), pt);
    if (!_font) {
        Logw("can't open font %s, %s", font_filename.c_str(), TTF_GetError());
    }
}

Texture* Font::BlendSurface(SDL_Renderer* render, icolor color, const char* format, ...) {
    char buffer[1024] = {0};
    VARARGS2BUF(buffer, sizeof(buffer), format);
    if (buffer[0] == '\0') {
        return nullptr;
    }
    SDL_Surface* surface = nullptr;
    if (_font) {
        surface = TTF_RenderUTF8_Blended(_font, buffer, IColor2SDL_Color(color));
    }
    if (!surface) {
        Loge("Font::BlendSurface", "surface create failed");
    }
    Texture* texture = Texture::CreateIndependent(SDL_CreateTextureFromSurface(render, surface));
    if (!texture) {
        Loge("Font::BlendSurface", "surface convert to texture failed");
    }
    SDL_FreeSurface(surface);
    return texture;
}

Font::~Font() {
    if (_font) {
        TTF_CloseFont(_font);
    }
}
