#include "uiobject.hpp"

void UIObject::SetRender(SDL_Renderer* render) {
    _render = render;
}

SDL_Renderer* UIObject::GetRender() {
    if (!_render)
        SDL_Log("UI object's render is nullptr");
    return _render;
}

void UIObject::EventHandle(SDL_Event& event) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (SDL_BUTTON(event.button.button)&SDL_BUTTON_LEFT) {
            _mouse_left_pressing = true;
            onMouseLeftDown(event);
        }
        if(SDL_BUTTON(event.button.button)&SDL_BUTTON_RIGHT) {
            _mouse_right_pressing = true;
            onMouseRightDown(event);
        }
    }

    if (event.type == SDL_MOUSEBUTTONUP) {
        if (SDL_BUTTON(event.button.button)&SDL_BUTTON_LEFT) {
            onMouseLeftUp(event);
            _mouse_left_pressing = false;
        }
        if (SDL_BUTTON(event.button.button)&SDL_BUTTON_RIGHT) {
            _mouse_right_pressing = false;
            onMouseRightUp(event);
        }
    }


    if (event.type == SDL_MOUSEMOTION) {
        onMouseMotion(event);
        if (_mouse_left_pressing)
            onDrag(event);
    }

    if (event.type == SDL_DROPFILE) {
        onDropFile(event, event.drop.file);
    }

    if (event.type == SDL_KEYDOWN) {
        onKeyDown(event);
    }

    if (event.type == SDL_KEYUP) {
        onKeyUp(event);
    }
}
