#include "engin/stage.hpp"
#include "engin/app.hpp"
#include "engin/ui/ui.hpp"

class UI_Work: public Stage {
 public:
    void Init() override {
        SetLogLevel(LOG_ALL);
        _font = Font::Create(Director::GetInstance()->GetRender(), "resources/SimHei.ttf", 20, FONT_STYLE_BOLD);
        SDL_StartTextInput();
        _button_text = Text::Create(_font, "", {255, 255, 255, 255});
        _label1_text = Text::Create(_font, "", {255, 255, 255, 255});
        _label2_text = Text::Create(_font, "", {255, 255, 255, 255});
        _inputbox1_text = Text::Create(_font, "", {255, 255, 255, 255});
        _inputbox2_text = Text::Create(_font, "", {255, 255, 255, 255});
        _path = fs::current_path();
    }

    void EventHandle(SDL_Event&) override {}

    void Step() override {
        _button_text->SetText("show save dialog");
        if (imgui::Button(ID_ANY, _button_text, 100, 100, 64, 40) == imgui::EVENT_BUTTON_CLICK) {
            _show_filedialog = true;
        }
        imgui::Scrollbar(ID_ANY, imgui::SCROLLBAR_HORIZONTAL, 50, 300, 200, 0, 100, _scroll_value, 20);
        imgui::Scrollbar(ID_ANY, imgui::SCROLLBAR_VERTICAL, 50, 350, 300, 0, 100, _scroll_value, 10);
        _label1_text->SetText(to_string(_scroll_value).c_str());
        _label1_text->SetColor(0, 0, 0, 255);
        imgui::Label(ID_ANY, 250, 300, _label1_text);
        imgui::Checkbox(ID_ANY, 200, 200, 50, _is_checked);
        if (_is_checked) {
            _label2_text->SetText("pressed");
            _label2_text->SetColor(200, 0, 0, 255);
            imgui::Label(ID_ANY, 260, 200, _label2_text);
        } else {
            _label2_text->SetText("not pressed");
        _label1_text->SetColor(0, 200, 0, 255);
            imgui::Label(ID_ANY, 260, 200, _label2_text);
        }
        imgui::Inputbox(ID_ANY, 400, 400, 200, 50, _inputbox1_text);
        imgui::Inputbox(ID_ANY, 400, 600, 200, 50, _inputbox2_text);
        if (_show_filedialog) {
            auto evt = FileDialog("Save Test", _path, imgui::FILEDIALOG_TYPE_OPEN, _font);
            if (evt != imgui::EVENT_NONE) {
                _show_filedialog = false;
                if (evt == imgui::EVENT_FILEDIALOG_OPEN) {
                        Logi("UI_Work::Step()", "open file: %s", _path.string().c_str());
                    } else if (evt == imgui::EVENT_FILEDIALOG_SAVE) {
                        Logi("UI_Work::Step()", "save file: %s", _path.string().c_str());
                    } else if (evt == imgui::EVENT_FILEDIALOG_CANCEL) {
                    }
                }
        }
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
    Text* _button_text = nullptr;
    Text* _label1_text = nullptr;
    Text* _label2_text = nullptr;
    Text* _inputbox1_text = nullptr;
    Text* _inputbox2_text = nullptr;
    bool _show_filedialog = false;
    fs::path _path;
};

int main(int argc, char** argv) {
    UI_Work workable;

    App app(&workable);
    app.SetTitle("UI Workable");

    app.Run();
    return 0;
}
