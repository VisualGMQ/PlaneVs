#include "engin/ui/ui.hpp"
using imgui::IDType;
using imgui::uistate;
using imgui::EventType;

// some state
enum State {
    PRESS_ON_WIDGETS = 0,   // left button pressed when in widgets area
    RELEASE_ON_WIDGETS,     // released left button in widgets area
    HOVE_ON_WIDGETS,        // mouse hove on widgets area but not pressed
    OUTOF_WIDGETS,          // mouse point don't in widgets
    DRAG_OUT_WIDGETS,       // left button pressed in widgets and leave the widgets area without release
    DRAG_IN_WIDGETS,        // left button pressed out of widgets and go into widgets area without release
};

const State UpdateState(IDType id, int x, int y, int w, int h) {
    State state = OUTOF_WIDGETS;
    SDL_Rect rect = {x, y, w, h};
    SDL_Point pos = IVec2SDL_Point(uistate.mouse_position);
    if (SDL_PointInRect(&pos, &rect)) {
        uistate.hot_item = id;
        if (uistate.left_button_state == imgui::BUTTON_PRESSED ||
            (uistate.left_button_state == imgui::BUTTON_PRESSING && uistate.active_item == id)) {
            if (uistate.active_item != id) {
                SDL_StopTextInput();
            }
            uistate.active_item = id;
            state = PRESS_ON_WIDGETS;
        } else if (uistate.left_button_state == imgui::BUTTON_PRESSING && uistate.active_item != id) {
            state = DRAG_IN_WIDGETS;
        } else if (uistate.left_button_state == imgui::BUTTON_RELEASED) {
            state = RELEASE_ON_WIDGETS;
        } else if (uistate.left_button_state == imgui::BUTTON_RELEASING) {
            state = HOVE_ON_WIDGETS;
        }
    } else {
        if (uistate.left_button_state == imgui::BUTTON_PRESSING && uistate.active_item == id) {
            state = DRAG_OUT_WIDGETS;
        } else {
            state = OUTOF_WIDGETS;
        }
    }
    return state;
}

EventType imgui::Button(IDType id, string text, int x, int y, int w, int h, imgui::ButtonDrawCb draw_cb, void* param) {
    EventType evt = imgui::EVENT_NONE;
    const State state = UpdateState(id, x, y, w, h);
    if (state == HOVE_ON_WIDGETS || state == DRAG_IN_WIDGETS) {
        evt = EVENT_HOVER;
    }
    if (state == PRESS_ON_WIDGETS || state == DRAG_OUT_WIDGETS) {
        evt = EVENT_MOUSELEFT_PRESSING;
    }
    if (state == RELEASE_ON_WIDGETS) {
        if (uistate.active_item == id) {
            evt = EVENT_BUTTON_CLICK;
        } else {
            evt = EVENT_HOVER;
        }
    }
    if (!draw_cb)
        draw_cb = imgui::DefaultButtonDrawCb;
    draw_cb(id, evt, text, x, y, w, h, param);
    return evt;
}

EventType imgui::Scrollbar(IDType id, imgui::ScrollbarDirection direction, int x, int y, int len, int min, int max, int& value, int button_len, imgui::ScrollbarDrawCb draw_cb, void* param) {
    imgui::EventType evt = EVENT_NONE;
    const int actual_len = len - button_len;
    Clamp(min, max, value);
    State state;
    if (direction == SCROLLBAR_VERTICAL) {
        state = UpdateState(id, x, y, ScrollbarWidth, len);
    } else {
        state = UpdateState(id, x, y, len, ScrollbarWidth);
    }
    if (state == State::HOVE_ON_WIDGETS || state == State::DRAG_IN_WIDGETS) {
        evt = imgui::EVENT_HOVER;
    }
    if (state == State::DRAG_OUT_WIDGETS || state == State::PRESS_ON_WIDGETS) {
        evt = imgui::EVENT_SCROLLBAR_DRAG;
        if (direction == SCROLLBAR_VERTICAL) {
            int new_y = Clamp(y+button_len/2, y+len-button_len/2, uistate.mouse_position.y);
            value = (new_y-y-button_len/2)/static_cast<float>(actual_len)*(max-min);
        } else {
            int new_x = Clamp(x+button_len/2, x+len-button_len/2, uistate.mouse_position.x);
            value = (new_x-x-button_len/2)/static_cast<float>(actual_len)*(max-min);
        }
    }
    if (draw_cb)
        draw_cb(id, direction, evt, x, y, len, min, max, value, button_len, param);
    return evt;
}

EventType imgui::Checkbox(IDType id, int x, int y, int boarder_len, bool& is_checked, CheckboxDrawCb draw_cb, void* param) {
    State state = UpdateState(id, x, y, boarder_len, boarder_len);
    EventType evt = EVENT_NONE;
    if (state == State::HOVE_ON_WIDGETS) {
        evt = EVENT_HOVER;
    }
    if (state == State::PRESS_ON_WIDGETS) {
        uistate.active_item = id;
        if (uistate.left_button_state == BUTTON_PRESSED) {
            is_checked = !is_checked;
            evt = EVENT_CHECKBOX_ALTER;
        }
    }
    if (draw_cb)
        draw_cb(id, evt, x, y, boarder_len, is_checked, param);
    return evt;
}

EventType imgui::Label(IDType id, int x, int y, const icolor& color, Font* font, const string& text, LabelDrawCb draw_cb, void* param) {
    EventType evt = EVENT_NONE;
    if (!font) {
        return evt;
    }
    isize size = font->GetSizeByText(text);
    const State state = UpdateState(id, x, y, size.w, size.h);
    if (state == State::HOVE_ON_WIDGETS) {
        evt = EVENT_HOVER;
    }
    if (draw_cb) {
        draw_cb(id, evt, x, y, color, font, text, param);
    }
    return evt;
}

EventType imgui::Inputbox(IDType id, int x, int y, int w, int h, Font* font, string& text, InputboxDrawCb draw_cb, void* param) {
    const State state = UpdateState(id, x, y, w, h);
    EventType evt = EVENT_NONE;
    if (state == State::HOVE_ON_WIDGETS) {
        evt = EVENT_HOVER;
    }
    if (state == State::PRESS_ON_WIDGETS) {
        if (uistate.old_active_item != id && !SDL_IsTextInputActive()) {
            SDL_StartTextInput();
        }
    }
    if (uistate.active_item == id) {
        if (uistate.inputted) {
            text += uistate.input_text;
        }
        if (uistate.keycode == SDLK_BACKSPACE && !text.empty()) {
            text.pop_back();
        }
    }
    if (draw_cb) {
        draw_cb(id, evt, x, y, w, h, font, text, param);
    }
    return evt;
}
