#include "engin/stage.hpp"
#include "engin/app.hpp"

#include <iostream>
using namespace std;

class Input_Work: public Stage {
 public:
    void Init() override {
        _font = Font::Create(Director::GetInstance()->GetRender(), "resources/SimHei.ttf", 20, FONT_STYLE_BOLD);
        _text1 = Text::Create(_font, "Please press j or press mouse left button", {0, 200, 0, 255});
        _text2 = Text::Create(_font, "", {0, 200, 200, 255});
        _text3 = Text::Create(_font, "", {0, 200, 200, 255});
    }

    void EventHandle(SDL_Event&) override {}

    void Step() override {
        input::Button j_button = input::Keyboard::GetInstance()->Query(SDLK_j);
        if (j_button.IsPressed()) {
            _text2->SetText("j pressed");
        } else if (j_button.IsPressing()) {
            _text2->SetText("j pressing");
        } else if (j_button.IsReleased()) {
            _text2->SetText("j released");
        } else if (j_button.IsReleasing()) {
            _text2->SetText("j releasing");
        }
        input::Button left_button = input::Mouse::GetInstance()->GetLeftButtonState();
        if (left_button.IsPressed()) {
            _text3->SetText("left pressed");
        } else if (left_button.IsPressing()) {
            _text3->SetText("left pressing");
        } else if (left_button.IsReleased()) {
            _text3->SetText("left released");
        } else if (left_button.IsReleasing()) {
            _text3->SetText("left releasing");
        }
        _text1->Draw(400, 100);
        _text2->Draw(400, 200);
        _text3->Draw(400, 400);
    }

    void Destroy() override {
    }

    virtual ~Input_Work() = default;

 private:
    Font* _font = nullptr;
    Text* _text1 = nullptr;
    Text* _text2 = nullptr;
    Text* _text3 = nullptr;
};

int main(int argc, char** argv) {
    Input_Work workable;

    App app(&workable);
    app.SetTitle("Input Workable");

    app.Run();
    return 0;
}
