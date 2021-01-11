#include "text_inputter.hpp"
void TextInputter::InitResources(string font_filename, int font_size, SDL_Renderer* render) {
    _render = render;
    _font = TTF_OpenFont(font_filename.c_str(), font_size);
}

SDL_Point TextInputter::GetPosition() const {
    return _position;
}

void TextInputter::SetPosition(int x, int y) {
    _position.x = x;
    _position.y = y;
}

SDL_Color TextInputter::GetTextColor() const {
    return _text_color;
}

void TextInputter::SetTextColor(SDL_Color color) {
    _text_color = color;
}

void TextInputter::EventHandle(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_BACKSPACE) {
            _inputted_text.text.pop_back();
            if (_inputted_text.text.empty()) {
                SDL_DestroyTexture(_inputted_text.texture);
                _inputted_text.texture = nullptr;
            } else {
                genText(_inputted_text, _text_color);
            }
        }
    }
    if (event.type == SDL_TEXTINPUT) {
        _inputted_text.text += event.text.text;
        genText(_inputted_text, _text_color);
        SDL_Rect rect = {_position.x, _position.y, 800, _inputted_text.size.h+10};
        SDL_SetTextInputRect(&rect);
    }
}

void TextInputter::Update() {
    auto render = getRender();
    SDL_Rect rect = {_position.x, _position.y, _inputted_text.size.w, _inputted_text.size.h};
    SDL_RenderCopy(render, _inputted_text.texture, nullptr, &rect);
}

TextInputter::~TextInputter() {
    SDL_DestroyTexture(_inputted_text.texture);
    TTF_CloseFont(_font);
}



SDL_Renderer* TextInputter::getRender() {
    if (!_render) {
        SDL_Log("TextInput render empty");
    }
    return _render;
}

void TextInputter::genText(Text& text_info, SDL_Color color) {
    auto render = getRender();
    if (text_info.texture)
        SDL_DestroyTexture(text_info.texture);
    SDL_Surface* surface = TTF_RenderUTF8_Blended(_font, text_info.text.c_str(), color);
    text_info.size.w = surface->w;
    text_info.size.h = surface->h;
    text_info.texture = SDL_CreateTextureFromSurface(render, surface);
    SDL_FreeSurface(surface);
}
