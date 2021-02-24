#ifndef UI_HPP
#define UI_HPP
#include <vector>
#include <string>
#include <filesystem>

#include <SDL.h>
#include <glm/glm.hpp>

#include "base/geo_math.hpp"
#include "engin/text.hpp"
using std::string;
namespace fs = std::filesystem;

namespace imgui {

using IDType = unsigned int;
constexpr IDType ID_NONE = 0;

extern SDL_Renderer* gRender;
extern SDL_Texture* gCanva;
/*
 * @brief a macro to generate random id
 * @warn don't use this twice in one line, because it used `__LINE__` to generate id
 */
#define ID_ANY (*(int*)(__FILE__)+__LINE__)

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

    // for SDL_TEXTINPUT
    string input_text;
    bool inputted;
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

    // filedialog events
    FILEDIALOG_OPEN,
    FILEDIALOG_SAVE,
    FILEDIALOG_CANCEL,
};

void EventHandle(SDL_Event& event);
void Init(SDL_Renderer*);
void ClearFocus();
void Prepare();
void Finish();
void Quit();

// widgets
// x, y, is left-top point of widgets

// Button
using ButtonDrawCb = void(*)(IDType id, EventType, Text*, int, int, int, int, void*);

void DefaultButtonDrawCb(IDType id, EventType evt, Text* text, int x, int y, int w, int h, void* param);

EventType Button(IDType id, Text*, int x, int y, int w, int h, ButtonDrawCb draw_cb = DefaultButtonDrawCb, void* param = nullptr);

enum ScrollbarDirection {
    SCROLLBAR_VERTICAL,
    SCROLLBAR_HORIZONTAL
};

// Scrollbar
constexpr int ScrollbarWidth = 20;

using ScrollbarDrawCb = void(*)(IDType, ScrollbarDirection, EventType, int, int, int, int, int, int, int, void*);
void DefaultScrollbarDrawCb(IDType, ScrollbarDirection, EventType, int x, int y, int len, int min, int max, int value, int button_len, void*);
EventType Scrollbar(IDType id, ScrollbarDirection direction, int x, int y, int len, int min, int max, int& value, int button_len, ScrollbarDrawCb draw_cb = DefaultScrollbarDrawCb, void* param = nullptr);

// CheckBox
using CheckboxDrawCb = void(*)(IDType, EventType, int, int, int, bool, void*);
void DefaultCheckboxDrawCb(IDType id, EventType, int x, int y, int boarder_len, bool is_checked, void* param);
EventType Checkbox(IDType id, int x, int y, int boarder_len, bool& is_checked, CheckboxDrawCb draw_cb = DefaultCheckboxDrawCb, void* param = nullptr);

// Label
using LabelDrawCb = void(*)(IDType, EventType, int, int, Text*, void*);
void DefaultLabelDrawCb(IDType, EventType, int x, int y, Text*, void*);
EventType Label(IDType id, int x, int y, Text*, LabelDrawCb draw_cb = DefaultLabelDrawCb, void* param = nullptr);

// InputBox
using InputboxDrawCb = void(*)(IDType, EventType, int, int, int, int, Text*, void*);
void DefaultInputboxDrawCb(IDType, EventType, int x, int y, int w, int h, Text*, void*);
EventType Inputbox(IDType id, int x, int y, int w, int h, Text* text, InputboxDrawCb draw_cb = DefaultInputboxDrawCb, void* param = nullptr);

// FileDialog

enum FileDialogType {
    FILEDIALOG_TYPE_OPEN,
    FILEDIALOG_TYPE_SAVE
};

// filedialog is a singlton, it don't have id
EventType FileDialog(string title, fs::path&, FileDialogType type, Font*);

}; // namespace imgui

#endif
