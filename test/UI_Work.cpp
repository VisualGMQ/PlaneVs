#include "engin/stage.hpp"
#include "engin/app.hpp"
#include "engin/ui/ui.hpp"

enum {
    ID_BUTTON1 = 1,
    ID_SCROLLBAR_VERT,
    ID_SCROLLBAR_HORI,
    ID_CHECKBOX,
    ID_LABEL1,
    ID_LABEL2,
    ID_INPUTBOX1,
    ID_INPUTBOX2,
};

class UI_Work: public Stage {
 public:
    void Init() override {
        SetLogLevel(LOG_ALL);
        _font = Font::Create(Director::GetInstance()->GetRender(), "test_resources/SimHei.ttf", 20, FONT_STYLE_BOLD);
        SDL_StartTextInput();
    }

    void EventHandle(SDL_Event&) override {}

    void Step() override {
        if (imgui::Button(ID_BUTTON1, "click me", 100, 100, 64, 40) == imgui::EVENT_BUTTON_CLICK) {
            Logi("UI_Work::Step", "button1 clicked");
        }
        imgui::Scrollbar(ID_SCROLLBAR_HORI, imgui::SCROLLBAR_HORIZONTAL, 50, 300, 200, 0, 100, _scroll_value, 20);
        imgui::Scrollbar(ID_SCROLLBAR_VERT, imgui::SCROLLBAR_VERTICAL, 50, 350, 300, 0, 100, _scroll_value, 10);
        imgui::Label(ID_LABEL1, 250, 300, {0, 0, 0, 255}, _font, std::to_string(_scroll_value));
        imgui::Checkbox(ID_CHECKBOX, 200, 200, 50, _is_checked);
        if (_is_checked) {
            imgui::Label(ID_LABEL2, 260, 200, {200, 0, 0, 255}, _font, "按下了");
        } else {
            imgui::Label(ID_LABEL2, 260, 200, {0, 200, 0, 255}, _font, "没按下");
        }
        imgui::Inputbox(ID_INPUTBOX1, 400, 400, 200, 50, _font, _str1);
        imgui::Inputbox(ID_INPUTBOX2, 400, 600, 200, 50, _font, _str2);
    }

    void Destroy() override {
        SDL_StopTextInput();
    }

    virtual ~UI_Work() = default;

 private:
    int _scroll_value = 0;
    bool _is_checked = false;
    Font* _font = nullptr;
    string _str1;
    string _str2;
};

int main(int argc, char** argv) {
    UI_Work workable;

    App app(&workable);
    app.SetTitle("UI Workable");

    app.Run();
    return 0;
}
