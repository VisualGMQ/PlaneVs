#ifndef LABEL_HPP
#define LABEL_HPP
#include <string>
#include "uiobject.hpp"
#include "header.hpp"
using std::string;

class Label: public UIObject {
 public:
    Label() = default;
    void InitFont();
    void SetPosition(SDL_Point);
    void Paint() override;
    void Show();
    void Hide();
    SDL_Size GetSize() const;
    string GetText();
    void SetText(string text);
    virtual ~Label();
 protected:
 private:
    SDL_Point _position = {-1, -1};
    TTF_Font* _font = nullptr;
    bool _show = false;
    string _text;
    SDL_Texture* _texture = nullptr;
    SDL_Size _size = {0, 0};

    void paint();
    void updateTextureByText(string text);
};


#endif
