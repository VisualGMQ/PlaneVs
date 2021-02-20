#ifndef FONT_HPP
#define FONT_HPP
#include <string>
#include <vector>

#include <SDL_FontCache.h>

#include "base/tools.hpp"
#include "base/geo_math.hpp"
#include "base/log.hpp"
using std::string;
using std::vector;

enum FontStyle {
    FONT_STYLE_NORMAL,
    FONT_STYLE_BOLD,
    FONT_STYLE_UNDERLINE,
    FONT_STYLE_ITALIC,
    FONT_STYLE_OUTLINE,
    FONT_STYLE_STRIKETHROUGH
};

enum FontAlignment{
    FONT_ALIGN_LEFT,
    FONT_ALIGN_CENTER,
    FONT_ALIGN_RIGHT
};

int FontStyle2TTFStyle(FontStyle style);

class Font;

class Font final {
 public:
    static Font* Create(SDL_Renderer* render, string font_filename, int pt, FontStyle style);
    int GetPt() const { return _pt; }
    FC_Font* GetFont() { return _font; }
    static void DestroyAll();

    isize GetSizeByText(string text);
    void Draw(SDL_Renderer*, int x, int y, icolor color, scale s, const char* format, ...);
    void DrawBox(SDL_Renderer*, FontAlignment align, irect box, icolor color, scale s, const char* format, ...);
    ~Font();

 private:
    FC_Font* _font = nullptr;
    int _pt = 0;
    static vector<Font*> _instances;

    Font(SDL_Renderer* render, string font_filename, int pt, FontStyle style);
};

#endif

