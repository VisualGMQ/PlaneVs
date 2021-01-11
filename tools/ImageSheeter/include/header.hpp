#ifndef HEADER_HPP
#define HEADER_HPP
#include "SDL.h"
#include <string>
using std::string;

struct SDL_Size {
    int w;
    int h;
};

struct TextureInfo {
    string name;
    SDL_Texture* texture;
    SDL_Surface* surface;   // to allow SDL save image
    SDL_Point position;
    SDL_Size size;

    SDL_Rect GetRectByCenter() const {
        return {position.x - size.w/2, position.y - size.h/2, size.w, size.h};
    }

    SDL_Rect GetRect() const {
        return {position.x, position.y, size.w, size.h};
    }

    bool IsClicked(SDL_Point& mouse_position) {
        SDL_Rect rect = GetRectByCenter();
        return SDL_PointInRect(&mouse_position, &rect);
    }
};

enum YesNoMsgBoxRet {
    YESNOMSG_YES,
    YESNOMSG_NO,
    YESNOMSG_UNKNOWN,
    YESNOMSG_ERROR
};

YesNoMsgBoxRet ShowYesNoMessageBox(string title, string text, string yes_msg, string no_msg);

#endif

