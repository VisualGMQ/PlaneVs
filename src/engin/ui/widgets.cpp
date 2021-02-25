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
        if (uistate.left_button_state == input::BUTTON_PRESSED ||
            (uistate.left_button_state == input::BUTTON_PRESSING && uistate.active_item == id)) {
            if (uistate.active_item != id) {
                SDL_StopTextInput();
            }
            uistate.active_item = id;
            state = PRESS_ON_WIDGETS;
        } else if (uistate.left_button_state == input::BUTTON_PRESSING && uistate.active_item != id) {
            state = DRAG_IN_WIDGETS;
        } else if (uistate.left_button_state == input::BUTTON_RELEASED) {
            state = RELEASE_ON_WIDGETS;
        } else if (uistate.left_button_state == input::BUTTON_RELEASING) {
            state = HOVE_ON_WIDGETS;
        }
    } else {
        if (uistate.left_button_state == input::BUTTON_PRESSING && uistate.active_item == id) {
            state = DRAG_OUT_WIDGETS;
        } else {
            state = OUTOF_WIDGETS;
        }
    }
    return state;
}

EventType imgui::Button(IDType id, Text* text, int x, int y, int w, int h, imgui::ButtonDrawCb draw_cb, void* param) {
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
        if (uistate.left_button_state == input::BUTTON_PRESSED) {
            is_checked = !is_checked;
            evt = EVENT_CHECKBOX_ALTER;
        }
    }
    if (draw_cb)
        draw_cb(id, evt, x, y, boarder_len, is_checked, param);
    return evt;
}

EventType imgui::Label(IDType id, int x, int y, Text* text, LabelDrawCb draw_cb, void* param) {
    EventType evt = EVENT_NONE;
    if (!text) {
        return evt;
    }
    isize size = text->GetSize();
    const State state = UpdateState(id, x, y, size.w, size.h);
    if (state == State::HOVE_ON_WIDGETS) {
        evt = EVENT_HOVER;
    }
    if (draw_cb) {
        draw_cb(id, evt, x, y, text, param);
    }
    return evt;
}

EventType imgui::Inputbox(IDType id, int x, int y, int w, int h, Text* text, InputboxDrawCb draw_cb, void* param) {
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
            // FIXM is this will cause memory leak?
            text->SetText((text->GetText()+uistate.input_text).c_str());
        }
        if (uistate.keycode == SDLK_BACKSPACE && !text->GetText().empty()) {
            string new_text = text->GetText();
            new_text.pop_back();
            text->SetText(new_text.c_str());
        }
    }
    if (draw_cb) {
        draw_cb(id, evt, x, y, w, h, text, param);
    }
    return evt;
}

void imgui::PanelStart(icolor color) {
    SDL_SetRenderTarget(gRender, gCanva);
    SDL_SetRenderDrawColor(gRender, color.r, color.g, color.b, color.a);
    SDL_RenderClear(gRender);
}

void imgui::PanelEnd(int x, int y, int w, int h) {
    Director::GetInstance()->SetRenderTargetToDefault();
    SDL_Rect src_rect = {0, 0, w, h},
             dst_rect = {x, y, w, h};
    SDL_RenderCopy(gRender, gCanva, &src_rect, &dst_rect);
}

// a small metaprogram to calculate areas of filedialog in compile time
template <int offset_x, int offset_y, int Width, int Height, int padding_w, int padding_h, int pt>
struct CalculateDialogRects {
    static constexpr irect title_area = {offset_x+padding_w, offset_y+padding_h, Width-2*padding_w, pt+2};
    static constexpr irect saveload_area = {offset_x+Width-padding_w-100, offset_y+Height-padding_h-pt-20, 100, pt+10};
    static constexpr irect cancel_area = {offset_x+padding_w, saveload_area.y, 100, pt+10};
    static constexpr irect path_area = {offset_x+padding_w, saveload_area.y-padding_h-pt-2, Width-padding_w*2, pt+2};
    static constexpr irect input_area = {offset_x+padding_w, path_area.y-padding_h-pt-2, Width-padding_w*2, pt+2};
    static constexpr irect main_area = {offset_x+padding_w, title_area.y+title_area.h+padding_h, Width-padding_w*2, input_area.y-title_area.y-title_area.h-padding_h*2};
};

constexpr int DialogWidth = 800;
constexpr int DialogHeight = 600;
constexpr int DialogOffsetX = (CanvaSize.w-DialogWidth)/2;
constexpr int DialogOffsetY = (CanvaSize.h-DialogHeight)/2;
constexpr int pt = 20;

using DialogRects = CalculateDialogRects<DialogOffsetX, DialogOffsetY, DialogWidth, DialogHeight, 10, 10, pt>;
constexpr irect title_area = DialogRects::title_area;
constexpr irect saveload_area = DialogRects::saveload_area;
constexpr irect cancel_area = DialogRects::cancel_area;
constexpr irect path_area = DialogRects::path_area;
constexpr irect input_area = DialogRects::input_area;
constexpr irect main_area = DialogRects::main_area;

constexpr icolor text_color = {255, 255, 255, 255};

void __filedialog_draw_file_item(const fs::path& path, Text* text, const icolor& color, const SDL_Rect& rect, const int padding, int button_len) {
    static Sprite* file_sprite = Sprite::Create("resources/file_ico.png"),
                  *dir_sprite = Sprite::Create("resources/dir_ico.png");
    const int ico_width = 40;
    SDL_SetRenderDrawColor(imgui::gRender, color.r, color.g, color.b, 255);
    SDL_RenderFillRect(imgui::gRender, &rect);
    text->Draw(rect.x+text->GetSize().w/2 + ico_width, text->GetSize().h/2+rect.y);
    if (fs::is_directory(path)) {
        dir_sprite->Show();
        dir_sprite->MoveTo(rect.x+rect.h/2, rect.y+ico_width/2);
        dir_sprite->Draw();
    } else {
        file_sprite->Show();
        file_sprite->MoveTo(rect.x+rect.h/2, rect.y+ico_width/2);
        file_sprite->Draw();
    }
}

Text* __query_text(vector<Text*>& texts, int idx, Font* font, string str) {
    if (idx >= texts.size()) {
        texts.push_back(nullptr);
    }
    if (texts.at(idx) == nullptr) {
        texts[idx] = Text::Create(font, str, text_color);
    } else {
        texts.at(idx)->SetText(str.c_str());
    }
    return texts.at(idx);
}

EventType imgui::FileDialog(string title, fs::path& p, imgui::FileDialogType type, Font* font) {
    static Text* path_text = Text::Create(font, p.string(), text_color),
                *cancel_text = Text::Create(font, "cancel", text_color),
                *save_load_text = Text::Create(font, type == FILEDIALOG_TYPE_OPEN?"open":"save", text_color),
                *title_text = Text::Create(font, title, text_color),
                *input_text = Text::Create(font, "", text_color);
    static string selected_filename_absolute = "";
    static vector<Text*> file_texts(20, nullptr);
    static int scrollbar_value = 0;

    if (!fs::exists(p) || !fs::is_directory(p)) {
        Logw("imgui::FileDialog", "path `%s` is invalid", p.string().c_str());
        p = fs::current_path();
    }

    // update dialog state, the id is ID_ANY due to it is singlton, we don't care it's ID
    UpdateState(ID_ANY, DialogOffsetX, DialogOffsetY, DialogWidth, DialogHeight);

    SDL_SetRenderDrawColor(gRender, 0, 0, 0, 150);
    SDL_Rect outline_rect = {(CanvaSize.w-DialogWidth)/2, (CanvaSize.h-DialogHeight)/2, DialogWidth, DialogHeight};
    SDL_RenderFillRect(gRender, &outline_rect);

    // title label
    SDL_Rect title_rect = IRect2SDL_Rect(title_area);
    SDL_SetRenderDrawColor(gRender, 0, 0, 0, 100);
    SDL_RenderFillRect(gRender, &title_rect);

    Label(ID_ANY, title_rect.x+title_rect.w/2-title_text->GetSize().w/2, title_rect.y, title_text);

    // path label
    SDL_Rect path_rect = IRect2SDL_Rect(path_area);
    SDL_SetRenderDrawColor(gRender, 0, 0, 0, 100);
    SDL_RenderFillRect(gRender, &path_rect);
    string path_str = "path: " + fs::absolute(p).string();
    path_text->SetText(path_str.c_str());
    Label(ID_ANY, path_rect.x, path_rect.y, path_text);

    // saveload button
    if (Button(ID_ANY, save_load_text, saveload_area.x, saveload_area.y, saveload_area.w, saveload_area.h) == EVENT_BUTTON_CLICK) {
        if (type == FILEDIALOG_TYPE_OPEN) {
            p = selected_filename_absolute;
            return EVENT_FILEDIALOG_OPEN;
        } else if (type == FILEDIALOG_TYPE_SAVE) {
            p.append(input_text->GetText());
            return EVENT_FILEDIALOG_SAVE;
        }
    }

    // cancel button
    if (Button(ID_ANY, cancel_text, cancel_area.x, cancel_area.y, cancel_area.w, cancel_area.h) == EVENT_BUTTON_CLICK) {
        return EVENT_FILEDIALOG_CANCEL;
    }

    // inputbox
    if (type == FileDialogType::FILEDIALOG_TYPE_SAVE) {
        Inputbox(ID_ANY, input_area.x, input_area.y, input_area.w, input_area.h, input_text);
    }

    // draw directories and files
    SDL_SetRenderTarget(gRender, gCanva);
    SDL_SetRenderDrawColor(gRender, 0, 100, 0, 50);
    SDL_RenderClear(gRender);

    const int button_len = 20;

    const int padding = 3;

    int i = 0;
    SDL_Rect rect = {main_area.x, main_area.y, main_area.w-button_len-5, pt+4};
    icolor item_color = {0, 120, 0, 255};
    SDL_Point mouse_pos = IVec2SDL_Point(input::Mouse::GetInstance()->GetPosition());
    // FIXME the codes in if area duplicated by code in for loop.Please eliminate the duplication
    if (p.root_directory() != p) {
        if (SDL_PointInRect(&mouse_pos, &rect)) {
            item_color.g = 150;
            if (input::Mouse::GetInstance()->GetLeftButtonState().IsPressed()) {
                p = p.parent_path();
                scrollbar_value = 0;
            }
        }
        __filedialog_draw_file_item("../", __query_text(file_texts, i, font, "../"), item_color, rect, padding, button_len);
        i++;
    }

    /* FIXME a bad way to draw file items
       I set Director::_canva.h = CanvaSize.h*10, to let all file items can draw.
       I want to change to draw items by their position, and then change back _canva.h = CanvaSize.h
     */
    int totle_h = 0;
    int offset_y = 0;
    SDL_Rect main_rect_src = IRect2SDL_Rect(main_area);
    for (auto& it : fs::directory_iterator(p)) {
        if (type == FileDialogType::FILEDIALOG_TYPE_SAVE && !fs::is_directory(it.path()))
            continue;
        string name = it.path().filename().string();
        item_color = {0, 120, 0, 255};
        rect.x = main_area.x;
        rect.y = main_area.y+(padding+pt+4)*i;
        rect.w = main_area.w-button_len-5;
        rect.h = pt+4;
        SDL_Point offseted_pos = mouse_pos;
        offseted_pos.y += scrollbar_value;
        std::error_code err_code;
        if (fs::equivalent(fs::path(selected_filename_absolute), it.path(), err_code)) {
            item_color.g = 175;
        }
        if (SDL_PointInRect(&mouse_pos, &main_rect_src) && SDL_PointInRect(&offseted_pos, &rect)) {
            if (!fs::equivalent(fs::path(selected_filename_absolute), it.path(), err_code)) {
                item_color.g = 150;
            }
            if (input::Mouse::GetInstance()->GetLeftButtonState().IsPressed()) {
                if (!fs::is_directory(it.path()) && type == FILEDIALOG_TYPE_OPEN) {
                    selected_filename_absolute = fs::absolute(it.path()).string();
                } else {
                    p = it.path();
                    scrollbar_value = 0;
                }
            }
        }
        __filedialog_draw_file_item(it.path(), __query_text(file_texts, i, font, name), item_color, rect, padding, button_len);
        totle_h = rect.y+rect.h - main_area.y;
        i++;
    }

    Director::GetInstance()->SetRenderTargetToDefault();

    SDL_Rect main_rect_dst = main_rect_src;
    main_rect_src.y += scrollbar_value;
    SDL_RenderCopy(gRender, gCanva, &main_rect_src, &main_rect_dst);

    int excess_height = totle_h-main_area.h < 0 ? 0 : totle_h-main_area.h;
    if (excess_height > 0) {
        Scrollbar(ID_ANY, imgui::ScrollbarDirection::SCROLLBAR_VERTICAL,
                main_area.x+main_area.w-button_len, main_area.y,
                main_area.h,
                0, excess_height,
                scrollbar_value,
                button_len);
    }
    return EVENT_NONE;
}
