#include "engin/ui/ui.hpp"

SDL_Renderer* imgui::gRender = nullptr;
SDL_Texture* imgui::gCanva = nullptr;
imgui::UIState imgui::uistate = {imgui::ID_NONE, imgui::ID_NONE, imgui::ID_NONE, imgui::ID_NONE, glm::ivec2(0, 0), input::BUTTON_RELEASING, input::BUTTON_RELEASING, input::BUTTON_RELEASING, 0, imgui::ID_NONE, SDLK_UNKNOWN, KMOD_NONE, "", false};

void imgui::Init(SDL_Renderer* renderer) {
    gRender = renderer;
    Font* font = Font::Create(gRender, "resources/SimHei.ttf", 25, FONT_STYLE_NORMAL);
    Logi("imgui::Init", "font created");
    gCanva = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, CanvaSize.w, CanvaSize.h);
    Logi("imgui::Init", "gCanva created");
}

void imgui::EventHandle(SDL_Event& event) {
    if (event.type == SDL_MOUSEMOTION) {
        uistate.mouse_position.x = event.motion.x;
        uistate.mouse_position.y = event.motion.y;
    }
#define BUTTONDOWN_STATE_CHANGE(button) \
    do { \
        if (button == input::BUTTON_RELEASING || button == input::BUTTON_RELEASED) \
            button = input::BUTTON_PRESSED; \
    }while(0)
// END OF BUTTONDOWN_STATE_CHANGE

    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            BUTTONDOWN_STATE_CHANGE(uistate.left_button_state);
        }
        if (event.button.button == SDL_BUTTON_MIDDLE) {
            BUTTONDOWN_STATE_CHANGE(uistate.middle_button_state);
        }
        if (event.button.button == SDL_BUTTON_RIGHT) {
            BUTTONDOWN_STATE_CHANGE(uistate.right_button_state);
        }
    }
#undef BUTTONDOWN_STATE_CHANGE

#define BUTTONUP_STATE_CHANGE(button) \
    do { \
        if (button == input::BUTTON_PRESSED || button == input::BUTTON_PRESSING) { \
            button = input::BUTTON_RELEASED; \
        } \
    }while(0)
// END OF BUTTONUP_STATE_CHANGE

    if (event.type == SDL_MOUSEBUTTONUP) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            BUTTONUP_STATE_CHANGE(uistate.left_button_state);
        }
        if (event.button.button == SDL_BUTTON_MIDDLE) {
            BUTTONUP_STATE_CHANGE(uistate.middle_button_state);
        }
        if (event.button.button == SDL_BUTTON_RIGHT) {
            BUTTONUP_STATE_CHANGE(uistate.right_button_state);
        }
    }
#undef BUTTONUP_STATE_CHANGE

    if (event.type == SDL_MOUSEWHEEL) {
        int sign = 1;
        if (event.wheel.direction == SDL_MOUSEWHEEL_FLIPPED)
            sign = -1;
        uistate.wheel = sign*event.wheel.y;
    }
    if (event.type == SDL_TEXTINPUT) {
        uistate.input_text = event.text.text;
        uistate.inputted = true;
    }
    if (event.type == SDL_KEYDOWN) {
        uistate.keycode = event.key.keysym.sym;
        uistate.keymode = event.key.keysym.mod;
    }
    if (event.type == SDL_KEYUP) {
        Uint16 mod = event.key.keysym.mod;
        if (mod != KMOD_NONE && mod == uistate.keymode) {
            uistate.keymode = KMOD_NONE;
        }
    }
}

void imgui::ClearFocus() {
    uistate.active_item = ID_NONE;
}

void imgui::Prepare() {
    uistate.hot_item = ID_NONE;
    uistate.wheel = 0;
    uistate.keycode = SDLK_UNKNOWN;
    uistate.inputted = false;
}

void imgui::Finish() {
    uistate.old_hot_item = uistate.hot_item;
    uistate.old_active_item = uistate.active_item;
#define CHANGE_BUTTON_STATE(button) \
    do { \
        if (button == input::BUTTON_PRESSED) \
            button = input::BUTTON_PRESSING; \
        if (button == input::BUTTON_RELEASED) \
            button = input::BUTTON_RELEASING; \
    }while(0)
// END CHANGE_BUTTON_STATE

    CHANGE_BUTTON_STATE(uistate.left_button_state);
    CHANGE_BUTTON_STATE(uistate.middle_button_state);
    CHANGE_BUTTON_STATE(uistate.right_button_state);
#undef CHANGE_BUTTON_STATE
}

void imgui::Quit() {
    SDL_DestroyTexture(gCanva);
}
