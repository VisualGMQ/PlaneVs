#ifndef TEXT_HPP
#define TEXT_HPP
#include <string>
#include <forward_list>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "base/log.hpp"
#include "base/geo_math.hpp"
#include "base/tools.hpp"
#include "base/texture.hpp"
#include "base/destroyable.hpp"
#include "base/font.hpp"
#include "engin/director.hpp"

using std::string;
using std::forward_list;
using std::vector;
class Text final: public Destroyable {
 public:
    static Text* Create(Font* font, string text, icolor color);

    void SetText(const char* format, ...);
    icolor GetColor() const { return _color; }
    void SetColor(int r, int g, int b, int a);
    isize GetSize();
    string GetText() const;
    void Draw(int x, int y);
    void Destroy() override;
    virtual ~Text();

 private:
    string _text;
    Font* _font = nullptr;
    Texture* _texture = nullptr;
    icolor _color;
    bool _should_gen_texture = false;

    void regenerateTexture();

    Text(Font* font, string text, icolor color);

    static forward_list<Text> _instances;
};

#endif

