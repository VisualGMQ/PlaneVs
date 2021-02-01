#ifndef TEXT_HPP
#define TEXT_HPP
#include <string>
#include <forward_list>
#include <vector>

#include <SDL_ttf.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "base/log.hpp"
#include "base/geomentry.hpp"
#include "base/tools.hpp"
#include "base/texture.hpp"
#include "base/destroyable.hpp"

using std::string;
using std::forward_list;
using std::vector;

class Font final {
 public:
    static Font* Create(string font_filename, int pt);
    static void DestroyAll();

    int GetHeight() const;
    SDL_Surface* RenderSurface(string text);
    ~Font();

 private:
    TTF_Font* _font = nullptr;

    static vector<Font*> _instances;

    Font(string font_filename, int pt);
};

class Text final: public Destroyable {
 public:
    static Text* Create(Font* font, string text, icolor color);

    void SetText(string text);
    icolor GetColor() const { return _color; }
    void SetColor(int r, int g, int b);
    string GetText() const;
    void Draw(int x, int y);
    void Destroy() override;
    virtual ~Text() = default;

 private:
    string _text;
    Font* _font = nullptr;
    icolor _color;
    isize _size;
    Texture* _texture = nullptr;

    Text(Font* font, string text, icolor color);
    void initGLBuffer();

    static forward_list<Text> _instances;
};

#endif

