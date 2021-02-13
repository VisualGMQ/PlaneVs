#ifndef UI_HPP
#define UI_HPP
#include <vector>
#include <string>

#include <SDL.h>
#include <glm/glm.hpp>

#include "base/geo_math.hpp"
#include "engin/text.hpp"
using std::string;

namespace imgui {

using IDType = unsigned int;

enum {
    ID_NONE = 0
};

extern SDL_Renderer* gRender;
extern Text* gText;
extern SDL_Texture* gCanva;

/*
 * @brief a macro to generate random id
 * @warn don't use this twice in one line, because it used `__LINE__`
 */
// FIXME error ocurred
#define GenID() (int)(__LINE__)

enum ButtonState {
    BUTTON_PRESSED,
    BUTTON_RELEASED,
    BUTTON_PRESSING,
    BUTTON_RELEASING
};

struct UIState {
    IDType hot_item;
    IDType old_hot_item;
    IDType active_item;
    IDType old_active_item;

    glm::ivec2 mouse_position;
    ButtonState left_button_state;
    ButtonState right_button_state;
    ButtonState middle_button_state;
    int wheel;

    IDType kdb_item;
    SDL_Keycode keycode;
    Uint16 keymode;
};

extern UIState uistate;

enum EventType {
    // common events
    EVENT_NONE,
    EVENT_HOVER,
    EVENT_DRAG,
    EVENT_KEYDOWN,
    EVENT_KEYUP,
    EVENT_MOUSELEFT_PRESSING,
    EVENT_MOUSELEFT_RELEASED,

    // button events
    EVENT_BUTTON_CLICK,

    // scrollbar events
    EVENT_SCROLLBAR_DRAG,   // drag the button in scrollbar

    // checkbox events
    EVENT_CHECKBOX_ALTER,   // pressed checkbox and alternated state
};

void EventHandle(SDL_Event& event);
void Init(SDL_Renderer*);
void Prepare();
void Finish();
void Quit();

// widgets
// x, y, is left-top point of widgets

// button
using ButtonDrawCb = void(*)(IDType id, EventType, string, int, int, int, int, void*);

void DefaultButtonDrawCb(IDType id, EventType evt, string text, int x, int y, int w, int h, void* param);

EventType Button(IDType id, string text, int x, int y, int w, int h, ButtonDrawCb draw_cb = DefaultButtonDrawCb, void* param = nullptr);

enum ScrollbarDirection {
    SCROLLBAR_VERTICAL,
    SCROLLBAR_HORIZONTAL
};

// scrollbar
constexpr int ScrollbarWidth = 20;

using ScrollbarDrawCb = void(*)(IDType, ScrollbarDirection, EventType, int, int, int, int, int, int, int, void*);

void DefaultScrollbarDrawCb(IDType, ScrollbarDirection, EventType, int x, int y, int len, int min, int max, int value, int button_len, void*);

EventType Scrollbar(IDType id, ScrollbarDirection direction, int x, int y, int len, int min, int max, int& value, int button_len, ScrollbarDrawCb draw_cb = DefaultScrollbarDrawCb, void* param = nullptr);

// CheckBox
using CheckboxDrawCb = void(*)(IDType, EventType, int, int, int, bool, void*);

void DefaultCheckboxDrawCb(IDType id, EventType, int x, int y, int boarder_len, bool is_checked, void* param);

EventType Checkbox(IDType id, int x, int y, int boarder_len, bool& is_checked, CheckboxDrawCb draw_cb = DefaultCheckboxDrawCb, void* param = nullptr);
}; // namespace imgui

#endif
