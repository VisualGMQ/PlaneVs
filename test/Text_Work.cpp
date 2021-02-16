#include "engin/stage.hpp"
#include "engin/app.hpp"
#include "engin/text.hpp"

class Text_Workable: public Stage {
 public:
    void Init() override {
        _font = Font::Create(Director::GetInstance()->GetRender(), "./test_resources/SimHei.ttf", 20, FONT_STYLE_NORMAL);
        _text1 = Text::Create(_font, "Hello World", {255, 255, 0, 255});
        _text2 = Text::Create(_font, "你好世界", {0, 255, 255, 255});
    }

    void EventHandle(SDL_Event&) override {}

    void Step() override {
        auto render = Director::GetInstance()->GetRender();
        _text2->Draw(100, 100);
        _text1->Draw(100, 300);
    }

    void Destroy() override {
    }

    virtual ~Text_Workable() = default;

 private:
    Font* _font = nullptr;
    Text* _text1 = nullptr;
    Text* _text2 = nullptr;
};


int main(int argc, char** argv) {
    Text_Workable workable;

    App app(&workable);
    app.SetTitle("Text Workable");

    app.Run();
    return 0;
}
