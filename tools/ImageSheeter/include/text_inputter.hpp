#ifndef TEXT_INPUTTER_HPP
#define TEXT_INPUTTER_HPP
#include "SDL.h"
#include "SDL_ttf.h"
#include "header.hpp"

class TextInputter final{
 public:
     TextInputter() = default;
     void InitResources(string font_filename, int font_size, SDL_Renderer* render);
     SDL_Point GetPosition() const;
     void SetPosition(int x, int y);
     SDL_Color GetTextColor() const;
     void SetTextColor(SDL_Color color);
     void EventHandle(SDL_Event& event);
     void Update();
     ~TextInputter();

 private:
     struct Text {
         SDL_Texture* texture;
         SDL_Size size = {0, 0};
         string text;
     }_inputted_text;
     TTF_Font* _font = nullptr;
     SDL_Renderer* _render;
     SDL_Color _text_color = {255, 255, 0, 255};
     SDL_Point _position = {0, 0};

     SDL_Renderer* getRender();
     void genText(Text& text_info, SDL_Color color);
};


#endif

