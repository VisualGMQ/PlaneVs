#include "engin/stage.hpp"
#include "engin/app.hpp"
#include "base/font.hpp"

class Font_Workable: public Stage {
 public:
    void Init() override {
        _font = Font::Create(Director::GetInstance()->GetRender(), "./test_resources/SimHei.ttf", 20, FONT_STYLE_NORMAL);
    }

    void EventHandle(SDL_Event&) override {}

    void Step() override {
        SDL_Renderer* render = Director::GetInstance()->GetRender();
        _font->Draw(render, 200, 50, {255, 0, 0, 255}, {1, 1}, "hello world");
        irect rect = {200, 100, 100, 100};
        _font->DrawBox(render, FONT_ALIGN_LEFT, rect, {0, 255, 0, 255}, {1, 1}, "hello world, this is a text in box");
        rect.x = 400;
        _font->DrawBox(render, FONT_ALIGN_CENTER, rect, {0, 255, 0, 255}, {1, 1}, "hello world, this is a text in box");
        rect.x = 600;
        _font->DrawBox(render, FONT_ALIGN_RIGHT, rect, {0, 255, 0, 255}, {1, 1}, "hello world, this is a text in box");
        _font->Draw(render, 200, 200, {255, 0, 0, 255}, {2, 2}, "hello world");
    }

    void Destroy() override {
    }

    virtual ~Font_Workable() = default;

 private:
    Font* _font = nullptr;
};


int main(int argc, char** argv) {
    Font_Workable workable;

    App app(&workable);
    app.SetTitle("Text Workable");

    app.Run();
    return 0;
}
